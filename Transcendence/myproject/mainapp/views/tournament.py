import json

from django.http import JsonResponse
from django.shortcuts import get_object_or_404
from django.core.exceptions import ObjectDoesNotExist

from rest_framework.permissions import IsAuthenticated
from rest_framework.decorators import api_view, permission_classes
from django.contrib.auth.hashers import check_password

from ..models import Tournament, Round, MyUser, Team
from .secure import is_valid_username


@api_view(['GET'])
@permission_classes([IsAuthenticated])
def pong(request, teams_id):
    try:
        teams = get_object_or_404(Team, id=teams_id)
        tournament = Tournament.objects.filter(matches__teams=teams).values_list('id', flat=True)
        teams_data = {
            'id': teams.id,
            'name': teams.name,
            'players_name': [player.nickname for player in teams.players.all()],
            'players_id' : [player.id for player in teams.players.all()],
            'tournament' : tournament[0],
            }
        return JsonResponse({'teams_data' : teams_data})
    except Exception as e:
        return JsonResponse({'error': 'Not found'}, status=404)

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def check_pw(request, teams_id):
    try:
        team = get_object_or_404(Team, id=teams_id)
        users = [player.id for player in team.players.all() if player.id != request.user.id]
        user_id = users[0]
        user = MyUser.objects.get(id=user_id)
        if request.method == 'POST':
            
            mdp = request.POST.get('mdp')
            if not user.is_oauth_user:
                if check_password(mdp, user.password): 
                    return JsonResponse({'success' : True, 'message' : 'Good Password'})
                else:
                    return JsonResponse({'success' : False, 'message' : 'Wrong Password'})
            else:
                return JsonResponse({'success' : True, 'message' : 'This user is an oauth user'})
        else:
            return JsonResponse({'message' : 'coucou :)'})
    except ObjectDoesNotExist:
         return JsonResponse({'error' : 'backend error'})

        

def update_player_scores(request):
    if request.method == 'POST':
        try:
            data = json.loads(request.body)
            winner_id = data.get('winner')
            loser_id = data.get('loser')
            teams_id = data.get('teams')
            scorewin = data.get('score1')
            scorelose = data.get('score2')

            winner = MyUser.objects.get(id=winner_id)
            loser = MyUser.objects.get(id=loser_id)
            teams = Team.objects.get(id=teams_id)

            winner.score += 10
            winner.games_played += 1
            winner.games_won += 1
            if (loser.score != 0):
                loser.score -= 5
            loser.games_played += 1
            loser.games_lost += 1 

            teams.winner = winner
            teams.score1 = scorewin
            teams.score2 = scorelose
            winner.save()
            loser.save()
            teams.save()
            return JsonResponse({'message': 'Scores updated successfully'})
        except ObjectDoesNotExist:
            return JsonResponse({'error': 'Player not found'}, status=404)
    else:
        return JsonResponse({'error': 'Invalid request'}, status=400)

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def tournament(request):
    try:
        tournaments = Tournament.objects.filter(finish=False)
        tournaments_data = []
        is_already_engaged = False
        for tournament in tournaments:
            is_registered = tournament.players.filter(id=request.user.id).exists()
            if (is_registered and tournament.players.count != 0):
                is_already_engaged = True
            print(is_registered)
            slots = tournament.numb_p - tournament.players.count()
            date = tournament.start.strftime('%Y-%m-%d %H:%M')
            tournaments_data.append({
                'id': tournament.id,
                'name': tournament.name,
                'start': date,
                'numb_p': tournament.numb_p,
                'slots': slots,
                'full': tournament.full,
                'is_registered': is_registered 
            })
        return JsonResponse({'tournaments_data': tournaments_data, 'is_already_engaged' : is_already_engaged})
    except Exception as e:
        return JsonResponse({'error': 'Error'}, status=404)

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def create_tour(request):
    if request.method == "POST":
        try:
            name = request.POST.get('name')
            start = request.POST.get('start')
            numb_p = int(request.POST.get('num'))
            if (name):
                if not is_valid_username(name):
                    return JsonResponse({'errors': 'Invalid name'}) 
            if (numb_p != 2 and numb_p != 4 and numb_p != 8):
                return JsonResponse({'errors': 'Wrong number of players'})
            try:
                already_exist = Tournament.objects.get(name=name)
                return JsonResponse({'errors': 'Tournament already exist with this name'})
            except ObjectDoesNotExist:
                pass
            tournament = Tournament.objects.create(
                    name=name,
                    start=start,
                    numb_p=numb_p
            )
            return JsonResponse({'message': 'Tournament created successfully!'})
        except Exception as e:
            return JsonResponse({'error': 'Server Error try again'}, status=404)
    else:
        form_data = {
                    'fields': {
                        'name': { 
                            'label' : 'Name',
                            'type' : 'text' },
                        'num':  {
                            'label' : 'Number of Participants',
                            'type' : 'number' }
                    }
                }
        return JsonResponse({'form_data': form_data})

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def tour_details(request, tournament_id):
    try:
        user = request.user
        tournament = get_object_or_404(Tournament, id=tournament_id)
        tournament_data = [{'name': tournament.name, 'start': tournament.start, 'numb_p': tournament.numb_p, 'full': tournament.full}]
        count = [{'count' : tournament.players.count()}]
        if request.method == "POST":
            nickname = request.POST.get('player')
            if not is_valid_username(nickname):
                return JsonResponse({'success': False, 'message': "Invalid username"}, status=400)
            if tournament.players.filter(id=user.id).exists():
                return JsonResponse({'success': False, 'message': "Player already signed up"}, status=400)
            if tournament.full:
                return JsonResponse({'success': False, 'message' : "Tournament full"}, status=400)
            user.nickname = nickname
            user.save()
            tournament.players.add(user)

            if tournament.players.count() == tournament.numb_p :
                tournament.full = True
                tournament.save()
            data = {
                'success': True,
                'message': 'Registered!',

            }
            return JsonResponse(data)
        else:
            form_data = {
                'player': {
                    'label' : 'Name of palyer',
                    'type' : 'text' },
                    }
            return JsonResponse({'form_data': form_data, 'tournament_data':tournament_data, 'count' : count})
    except Exception as e:
        return JsonResponse({'error': 'Error 404'}, status=404)

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def teams_play(request, tournament_id):
    try:
        tournament = get_object_or_404(Tournament, id=tournament_id)
        last_round = tournament.matches.latest('round_number')
        teams_in_last_round = last_round.teams.filter(winner__isnull=True)
        teams_data = [{
            'name': team.name,
            'id' : team.id,
            'players_name': [player.username for player in team.players.all()],
            'players_id' : [player.id for player in team.players.all()],
            'is_co' : any(player.id == request.user.id for player in team.players.all()),
        } for team in teams_in_last_round]
        if not teams_data:
            round_finish(tournament, last_round)
        tournament_data = {
            'name': tournament.name,
            'start': tournament.start.strftime('%Y-%m-%d %H:%M:%S'),
            'teams': teams_data,
            'round' : str(last_round.round_number),
            'user_id' : request.user.id,
            'finish' : tournament.finish,
        }
        try:
            all_rounds = tournament.matches.all()
            all_data_tour = [] 
            for round in all_rounds:
                all_data_tour.append({
                    'round': round.round_number,
                    'teams': [{
                        'name': team.name,
                        'players_name': [player.nickname for player in team.players.all()],
                        'players_id' : [player.id for player in team.players.all()],
                        'scorewin': team.score1,
                        'scorelose': team.score2,
                        'winner': team.winner.nickname if team.winner else None,
                    } for team in round.teams.all()]
                })
        except:
            pass
        return JsonResponse({'tournament_data':tournament_data, 'all_data_tour': all_data_tour})
    except ObjectDoesNotExist:
        return JsonResponse({'error': 'Aucun tournoi trouvé'}, status=404)


def round_finish(tournament, last_round):
    try:
        print(last_round.teams.count())
        if last_round.teams.count() > 1:
            all_players = set(tournament.players.all())
            winners = set()
            for team in last_round.teams.all():
                if team.winner:
                    winners.add(team.winner)
            not_winners = all_players - winners
            for p in not_winners:
                tournament.players.remove(p)
            round_number = last_round.round_number + 1
            Round.objects.create(name="Round", tournament=tournament, round_number=round_number)
            tournament.save()
        else:
            for p in tournament.players.all():
                tournament.players.remove(p)
            tournament.finish = True
            tournament.save()
    except:
        pass



        
