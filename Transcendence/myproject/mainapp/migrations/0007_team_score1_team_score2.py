# Generated by Django 5.0.6 on 2024-06-22 18:33

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('mainapp', '0006_conversation_chatmessage'),
    ]

    operations = [
        migrations.AddField(
            model_name='team',
            name='score1',
            field=models.IntegerField(default=0),
        ),
        migrations.AddField(
            model_name='team',
            name='score2',
            field=models.IntegerField(default=0),
        ),
    ]
