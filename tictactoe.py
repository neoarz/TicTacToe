import os
import shutil

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_centered(text):
    terminal_width = shutil.get_terminal_size().columns
    print(text.center(terminal_width))

def print_board(board):
    print("\n" * 3)
    print_centered("     A     B     C   ")
    for i, row in enumerate(board):
        print_centered("       |       |       ")
        print_centered(f"{i+1}  {row[0]}   |   {row[1]}   |   {row[2]}   ")
        print_centered("       |       |       ")
        if i < 2:
            print_centered("-------|-------|-------")
    print("\n")

def check_winner(board):
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != " ":
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != " ":
            return board[0][i]
    if board[0][0] == board[1][1] == board[2][2] != " ":
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != " ":
        return board[0][2]
    if all(cell != " " for row in board for cell in row):
        return "Draw"
    return None

def tic_tac_toe():
    board = [[" " for _ in range(3)] for _ in range(3)]
    current_player = "X"
    
    clear_screen()
    print("\n" * 2)
    print_centered("Welcome to Neo's Tic Tac Toe!")
    print_centered("Move with letter for column, number for row")
    print_centered("Example: 'B1' is middle column, top row")
    
    while True:
        print_board(board)
        try:
            move = input(f"Player {current_player}, enter your move (e.g., B2) or type 'quit' to exit: ".center(shutil.get_terminal_size().columns)).strip().lower()
            clear_screen()
            
            if move == "quit":
                print_centered("Thanks for playing! Goodbye!")
                print("\n" * 2)
                break
            
            if len(move) != 2:
                raise ValueError
                
            col = ord(move[0]) - ord('a')
            row = int(move[1]) - 1
            
            if not (0 <= row <= 2 and 0 <= col <= 2):
                print_centered("Invalid input. Please use A-C for columns and 1-3 for rows.")
                continue
                
            if board[row][col] != " ":
                print_centered("Cell already taken. Try again.")
                continue
                
            board[row][col] = current_player
            winner = check_winner(board)
            
            if winner:
                print_board(board)
                if winner == "Draw":
                    print_centered("It's a draw!")
                else:
                    print_centered(f"Player {winner} wins!")
                print("\n" * 2)
                break
                
            current_player = "O" if current_player == "X" else "X"
            
        except (ValueError, IndexError):
            clear_screen()
            print_centered("Invalid input. Please enter column letter and row number (e.g., B2)")

if __name__ == "__main__":
    tic_tac_toe()