const widthMap = 10;
const heightMap = 20;
const empty = -1;
const spawn = Math.floor(widthMap /2) - 1;

const lengthOfBricks = 7;
const Bricks = { I:0, J:1, L:2, O:3, S:4, T:5, Z:6 }

class Figure {
    constructor(type) {
        this.arrPos = [];
        this.buildFigure(this.arrPos, type);
        this.type = type;
    }

    buildFigure(arr, type) {
        switch (type) {
            case Bricks.I:
                arr.push([0, 0]);
                arr.push([0, 1]);
                arr.push([0, 2]);
                arr.push([0, 3]);
                break;
            case Bricks.J:
                arr.push([1, 0]);
                arr.push([1, 1]);
                arr.push([0, 2]);
                arr.push([1, 2]);
                break;
            case Bricks.S:
                arr.push([0, 1]);
                arr.push([1, 0]);
                arr.push([1, 1]);
                arr.push([2, 0]);
                break;
            case Bricks.O:
                arr.push([0, 0]);
                arr.push([0, 1]);
                arr.push([1, 0]);
                arr.push([1, 1]);
                break;
            case Bricks.Z:
                arr.push([0, 0]);
                arr.push([1, 0]);
                arr.push([1, 1]);
                arr.push([2, 1]);
                break;
            case Bricks.L:
                arr.push([0, 0]);
                arr.push([0, 1]);
                arr.push([0, 2]);
                arr.push([1, 2]);
                break;
            case Bricks.T:
                arr.push([0, 0]);
                arr.push([1, 0]);
                arr.push([1, 1]);
                arr.push([2, 0]);
                break;
            default:
                console.log(type);
                break;
        }
    }

    move(offsetX, offsetY) {
        for (let i = 0; i < this.arrPos.length; i++) {
            this.arrPos[i][0] += offsetX;
            this.arrPos[i][1] += offsetY;
        }
    }
}

class Map {
    constructor() {
        this.rand = Math.floor(Math.random() * lengthOfBricks);
        this.map = new Array(heightMap).fill(empty);
        this.curFigure = null;
        for (let i = 0;i < this.map.length;i++) {
            this.map[i] = new Array(widthMap).fill(empty);
        }
        this.createRandomFigure();
    }

    createRandomFigure() {
        this.initCurrentFigure(new Figure(this.rand));
        this.rand = Math.floor(Math.random() * lengthOfBricks);
    }

    initCurrentFigure(figure) {
        this.curFigure = figure;
        this.curFigure.move(spawn, -3);
        this.insertFigureToMap();
    }

    clearFigureInMap() {
        for (let i = 0; i < this.curFigure.arrPos.length; i++) {
            if (this.curFigure.arrPos[i][1] >= 0)
                this.map[this.curFigure.arrPos[i][1]][this.curFigure.arrPos[i][0]] = empty;
        }
    }

    insertFigureToMap() {
        for (let i = 0; i < this.curFigure.arrPos.length; i++) {
            if (this.curFigure.arrPos[i][1] >= 0)
                this.map[this.curFigure.arrPos[i][1]][this.curFigure.arrPos[i][0]] = this.curFigure.type;
        }
    }

    crossesBorders(arr, offsetX, offsetY) {
        for (let i = 0; i < arr.length; i++) {
            if (arr[i][0] + offsetX >= widthMap || arr[i][0] + offsetX < 0)
                return true;
        }
        return false;
    }

    canInsert(arr, offsetX, offsetY) {
        for (let i = 0; i < arr.length; i++) {
            if(arr[i][1] + offsetY >= heightMap)
                return false;
            if (arr[i][1] + offsetY >= 0)
                if (this.map[arr[i][1] + offsetY][arr[i][0] + offsetX] != empty) {
                    return false;
                }
        }
        return true;
    }

    moveFigure(offsetX, offsetY) {
        if (this.crossesBorders(this.curFigure.arrPos, offsetX, offsetY))
            return;
        this.clearFigureInMap();
        if (this.canInsert(this.curFigure.arrPos, offsetX, offsetY)) {
            this.curFigure.move(offsetX, offsetY);
            this.insertFigureToMap();
        } else {
            this.insertFigureToMap();
            if (offsetY != 0)
                this.curFigure = null;
        }
    }

    update() {
        if (this.curFigure == null) {
            this.deleteCompleteStroke();
            if (!this.isFinished()) {
                this.createRandomFigure();
                document.dispatchEvent(NewFigureEvent);
            } else {
                document.dispatchEvent(GameOverEvent);
            }
            return;
        }
        this.moveFigure(0, 1);
       // this.showMap();
    }

    deleteCompleteStroke() {
        let countOfStroke = 0;
        for (let i = 0; i < heightMap; i++) {
            if (this.isCompleted(i)) {
                countOfStroke++;
                for (let j = 0; j < widthMap; j++) {
                    this.map[i][j] = empty;
                }
                let stroke = this.map[i];
                this.map.splice(i, 1);
                this.map.unshift(stroke);
            }
        }
        this.getScoreOfComleteStrokes(countOfStroke);
    }

    getScoreOfComleteStrokes(count) {
        let _score = 0;
        switch (count) {
            case 0:
                return;
            case 1:
                _score = 100;
                break;
            case 2:
                _score = 300;
                break;
            case 3:
                _score = 700;
                break;
            case 4:
                _score = 1500;
                break;
        }
        document.dispatchEvent(new CustomEvent("addscore", {
            detail: {score: _score,}
        }));
    }

    isCompleted(i) {
        for (let j = 0; j < widthMap;j++) {
            if (this.map[i][j] == empty)
                return false;
        }
        return true;
    }

    isFinished() {
        if (this.map[0][spawn] != empty || this.map[0][spawn + 1] != empty)
            return true;
        return false;
    }

    showMap() {
        for (let i = 0; i < heightMap;i++) {
            for (let j = 0; j < widthMap;j++) {
                process.stdout.write(this.map[i][j]);
            }
            process.stdout.write('\n');
        }
        process.stdout.write('\n');
    }

    rotateFigure() {
        if (this.curFigure == null || this.curFigure.type == 3) {
            return;
        }
        let _arrPos = new Array(this.curFigure.arrPos.length);
        let pivot = this.curFigure.arrPos[1].slice(0);
        for (let i = 0; i < this.curFigure.arrPos.length; i++) {
            _arrPos[i] = new Array(2);
            _arrPos[i][0] = this.curFigure.arrPos[i][0] - pivot[0];
            _arrPos[i][1] = this.curFigure.arrPos[i][1] - pivot[1];
            _arrPos[i] = [_arrPos[i][1], -_arrPos[i][0]];
            _arrPos[i][0] += pivot[0];
            _arrPos[i][1] += pivot[1];
            //      process.stdout.write(_arrPos[i] + ' ' + this.curFigure.arrPos[i] + ' '+ pivot + '\n');
        }
        this.clearFigureInMap();
        if (!this.crossesBorders(_arrPos, 0, 0) && this.canInsert(_arrPos, 0, 0)) {
            this.curFigure.arrPos = _arrPos;
        }
        this.insertFigureToMap();
//        this.showMap();
    }

    dropFigure() {
        this.clearFigureInMap();
        while (this.canInsert(this.curFigure.arrPos, 0, 1)) {
            for (let i = 0; i < this.curFigure.arrPos.length; i++) {
                this.curFigure.arrPos[i][1]++;
            }
        }
        this.insertFigureToMap();
    }
}


