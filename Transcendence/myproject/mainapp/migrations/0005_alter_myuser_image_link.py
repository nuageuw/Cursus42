# Generated by Django 5.0.6 on 2024-06-19 16:49

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('mainapp', '0004_myuser_first_connection'),
    ]

    operations = [
        migrations.AlterField(
            model_name='myuser',
            name='image_link',
            field=models.URLField(default='https://localhost:8443/media/profile1.png'),
        ),
    ]
