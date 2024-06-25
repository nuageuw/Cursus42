async function loadUserInfo(userId) {
    const url = `/api/user_info/${userId}/`; 
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    const response = await fetch(url, {
        method: 'GET',
        headers: {
            'Authorization': `Bearer ${token}`,  
            'Content-Type': 'application/json' 
        }
    });
    if (!response.ok) throw new Error('Failed to fetch tournament details');
    const data = await response.json();
    displayUserInfo(data.user_data);
}

async function displayUserInfo(user) {
    const container = document.getElementById('container_profil');
    container.innerHTML = `<h1> ${user.username} </h1>`;
    container.innerHTML = `<div class="profil" > <img class="profile-image" src=${user.img}> <h1> ${user.username} </h1> <div data-user='${JSON.stringify(user)}' onclick="ToggleFriend(this)" class="add"> <p>${user.is_registered.status}</p> </div> <div class="message"> 
                                <a href="#chat/${user.id}">Envoyer un message </a>
                            </div> </div>`
    container.innerHTML += 
    `<div class="info">
                <div class="details" >
                    <p> MMR: </p>
                    <p> ${user.score} </p>
                </div>
                <div class="details" >
                    <p> Games played: </p>
                    <p> ${user.games_played} </p>
                </div>
                <div class="details" >
                    <p> Games lost: </p>
                    <p> ${user.games_lost} </p>
                </div>
                <div class="details" >
                    <p> Games won: </p>
                    <p> ${user.games_won} </p>
                </div>
        </div>`;
        const container2 = document.getElementById('container2');
        user.tournaments.forEach(tournament => {
            let tournamentDiv = document.createElement('div');
            tournamentDiv.className = 'tournament';
            tournamentDiv.innerHTML = `<h2>Tournament: ${tournament.name}</h2>`;
    
            tournament.rounds.forEach(round => {
                let roundDiv = document.createElement('div');
                roundDiv.className = 'round';
                roundDiv.innerHTML = `<h3>Round ${round.number}</h3>`;
    
                round.teams.forEach(team => {
                    let teamDiv = document.createElement('div');
                    teamDiv.className = 'team';
                    teamDiv.innerHTML = `<h4>${team.name}</h4><ul>`;
    
                    team.members.forEach(member => {
                        if(member.id == team.winner) {
                            let teamWin = document.createElement('div');
                            teamWin.className = 'win';
                            teamWin.innerHTML += `<p>${member.name}<p>`;
                            teamWin.innerHTML += `<i class='bx bxs-crown' ></i>`;
                            teamDiv.appendChild(teamWin);
                        }
                    });
    
                    teamDiv.innerHTML += `</ul>`;
                    roundDiv.appendChild(teamDiv);
                });
                if (round.teams.length == 0) {
                    roundDiv.innerHTML += `<p> Teams are not created yet </p>`;
                };
    
                tournamentDiv.appendChild(roundDiv);
            });
            container2.appendChild(tournamentDiv);
        });
}

function ToggleFriend(element)
{
    const user = JSON.parse(element.getAttribute('data-user'));
    if (user.is_registered.status == "Add Friend") {
        sendFriendRequest(user.id);
    }
    else if (user.is_registered.status == "Demand sent") {

    }
    else if (user.is_registered.status == "Accept or refuse") {
        ResponseFriendRequest(user.id);
    }
    else if (user.is_registered.status == "Remove Friend") {
        RemoveFriend(user.id);
    }
}

function sendFriendRequest(userId) {
    const token = localStorage.getItem('token');
    const csrf = getCSRFToken();
    fetch(`/api/send_friend_request/${userId}/`, {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf 
            },
            body: JSON.stringify({}),
        })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            window.location.href = `/#profile/`;
        } else {
            alert(data.message);
        }
    })
    .catch(error => console.error('Error:', error));
}

function ResponseFriendRequest(userId) {
    const formContainer = document.getElementById('eventFormContainer');
    const isDisplayed = formContainer.style.display === "block";
    if (!isDisplayed) {
        formContainer.innerHTML += `<div class="form">
            <button data-user='${JSON.stringify(userId)}' onclick="toggleAccepted(this)"> Accept </button>
            <button data-user='${JSON.stringify(userId)}' onclick="toggleRefused(this)"> Refuse </button>
        </div>`
        
        formContainer.style.display = "block";
    } else {
        formContainer.style.display = "none";
        
    }
}

function RemoveFriend(userId) {
    const token = localStorage.getItem('token');
    const csrf = getCSRFToken();
    fetch(`/api/remove_friend/${userId}/`, {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf 
            },
            body: JSON.stringify({}),
        })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            window.location.href = `/#profile/`;
        } else {
            alert(data.message);
        }
    })
}

function toggleAccepted(element) {
    const formContainer = document.getElementById('eventFormContainer');
    const user = JSON.parse(element.getAttribute('data-user'));
    const token = localStorage.getItem('token');
    const csrf = getCSRFToken();
    fetch(`/api/accept_friend_request/${user}/`, {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf 
            },
            body: JSON.stringify({}),
        })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            formContainer.style.display = "none";
            
            window.location.href = `/#profile/`;
        } else {
            alert(data.message);
        }
    })
    .catch(error => console.error('Error:', error));
}

function toggleRefused(element) {
    const formContainer = document.getElementById('eventFormContainer');
    const token = localStorage.getItem('token');
    const csrf = getCSRFToken();
    const user = JSON.parse(element.getAttribute('data-user'));

    fetch(`/api/reject_friend_request/${user}/`, {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf 
            },
            body: JSON.stringify({}),
        })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            formContainer.style.display = "none";
            
            window.location.href = `/#profile/`;
        } else {
            alert(data.message);
        }
    })
    .catch(error => console.error('Error:', error));
}

async function attachFormSubmitHandler3(postUrl) {
    const form = document.getElementById('eventForm');
    const csrf = await getCSRFToken();
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    form.addEventListener('submit', function(e) {
        e.preventDefault();
        fetch(postUrl, {
            method: 'POST',
            body: new FormData(form),
            headers: {
                'Authorization': `Bearer ${token}`,  
                'X-CSRFToken': csrf 
            }
        })
        .then(response => response.json())
        .then(data => {
            if (data.message) {
                toggleForm();
            } else {
                showNotification('❌ Error while modifing', 3);
            }
        })
    });
}
