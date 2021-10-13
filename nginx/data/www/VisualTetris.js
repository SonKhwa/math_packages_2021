const sizeOfSide = 30;
const sizeOfBorder = 5;

function drawCanvas() {
	let canvas = document.getElementById("canvasid");
	if (canvas.getContext) {
		let ctx = canvas.getContext("2d");
		canvas.width = sizeOfSide * 10 + sizeOfBorder * 2;
		canvas.height = sizeOfSide * 20 + sizeOfBorder * 2;
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		ctx.clearRect(sizeOfBorder, sizeOfBorder, canvas.width - sizeOfBorder * 2, canvas.height - sizeOfBorder * 2);
	}
}

function drawMiniCanvas() {

	let miniCanvas = document.getElementById("minicanvasid");
	if (miniCanvas.getContext) {
		let ctx = miniCanvas.getContext("2d");
		miniCanvas.width = sizeOfSide * 5;
		miniCanvas.height = sizeOfSide * 5;
		ctx.fillRect(0, 0, miniCanvas.width, miniCanvas.height);
		ctx.clearRect(sizeOfBorder, sizeOfBorder, miniCanvas.width - sizeOfBorder * 2, miniCanvas.height - sizeOfBorder * 2);
	}
}

function updateMiniCanvas(mp) {
	let miniCanvas = document.getElementById("minicanvasid");
	if (miniCanvas.getContext) {
		let ctx = miniCanvas.getContext("2d");
		ctx.clearRect(sizeOfBorder, sizeOfBorder, miniCanvas.width - sizeOfBorder * 2, miniCanvas.height - sizeOfBorder * 2);
		drawNextFigure(ctx, mp);
	}
}

function updateCanvas(mp) {
	let canvas = document.getElementById("canvasid");
	if (canvas.getContext) {
		let ctx = canvas.getContext("2d");
		ctx.clearRect(sizeOfBorder, sizeOfBorder, canvas.width - sizeOfBorder * 2, canvas.height - sizeOfBorder * 2);
		drawMap(ctx, mp);
	}
}

function drawNextFigure(ctx, mp) {
	let arr = [];
	mp.curFigure.buildFigure(arr, mp.rand);
	ctx.fillStyle = setColor(mp.rand);
	for (let i = 0; i < arr.length; i++) {
		ctx.fillRect(arr[i][0] * sizeOfSide + sizeOfSide, arr[i][1] * sizeOfSide + sizeOfSide, sizeOfSide, sizeOfSide);
	}
}

function drawMap(ctx, mp) {
	for (let i = 0; i < heightMap; i++) {
		for (let j = 0; j < widthMap; j++) {
			if (mp.map[i][j] != empty) {
				ctx.fillStyle = setColor(mp.map[i][j]);
				ctx.fillRect(j * sizeOfSide + sizeOfBorder, i * sizeOfSide + sizeOfBorder, sizeOfSide, sizeOfSide);
			} else {
				ctx.fillStyle = setColor(empty);
				ctx.fillRect(j * sizeOfSide + sizeOfBorder, i * sizeOfSide + sizeOfBorder, sizeOfSide, sizeOfSide);
				ctx.clearRect(j * sizeOfSide + sizeOfBorder + 1, i * sizeOfSide + sizeOfBorder + 1, sizeOfSide - 2, sizeOfSide - 2);
			}
		}
	}
}

function setColor(type) {
	switch (type) {
		case Bricks.I:
			return "red";
			break;
		case Bricks.J:
			return "orange";
			break;
		case Bricks.S:
			return "yellow";
			break;
		case Bricks.O:
			return "green";
			break;
		case Bricks.Z:
			return "blue";
			break;
		case Bricks.L:
			return "purple";
			break;
		case Bricks.T:
			return "black";
			break;
		default:
			return "grey";
			break;
	}
}
