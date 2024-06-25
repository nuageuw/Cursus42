from channels.middleware import BaseMiddleware
from django.contrib.auth.models import AnonymousUser
from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework_simplejwt.exceptions import InvalidToken, TokenError
from urllib.parse import parse_qs
from channels.auth import AuthMiddlewareStack
from channels.db import database_sync_to_async

class TokenAuthMiddleware(BaseMiddleware):
    """
    Middleware that extracts the JWT from the query string and authenticates the WebSocket connection if valid.
    """
    async def __call__(self, scope, receive, send):
        query_string = parse_qs(scope['query_string'].decode('utf8'))
        token = query_string.get('token', [None])[0]

        if token:
            jwt_auth = JWTAuthentication()
            try:
                validated_token = jwt_auth.get_validated_token(token)
                user = await database_sync_to_async(jwt_auth.get_user)(validated_token)
                scope['user'] = user if user is not None else AnonymousUser()
            except TokenError as e:
                scope['user'] = AnonymousUser()
            except InvalidToken as e:
                scope['user'] = AnonymousUser()
            except Exception as e:
                scope['user'] = AnonymousUser()
        else:
            scope['user'] = AnonymousUser()

        return await super().__call__(scope, receive, send)

def TokenAuthMiddlewareStack(inner):
    return TokenAuthMiddleware(AuthMiddlewareStack(inner))
