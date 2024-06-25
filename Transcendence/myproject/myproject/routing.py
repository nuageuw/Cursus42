from channels.routing import ProtocolTypeRouter, URLRouter
from django.urls import path, re_path
from channels.auth import AuthMiddlewareStack
from django.core.asgi import get_asgi_application
django_asgi_app = get_asgi_application()
from myproject.consumers import ChatConsumer
from mainapp.midd import TokenAuthMiddlewareStack


websocket_urlpatterns = [
    re_path(r'ws/chatpage/(?P<room_id>\d+)/$', ChatConsumer.as_asgi()),
    re_path(r'chatpage/$', ChatConsumer.as_asgi()),
]

application = ProtocolTypeRouter({
    
    "http": django_asgi_app,
    
    "websocket":
        URLRouter(
        websocket_urlpatterns
    ),
})