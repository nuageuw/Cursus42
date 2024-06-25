from .models import MyUser
from rest_framework import serializers
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import RefreshToken, TokenError
from django.contrib.auth import authenticate
from django.utils.translation import gettext_lazy as _
from .views.secure import is_valid_username

class UserRegisterSerializer(serializers.ModelSerializer):
    password = serializers.CharField(max_length=68, min_length=6, write_only=True)
    password2 = serializers.CharField(max_length=68, min_length=6, write_only=True)

    class Meta:
        model = MyUser
        fields = ['email', 'username', 'password', 'password2']

    def validate(self, attrs):
        email = attrs.get('email', '')
        username = attrs.get('username', '')
        password = attrs.get('password', '')
        password2 = attrs.get('password2', '')

        if email:
            email = email.lower()
        if username:
            username = username.lower()

        if not is_valid_username(username):
            raise serializers.ValidationError("Username is invalid")

        if password != password2:
            raise serializers.ValidationError("Passwords do not match")

        if MyUser.objects.filter(email=email).exists():
            raise serializers.ValidationError("Email already exists")

        if MyUser.objects.filter(username=username).exists():
            raise serializers.ValidationError("Username already exists")

        return attrs

    def create(self, validated_data):
        user = MyUser.objects.create_user(
            email=validated_data['email'],
            username=validated_data['username'],
            password=validated_data.get('password')
        )
        return user
    

class LoginSerializer(serializers.ModelSerializer):
    email = serializers.EmailField(max_length=155, min_length=6)
    password = serializers.CharField(max_length=68, write_only=True)
    access_token = serializers.CharField(max_length=255, read_only=True)
    refresh_token = serializers.CharField(max_length=255, read_only=True)

    class Meta:
        model = MyUser
        fields = ['email', 'password', 'access_token', 'refresh_token']

    def validate(self, attrs):
        email = attrs.get('email')
        password = attrs.get('password')
        request = self.context.get('request')

        if(email):
            email = email.lower()

        try:
            user_info = MyUser.objects.get(email=email)
            if user_info.is_oauth_user:
                raise AuthenticationFailed("Please login using your social account")
        except MyUser.DoesNotExist:
            raise AuthenticationFailed("User not found")

        user = authenticate(request, email=email, password=password)
        if not user:
            raise AuthenticationFailed("Invalid credentials, try again")

        return {
            'user': user,
            'email': user.email,
            'username': user.username,
            'first_connection': user.first_connection,
            'access_token': str(user.tokens().get('access')),
            'refresh_token': str(user.tokens().get('refresh'))
        }
    

class LogoutUserSerializer(serializers.Serializer):
    refresh_token=serializers.CharField()

    default_error_messages = {
        'bad_token': _('Token is expired or invalid')
    }

    def validate(self, attrs):
        self.token = attrs.get('refresh_token')
        self.id = attrs.get('id')

        return attrs

    def save(self, **kwargs):
        try:
            token=RefreshToken(self.token)
            token.blacklist()
        except TokenError:
            return self.fail('bad_token')


class OTPSerializer(serializers.Serializer):
    otp_code = serializers.CharField(max_length=6, min_length=6)