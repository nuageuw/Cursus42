import datetime, jwt
import os
import logging

from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.core.exceptions import ObjectDoesNotExist
from django.conf import settings

from rest_framework.generics import GenericAPIView
from rest_framework import status
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response

from ..models import MyUser, Team
from .secure import is_valid_username


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def id(request):
    try:
        user = request.user
        user_data = {
            'id': user.id,
            'name': user.username,
            'userImg': user.image_link,
        }
        return JsonResponse({'user_data': user_data})
    except Exception as e:
        logging.error(str(e))
        return JsonResponse({'errors': "Backend error occured, if the problem persists, please contact the administrator"})

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def profil(request):
    try:
        user = request.user
        user_data = {
            'id': user.id,
            'username': user.username,
            'email': user.email,
            'score': user.score,
            'games_played': user.games_played,
            'games_lost': user.games_lost,
            'games_won': user.games_won,
            'img': user.image_link,
            'friends': [friend.username for friend in user.friends.all()],
            'tournaments': []
        }

        teams = Team.objects.filter(players=user)
        tournaments_set = set()

        for team in teams:
            round_obj = team.round_number
            tournament = round_obj.tournament

            if tournament not in tournaments_set:
                tournaments_set.add(tournament)
                tournament_info = {
                    'name': tournament.name,
                    'rounds': [],
                    'date': tournament.start.strftime('%d-%m-%Y'),
                }
                rounds = tournament.matches.all()
                for r in rounds:
                    round_info = {
                        'number': r.round_number,
                        'teams': []
                    }
                    round_teams = r.teams.all()
                    for round_team in round_teams:
                        if round_team.winner:
                            winner = round_team.winner.id
                        else:
                            winner = False
                        players = list(round_team.players.values())
                        team_info = {
                            'name': round_team.name,
                            'members':[{'id' : player['id'] ,
                                        'name' : player['username'],
                                } for player in players],
                            'winner' : winner,
                        }
                        round_info['teams'].append(team_info)
                    tournament_info['rounds'].append(round_info)

                user_data['tournaments'].append(tournament_info)
        return JsonResponse({'user_data': user_data})
    except Exception as e:
        logging.error(str(e))
        return JsonResponse({'errors': "Backend error occured, if the problem persists, please contact the administrator"})

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def search_players(request):
    try:
        query = request.GET.get('query', '')
        if query:
            users = MyUser.objects.filter(username__istartswith=query)[:6]
        else:
            users = None
        current_user_id = request.user.id
        users_data = [{'id' : user.id ,
            'name' : user.username,
            'is_registered': user.id == current_user_id
        } for user in users]
        return JsonResponse({'users_data' : users_data})
    except Exception as e:
        logging.error(str(e))
        return JsonResponse({'errors': "Backend error occured, if the problem persists, please contact the administrator"})


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def user_info(request, user_id):
    user_is_co = request.user
    try:
        user = get_object_or_404(MyUser, id=user_id)
        if user_is_co.is_friend(user):
            friendship_status = 'Remove Friend'
        elif user_is_co.has_sent_friend_request_to(user):
            friendship_status = 'Demand sent'
        elif user_is_co.has_received_friend_request_from(user):
            friendship_status = 'Accept or refuse'
        else:
            friendship_status = 'Add Friend'

        user_data = {
            'id': user.id,
            'username': user.username,
            'email': user.email,
            'score': user.score,
            'games_played': user.games_played,
            'games_lost': user.games_lost,
            'games_won': user.games_won,
            'img': user.image_link,
            'friends': [friend.username for friend in user.friends.all()],
            'tournaments': [],
            'is_registered' : {
                'id': user.id,
                'status' :  friendship_status,
            }
        }   

        teams = Team.objects.filter(players=user)
        tournaments_set = set()
        
        for team in teams:
            round_obj = team.round_number
            tournament = round_obj.tournament

            if tournament not in tournaments_set:
                tournaments_set.add(tournament)
                tournament_info = {
                    'name': tournament.name,
                    'rounds': []
                }
                rounds = tournament.matches.all()
                for r in rounds:
                    round_info = {
                        'number': r.round_number,
                        'teams': []
                    }
                    round_teams = r.teams.all()
                    for round_team in round_teams:
                        if round_team.winner:
                            winner = round_team.winner.id
                        else:
                            winner = False
                        players = list(round_team.players.values())
                        for p in players:
                            print(p['id'])
                        team_info = {
                            'name': round_team.name,
                            'members':[{'id' : player['id'] ,
                                        'name' : player['username'],
                                } for player in players],
                            'winner' : winner,
                        }
                        round_info['teams'].append(team_info)
                    tournament_info['rounds'].append(round_info)
                print(tournaments_set)

                user_data['tournaments'].append(tournament_info)
        return JsonResponse({'user_data': user_data})
    except ObjectDoesNotExist:
        return JsonResponse({'errors': "User does not exist"})


@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def modify(request):
    user = request.user
    if request.method == "POST":
        try:
            username = request.POST.get('username')
            email = request.POST.get('email')
            image = request.FILES.get('img')

            if username:
                if not is_valid_username(username):
                    return JsonResponse({'errors': "Invalid username"})
                if user.is_oauth_user:
                    if username != user.username:
                        return JsonResponse({'errors': "Username cannot be modified for OAuth users"})
                else:
                    if username != user.username and MyUser.objects.filter(username=username).exists():
                        return JsonResponse({'errors': "Username already exists"})
                    user.username = username

            if email:
                if user.is_oauth_user:
                    if email != user.email:
                        return JsonResponse({'errors': "Email cannot be modified for OAuth users"})
                else:
                    if email != user.email and MyUser.objects.filter(email=email).exists():
                        return JsonResponse({'errors': "Email already exists"})
                    user.email = email

            if image:
                file_extension = os.path.splitext(image.name)[1]
                if file_extension.lower() not in ['.jpg', '.jpeg', '.png', '.gif']:
                    return Response({'errors': 'Invalid file format'}, status=status.HTTP_400_BAD_REQUEST)
                user.image_link = handle_uploaded_image(image) 

            user.save()
            return JsonResponse({'messages': 'Modifications successful'})
        except Exception as e:
            logging.error(str(e))
            return JsonResponse({'errors': "Backend error occured, if the problem persists, please contact the administrator"})
    else:
        form_data = { 
            'username': user.username,
            'email': user.email,
            'image_link': user.image_link,
            'two_factor_enabled': user.two_factor_enabled,
            'is_oauth_user': user.is_oauth_user,
        }
        return JsonResponse({'form_data': form_data})

def handle_uploaded_image(image_file):
    random_string = str(datetime.datetime.now().timestamp())
    img_name = f"{random_string + image_file.name[-4:]}"
    file_path = os.path.join(settings.MEDIA_ROOT, img_name)

    with open(file_path, 'wb') as f:
        for chunk in image_file.chunks():
            f.write(chunk)

    return os.path.join(settings.MEDIA_URL, img_name)\
    
class UpdatePictureView(GenericAPIView):
    def post(self, request):
        try:
            token = request.headers.get('Authorization')
            if token is None:
                return Response({'error': 'Unauthorized'}, status=status.HTTP_401_UNAUTHORIZED)

            token = token.split(' ')[1]
            payload = jwt.decode(token, settings.SECRET_KEY, algorithms=['HS256'])
            user = MyUser.objects.get(id=payload['user_id'])

            if 'image_link' in request.data:
                image = request.data['image_link']
                user.image_link = image
            elif 'file' in request.FILES:
                uploaded_file = request.FILES['file']
                file_extension = os.path.splitext(uploaded_file.name)[1]
                if file_extension.lower() not in ['.jpg', '.jpeg', '.png', '.gif']:
                    return Response({'error': 'Invalid file format'}, status=status.HTTP_400_BAD_REQUEST)
                user.image_link = handle_uploaded_image(uploaded_file)
            else:
                return Response({'error': 'No image provided'}, status=status.HTTP_400_BAD_REQUEST)

            user.first_connection = False
            user.save()

            return Response({'message': 'Image updated successfully', 'image_url': user.image_link}, status=status.HTTP_200_OK)
        except Exception as e:
            logging.error(str(e))
            return Response({'error': 'Backend error occured, if the problem persists, please contact the administrator'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)