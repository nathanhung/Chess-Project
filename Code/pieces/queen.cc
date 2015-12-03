#include "queen.h"
#include "../game.h"

Queen::Queen(char owner, char type, Game* game): ChessPiece(owner, type, game) {}

Queen::~Queen() {}

bool Queen::checkMove(int curRow, int curCol, int newRow, int newCol) {
    // if diag
    if(curRow != newRow && curCol != newCol){

        // check if spot can be reached
        int reached = 0;
        for (int i = 1; i <= 7; i++) {
            if (curRow - i == newRow && curCol + i == newCol) reached = 1;
            if (curRow + i == newRow && curCol + i == newCol) reached = 1;
            if (curRow + i == newRow && curCol - i == newCol) reached = 1;
            if (curRow - i == newRow && curCol - i == newCol) reached = 1;
        }
        if (reached == 0) return false;
        
        int i = curRow;
        int j = curCol;
            // check if pieces are in the way
        if (curRow > newRow && curCol > newCol) {
            for (; i > newRow + 1 && j > newCol + 1; i--, j--) {
                if (game->getTile(i - 1, j - 1)->getPiece()) return false;
            } 
        } else if (curRow < newRow && curCol > newCol) {
            for (; i < newRow -1 && j > newCol + 1; i++, j--) {
                if (game->getTile(i + 1, j - 1)->getPiece()) return false;
            }
        } else if (curRow > newRow && curCol < newCol) {
            for (; i > newRow + 1 && j < newCol - 1; i--, j++) {
                if (game->getTile(i - 1, j + 1)->getPiece()) return false;
            }
        } else if (curRow > newRow && curCol > newCol) {
            for (; i > newRow + 1 && j > newCol + 1; i--, j--) {
                if (game->getTile(i - 1, j - 1)->getPiece()) return false;
            }
        }
    }
    // if hor
    if(curCol == newCol){
        if (curRow < newRow) {
            for (int i = curRow + 1; i < newRow; i++) {
                if (game->getTile(i, newCol)->getPiece()) return false;
            }
        } else {
            for (int i = curRow - 1; i > newRow; i--) {
                if (game->getTile(i, newCol)->getPiece()) return false;
            }
        }
    }

    // if vert
    if(curRow == newRow){ 
        if (curCol < newCol) {
            for (int i = curCol + 1; i < newCol; i++) {
                if (game->getTile(newRow, i)->getPiece()) return false;
            }   
        } else {
            for (int i = curCol - 1; i > newCol; i--) {
                if (game->getTile(newRow, i)->getPiece()) return false;
            }
        }
    }
    return true;
}
