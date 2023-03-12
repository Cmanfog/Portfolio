#include "Piece.h"
using namespace std;

void BlankInit(char **board) {
  for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = '_';
        }
    }  
}

void BoardPrint(char **board) {
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            cout<< board[i][j]<< "   ";
        }
        cout<< endl;
    }
    cout<<endl;
}

int main() {
    char **board = new char*[8];
    for (int i=0; i<8; i++) {
        board[i] = new char[8];
    }

    BlankInit(board);
    Piece p1("11", board , 'p');
    BoardPrint(board);

    int *xy = p1.GetPosition();
    cout << xy[0] << xy[1] << endl;

    p1.Move("21");
    BoardPrint(board);

    Piece p2;
    p2.AddToBoard(board, "32");
    BoardPrint(board);

    p1.Move("32");
    BoardPrint(board);


    for (int i=0; i<8; i++) {
            delete board[i];
        }
    delete [] board;
}