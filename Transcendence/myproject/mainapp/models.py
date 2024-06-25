from django.db import models
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.contrib.auth.hashers import make_password
from django.core.validators import validate_email
from django.core.exceptions import ValidationError
from django.utils.translation import gettext_lazy as _

from rest_framework_simplejwt.tokens import RefreshToken

class MyUserManager(BaseUserManager):
    def email_validator(self, email):
        try:
            validate_email(email)
        except ValidationError:
            raise ValueError(_("please enter a valid email address"))

    def create_user(self, email, username, password, **extra_fields):
        if email:
            email = self.normalize_email(email)
            self.email_validator(email)
        else:
            raise ValueError(_("Base User Account: An email address is required"))
        user = self.model(email=email, username=username, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_superuser(self, email, password, **extra_fields):
        extra_fields.setdefault("is_staff", True)
        extra_fields.setdefault("is_superuser", True)

        if extra_fields.get("is_staff") is not True:
            raise ValueError(_("is staff must be true for admin user"))

        if extra_fields.get("is_superuser") is not True:
            raise ValueError(_("is superuser must be true for admin user"))
        username = email.split('@')[0]
        user = self.create_user(
            email, username, password, **extra_fields
        )
        user.save(using=self._db)
        return user


class MyUser(AbstractBaseUser, PermissionsMixin):
    id = models.BigAutoField(primary_key=True, editable=False) 
    email = models.EmailField(('email address'), unique=True, null=True)
    username = models.CharField(max_length=50,unique=True, null=True)
    score = models.IntegerField(default=0)
    nickname = models.CharField(max_length=50, blank=True, null=True)
    image_link = models.URLField(default="https://localhost:8443/media/profile1.png")
    friends = models.ManyToManyField('self', symmetrical=True, blank=True)  
    blocked_users = models.ManyToManyField('self', symmetrical=False, related_name='blocked_by', blank=True) 
    two_factor_enabled = models.BooleanField(default=False)
    activation_code = models.CharField(max_length=255, blank=True, null=True)
    is_oauth_user = models.BooleanField(default=False)
    games_played = models.IntegerField(default=0)  
    games_won = models.IntegerField(default=0)  
    games_lost = models.IntegerField(default=0)
    is_online = models.BooleanField(default=False)
    is_staff = models.BooleanField(default=False)
    is_superuser = models.BooleanField(default=False)
    is_active = models.BooleanField(default=True)
    first_connection = models.BooleanField(default=True)

    objects = MyUserManager()

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = []

    def tokens(self):    
        refresh = RefreshToken.for_user(self)
        return {
            "refresh": str(refresh),
            "access": str(refresh.access_token)
        }
    
    def add_friend(self, friend):
        self.friends.add(friend)
        friend.friends.add(self)

    def remove_friend(self, friend):
        self.friends.remove(friend)
        friend.friends.remove(self)

    def is_friend(self, friend):
        return friend in self.friends.all()
    
    def has_sent_friend_request_to(self, user):
        return FriendRequest.objects.filter(from_user=self, to_user=user).exists()
    
    def has_received_friend_request_from(self, user):
        return FriendRequest.objects.filter(from_user=user, to_user=self).exists()


    def __str__(self):
        return f"{self.username} - {self.email}"

#------------------ Tournois --------------------

class Tournament(models.Model):
    name = models.CharField(max_length=30, blank=True, null=True)
    start = models.DateTimeField()
    players = models.ManyToManyField(MyUser, related_name='enrolled_tournaments', blank=True)
    numb_p = models.IntegerField()
    full = models.BooleanField(default=False)
    finish = models.BooleanField(default=False)
    def __str__(self):
        return self.name 


class Round(models.Model):
    name = models.CharField(max_length=30, blank=True, null=True)
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE, related_name='matches')
    round_number = models.IntegerField()
    
    def __str__(self):
        return f"{self.tournament.name} - Round {self.round_number}"


class Team(models.Model):
    name = models.CharField(max_length=30, blank=True, null=True)
    round_number = models.ForeignKey(Round, on_delete=models.CASCADE, related_name='teams')
    players = models.ManyToManyField(MyUser, related_name='tournaments', blank=True)
    winner = models.ForeignKey(MyUser, on_delete=models.CASCADE, null=True, blank=True, related_name='won_teams')
    score1 = models.IntegerField(default=0)
    score2 = models.IntegerField(default=0)
    
    def __str__(self):
    	return self.name


#------------------ Friends --------------------

class FriendRequest(models.Model):
    from_user = models.ForeignKey(MyUser, related_name='from_user', on_delete=models.CASCADE)
    to_user = models.ForeignKey(MyUser, related_name='to_user', on_delete=models.CASCADE)
    timestamp = models.DateTimeField(auto_now_add=True)


class Friendship(models.Model):
    user1 = models.ForeignKey(MyUser, related_name='friend_user1', on_delete=models.CASCADE)
    user2 = models.ForeignKey(MyUser, related_name='friend_user2', on_delete=models.CASCADE)
    friends_since = models.DateTimeField(auto_now_add=True)


class Conversation(models.Model):
    participants = models.ManyToManyField(MyUser, related_name='conversations')

    @classmethod
    def get_or_create_conversation(cls, user1, user2):
        conversation = cls.objects.filter(participants=user1).filter(participants=user2).first()
        if not conversation:
            conversation = cls.objects.create()
            conversation.participants.add(user1, user2)
        return conversation

class ChatMessage(models.Model):
    sender = models.ForeignKey(MyUser, on_delete=models.CASCADE, related_name='sent_messages')
    recipient = models.ForeignKey(MyUser, on_delete=models.CASCADE, related_name='received_messages')
    conversation = models.ForeignKey(Conversation, on_delete=models.CASCADE, related_name='messages')
    message = models.TextField()
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f'{self.sender} to {self.recipient}: {self.message[:20]}'