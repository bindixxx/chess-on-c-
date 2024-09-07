#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

const int BOARD_SIZE = 8;

enum PieceType {
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum PlayerColor {
    NONE,
    WHITE,
    BLACK
};

struct Piece {
    PieceType type;
    PlayerColor color;

    Piece(PieceType t = EMPTY, PlayerColor c = NONE) : type(t), color(c) {}
};

class Chess {
private:
    vector<vector<Piece>> board;

    void initializeBoard() {
        board = vector<vector<Piece>>(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece()));
        board[0][0] = board[0][7] = Piece(ROOK, WHITE);
        board[0][1] = board[0][6] = Piece(KNIGHT, WHITE);
        board[0][2] = board[0][5] = Piece(BISHOP, WHITE);
        board[0][3] = Piece(QUEEN, WHITE);
        board[0][4] = Piece(KING, WHITE);
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[1][i] = Piece(PAWN, WHITE);
        }
        board[7][0] = board[7][7] = Piece(ROOK, BLACK);
        board[7][1] = board[7][6] = Piece(KNIGHT, BLACK);
        board[7][2] = board[7][5] = Piece(BISHOP, BLACK);
        board[7][3] = Piece(QUEEN, BLACK);
        board[7][4] = Piece(KING, BLACK);
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[6][i] = Piece(PAWN, BLACK);
        }
    }

    bool isValidMove(int startX, int startY, int endX, int endY, PlayerColor currentPlayer) {
        if (startX < 0 || startX >= BOARD_SIZE || startY < 0 || startY >= BOARD_SIZE ||
            endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
            return false;
        }
        if (board[startX][startY].color != currentPlayer) {
            return false;
        }
        if (board[endX][endY].color == currentPlayer) {
            return false;
        }

        int dx = abs(endX - startX);
        int dy = abs(endY - startY);

        switch (board[startX][startY].type) {
        case PAWN:
            if (currentPlayer == WHITE) {
                if (startX == 1 && endX == 3 && startY == endY && board[2][startY].type == EMPTY && board[3][startY].type == EMPTY) {
                    return true;
                }
                if (endX == startX + 1 && startY == endY && board[endX][endY].type == EMPTY) {
                    return true;
                }
                if (endX == startX + 1 && dy == 1 && board[endX][endY].color == BLACK) {
                    return true;
                }
            }
            else {
                if (startX == 6 && endX == 4 && startY == endY && board[5][startY].type == EMPTY && board[4][startY].type == EMPTY) {
                    return true;
                }
                if (endX == startX - 1 && startY == endY && board[endX][endY].type == EMPTY) {
                    return true;
                }
                if (endX == startX - 1 && dy == 1 && board[endX][endY].color == WHITE) {
                    return true;
                }
            }
            break;
        case ROOK:
            if (dx == 0 || dy == 0) {
                return true;
            }
            break;
        case KNIGHT:
            if (dx * dy == 2) {
                return true;
            }
            break;
        case BISHOP:
            if (dx == dy) {
                return true;
            }
            break;
        case QUEEN:
            if (dx == dy || dx == 0 || dy == 0) {
                return true;
            }
            break;
        case KING:
            if (dx <= 1 && dy <= 1) {
                return true;
            }
            break;
        default:
            break;
        }

        return false;
    }

public:
    Chess() {
        initializeBoard();
    }

    void displayBoard() {
        cout << "   ";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << setw(2) << i << " ";
        }
        cout << endl;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << setw(2) << i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                string pieceSymbol;
                switch (board[i][j].type) {
                case EMPTY:
                    pieceSymbol = ".";
                    break;
                case PAWN:
                    pieceSymbol = "♟";
                    break;
                case ROOK:
                    pieceSymbol = "♜";
                    break;
                case KNIGHT:
                    pieceSymbol = "♞";
                    break;
                case BISHOP:
                    pieceSymbol = "♝";
                    break;
                case QUEEN:
                    pieceSymbol = "♛";
                    break;
                case KING:
                    pieceSymbol = "♚";
                    break;
                }
                if (board[i][j].color == WHITE) {
                    cout << "W" << pieceSymbol << " ";
                }
                else if (board[i][j].color == BLACK) {
                    cout << "B" << pieceSymbol << " ";
                }
                else {
                    cout << pieceSymbol << " ";
                }
            }
            cout << endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY, PlayerColor currentPlayer) {
        if (!isValidMove(startX, startY, endX, endY, currentPlayer)) {
            cout << "Некорректный ход. Попробуйте снова." << endl;
            return false;
        }

        board[endX][endY] = board[startX][startY];
        board[startX][startY] = Piece();

        return true;
    }
};

int main() {
    Chess game;
    int startX, startY, endX, endY;
    PlayerColor currentPlayer = WHITE;

    while (true) {
        game.displayBoard();
        cout << (currentPlayer == WHITE ? "Ход белых (W)" : "Ход черных (B)") << endl;
        cout << "Введите координаты: стартX стартY конецX конецY" << endl;
        cin >> startX >> startY >> endX >> endY;

        if (game.movePiece(startX, startY, endX, endY, currentPlayer)) {
            currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
        }
        else {
            cout << "Некорректный ход. Попробуйте снова." << endl;
        }
    }

    return 0;
}
