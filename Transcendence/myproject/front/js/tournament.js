function toggleForm() {
    const url = "/api/create_tour/";
    const formContainer = document.getElementById('eventFormContainer');
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
        const isDisplayed = formContainer.style.display === "block";
        if (!isDisplayed) {
            const formHtml = generateFormHtml(data.form_data);
            formContainer.innerHTML = formHtml;
            formContainer.style.display = "block";
            const modalBackdrop = createModalBackdrop();
            document.querySelector('.tournament').appendChild(modalBackdrop);
            document.body.classList.add('modal-open');
            
            const closeModalButton = document.querySelector('.close-modal');
            if (closeModalButton) {
                closeModalButton.addEventListener('click', function() {
                    toggleForm();
                });
            }
        } else {
            formContainer.style.display = "none";
            document.body.classList.remove('modal-open');
            const modalBackdrop = document.querySelector('.modal-backdrop-tournament');
            if (modalBackdrop) {
                modalBackdrop.parentNode.removeChild(modalBackdrop);
            }
        }
    })
    .catch(error => {
        console.error('Error fetching form data:', error);
    });
}


function createModalBackdrop() {
    const modalBackdrop = document.createElement('div');
    modalBackdrop.classList.add('modal-backdrop-tournament');
    modalBackdrop.classList.add('fade-in');
    return modalBackdrop;
}

function generateFormHtml(formData) {
    let formHtml = `<div class="modal-box fade-in"><h2>Add Tournament</h2><form id="eventForm" class="eventForm"><div class="containForm">`;
    for (const key in formData.fields) {
        if (formData.fields.hasOwnProperty(key)) {
            const info = formData.fields[key];
            formHtml += `<div><p>${info['label']}</p><div class="text"><input id="${key}" type="${info['type']}" name="${key}" required></div></div>`;
        }
    }
    formHtml += `</div><div class="btn-div"><button type="button" class="btn" onclick="sendCreateTour()">Add</button></div>`;
    formHtml += `<span class="close-modal">&times;</span>`;
    formHtml += `</form></div>`;
    return formHtml;
}

async function sendCreateTour() {
    const form = document.getElementById('eventForm');
    const csrf = await getCSRFToken();
    const date = new Date();
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');
    const formattedDate = `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    const formSend = new FormData(form);
    formSend.append('start', formattedDate);
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    try {
        const response = await fetch('/api/create_tour/', {
            method: 'POST',
            body: formSend,
            headers: {
                'Authorization': `Bearer ${token}`,  
                'X-CSRFToken': csrf
            }
        })
        .then(response => response.json())
        .then(data => {
            if (data.message) {
                showNotification('✅ ' + data.message, 2);
                toggleForm();
                loadTournaments();
            } else {
                showNotification('❌ ' + data.errors, 3);
                toggleForm();
            }
        })
    } catch (error) {
        showNotification('❌ Error while adding the tournament: ', error);
    }
}

window.addEventListener('hashchange', function() {
  if (window.location.hash === '#tournament') {
    loadTournaments();
  }
});

window.addEventListener('load', function() {
    if (window.location.hash === '#tournament') {
        loadTournaments();
    }
});

function loadTournaments() {
    try {
        const xhr = new XMLHttpRequest();
        xhr.open('GET', '/api/tournament/', true);
      
        const accessToken = localStorage.getItem('token');
        xhr.setRequestHeader('Authorization', `Bearer ${accessToken}`);
      
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    const response = JSON.parse(xhr.responseText);
                    displayTournaments(response.tournaments_data, response.is_already_engaged);
                } else {
                    showNotification('❌ Error while loading tournament', 3);
                }
            }
        };
      
        xhr.send();
    } catch (error) {}
}


function displayTournaments(tournaments, already) {
    const registeredContainer = document.getElementById('registered-tour');
    const availableContainer = document.getElementById('available-tour');

    registeredContainer.innerHTML = '';
    availableContainer.innerHTML = '';

    const registeredTournaments = tournaments.filter(t => t.is_registered);
    const availableTournaments = tournaments.filter(t => !t.is_registered);

    if (registeredTournaments.length > 0) {
        registeredTournaments.forEach(function(tournament) {
            const registeredTournament = document.getElementById('registered-tournament');
            registeredTournament.classList.remove('hidden');
            const tournamentHTML = createTournamentHTML(tournament, true, already);
            registeredContainer.innerHTML += tournamentHTML;
        });
    }

    if (availableTournaments.length > 0) {
        availableTournaments.forEach(function(tournament) {
            const tournamentHTML = createTournamentHTML(tournament, false, already);
            availableContainer.innerHTML += tournamentHTML;
        });
    } else {
        availableContainer.innerHTML = '<p>No tournament available.</p>';
    }
}

function createTournamentHTML(tournament, isRegistered, already) {
    let inscriptionButtonHTML = '';
    let startText = 'Need to be full to start';
    if (tournament.full) {
        inscriptionButtonHTML = `<a href="#teams_play/${tournament.id}">Tournament full, see the teams.</a>`;
        startText = 'Tournament is full! Start the game!';
    } else if (isRegistered) {
        inscriptionButtonHTML = `<a disabled="disabled">Already Joined.</a>`;
    } else if (already) {
        inscriptionButtonHTML = `<a disabled="disabled">You have already joined another tournament.</a>`;
    } else {
        inscriptionButtonHTML = `<a href="#details/${tournament.id}">Join</a>`;
    }

    return `
        <div class="tournois-info">
            <img src="media/tournament.jpg" alt="Tournament Image">
            <div class="tournois-details">
                <p class="tournament-name">Name: ${tournament.name}</p>
                <p>Capacity: ${tournament.numb_p}</p>
                <p>Slots available: ${tournament.slots}</p>
                <p class="tournament-time">${startText}</p>
                <div class="inscription-button">
                    ${inscriptionButtonHTML}
                </div>
            </div>
        </div>
    `;
}


