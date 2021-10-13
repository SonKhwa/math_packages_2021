const mp = new Map();
const priceOfNextLevel = 300;
var userScore = 0;
var level = 0;
var time = 300;
var speed = 50;
var gameInterval;

function prepareForGame() {
    setLevel();
    drawMiniCanvas();
    drawCanvas();
    setControl(mp);
    document.addEventListener("newfigure"
        , (event) => {
            updateMiniCanvas(mp);
        }
    );
}

function setLevel() {
    let input = document.getElementById('levelid');
    document.addEventListener("addscore", (event) => {
        let _score = event.detail.score;
        userScore += _score;
        if (level != Math.round(userScore / priceOfNextLevel)) {
            level = Math.round(userScore / priceOfNextLevel);
            speedUpGame();
            input.innerHTML = "Level: " + level;
        }
    });
}

function speedUpGame() {
    time -= speed;
    clearInterval(gameInterval);
    gameInterval = setInterval(() => {
        mp.update();
        updateCanvas(mp);
    }, time);
}


function startGame() {
    gameInterval = setInterval(() => {
        mp.update();
        updateCanvas(mp);
    }, time);
    updateMiniCanvas(mp);
    document.addEventListener("gameover"
        , (event) => {
            clearInterval(gameInterval);
            alert("Game Over");
            saveScore();
            openTableScore();
        }
    );
}

function setControl(mp) {
    document.addEventListener('keydown', (event) => {
        if (mp.curFigure == null) {
            return;
        }
        const keyName = event.key;
        console.log('Event keydown: ' + keyName);
        switch (keyName) {
            case 'ArrowUp':
                mp.rotateFigure();
                break;
            case 'ArrowDown':
                mp.dropFigure();
                break;
            case 'ArrowLeft':
                mp.moveFigure(-1, 0);
                break;
            case 'ArrowRight':
                mp.moveFigure(1, 0);
                break;
        }
        updateCanvas(mp);
    });
    window.addEventListener('beforeunload'
        , (event) => {
            clearStorage();
        }
    );
}