from django.db.models.signals import post_save
from django.dispatch import receiver
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

from .models import Tournament, Round, Team

@receiver(post_save, sender=Tournament)
def create_initial_round(sender, instance, created, **kwargs):
    if created:
        try:
            Round.objects.create(name="Round 1", tournament=instance, round_number=1)
        except Exception as e:
            print(e)

@receiver(post_save, sender=Tournament)
def tournoi_full(sender, instance, created, **kwargs):
    if instance.full and not created:
        players = list(instance.players.all().order_by('-score'))
        round_one = instance.matches.latest('round_number')
        channel_layer = get_channel_layer()

        while players:
            team_players = [players.pop(0), players.pop(0)]
            team = Team.objects.create(name=f"{team_players[0].nickname} VS {team_players[1].nickname}", round_number=round_one)
            team.players.set(team_players)

            for player in team.players.all():
                async_to_sync(channel_layer.group_send)(
                    f'user_{player.id}',
                    {
                        'type': 'tournament_notification',
                        'message': f'The tournament {instance.name} has been updated: {team.name}'
                    }
                )