var rounds = [5];


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
    new: function(side) {
        return {
            width: 18,
            height: 180,
            x: side === 'left' ? 150 : this.canvas.width - 150,
            y: (this.canvas.height / 2) - 90,
            score: 0,
            total_score: 5,
            move: DIRECTION.IDLE,
            speed: 8
        };
    }
};

var Ai = {
    new: function(side) {
        return {
            width: 18,
            height: 180,
            x: side === 'left' ? 150 : this.canvas.width - 150,
            y: (this.canvas.height / 2) - 35,
            score: 0,
            move: DIRECTION.IDLE,
            speed: 8
        };
    }
};

var GameIA = {
    initialize: function () {
        try {
            this.canvas = document.querySelector('canvas');
            this.context = this.canvas.getContext('2d');
    
            this.canvas.width = 1400;
            this.canvas.height = 1000;
    
            this.canvas.style.width = (this.canvas.width / 2) + 'px';
            this.canvas.style.height = (this.canvas.height / 2) + 'px';
    
            this.player = Ai.new.call(this, 'left');
            this.ai = Ai.new.call(this, 'right');
            this.ball = Ball.new.call(this);
    
            this.ai.speed = 8;
            this.running = this.over = false;
            this.turn = this.ai;
            this.timer = this.round = 0;
            this.color = '#d8a8e6';
    
            this.rounds = [11];
    
            PongIA.menu();
            PongIA.listen();
        } catch (error) {}
    },

    endGameMenu: function (text) {
        PongIA.context.font = '45px Courier New';
        PongIA.context.fillStyle = this.color;

        PongIA.context.fillRect(
            PongIA.canvas.width / 2 - 350,
            PongIA.canvas.height / 2 - 48,
            700,
            100,
        );

        PongIA.context.fillStyle = '#ffffff';

        PongIA.context.fillText(text,
            PongIA.canvas.width / 2,
            PongIA.canvas.height / 2 + 15
        );

        setTimeout(function () {
            PongIA = Object.assign({}, GameIA);
            PongIA.initialize();
        }, 3000);
    },

    menu: function () {
        PongIA.draw();

        this.context.font = '50px Courier New';
        this.context.fillStyle = this.color;

        this.context.fillRect(
            this.canvas.width / 2 - 350,
            this.canvas.height / 2 - 48,
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
            if (this.ball.x <= 0) PongIA._resetTurn.call(this, this.ai, this.player);
            if (this.ball.x >= this.canvas.width - this.ball.width) PongIA._resetTurn.call(this, this.player, this.ai);
            if (this.ball.y <= 0) this.ball.moveY = DIRECTION.DOWN;
            if (this.ball.y >= this.canvas.height - this.ball.height) this.ball.moveY = DIRECTION.UP;

            if (this.player.move === DIRECTION.UP) this.player.y -= this.player.speed;
            else if (this.player.move === DIRECTION.DOWN) this.player.y += this.player.speed;

            if (PongIA._turnDelayIsOver.call(this) && this.turn) {
                this.ball.moveX = this.turn === this.player ? DIRECTION.LEFT : DIRECTION.RIGHT;
                this.ball.moveY = [DIRECTION.UP, DIRECTION.DOWN][Math.round(Math.random())];
                this.turn = null;
            }

            if (this.player.y <= 0) this.player.y = 0;
            else if (this.player.y >= (this.canvas.height - this.player.height)) this.player.y = (this.canvas.height - this.player.height);
            
            if (this.ball.moveY === DIRECTION.UP) this.ball.y -= (this.ball.speed / 1.5);
            else if (this.ball.moveY == DIRECTION.DOWN) this.ball.y += (this.ball.speed / 1.5);
            if (this.ball.moveX === DIRECTION.LEFT) this.ball.x -= this.ball.speed;
            else if (this.ball.moveX === DIRECTION.RIGHT) this.ball.x += this.ball.speed;

            if (this.ai.y > this.ball.y - (this.ai.height / 2)) {
                if (this.ball.moveX === DIRECTION.RIGHT) this.ai.y -= this.ai.speed / 1.5;
                else this.ai.Y -= this.ai.speed / 4;
            }
            if (this.ai.y < this.ball.y - (this.ai.height / 2)) {
                if (this.ball.moveX === DIRECTION.RIGHT) this.ai.y += this.ai.speed / 1.5;
                else this.ai.Y += this.ai.speed / 4;
            }

            if (this.ai.y >= this.canvas.height - this.ai.height) this.ai.y = this.canvas.height - this.ai.height;
            else if (this.ai.y <= 0) this.ai.y = 0;

            if (this.ball.x - this.ball.width <= this.player.x && this.ball.x >= this.player.x - this.player.width) {
                if (this.ball.y <= this.player.y + this.player.height && this.ball.y + this.ball.height >= this.player.y) {
                    this.ball.x = (this.player.x + this.ball.width);
                    this.ball.moveX = DIRECTION.RIGHT;
                }
            }

            if (this.ball.x - this.ball.width <= this.ai.x && this.ball.x >= this.ai.x - this.ai.width) {
                if (this.ball.y <= this.ai.y + this.ai.height && this.ball.y + this.ball.height >= this.ai.y) {
                    this.ball.x = (this.ai.x - this.ball.width);
                    this.ball.moveX = DIRECTION.LEFT;
                }
            }	
        }

        if (this.player.score >= this.rounds[this.round]) {
            this.over = true;
            setTimeout(function () { PongIA.endGameMenu('Winner!'); }, 1000);
        } else if (this.ai.score >= this.rounds[this.round]) {
            this.over = true;
            setTimeout(function () { PongIA.endGameMenu('Game Over'); }, 1000);
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

        this.context.fillRect(
            0,
            0,
            this.canvas.width,
            this.canvas.height
        );

        this.context.fillStyle = '#ffffff';

        this.context.fillRect(
            this.player.x,
            this.player.y,
            this.player.width,
            this.player.height
        );

        this.context.fillRect(
            this.ai.x,
            this.ai.y,
            this.ai.width,
            this.ai.height
        );

        if (PongIA._turnDelayIsOver.call(this)) {
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
            this.player.score.toString(),
            (this.canvas.width / 2) - 300,
            200
        );

        this.context.fillText(
            this.ai.score.toString(),
            (this.canvas.width / 2) + 300,
            200
        );

        this.context.font = '30px Courier New';

        this.context.fillText(
            'Round ' + (PongIA.round + 1),
            (this.canvas.width / 2),
            35
        );

        this.context.font = '40px Courier';

        this.context.fillText(
            this.rounds[PongIA.round] ? this.rounds[PongIA.round] : this.rounds[PongIA.round - 1],
            (this.canvas.width / 2),
            100
        );
    },

    loop: function () {
        PongIA.update();
        PongIA.draw();

        if (!PongIA.over) requestAnimationFrame(PongIA.loop);
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
            if (PongIA.running === false) {
                PongIA.running = true;
                this.animationFrameId = window.requestAnimationFrame(PongIA.loop);
            }
    
            if (key.keyCode === 38 || key.keyCode === 87) {
                key.preventDefault();
                PongIA.player.move = DIRECTION.UP;
            }
    
            if (key.keyCode === 40 || key.keyCode === 83) {
                key.preventDefault();
                PongIA.player.move = DIRECTION.DOWN;
            }
        };
    
        this.keyupHandler = function (key) {
            if (key.keyCode === 38 || key.keyCode === 40 || key.keyCode === 87 || key.keyCode === 83) {
                key.preventDefault();
            }
            PongIA.player.move = DIRECTION.IDLE;
        };
        document.addEventListener('keydown', this.keydownHandler);
        document.addEventListener('keyup', this.keyupHandler);
    },

    _resetTurn: function (victor, loser) {
        this.ball = Ball.new.call(this, this.ball.speed);
        this.ball.x = this.canvas.width / 2 - this.ball.width / 2;
        this.ball.y = this.canvas.height / 2 - this.ball.height / 2;
        this.turn = loser;
        this.timer = (new Date()).getTime();
    
        victor.score++;
    },

    _turnDelayIsOver: function () {
        return ((new Date()).getTime() - this.timer >= 1000);
    },

    _generateRoundColor: function () {
        var newColor = colors[Math.floor(Math.random() * colors.length)];
        if (newColor === this.color) return PongIA._generateRoundColor();
        return newColor;
    }
};

var DIRECTION = { UP: 0, DOWN: 1, LEFT: 2, RIGHT: 3, IDLE: 4 };
var colors = ['#d8a8e6', '#e6d8a8', '#a8d8e6'];



var GameT = {
    initialize: function () {
        try {
            this.canvas = document.querySelector('canvas');
            this.context = this.canvas.getContext('2d');
    
            this.canvas.width = 1400;
            this.canvas.height = 1000;
    
            this.canvas.style.width = (this.canvas.width / 2) + 'px' ;
            this.canvas.style.height = (this.canvas.height / 2) + 'px' ;
    
            this.player1 = Player.new.call(this, 'left');
            this.player2 = Player.new.call(this, 'right');
            this.ball = Ball.new.call(this);
    
            this.running = this.over = false;
            this.turn = this.player1;
            this.timer = this.round = 0;
            this.color = '#d8a8e6';
            this.rounds = [11];
    
            PongT.menu();
            PongT.listen();
        } catch (error) {}
    },

    endGameMenu: function (text, score1, score2) {

        PongT.context.font = '45px Courier New';
        PongT.context.fillStyle = this.color;

        PongT.context.fillRect(
            PongT.canvas.width / 2 - 350,
            PongT.canvas.height / 2 - 48,
            700,
            100,
        );

        PongT.context.fillStyle = '#ffffff';

        PongT.context.fillText(text,
            PongT.canvas.width / 2,
            PongT.canvas.height / 2 + 15
        );

        PongT.context.font = '70px Courier New';

        PongT.context.fillText(score1.toString(),
            (PongT.canvas.width / 2) -40,
            950
        );

        PongT.context.fillText("-",
            (PongT.canvas.width / 2) ,
            950
        );

        PongT.context.fillText(score2.toString(),
            (PongT.canvas.width / 2) +40,
            950
        );


        setTimeout(function () {
            Pong = Object.assign({}, Game);
            PongT.initialize();
        }, 3000);
    },

    menu: function () {
        PongT.draw();

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
            if (this.ball.x <= 0) PongT._resetTurn.call(this, this.player2, this.player1);
            if (this.ball.x >= this.canvas.width - this.ball.width) PongT._resetTurn.call(this, this.player1, this.player2);
            if (this.ball.y <= 0) this.ball.moveY = DIRECTION.DOWN;
            if (this.ball.y >= this.canvas.height - this.ball.height) this.ball.moveY = DIRECTION.UP;

            if (this.player1.move === DIRECTION.UP) this.player1.y -= this.player1.speed;
            else if (this.player1.move === DIRECTION.DOWN) this.player1.y += this.player1.speed;

            if (this.player2.move === DIRECTION.UP) this.player2.y -= this.player2.speed;
            else if (this.player2.move === DIRECTION.DOWN) this.player2.y += this.player2.speed;

            if (PongT._turnDelayIsOver.call(this) && this.turn) {
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
            setTimeout(function () { PongT.endGameMenu('Player 1 Win!', score1, score2); }, 1000);
        } else if (this.player2.score >= this.rounds[this.round]) {
            this.over = true;
            const score1 = this.player1.score;
            const score2 = this.player2.score;
            setTimeout(function () { PongT.endGameMenu('Player 2 Win!', score2, score1); }, 1000);
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

        if (PongT._turnDelayIsOver.call(this)) {
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
            'Round ' + (PongT.round + 1),
            (this.canvas.width / 2),
            35
        );

        this.context.font = '45px Courier New';

        this.context.fillText(
            'Player 1',
            (this.canvas.width / 2) - 500,
            100
        );

        this.context.fillText(
            'Player 2',
            (this.canvas.width / 2) + 500,
            100
        );

        this.context.font = '40px Courier';

        this.context.fillText(
            rounds[PongT.round] ? rounds[PongT.round] : rounds[PongT.round - 1],
            (this.canvas.width / 2),
            100
        );
    },

    loop: function () {
        PongT.update();
        PongT.draw();

        if (!PongT.over) requestAnimationFrame(PongT.loop);
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
            if (PongT.running === false) {
                PongT.running = true;
                PongT.animationFrameId = window.requestAnimationFrame(PongT.loop);
            }
    
            switch (key.keyCode) {
                case 87: 
                    PongT.player1.move = DIRECTION.UP;
                    key.preventDefault();
                    break;
                case 83: 
                    PongT.player1.move = DIRECTION.DOWN;
                    key.preventDefault();
                    break;
                case 38: 
                    PongT.player2.move = DIRECTION.UP;
                    key.preventDefault();
                    break;
                case 40: 
                    PongT.player2.move = DIRECTION.DOWN;
                    key.preventDefault();
                    break;
            }
        };
    
        this.keyupHandler = function (key) {
            switch (key.keyCode) {
                case 87: 
                case 83: 
                    PongT.player1.move = DIRECTION.IDLE;
                    key.preventDefault();
                    break;
                case 38:
                case 40:
                    PongT.player2.move = DIRECTION.IDLE;
                    key.preventDefault();
                    break;
            }
        };
    
        document.addEventListener('keydown', this.keydownHandler);
        document.addEventListener('keyup', this.keyupHandler);
    },

    _resetTurn: function (victor, loser) {
        this.ball = Ball.new.call(this, this.ball.speed);
        this.ball.x = this.canvas.width / 2 - this.ball.width / 2;
        this.ball.y = this.canvas.height / 2 - this.ball.height / 2;
        this.turn = loser;
        this.timer = (new Date()).getTime();
    
        victor.score++;
    },

    _turnDelayIsOver: function () {
        return((new Date()).getTime() - this.timer >= 1000);
    },

    _generateRoundColor: function() {
        var newColor = colors[Math.floor(Math.random() * colors.length)];
        if (newColor === this.color) return PongT._generateRoundColor();
        return newColor;
    }
};

function startGameWithAI() {
    const playAIButton = document.getElementById('playAI');
    const play1v1Button = document.getElementById('play1v1');
    play1v1Button.remove();
    playAIButton.remove();
    PongIA.initialize();
}

function startGame1v1T() {
    const playAIButton = document.getElementById('playAI');
    const play1v1Button = document.getElementById('play1v1');
    play1v1Button.remove();
    playAIButton.remove();
    PongT.initialize(); 
}

var PongIA = Object.assign({}, GameIA);
var PongT = Object.assign({}, GameT);