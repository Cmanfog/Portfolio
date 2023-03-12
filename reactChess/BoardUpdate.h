#ifndef _BOARDUPDATE_H_
#define _BOARDUPDATE_H_
#include<iostream>
#include "Piece.h"
using namespace std;


class Mechanics {
};
 
class BoardUpdate : public Mechanics {
    int dimensions;  
public:
    Piece ***board;
    BoardUpdate(int n): dimensions(n), board(0) {}
    BoardUpdate(): dimensions(8), board(0) {}
    ~BoardUpdate() {
        for (int i=0; i<dimensions; i++) {
            //for (int j=0; j<dimensions; j++) if (board[i][j] != 0) delete board[i][j];
            
            delete [] board[i];
        }
        delete [] board;
    }

    void BoardArrayInit();
    void DefaultArrayInit() ;//maybe not necessary?
    void BlankInit();
    void BoardPrint();
    void StandardInit();

    void KnightPractice();
    void BishopPractice();
    void RookPractice();
    void CheckmatePractice1();
    void CheckmatePractice2();
    void CheckmatePractice3();

    void Reset(int n);
    void Move(Piece*p, const char *pos);
    void StartPlaying();
    void StartPlaying(string s);
    bool IsInCheck(King *k);
};
 
#endif //_BOARD_H_