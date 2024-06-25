from django.http import JsonResponse
from ..models import Tournament, Round, MyUser, Team, FriendRequest, Friendship
from django.shortcuts import get_object_or_404
from django.core.exceptions import ObjectDoesNotExist
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
import math, json, datetime, jwt

@api_view(['POST'])
@permission_classes([IsAuthenticated])
def send_friend_request(request, user_id):
    try:
        user = MyUser.objects.get(id=user_id)
        if user == request.user:
            return JsonResponse({'success': False, 'error': "You can't add yourself as a friend"})
        friend_request, created = FriendRequest.objects.get_or_create(from_user=request.user, to_user=user)
        if created:
            return JsonResponse({'success': True, 'message': "Request sent!"})
        else:
            return JsonResponse({'success': False, 'error': "This request as already been sent"})
    except MyUser.DoesNotExist:
        return JsonResponse({'success': False, 'error': "User not found"})

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def accept_friend_request(request, request_id):
    try:
        friend = MyUser.objects.get(id=request_id)
        friend_request = FriendRequest.objects.get(from_user=friend, to_user=request.user)
        if friend_request:
            request.user.add_friend(friend_request.from_user)
            friend_request.delete()
            return JsonResponse({'success': True, 'message': "Request accepted"})
        else:
            return JsonResponse({'success': False, 'message': "Request rejected"})
    except MyUser.DoesNotExist:
        return JsonResponse({'success': False, 'error': "Request not found"})

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def reject_friend_request(request, request_id):
    try:
        friend = MyUser.objects.get(id=request_id)
        friend_request = FriendRequest.objects.get(from_user=friend, to_user=request.user)
        if friend_request:
            friend_request.delete()
            return JsonResponse({'success': True, 'message': "Request rejected"})
        else:
           return JsonResponse({'success': False, 'message': "Request error"})
    except MyUser.DoesNotExist:
        return JsonResponse({'success': False, 'error': "Request not found"})

@api_view(['GET', 'POST'])
@permission_classes([IsAuthenticated])
def remove_friend(request, request_id):
    try:
        friend = MyUser.objects.get(id=request_id)
        friendship = friend in request.user.friends.all()
        if (friendship):
            request.user.remove_friend(friend)
            return JsonResponse({'success': True, 'message': "Friend deleted"})
        else:
           return JsonResponse({'success': False, 'message': "Friend deleted error"})
    except MyUser.DoesNotExist:
        return JsonResponse({'success': False, 'error': "Friend not found"})