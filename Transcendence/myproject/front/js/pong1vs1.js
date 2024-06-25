async function loadTournamentPlay(teamsId) {
    const url = `/api/pong/${teamsId}/`;
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
    const teamsData = await response.json();
    startGame1v1(teamsData.teams_data);
}

function startGame1v1(teams) {
    Pong.initialize(teams);
}

async function updatePlayerScores(winner, loser, teams, scorewin, scorelose) {
    const updateUrl = `/api/update_player_scores/`;
    const csrf = await getCSRFToken();
    const token = localStorage.getItem('token');
    if (!token) {
        return;
    }
    fetch(updateUrl, {
        method: 'POST',
        headers: {
            'Authorization': `Bearer ${token}`,  
            'Content-Type': 'application/json',
            'X-CSRFToken': csrf, 
            
        },
        body: JSON.stringify({
            winner: winner,
            loser: loser,
            teams: teams.id,
            score1: scorewin,
            score2: scorelose
        })
    })
    .then(response => response.json())
    .then(data => {
        setTimeout(function () {
            Pong.destroy();
            window.location.href = `#teams_play/${teams.tournament}`; 
        }, 3000);
    })
    .catch(error => console.error('Error updating scores:', error));

}


var DIRECTION = {
    IDLE : 0,
    UP : 1,
    DOWN : 2,
    LEFT : 3,
    RIGHT : 4
};

var rounds =  [1];
var colors = ['#d8a8e6', '#b8a8f8', '#c8a8f8', '#F3BFF1', '#4C75C1'];

var Ball = {
    new: function (incrementedSpeed) {
        return {
            width: 18,
            height: 18,
            x: (this.canvas.width / 2) - 9,
            y: (this.canvas.height / 2) - 9,
            moveX: DIRECTION.IDLE,
            moveY: DIRECTION.IDLE,
            speed: incrementedSpeed || 7
        };
    }
};

var Player = {
    new: function(side, id, name) { 
        return {
            id: id,
            name: name,
            width: 18,
            height: 180,
            x: side === 'left' ? 150 : this.canvas.width - 150,
            y: (this.canvas.height / 2) - 90,
            score: 0,
            total_score: 0,
            move: DIRECTION.IDLE,
            speed: 8
        };
    }
};

var Game = {
    initialize: function (teams) {
        try {
            this.canvas = document.querySelector('canvas');
            this.context = this.canvas.getContext('2d');
    
            this.canvas.width = 1400;
            this.canvas.height = 1000;
    
            this.canvas.style.width = (this.canvas.width / 2) + 'px' ;
            this.canvas.style.height = (this.canvas.height / 2) + 'px' ;
    
            this.player1 = Player.new.call(this, 'left', teams.players_id[0],  teams.players_name[0]);
            this.player2 = Player.new.call(this, 'right', teams.players_id[1], teams.players_name[1]);
            this.ball = Ball.new.call(this);
    
            this.running = this.over = false;
            this.turn = this.player1;
            this.timer = this.round = 0;
            this.color = '#d8a8e6';
    
            this.teams = teams;
            this.rounds = [11];
    
            Pong.menu();
            Pong.listen();
        } catch (error) {}
    },

    endGameMenu: function (winner, loser, score1, score2) {

        Pong.context.font = '45px Courier New';
        Pong.context.fillStyle = this.color;

        Pong.context.fillRect(
            Pong.canvas.width / 2 - 350,
            Pong.canvas.height / 2 - 48,
            700,
            100,
        );

        Pong.context.fillStyle = '#ffffff';

        Pong.context.fillText( winner.name + " is the winner",
            Pong.canvas.width / 2,
            Pong.canvas.height / 2 + 15
        );

        Pong.context.font = '70px Courier New';

        Pong.context.fillText(score1.toString(),
            (Pong.canvas.width / 2) -40,
            950
        );

        Pong.context.fillText("-",
            (Pong.canvas.width / 2) ,
            950
        );

        Pong.context.fillText(score2.toString(),
            (Pong.canvas.width / 2) +40,
            950
        );
        
        updatePlayerScores(winner.id, loser.id, this.teams, score1, score2);
    },

    menu: function () {
        Pong.draw();

        this.context.font = '50px Courier New';
        this.context.fillStyle = this.color;

        this.context.fillRect(
            this.canvas.width / 2 - 350,
            this.canvas / 2 - 48,
            700,
            100,
        );

        this.context.fillStyle = '#ffffff';

        this.context.fillText('Press any key to begin',
            this.canvas.width / 2,
            this.canvas.height / 2 + 15
        );
    },

    update: function () {
        if (!this.over) {
            if (this.ball.x <= 0) Pong._resetTurn.call(this, this.player2, this.player1);
            if (this.ball.x >= this.canvas.width - this.ball.width) Pong._resetTurn.call(this, this.player1, this.player2);
            if (this.ball.y <= 0) this.ball.moveY = DIRECTION.DOWN;
            if (this.ball.y >= this.canvas.height - this.ball.height) this.ball.moveY = DIRECTION.UP;

            if (this.player1.move === DIRECTION.UP) this.player1.y -= this.player1.speed;
            else if (this.player1.move === DIRECTION.DOWN) this.player1.y += this.player1.speed;

            if (this.player2.move === DIRECTION.UP) this.player2.y -= this.player2.speed;
            else if (this.player2.move === DIRECTION.DOWN) this.player2.y += this.player2.speed;

            if (Pong._turnDelayIsOver.call(this) && this.turn) {
                this.ball.moveX = this.turn === this.player1 ? DIRECTION.LEFT : DIRECTION.RIGHT;
                this.ball.moveY = [DIRECTION.UP, DIRECTION.DOWN][Math.round(Math.random())];
                this.turn = null;
            }

            
            if (this.ball.moveY === DIRECTION.UP) this.ball.y -= (this.ball. speed / 1.5);
            else if (this.ball.moveY == DIRECTION.DOWN) this.ball.y += (this.ball.speed / 1.5);
            if (this.ball.moveX === DIRECTION.LEFT) this.ball.x -= this.ball.speed;
            else if (this.ball.moveX === DIRECTION.RIGHT) this.ball.x += this.ball.speed;

            if (this.player1.y <= 0) this.player1.y = 0;
            else if (this.player1.y >= (this.canvas.height - this.player1.height)) this.player1.y = (this.canvas.height - this.player1.height);

            if (this.player2.y <= 0) this.player2.y = 0;
            else if (this.player2.y >= (this.canvas.height - this.player2.height)) this.player2.y = (this.canvas.height - this.player2.height);


            if (this.ball.x - this.ball.width <= this.player1.x && this.ball.x >= this.player1.x - this.player1.width) {
                if (this.ball.y <= this.player1.y + this.player1.height && this.ball.y + this.ball.height >= this.player1.y) {
                    this.ball.x = (this.player1.x + this.ball.width);
                    this.ball.moveX = DIRECTION.RIGHT;
                }
            }

            if (this.ball.x - this.ball.width <= this.player2.x && this.ball.x >= this.player2.x - this.player2.width) {
                if (this.ball.y <= this.player2.y + this.player2.height && this.ball.y + this.ball.height >= this.player2.y) {
                    this.ball.x = (this.player2.x - this.ball.width);
                    this.ball.moveX = DIRECTION.LEFT;
                }
            }	
        }


        if (this.player1.score >= this.rounds[this.round]) {
            this.over = true;
            const score1 = this.player1.score;
            const score2 = this.player2.score;
            const winner = this.player1;
            const loser = this.player2;
            setTimeout(function () { Pong.endGameMenu(winner, loser, score1, score2); }, 1000);
        } else if (this.player2.score >= this.rounds[this.round]) {
            this.over = true;
            const score1 = this.player1.score;
            const score2 = this.player2.score;
            const winner = this.player2;
            const loser = this.player1;
            setTimeout(function () { Pong.endGameMenu(winner, loser, score2, score1); }, 1000);
        }
    },

    draw: function () {
        this.context.clearRect(
            0,
            0,
            this.canvas.width,
            this.canvas.height
        );

        this.context.fillStyle = this.color;

        this.context.fillRect (
            0,
            0,
            this.canvas.width,
            this.canvas.height
        );

        this.context.fillStyle = '#ffffff';

        this.context.fillRect(
            this.player1.x,
            this.player1.y,
            this.player1.width,
            this.player1.height
        );

        this.context.fillRect(
            this.player2.x,
            this.player2.y,
            this.player2.width,
            this.player2.height
        );

        if (Pong._turnDelayIsOver.call(this)) {
            this.context.fillRect(
                this.ball.x,
                this.ball.y,
                this.ball.width,
                this.ball.height
            );
        }


        this.context.beginPath();
        this.context.setLineDash([7, 15]);
        this.context.moveTo((this.canvas.width / 2), this.canvas.height - 140);
        this.context.lineTo((this.canvas.width / 2), 140);
        this.context.lineWidth = 10;
        this.context.strokeStyle = '#ffffff';
        this.context.stroke();

        this.context.font = '100px Courier New';
        this.context.textAlign = 'center';

        this.context.fillText(
            this.player1.score.toString(),
            (this.canvas.width / 2) - 300,
            200
        );

        this.context.fillText(
            this.player2.score.toString(),
            (this.canvas.width / 2) + 300,
            200
        );

        this.context.font = '30px Courier New';

        this.context.fillText(
            'Round ' + (Pong.round + 1),
            (this.canvas.width / 2),
            35
        );

        this.context.font = '45px Courier New';

        this.context.fillText(
            this.player1.name,
            (this.canvas.width / 2) - 500,
            100
        );

        this.context.fillText(
            this.player2.name,
            (this.canvas.width / 2) + 500,
            100
        );

        this.context.font = '40px Courier';

        this.context.fillText(
            rounds[Pong.round] ? rounds[Pong.round] : rounds[Pong.round - 1],
            (this.canvas.width / 2),
            100
        );
    },

    loop: function () {
        Pong.update();
        Pong.draw();

        if (!Pong.over) requestAnimationFrame(Pong.loop);
    },

    destroy: function() {
        if (this.animationFrameId) {
            cancelAnimationFrame(this.animationFrameId);
        }

        document.removeEventListener('keydown', this.keydownHandler);
        document.removeEventListener('keyup', this.keyupHandler);


        if (this.canvas) {
            this.canvas.width = this.canvas.width;
            this.canvas.style.display = 'none';
        }
    },

    listen: function () {
        this.keydownHandler = function (key) {
            if (Pong.running === false) {
                Pong.running = true;
                Pong.animationFrameId = window.requestAnimationFrame(Pong.loop);
            }
    
            switch (key.keyCode) {
                case 87:
                    Pong.player1.move = DIRECTION.UP;
                    key.preventDefault();
                    break;
                case 83:
                    Pong.player1.move = DIRECTION.DOWN;
                    key.preventDefault();
                    break;
                case 38:
                    Pong.player2.move = DIRECTION.UP;
                    key.preventDefault();
                    break;
                case 40:
                    Pong.player2.move = DIRECTION.DOWN;
                    key.preventDefault();
                    break;
            }
        };
    
        this.keyupHandler = function (key) {
            switch (key.keyCode) {
                case 87:
                case 83:
                    Pong.player1.move = DIRECTION.IDLE;
                    key.preventDefault();
                    break;
                case 38:
                case 40:
                    Pong.player2.move = DIRECTION.IDLE;
                    key.preventDefault();
                    break;
            }
        };
    
        document.addEventListener('keydown', this.keydownHandler);
        document.addEventListener('keyup', this.keyupHandler);
    },

    _resetTurn: function( victor, loser) {
        this.ball = Ball.new.call(this, this.ball.speed);
        this.turn = loser;
        this.timer = (new Date()).getTime();

        victor.score++;
    },

    _turnDelayIsOver: function () {
        return((new Date()).getTime() - this.timer >= 1000);
    },

    _generateRoundColor: function() {
        var newColor = colors[Math.floor(Math.random() * colors.length)];
        if (newColor === this.color) return Pong._generateRoundColor();
        return newColor;
    }
};

var Pong = Object.assign({}, Game);