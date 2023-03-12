#ifndef _MOVEHISTORY_H_
#define _MOVEHISTORY_H_
#include<iostream>
#include "Piece.h"
#include "BoardUpdate.h"
using namespace std;

class MoveHistory : public Mechanics {
    int **record;
    int num_moves;
public:
    MoveHistory();
    ~MoveHistory();
    void RecordMove();
    int *GetMove();
    void ResetRecord();
    void DeleteFuture();
    void NewRecord();
    int **ChangeRecord();
    int GetNum_Moves() {return num_moves;}
}

#endif