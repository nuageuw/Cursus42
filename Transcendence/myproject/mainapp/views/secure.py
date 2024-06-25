from django.http import JsonResponse
from django.middleware.csrf import get_token
from django.views.decorators.csrf import ensure_csrf_cookie
import re


@ensure_csrf_cookie
def get_csrf_token(request):
    try:
        csrf_token = get_token(request)
        return JsonResponse({'csrfToken': csrf_token})
    except Exception as e:
        return JsonResponse({'error': str(e)}, status=400)
    
def is_valid_username(username):
    pattern = r'^[a-zA-Z0-9.]+$'
    if re.match(pattern, username):
        return True
    else:
        return False