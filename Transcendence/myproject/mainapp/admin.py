from django.contrib import admin
from .models import MyUser, Tournament, Round, Team, FriendRequest, Friendship, Conversation, ChatMessage

admin.site.register(MyUser)
admin.site.register(Tournament)
admin.site.register(Round)
admin.site.register(Team)
admin.site.register(FriendRequest)
admin.site.register(Friendship)
admin.site.register(Conversation)
admin.site.register(ChatMessage)
