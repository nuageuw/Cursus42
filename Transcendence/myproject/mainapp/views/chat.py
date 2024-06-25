from django.shortcuts import get_object_or_404
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from ..models import MyUser, Conversation, ChatMessage

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def get_messages(request, recipient_id):
    try:
        user = request.user
        recipient = get_object_or_404(MyUser, id=recipient_id)
        is_blocked =  user.blocked_users.filter(id=recipient_id).exists()
        conversation = Conversation.get_or_create_conversation(user, recipient)

        conversation_data = { 
            'user' : {
                'id' : request.user.id,
                'name' : request.user.username,
                'img' : request.user.image_link
            },
            'recipient' : {
                'id' : recipient.id,
                'name' : recipient.username,
                'img' : recipient.image_link,
            },
            'id': conversation.id,
            'blocked' : is_blocked,
        }

        return Response({'conversation': conversation_data})
    except MyUser.DoesNotExist:
        return Response({'error': 'User not found'})
