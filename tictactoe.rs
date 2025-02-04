use std::io;

fn print_board(board: &[[char; 3]; 3]) {
    println!("\n     A   B   C ");
    for (i, row) in board.iter().enumerate() {
        println!("   -------------");
        println!(" {} | {} | {} | {} |", i + 1, row[0], row[1], row[2]);
    }
    println!("   -------------\n");
}

fn check_winner(board: &[[char; 3]; 3]) -> Option<char> {
    for i in 0..3 {
        if board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ' {
            return Some(board[i][0]);
        }
        if board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ' {
            return Some(board[0][i]);
        }
    }
    if board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ' {
        return Some(board[0][0]);
    }
    if board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ' {
        return Some(board[0][2]);
    }
    if board.iter().all(|row| row.iter().all(|&cell| cell != ' ')) {
        return Some('D');
    }
    None
}

fn main() {
    let mut board = [[' '; 3]; 3];
    let mut current_player = 'X';

    println!("Welcome to Neo's Tic-Tac-Toe!");
    println!("Move using column letter and row number (e.g., B2)");
    
    loop {
        print_board(&board);
        println!("Player {}, enter your move (e.g., B2) or type 'q' to quit: ", current_player);
        
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let input = input.trim().to_uppercase();

        if input == "Q" {
            println!("Thanks for playing!");
            break;
        }

        if input.len() != 2 {
            println!("Invalid input. Use format like B2.");
            continue;
        }

        let col = match input.chars().nth(0).unwrap() {
            'A' => 0,
            'B' => 1,
            'C' => 2,
            _ => {
                println!("Invalid column. Use A, B, or C.");
                continue;
            }
        };

        let row = match input.chars().nth(1).unwrap().to_digit(10) {
            Some(n) if (1..=3).contains(&n) => (n - 1) as usize,
            _ => {
                println!("Invalid row. Use 1, 2, or 3.");
                continue;
            }
        };

        if board[row][col] != ' ' {
            println!("Cell already taken. Try again.");
            continue;
        }

        board[row][col] = current_player;

        if let Some(winner) = check_winner(&board) {
            print_board(&board);
            if winner == 'D' {
                println!("It's a draw!");
            } else {
                println!("Player {} wins!", winner);
            }
            break;
        }

        current_player = if current_player == 'X' { 'O' } else { 'X' };
    }
}
