async function loadTournamentDetails(tournamentId) {
    const url = `/api/tour_details/${tournamentId}/`; 
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
    const tournamentData = await response.json();
    displayTournamentDetails(tournamentData.tournament_data, tournamentData.count, tournamentData.form_data[0]);
    attachFormSubmitHandler2(url)
}


function displayTournamentDetails(tournament, count, ) {
    const details = tournament[0]
    const container = document.getElementById('available');
    container.innerHTML = `<h1>${details.name} tournament</h1>`;
    
    const tournamentInfo = document.createElement('div');
    tournamentInfo.className = 'details-info';
    tournamentInfo.innerHTML = `
        <div class="details-info-mod">
            <p>Peoples required: ${details.numb_p}</p>
        </div>
        <div class="details-info-mod">
            <p>Slots already taken: ${count[0].count}</p>
        </div>
    `;

   const tournamentForm = document.createElement('form');
   tournamentForm.id = "teamForm";
   tournamentForm.method = "post";
   tournamentForm.className = "teamForm";

   tournamentForm.innerHTML = 
   `<div class="team">
						<div class="aff" >
							<input type="text"  id="player" name="player" placeholder="Nickname " class="player" autocomplete="off">
							<div class="player-completion" ></div>
						</div>
					</div>`;

   const submitButton = document.createElement('button');
   submitButton.type = 'submit';
   submitButton.textContent = 'Join Tournament';
   tournamentForm.appendChild(submitButton);

   container.appendChild(tournamentInfo);
   tournamentInfo.appendChild(tournamentForm);
}

async function attachFormSubmitHandler2(postUrl) {
    const form = document.getElementById('teamForm');
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
                if (data.success) {
                    showNotification('✅ ' + data.message, 2);
                    window.location.href = "#tournament";
                } else {
                    showNotification('❌ ' + data.message, 3);
                }
            } else {
                showNotification('❌ Error while adding event', 3);
            }
        })
    });
}