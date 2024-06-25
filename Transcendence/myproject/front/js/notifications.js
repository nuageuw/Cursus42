let notificationQueue = [];

function showNotification(message, colorIndex = 1) {
    notificationQueue.push({ message, colorIndex });
    if (notificationQueue.length === 1) {
        displayNextNotification();
    }
}

function displayNextNotification() {
    if (notificationQueue.length === 0) {
        return;
    }

    const notificationsContainer = document.getElementById('notifications-containers');
    const { message, colorIndex } = notificationQueue.shift();
    const notificationBox = document.createElement('div');
    notificationBox.className = `notification-box color-${colorIndex} show`;
    notificationBox.textContent = message;
    notificationsContainer.appendChild(notificationBox);

    setTimeout(() => {
        notificationBox.classList.remove('show');
        notificationBox.classList.add('hide');
    }, 3000);

    setTimeout(() => {
        notificationsContainer.removeChild(notificationBox);
        displayNextNotification();
    }, 3500);
}
