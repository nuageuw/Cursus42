import json
from html import escape
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
from mainapp.models import MyUser


class ChatConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.room_group_name = f'user_{self.scope["url_route"]["kwargs"]["room_id"]}'
        self.global_online_group = 'online_users'
        await self.channel_layer.group_add(self.room_group_name, self.channel_name)
        await self.channel_layer.group_add(self.global_online_group, self.channel_name)
        await self.accept()
        

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.room_group_name, self.channel_name)
        await self.channel_layer.group_discard(self.global_online_group, self.channel_name)

    async def receive(self, text_data):
        data = json.loads(text_data)
        message_type = data.get('type', 'message')

        if message_type == 'message':
            await self.handle_message(data)
        elif message_type == 'game_request':
            await self.handle_game_request(data)
        elif message_type == 'game_response':
            await self.handle_game_response(data)
        elif message_type == 'login':
            await self.handle_user_co(data)
        elif message_type == 'block' or message_type == 'unblock':
            await self.handle_user_block(data)
    
    async def tournament_notification(self, event):
        await self.send(text_data=json.dumps({
            'type': 'tournament_notification',
            'message': event['message']
        }))


    async def handle_user_co(self, data):
        user_id = data.get('user_id')
        user_name = data.get('user_name')
        user_img = data.get('user_img')
        await self.channel_layer.group_send(
            self.global_online_group,
            {
                'type': 'user_online',
                'user_id': user_id,
                'user_name': user_name,
                'user_img' : user_img,
            }
        )

    async def handle_user_block(self, data):
        message = escape(data.get('message', ''))
        action = data.get('type')
        user_id = data.get('user_id')
        recipient_id = data.get('recipient_id')
        user_name = data.get('user_name')
        sender_group_name = f"user_{user_id}"
        recipient_group_name = f"user_{recipient_id}"

        await self.block_user( action, user_id, recipient_id)

        content_not = {
            'type': 'receive_notification',
            'message': message,
            'from_user_id': user_id,
            'recipient_id': recipient_id,
            'user_name' : user_name,
        }
        await self.channel_layer.group_send(recipient_group_name,content_not)
    
    @database_sync_to_async
    def block_user(self ,action ,user_id, recipient_id):
        user = MyUser.objects.get(id=user_id)
        recipient = MyUser.objects.get(id=recipient_id)
        if (action == 'block'):
            user.blocked_users.add(recipient)
        else:
            user.blocked_users.remove(recipient)
        user.save()
    
    @database_sync_to_async
    def blocked(self ,user_id, recipient_id):
        user = MyUser.objects.get(id=user_id)
        recipient = MyUser.objects.get(id=recipient_id)
        if recipient.blocked_users.filter(id=user.id).exists():
            return True
        else:
            return False

    
    async def handle_message(self, data):
        message = escape(data.get('message', ''))
        user_id = data.get('user_id')
        recipient_id = data.get('recipient_id')
        user_name = data.get('user_name')
        sender_group_name = f"user_{user_id}"
        recipient_group_name = f"user_{recipient_id}"

        blocked = await self.blocked(user_id, recipient_id)

        content = {
            'type': 'chat_message',
            'message': message,
            'user_id': user_id,
            'recipient_id': recipient_id,
        }

        content_not = {
            'type': 'receive_notification',
            'message': message,
            'from_user_id': user_id,
            'recipient_id': recipient_id,
            'user_name' : user_name,
        }
        await self.channel_layer.group_send(sender_group_name, content)
        if (not blocked):
            await self.channel_layer.group_send(recipient_group_name, content)
            await self.channel_layer.group_send(recipient_group_name,content_not)
    

    async def handle_game_request(self, data):
        user_id = data.get('user_id')
        user_name = data.get('user_name')
        recipient_id = data.get('recipient_id')
        sender_group_name = f"user_{user_id}"
        recipient_group_name = f"user_{recipient_id}"

        content = {
            'type': 'game_request',
            'user_id': user_id,
            'user_name' : user_name,
            'recipient_id': recipient_id,
        }
        await self.channel_layer.group_send(recipient_group_name, content)

    async def handle_game_response(self, data):
        from_user_id = data.get('from_user_id')
        to_user_id = data.get('to_user_id')
        from_user_name = data.get('from_user_name')
        accepted = data.get('accepted')
        recipient_group_name = f"user_{to_user_id}"
        content = {
            'type': 'game_response',
            'from_user_id': from_user_id,
            'from_user_name' : from_user_name,
            'to_user_id': to_user_id,
            'accepted': accepted
        }
        await self.channel_layer.group_send(recipient_group_name,content)

    async def chat_message(self, event):
        await self.send(text_data=json.dumps({
            'type': 'message',
            'message': event['message'],
            'user_id': event['user_id'],
            'recipient_id': event['recipient_id'],
        }))
    
    async def receive_notification(self, event):
        await self.send(text_data=json.dumps({
            'type': 'notification',
            'message': event['message'],
            'from_user_id': event['from_user_id'],
            'user_name' : event['user_name'],
        }))

    async def game_request(self, event):
        await self.send(text_data=json.dumps({
            'type': 'game_request',
            'user_id': event['user_id'],
            'user_name' :event['user_name'],
        }))

    async def game_response(self, event):
        await self.send(text_data=json.dumps({
            'type': 'game_response',
            'from_user_id': event['from_user_id'],
            'from_user_name': event['from_user_name'],
            'to_user_id': event['to_user_id'],
            'accepted': event['accepted']
        }))

    async def user_online(self, event):
        await self.send(text_data=json.dumps({
            'type': 'online_user',
            'user_id': event['user_id'],
            'user_img' : event['user_img'],
            'user_name' : event['user_name'],
        }))

    async def off_online(self, event):
        await self.send(text_data=json.dumps({
            'type': 'user_offline',
            'user_id': event['user_id'],
            'user_img' : event['user_img'],
            'user_name' : event['user_name'],
        }))