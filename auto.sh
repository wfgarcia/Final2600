#!/bin/bash

# Set the game board file and player 2's symbol
game_file=game.txt
player=O

# Read the game board from the file
game_board=($(cat $game_file))

# Check if player 2 has won, drawn, or lost
if [[ ${game_board[*]} =~ "111" ]]; then
    echo "Player 2 has lost"
    exit 0
elif [[ ${game_board[*]} =~ "222" ]]; then
    echo "Player 2 has won"
    exit 0
elif [[ ${game_board[*]} =~ "0" ]]; then
    # Play the next best move
    for i in 0 1 2; do
        for j in 0 1 2; do
            if [[ ${game_board[$((i*3+j))]} == 0 ]]; then
                game_board[$((i*3+j))]=$player
                echo "${game_board[*]}" > $game_file
                exit 0
            fi
        done
    done
else
    echo "It's a draw"
    exit 0
fi
