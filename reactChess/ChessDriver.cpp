#include "Piece.h"
#include"../react.h"
#include "BoardUpdate.h"
#include<string>
using namespace std;


int main() {
    
    BoardUpdate b1(8);
    b1.BoardArrayInit();
    b1.BlankInit();
    b1.StandardInit();
    b1.BoardPrint();
    b1.StartPlaying();

}