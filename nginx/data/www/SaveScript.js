var mustBeSaved = false;

const username = 'username';
const arrayname = "arrayScore";

function storeName(source) {
	localStorage.setItem(username, source.value);
}

function readName(source, def) {
	let item = localStorage.getItem(username);
	if (item !== null) {
		if (def === false)
		source.innerHTML = `Gamer: ${localStorage.getItem(username)}`;
	else
		source.value = localStorage.getItem(username);
	}
}

function saveUserName() {
	mustBeSaved = true;
}
function saveScore() {
	let arrayScore;
	if (localStorage.getItem(arrayname)) {
		arrayScore = JSON.parse(localStorage.getItem(arrayname));
		arrayScore.push({userName: localStorage.getItem(username), score: userScore, t: "\n"});
	} else {
		arrayScore = []
		arrayScore.push({userName: localStorage.getItem(username), score: userScore, t: "\n"});
		console.log(localStorage.getItem(username) + " " +  userScore);
	}
	arrayScore.sort(function(a, b) {
		return b.score - a.score;
	});
	localStorage.setItem(arrayname, JSON.stringify(arrayScore));
}

function openTableScore() {
	var tableScore = window.open("about:blank", "score table", "width=2000,height=2000");
	let arrayScore = JSON.parse(localStorage.getItem(arrayname));
	for (let i = 0; i < arrayScore.length; i++) {
		tableScore.document.write(`\<p\> ${i + 1}. ${arrayScore[i].userName}: ${arrayScore[i].score} \<\/p\>` );
	}
}

function clearStorage() {
	if (!mustBeSaved) {
		localStorage.clear();
		mustBeSaved = false;
	}
}