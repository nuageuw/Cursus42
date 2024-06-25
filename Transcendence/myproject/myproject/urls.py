from django.contrib import admin
from django.urls import path, include
from django.conf import settings
from django.conf.urls.static import static
from django.contrib.auth import views as auth_views
from . import consumers

from mainapp.views import login, secure, tournament, user, friends, chat
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView

urlpatterns = [
    path('admin/login/', auth_views.LoginView.as_view(template_name='login.html')),
    path('admin/', admin.site.urls),


    path('ws/chatpage/', consumers.ChatConsumer.as_asgi()),
    path('api/register/', login.RegisterView.as_view()),
    path('api/login/', login.LoginUserView.as_view()),
    path('api/logout/', login.LogoutApiView.as_view()),
    path('api/2fa/verify/', login.OTPAuthenticationView.as_view(), name='2fa-verify'),
    path('api/2fa/enable/', login.OTPSetupView.as_view(), name='2fa-enable'),
    path('api/oauth/login/', login.OAuthLoginView.as_view(), name='oauth_login'),
    path('api/oauth/authorize/', login.OAuthAuthorizeView.as_view(), name='oauth_authorize'),
    
    
    path('api/get-csrf-token/', secure.get_csrf_token),

    path('api/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),
    path('api/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),

    
    path('api/tournament/', tournament.tournament),
    path('api/create_tour/', tournament.create_tour),
    path('api/tour_details/<int:tournament_id>/', tournament.tour_details),
    path('api/teams_play/<int:tournament_id>/', tournament.teams_play),
    path('api/pong/<int:teams_id>/', tournament.pong),
    path('api/check_pw/<int:teams_id>/', tournament.check_pw),
    path('api/update_player_scores/', tournament.update_player_scores),
    path('api/search_players/', user.search_players),
    path('api/user_info/<int:user_id>/', user.user_info),
    path('api/profil/', user.profil),
    path('api/modify/', user.modify),
    path('api/id/', user.id),
    path('api/update_pictures/', user.UpdatePictureView.as_view()),
    path('api/send_friend_request/<int:user_id>/', friends.send_friend_request),
    path('api/accept_friend_request/<int:request_id>/', friends.accept_friend_request),
    path('api/reject_friend_request/<int:request_id>/', friends.reject_friend_request),
    path('api/remove_friend/<int:request_id>/', friends.remove_friend),
    path('api/get_messages/<int:recipient_id>/', chat.get_messages),





] + static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)

