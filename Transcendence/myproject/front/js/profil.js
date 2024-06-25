function fetchUser() {
    const accessToken = localStorage.getItem('token'); 
    if (!accessToken) {
        return;
    }
    fetch('/api/profil', {
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
        displayUser(data.user_data);
    })
    .catch(error => {
        console.error('Erreur:', error);
    });
}

async function displayUser(user) {
    const profileDiv = document.getElementById('profile-div');
    profileDiv.innerHTML = `<div id="container_profil" class="container_profil"> <div class="profile-info" id="profile-info"></div> </div> <div id="container_profil2" class="container_profil2"></div> <div id="container_profil3" class="container_profil3"></div>`;
    const container = document.getElementById('profile-info');
    container.innerHTML = `<h1> ${user.username} </h1>`;
    container.innerHTML = `<div class="profil" > <img src=${user.img} class="profile-image"> <h1> ${user.username} </h1> <div onclick="ToggleMod()" class="modify-profile"> <p> Modify profil </p> </div> </div> <div class="info">
                <div class="details" >
                    <p>MMR: ${user.score}</p>
                </div>
                <div class="details" >
                    <p>Games played: ${user.games_played}</p>
                </div>
                <div class="details" >
                    <p>Games lost: ${user.games_lost}</p>
                </div>
                <div class="details" >
                    <p>Games won: ${user.games_won}</p>
                </div>
        </div>`;
        const container2 = document.getElementById('container_profil2');
        user.tournaments.forEach(tournament => {
            let tournamentDiv = document.createElement('div');
            tournamentDiv.className = 'tournament';
            tournamentDiv.innerHTML = `<h2>${tournament.name} | ${tournament.date}</h2>`;
    
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
        if(user.friends.length > 0) {
            const container3 = document.getElementById('container_profil3');
            const friendsDiv = document.createElement('div');
            friendsDiv.className = 'friends';
            friendsDiv.innerHTML = `<h2>Friends</h2>`;
            user.friends.forEach(friend => {
                let friendDiv = document.createElement('div');
                friendDiv.className = 'friend';
                friendDiv.innerHTML = `<p>${friend}</p>`;
                friendsDiv.appendChild(friendDiv);
            });
            container3.appendChild(friendsDiv);
        }
}

async function ToggleMod(){
    url = "/api/modify/"
    const container_profil = document.getElementById('container_profil');
    const profileInfo = document.getElementById('profile-info');
    profileInfo.classList.add('fade-out');
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    fetch(url, {
        method: 'GET',
        headers: {
            'Authorization': `Bearer ${token}`,  
            'Content-Type': 'application/json' 
        }
    })
    .then(response => response.json())
    .then(data => {
        container_profil.innerHTML = generateFormHtmlProfile(data.form_data);
        document.getElementById('current-profile-pic').addEventListener('mouseover', function() {
            document.getElementById('img-profile').classList.remove('hidden');
        });
        document.getElementById('current-profile-pic').addEventListener('mouseout', function() {
            document.getElementById('img-profile').classList.add('hidden');
        });
        document.querySelector('.profile-pic-container').addEventListener('click', function() {
            document.getElementById('img-profile').click();
        });
        document.getElementById('img-profile').addEventListener('change', function(event) {
            if (event.target.files && event.target.files[0]) {
                var reader = new FileReader();
                reader.onload = function(e) {
                    document.getElementById('current-profile-pic').src = e.target.result;
                }
                reader.readAsDataURL(event.target.files[0]);
            }
        });
    });
}

function generateFormHtmlProfile(formData) {
    var formHtml = `
    <div class="modify-profile-form fade-in">
        <h2>Modify Profile</h2>
        <form id="profileForm" class="modify-profile-form">
            <div class="modify-profile-grid">
                <div class="left-section">
                    <p>Profile Picture</p>
                    <div class="text profile-pic-container">
                        <img src="${formData.image_link}" id="current-profile-pic" class="current-profile-pic">
                        <input id="img-profile" type="file" name="img-profile" class="hidden">
                        <div class="overlay">
                            <i class='bx bxs-pencil'></i>
                        </div>
                    </div>
                </div>
                <div class="center-section">
                    <div>
                        <p>Username</p>
                        <div class="text">
                            <input id="username-profile" type="text" name="username" value="${formData.username}" ${formData.is_oauth_user ? 'disabled' : ''}>
                        </div>
                    </div>
                    <div>
                        <p>Email</p>
                        <div class="text">
                            <input id="email-profile" type="email" name="email" value="${formData.email}" ${formData.is_oauth_user ? 'disabled' : ''}>
                        </div>
                    </div>
                    <div>
                        <p>OAuth User</p>
                        <div class="text">
                            <input id="oauth-user" type="checkbox" name="oauth-user" ${formData.is_oauth_user ? 'checked' : ''} disabled>
                        </div>
                    </div>
                </div>
                ${!formData.is_oauth_user ? `
                    <div class="right-section">
                        <p>2FA Status</p>
                        <div class="text">
                            <button type="button" onclick="enable2FAMod(${formData.two_factor_enabled})">${formData.two_factor_enabled ? 'Disable 2FA' : 'Enable 2FA'}</button>
                        </div>
                    </div>
                    ` : ''}
            </div>
        </form>
        <div class="btn-div">
            <button type="button" onclick="sendModification()" class="btn">Save</button>
        </div>
    </div>`;
    return formHtml;
}

async function sendModification() {
    var username = document.getElementById('username-profile').value;
    var email = document.getElementById('email-profile').value;
    var img = document.getElementById('img-profile').files[0];

    const formData = new FormData();
    formData.append('username', username);
    formData.append('email', email);
    if (img) {
        formData.append('img', img);
    }

    const csrf = await getCSRFToken();
    const token = localStorage.getItem('token');
    if (!token) {
        logout();
        return;
    }

    try {
        const response = await fetch('/api/modify/', {
            method: 'POST',
            body: formData,
            headers: {
                'Authorization': `Bearer ${token}`,
                'X-CSRFToken': csrf,
            }
        });
        const data = await response.json();
        if (response.ok) {
            if (data.messages) {
                showNotification('✅ ' + data.messages, 2);
                setTimeout(() => {
                    loadUser();
                    fetchUser();
                }, 1500);
            } else {
                showNotification('❌ ' + data.errors, 3);
            }
        } else {
            showNotification('❌ An internal error occurred:' + data.errors, 3);
        }
    } catch (error) {
        showNotification('❌ An internal error occurred: ' + error.message, 3);
    }
}

async function enable2FAMod(faStatus) {
    const accessToken = localStorage.getItem('token');
    const csrf = await getCSRFToken();

    try {
        const response = await fetch('/api/2fa/enable/', {
            method: 'POST',
            headers: {
                'Authorization': `Bearer ${accessToken}`,
                'X-CSRFToken': csrf,
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                'enable': faStatus,
            }),
        });

        if (response.ok) {
            const data = await response.json();
            if(data.detail) {
                showNotification('✅ ' + data.detail, 2);
                fetchUser();
                return;
            } else {
                displayQRCodeMod(data);
            }
        } else {
            showNotification('❌ Error enabling 2FA: ' + response.statusText, 3);
        }
    } catch (error) {
        showNotification('❌ An error occurred: ' + error.message, 3);
    }
}

function displayQRCodeMod(response) {
    const qrCodeBase64 = response.qr_code_base64;
    const container_profile = document.getElementById('container_profil');
    container_profile.innerHTML = `<div id="qrCodeContainer" class="qrCodeContainer"></div>`;
    container_profile.innerHTML += `
    <div id="otpContainer" class="otpContainer">
        <input type="text" id="otpInput" placeholder="Enter OTP code">
        <button onclick="verifyOTP()">Verify</button>
    </div>`;
    container_profile.style.borderRadius = '0px';
    qrCodeContainer.innerHTML = `<img src="data:image/png;base64,${qrCodeBase64}" alt="QR Code">`;
    qrCodeContainer.style.display = 'block';
    qrCodeContainer.style.margin = '50px';
}

async function verifyOTP() {
    const formData = new FormData();
    const otpCode = document.getElementById('otpInput').value;
    formData.append('otp_code', otpCode);
    const accessToken = localStorage.getItem('token');
    const csrf = await getCSRFToken();

    try {
        const response = await fetch('/api/2fa/verify/', {
            method: 'POST',
            body: formData,
            headers: {
                'Authorization': `Bearer ${accessToken}`,
                'X-CSRFToken': csrf,
            },
        });

        if (response.ok) {
           showNotification('✅ 2FA enabled successfully.', 2);
           setTimeout(() => {
                fetchUser();
           }, 1500);
        } else {
            showNotification('❌ OTP Code invalid.', 3);
        }
    } catch (error) {
        showNotification('❌ Error occured while checking OTP code', 3);
    }
}