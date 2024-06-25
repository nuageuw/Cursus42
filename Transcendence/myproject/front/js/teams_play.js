async function loadTournamentTeams(tournamentId) {
    const url = `/api/teams_play/${tournamentId}/`;
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
    displayTournamentTeams(tournamentData);
}

function displayTournamentTeams(tournaments) {
    const container = document.getElementById('available-tour');
    const tournament = tournaments.tournament_data;
    const userId = localStorage.getItem('userId');
    container.innerHTML = `<h1>Tournois ${tournament.name}</h1>`;
    container.innerHTML += `<h2>Round ${tournament.round}</h2>`;
    tournament.teams.forEach(function(teams) {
        const tournamentInfo = document.createElement('div');
        tournamentInfo.classList.add('tournois-play');
        tournamentInfo.innerHTML = 
        `
            <p>Current rounds: </p>
            </br>
            <p>${teams.name}</p>
        `;
        if (teams.is_co) {
            tournamentInfo.innerHTML += `
                <input type="password" id="password" name="password" placeholder="Password of non host player" class="player" autocomplete="off">
                <button id="sub" type="button">Play</button>
            `;
            container.appendChild(tournamentInfo);

            const button = document.getElementById('sub');
            button.addEventListener('click', function(e) {
                e.preventDefault();
                attachFormSubmitHandler4(teams.id);
            });
        } else {
            container.appendChild(tournamentInfo);
        }
    });
    createBracket(tournaments);
    sendNotificationOpponent(tournaments.tournament_data, userId);
}

async function attachFormSubmitHandler4(teams) {
    const csrf = await getCSRFToken();
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    var password = document.getElementById("password").value;
    var formData = new FormData();
    formData.append("mdp", password);
    fetch(`/api/check_pw/${teams}/`, {
        method: 'POST',
        body: formData,
        headers: {
            'Authorization': `Bearer ${token}`,
            'X-CSRFToken': csrf
        }
    })
    .then(response => response.json())
    .then(data => {
        if (data.message) {
            if (data.success) {
                window.location.href = `#pong/${teams}`;
            } else {
                showNotification(data.message, 3);
            }
        } else {
            showNotification('Error while adding event', 3);
        }
    })
    .catch(error => console.error('Error:', error));
}

function createBracket(data) {
    const bracketContainer = document.getElementById('bracket');
    const allDataTour = data.all_data_tour;
        const roundData1 = allDataTour.find(item => item.round === 1);
        var roundsCount = 0;
        roundData1.teams.forEach(team => {
            roundsCount++;
        });
        for (var i = 1; i <= roundsCount; i++) {
            const roundData = allDataTour.find(item => item.round === i);

            if (roundData) {
                const roundDiv = document.createElement('div');
                roundDiv.classList.add('round');
                roundData.teams.forEach(team => {
                    const matchDiv = document.createElement('div');
                    matchDiv.classList.add('match');

                    team.players_name.forEach((playerName) => {
                        const playerBox = document.createElement('div');
                        if (team.winner === playerName) {
                            var score = team.scorewin;
                            playerBox.classList.add('win-color');
                        } else if (team.winner === null) {
                            var score = 0;
                            playerBox.classList.add('win-color');
                        } else {
                            var score = team.scorelose;
                            playerBox.classList.add('lose-color');
                        }
                        playerBox.textContent = `${playerName} score: ${score}`;

                        matchDiv.appendChild(playerBox);
                    });

                    roundDiv.appendChild(matchDiv);
                });

                bracketContainer.appendChild(roundDiv);
            } else {
                const roundDiv = document.createElement('div');
                roundDiv.classList.add('round');

                const matchDiv = document.createElement('div');
                matchDiv.classList.add('match');

                const waitingBox = document.createElement('div');
                waitingBox.classList.add('player-box');
                waitingBox.classList.add('win-color');
                waitingBox.textContent = 'Wainting end of previous round';

                matchDiv.appendChild(waitingBox);
                matchDiv.appendChild(document.createElement('div')).classList.add('connector');
                matchDiv.appendChild(waitingBox.cloneNode(true));

                roundDiv.appendChild(matchDiv);
                bracketContainer.appendChild(roundDiv);
            }
        }

        if (data.tournament_data.finish) {
            const winnerContain = allDataTour.find(item => item.round === i - 1)
            const winner = winnerContain.teams[0].winner;
            const winnerDiv = document.createElement('div');
            winnerDiv.classList.add('round');
            const winnerBox = document.createElement('div');
            winnerBox.classList.add('winner-box');
            winnerBox.textContent = "Winner: " + winner + " ";
            winnerBox.innerHTML += `<i class='bx bxs-crown' ></i>`;

            winnerDiv.appendChild(winnerBox);
            bracketContainer.appendChild(winnerDiv);
        } else {
            const winnerDiv = document.createElement('div');
            winnerDiv.classList.add('round');
            const winnerBox = document.createElement('div');
            winnerBox.classList.add('winner-box');
            winnerBox.textContent = 'Winner'; 

            winnerDiv.appendChild(winnerBox);
            bracketContainer.appendChild(winnerDiv);
        }
}

function sendNotificationOpponent(tournamentData, currentUserId) {
    const round = tournamentData.round;
    if (round !== "1") {
        return;
    }
    if (!currentUserId) {
        return;
    }

    const teams = tournamentData.teams;
    var opponentUserId = null;

    teams.forEach(team => {
        if (team.players_id[0] == currentUserId) {
            opponentUserId = team.players_id[1];
            localStorage.setItem('recipientId', team.players_id[1]);
        } else if (team.players_id[1] == currentUserId) {
            opponentUserId = team.players_id[0];
            localStorage.setItem('recipientId', team.players_id[0]);
        }
    });

    if (opponentUserId) {
        const message = `Waiting you to start tournament: ${tournamentData.name}.`;
        sendMessage(message, opponentUserId);
    }
}
