const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const board = [
    [" ", " ", " "],
    [" ", " ", " "],
    [" ", " ", " "]
];

const printBoard = () => {
    console.clear();
    console.log("\n     A   B   C ");
    for (let i = 0; i < 3; i++) {
        console.log("   -------------");
        console.log(`${i + 1}  | ${board[i][0]} | ${board[i][1]} | ${board[i][2]} |`);
    }
    console.log("   -------------\n");
};

const checkWinner = () => {
    for (let i = 0; i < 3; i++) {
        if (board[i][0] === board[i][1] && board[i][1] === board[i][2] && board[i][0] !== " ") return board[i][0];
        if (board[0][i] === board[1][i] && board[1][i] === board[2][i] && board[0][i] !== " ") return board[0][i];
    }
    if (board[0][0] === board[1][1] && board[1][1] === board[2][2] && board[0][0] !== " ") return board[0][0];
    if (board[0][2] === board[1][1] && board[1][1] === board[2][0] && board[0][2] !== " ") return board[0][2];
    return board.flat().includes(" ") ? null : "Draw";
};

const playGame = (currentPlayer) => {
    printBoard();
    rl.question(`Player ${currentPlayer}, enter your move (e.g., B2) or type 'q' to quit: `, (move) => {
        if (move.toLowerCase() === "q") {
            console.log("Thanks for playing!");
            rl.close();
            return;
        }

        const col = move.charCodeAt(0) - "A".charCodeAt(0);
        const row = parseInt(move[1]) - 1;

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] !== " ") {
            console.log("Invalid move, try again.");
            return playGame(currentPlayer);
        }

        board[row][col] = currentPlayer;
        const winner = checkWinner();

        if (winner) {
            printBoard();
            console.log(winner === "Draw" ? "It's a draw!" : `Player ${winner} wins!`);
            rl.close();
        } else {
            playGame(currentPlayer === "X" ? "O" : "X");
        }
    });
};

console.log("Welcome to Neo's Tic-Tac-Toe!");
playGame("X");
