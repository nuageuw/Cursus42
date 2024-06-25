import logging
import requests
import re
import pyotp
import qrcode
import base64

from io import BytesIO
from urllib.parse import quote

from rest_framework.generics import GenericAPIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework.exceptions import AuthenticationFailed
from rest_framework.views import APIView

from django.http import JsonResponse
from django.middleware.csrf import get_token
from django.conf import settings
from django.shortcuts import redirect
from django.contrib.auth import authenticate
from django.http import HttpResponseRedirect

from ..models import MyUser
from ..serializers import LogoutUserSerializer, UserRegisterSerializer, LoginSerializer, OTPSerializer

class RegisterView(GenericAPIView):
    serializer_class = UserRegisterSerializer

    def post(self, request):
        user = request.data
        serializer=self.serializer_class(data=user)
        if serializer.is_valid(raise_exception=True):
            serializer.save()
            user_data=serializer.data
            return Response({
                'data':user_data,
            }, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    

class LoginUserView(GenericAPIView):
    serializer_class = LoginSerializer

    def post(self, request):
            serializer = self.serializer_class(data=request.data, context={'request': request})
            serializer.is_valid(raise_exception=True)

            user = serializer.validated_data['user']

            if user.two_factor_enabled:
                return Response({
                    'username': user.username,
                    'fa_required': True
                }, status=status.HTTP_200_OK)

            access_token = serializer.data.get('access_token')
            refresh_token = serializer.data.get('refresh_token')
            user.is_online = True
            return Response({
                'email': serializer.data.get('email'),
                'username': user.username,
                'first_connection': user.first_connection,
                'access_token': access_token,
                'refresh_token': refresh_token
            }, status=status.HTTP_200_OK)
    

class LogoutApiView(GenericAPIView):
    serializer_class=LogoutUserSerializer

    def post(self, request):
        serializer=self.serializer_class(data=request.data)
        serializer.is_valid(raise_exception=True)
        serializer.save()
        try:
            id = request.data.get('id')
            user = MyUser.objects.get(id=id)
            user.is_online = False
            user.save()
        except:
            pass
        return Response(status=status.HTTP_204_NO_CONTENT)
    

class OTPSetupView(GenericAPIView):
    def post(self, request):
        try:
            user = request.user

            status = request.data.get('enable')
            if (status):
                user.two_factor_enabled = False
                user.activation_code = None
                user.save()
                return JsonResponse({'detail': 'Two-factor authentication has been disabled'})

            secret = pyotp.random_base32()

            user.activation_code = secret
            user.save()

            otp_url = pyotp.totp.TOTP(secret).provisioning_uri(name=user.username, issuer_name='Transcendence')

            qr = qrcode.make(otp_url)
            qr_bytes = BytesIO()
            qr.save(qr_bytes)

            qr_base = qr_bytes.getvalue()
            qr_base64 = base64.b64encode(qr_base).decode('utf-8').replace('\n', '')

            return JsonResponse({'otp_url': otp_url, 'qr_code_base64': qr_base64})
        except Exception as e:
            logging.error(str(e))
            return JsonResponse({'error': 'An error occurred while setting up 2FA'}, status=400)


class OTPAuthenticationView(GenericAPIView):
    serializer_class = OTPSerializer

    def post(self, request):
        serializer = self.get_serializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        otp_code = serializer.validated_data['otp_code']
        username = request.data.get('username')
        if username:
            user = MyUser.objects.get(username=username)
        else:
            user = request.user
        try:
            otp = pyotp.TOTP(user.activation_code)
            is_valid_otp = otp.verify(int(otp_code))
        except Exception as e:
            logging.error(f'Error: {str(e)}')
            return Response({'detail': 'Invalid OTP code'}, status=status.HTTP_400_BAD_REQUEST)
        if is_valid_otp:
            if not user.two_factor_enabled:
                user.two_factor_enabled = True
                user.save()
            if username:
                return Response({'detail': 'OTP is valid',
                                'access_token': str(user.tokens().get('access')),
                                'refresh_token': str(user.tokens().get('refresh'))}, status=status.HTTP_200_OK)
            return Response({'detail': 'OTP is valid'}, status=status.HTTP_200_OK)
        else:
            return Response({'detail': 'Invalid OTP code'}, status=status.HTTP_400_BAD_REQUEST)


class OAuthLoginView(APIView):
    def get(self, request):
        try:
            client_id = settings.API42_UID

            referral_url = request.GET.get('referral_url')
            if referral_url:
                request.session['referral_url'] = referral_url
                referral_url = quote(referral_url)  

            authorization_url = f'https://api.intra.42.fr/oauth/authorize?client_id={client_id}&response_type=code&redirect_uri={referral_url}/api/oauth/authorize/'
        
            return HttpResponseRedirect(authorization_url)
    
        except Exception as e:
            logging.error(str(e))
            return HttpResponseRedirect('/')


class OAuthAuthorizeView(APIView):
    def get(self, request):
        try:
            code = request.GET.get('code')
            if not code:
                return JsonResponse({'error': 'Code parameter is missing'}, status=400)
            if len(code) != 64 or not re.match(r'^[a-zA-Z0-9]+$', code):
                return JsonResponse({'error': 'Invalid code format'}, status=400)
            client_id = settings.API42_UID
            client_secret = settings.API42_SECRET
            redirect_uri = request.session.get('referral_url')+'/api/oauth/authorize/'
            csrf_token = get_token(request)

            if not client_id or not client_secret or not redirect_uri:
                return JsonResponse({'error': 'Environment variables are not set correctly'}, status=400)

            data = {
                'grant_type': 'authorization_code',
                'client_id': client_id,
                'client_secret': client_secret,
                'code': code,
                'redirect_uri': redirect_uri,
                'csrfToken': csrf_token,
            }

            try:
                response = requests.post('https://api.intra.42.fr/oauth/token', data=data)
                response.raise_for_status()

                access_token = response.json().get('access_token')

                user_data_response = requests.get('https://api.intra.42.fr/v2/me', headers={'Authorization': f'Bearer {access_token}'})
                user_data_response.raise_for_status()

                user_data = user_data_response.json()
                login = user_data.get('login')
                email = user_data.get('email')
                image_data = user_data.get('image', {})
                image_link = image_data.get('versions', {}).get('medium', image_data.get('link'))
                password = settings.SOCIAL_AUTH_PASSWORD

                try:
                    user = MyUser.objects.get(username=login)
                    if not user.is_oauth_user: 
                        redirect_url = f'/#login?m=oauth'
                        return redirect(redirect_url)
                except MyUser.DoesNotExist:
                    try:
                        user = MyUser.objects.get(email=email)
                        if not user.is_oauth_user: 
                            redirect_url = f'/#login?m=oauth'
                            return redirect(redirect_url)
                    except MyUser.DoesNotExist:
                        user = MyUser.objects.create_user(username=login, email=email, password=password)
                        user.nickname = user_data.get('nickname', user.username)
                        user.image_link = image_link
                        user.is_oauth_user = True
                        user.save()

                user.is_online = True
                user.save()
                tokens = user.tokens()

                user = authenticate(request, email=email, password=password)
                if not user:
                    raise AuthenticationFailed("Invalid credentials, try again")
                response_data = {
                    'email': user.email,
                    'access_token': tokens.get('access'),
                    'refresh_token': tokens.get('refresh')
                }
                response_data['redirect'] = True
                url = f'/#return?access_token={response_data["access_token"]}&refresh_token={response_data["refresh_token"]}'
                return redirect(url)
            except requests.RequestException as e:
                return JsonResponse({'error': str(e)}, status=400)
        except Exception as e:
            return JsonResponse({'error': str(e)}, status=400)
