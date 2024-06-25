let chatSocket;
const NOTIFICATION_DURATION = 2000;
const MAX_RETRIES = 3;
let retryCount = 0;
const MESSAGE_SEND_INTERVAL = 5000;
const MAX_MESSAGE_LENGTH = 200;
let lastMessageSentTime = 0;

function initializeWebSocket() {
    const accessToken = localStorage.getItem('token'); 
    if (!accessToken) {
        return;
    }
    fetch('/api/id/', {
        method : 'GET',
        headers: {
            'Authorization': `Bearer ${accessToken}`,
            'Content-Type': 'application/json' 
        }
    })
    .then(response => {
        if (response.ok) {
            return response.json();
        } else {
            throw new Error('Non autorisé ou Token expiré');
        }
    })
    .then(data => {
        localStorage.setItem('userId', data.user_data.id);
        localStorage.setItem('username', data.user_data.name);
        localStorage.setItem('userImg', data.user_data.userImg);
        setupWebSocket(data.user_data.id);
    })
    .catch(error => {
        console.error('Erreur:', error);
    });
}

async function setupWebSocket(userId) {
    const token = localStorage.getItem('token');
    const websocketUrl = `wss://${window.location.host}/ws/chatpage/${userId}/`;
    chatSocket = new WebSocket(websocketUrl);

    chatSocket.addEventListener('open', () => {
        const userId = localStorage.getItem('userId');
        const userName = localStorage.getItem('username');
        const userImg = localStorage.getItem('userImg');
        chatSocket.send(JSON.stringify({
            type: 'login',
            user_id: userId, 
            user_name: userName,
            user_img: userImg,
        }));
        ensureDomLoaded();
    });

    chatSocket.addEventListener('message', event => {
        const data = JSON.parse(event.data);
        if (data.type === 'message') {
            displayMessages(data);
        } else if (data.type === 'notification') {
            displayNotification(data.message ,data.user_name, data.from_user_id);
        } else if (data.type === 'game_request') {
            displayGameRequest(data);
        } else if (data.type === 'game_response') {
            handleGameResponse(data);
        }
        else if (data.type === 'online_user') {
            displayUserOnline(data);
        }
        else if (data.type === 'tournament_notification') {
            displayNotification(data.message ,'', '');
        }
    });

    chatSocket.addEventListener('close', e => {
        console.error('Chat socket closed unexpectedly', e);
        handleWebSocketClose(localStorage.getItem('userId'));
    });

    chatSocket.addEventListener('error', e => {
        console.error('WebSocket error', e);
        showNotification('WebSocket error', 3);
    });

}

async function ensureDomLoaded() {
    const input = document.getElementById('chat-message-input');
    const submitButton = document.getElementById('chat-message-submit');
    const gamebut = document.getElementById('send-game-request');
    if (!input || !submitButton || !gamebut) {
        setTimeout(ensureDomLoaded, 50);
    } else {
        attachEventListeners(input, submitButton, gamebut);
    }
}

async function attachEventListeners(input, submitButton, gamebut) {
    input.addEventListener('keypress', event => {
        if (event.key === 'Enter') {
            event.preventDefault();
            sendMessage(input.value, localStorage.getItem('recipientId'));
            input.value = '';
        }
    });

    submitButton.addEventListener('click', () => {
        sendMessage(input.value, localStorage.getItem('recipientId'));
        input.value = '';
    });

    gamebut.addEventListener('click', () => {
        sendGameRequest();
    });

}

function handleWebSocketClose(conversationId) {
    if (retryCount < MAX_RETRIES) {
        setTimeout(() => setupWebSocket(conversationId), 3000);
        retryCount++;
        showNotification('Attempting to reconnect...', 3);
    } else {
        showNotification('Failed to reconnect. Please refresh the page.', 3);
    }
}

async function sendMessage(message, recipientId) {
    if (!message.trim()) return;
    if (new Date().getTime() - lastMessageSentTime < MESSAGE_SEND_INTERVAL) {
        showNotification("Please wait before sending another message.", 3);
        return;
    }

    lastMessageSentTime = new Date().getTime();
    const messageData = { type: 'message', message: message.trim(), user_id: localStorage.getItem('userId'), recipient_id:  localStorage.getItem('recipientId'), user_name :localStorage.getItem('username')};
    if (chatSocket.readyState === WebSocket.OPEN) {
        chatSocket.send(JSON.stringify(messageData));
        showNotification("Message sent successfully.", 2);
    } else {
        showNotification("Connection not established. Trying to reconnect...", 3);
        handleWebSocketClose(recipientId);
    }
}

async function displayUserOnline(data) {
    try {
        const userList = document.getElementById('user-list');
        if (data.type === 'online_user') {
            try {
                const userItem = document.getElementById(`user-${data.user_id}`);
                if (userItem) {
                    userList.removeChild(userItem);
                }
            } catch (error) {}
            const myId = localStorage.getItem('userId');
            if (data.user_id == myId) {
                return;
            }
            const userItem = document.createElement('li');
            const userImage = document.createElement('img');
            userItem.id = `user-${data.user_id}`;
            userItem.href = `/#chat/${data.user_id}`;
            userImage.src = data.user_img;
            userImage.alt = `${data.user_name}'s profile picture`;
            userImage.classList.add('user-image');
            userImage.style.width = '100%';
    
            const statusIndicator = document.createElement('span');
            statusIndicator.classList.add('status-indicator');
    
            userItem.appendChild(userImage);
            userItem.appendChild(statusIndicator);
            userList.appendChild(userItem);
        } else if (data.type === 'user_offline') {
            const userItem = document.getElementById(`user-${data.user_id}`);
            if (userItem) {
                userList.removeChild(userItem);
            }
        }
    } catch (error) {
        console.error('Failed to update user list', error);
    }
}

async function displayMessages(data) {
    try{
        const chatLog = document.querySelector('#chat-log');
        const messageDiv = document.createElement('div');
        const convId = window.location.hash.split('/')[1];
        const currentUserId = localStorage.getItem('userId');
        const currentUserName = localStorage.getItem('username');
        const recipientName = localStorage.getItem('recipientName');
        const UImg = localStorage.getItem('userImg');
        const RImg = localStorage.getItem('recipientImg');
        const imgElement = document.createElement('img');
        imgElement.style.width = '30px';
        imgElement.style.height = '30px';
        imgElement.style.borderRadius = '50%';
        imgElement.style.marginRight = '10px';
    
        if (data.user_id === currentUserId) {
            messageDiv.classList.add('message', 'right');
            imgElement.src = UImg;
            messageDiv.innerHTML = `<p>${imgElement.outerHTML}<strong>${currentUserName}:</strong> ${data.message}</p>`;
    
        } else if (data.user_id === convId) {
            messageDiv.classList.add('message', 'left');
            imgElement.src = RImg;
            messageDiv.innerHTML = `<p>${imgElement.outerHTML}<strong>${recipientName}:</strong> ${data.message}</p>`;
        }
        chatLog.appendChild(messageDiv);
        chatLog.scrollTop = chatLog.scrollHeight;
    } catch (error) {}
}

async function displayNotification(message, fromUserId, userId) {
    if (!(window.location.hash.includes(`#chat/${userId}`)) || (message.includes("blocked"))) {
        const container = document.getElementById('notifications-containers');
        const notification = document.createElement('div');
        notification.className = 'notification-box';
        notification.innerHTML = `${fromUserId} : ${message}`;
        container.appendChild(notification);
        container.style.display = 'block';

        setTimeout(() => {
            container.removeChild(notification);
            if (container.children.length === 0) {
                container.style.display = 'none';
            }
        }, 5000);
    }
}

async function sendGameRequest() {
    const messageData = { type: 'game_request', user_id: localStorage.getItem('userId'), recipient_id: localStorage.getItem('recipientId'), 'user_name' : localStorage.getItem('username')};
    if (chatSocket.readyState === WebSocket.OPEN) {
        chatSocket.send(JSON.stringify(messageData));
        showNotification("Game request sent.", 2);
    } else {
        showNotification("Connection not established. Trying to reconnect...", 3);
        handleWebSocketClose(conversationId);
    }
}

async function displayGameRequest(data) {
    if (data.user_id != localStorage.getItem('userId')) {
        const gameNotification = document.getElementById('game-notification');
        const gameRequestText = document.getElementById('game-request-text');
        gameRequestText.textContent = `You have received a game request! from ${data.user_name}`;
        gameNotification.style.display = 'flex';
    
        document.getElementById('accept-game-request').onclick = () => respondToGameRequest(data.user_id, true);
        document.getElementById('decline-game-request').onclick = () => respondToGameRequest(data.user_id, false);
    }
}


async function respondToGameRequest(fromUserId, accepted) {
    const responseMessage = {
        type: 'game_response',
        from_user_id: localStorage.getItem('userId'),
        from_user_name: localStorage.getItem('username'),
        to_user_id: fromUserId,
        accepted: accepted
    };

    if (chatSocket.readyState === WebSocket.OPEN) {
        chatSocket.send(JSON.stringify(responseMessage));
        showNotification("Response sent.", 2);
    }

    const gameNotification = document.getElementById('game-notification');
    gameNotification.style.display = 'none';
    if (accepted) {
        window.location.href = `/#pong_training/`;
    }
}

async function handleGameResponse(data) {
    if (data.to_user_id == localStorage.getItem('userId')) {
        const notificationText = data.accepted ? "Your game request was accepted!" : "Your game request was declined.";
        const color = data.accepted ? 2 : 3;
        showNotification(notificationText, color);
    }
}

async function fetchMessages(recipientId) {
    const response = await fetch(`/api/get_messages/${recipientId}/`, {
        method: 'GET',
        headers: {
            'Authorization': `Bearer ${localStorage.getItem('token')}`,
            'Content-Type': 'application/json'
        }
    });

    if (response.ok) {
        const data = await response.json();
        localStorage.setItem('userName', data.conversation.user.name);
        localStorage.setItem('recipientId', data.conversation.recipient.id);
        localStorage.setItem('recipientName', data.conversation.recipient.name);
        localStorage.setItem('recipientImg', data.conversation.recipient.img);
        localStorage.setItem('userImg', data.conversation.user.img);
        displayButton(data.conversation);
    } else {
        console.error('Failed to fetch messages');
    }
}

async function displayButton(conversationId) {
    const blockButton = document.getElementById("block");
    const profileButton = document.getElementById("profile");
    const img = document.createElement('img');
    let isBlocked = conversationId.blocked;

    img.style.width = '30px';
    img.style.height = '30px';
    img.style.borderRadius = '50%';
    img.style.marginRight = '10px';
    img.src = conversationId.recipient.img;
    profileButton.appendChild(img);
    profileButton.innerHTML += `See ${conversationId.recipient.name}\'s profile page`;
    profileButton.addEventListener('click', () => {
        window.location.href = `/#user_info/${conversationId.recipient.id}/`;
    });

    blockButton.textContent = blockButton.textContent = isBlocked ? 'Unblock user' : 'Block user';
    blockButton.addEventListener('click', () => {
    const message = isBlocked ? 'has just deblocked you': 'has just blocked you, he/she will not longer see your messages';
    const action = isBlocked ? 'unblock' : 'block';
    const messageData = {
        type: action,
        message: message,
        user_id: localStorage.getItem('userId'),
        recipient_id: localStorage.getItem('recipientId'),
        user_name: localStorage.getItem('username')
    };
    if (chatSocket.readyState === WebSocket.OPEN) {
        chatSocket.send(JSON.stringify(messageData));
        isBlocked = !isBlocked;
        blockButton.textContent = isBlocked ? 'Unblock user' : 'Block user';
        const notificationMessage = !isBlocked ?
            `Warning : ${conversationId.recipient.name} is unblocked, you will see her/his messages` :
            `Warning : ${conversationId.recipient.name} is blocked, you will not longer see her/his messages`;
        const color = isBlocked ? 3 : 2;
        showNotification(notificationMessage, color);
    } else {
        showNotification("Connection not established. Trying to reconnect...", 3);
        handleWebSocketClose(conversationId.user.id);
    }
    });
    

}

