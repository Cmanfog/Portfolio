#include"../react.h"
#include "BoardUpdate.h"
#include "Piece.h"
//#include "ChessDriver.cpp"
#include<iostream>
#include<cstring>
using namespace std;

King *k, *K;
int player = 0;

void initGlobalMem(){
    _put_raw(1, "2 Player");
    _put_raw(10, "Settings");
    _put_raw(19, "How to Play");
    _put_raw(31, "Title Page");
    _put_raw(43, "Standard Setup");
    _put_raw(58, "Make a Move:");
    _put_raw(100, "Pawns are the most common piece in the game. At the start of the game, they are able to move one or two spaces forward. Afterwards, they can only move forward one space as long as there is nothing in front of them. They can also move by capturing other pieces that are in front of them diagonally.");
    _put_raw(400, "Rooks can be found on the each corner of the board. They are capable of moving horizontally or vertically for as many empty spaces as the player desires.");
    _put_raw(700, "Bishops are capable of moving in any direction diagonally across the board. Here's a tip: If a bishop is on a darker space, it can only go to other darker spaces. Same thing if it's on a lighter space.");
    _put_raw(1000, "Despite the fact that knights are represented by mere horses and not their riders, these pieces are capable of going places other pieces can't. Knights can only move to another space that one space apart in one direction and two spaces apart in the direction perpendicular to it. Basically, if you can make L-shape to your destination, you can go there. ");
    _put_raw(1400, "Queens are by far the most powerful and versatile pieces in the game. They can move in any direction horizontally, vetically or diagonally, meaning they can go places that other pieces like bishops or rooks would have a hard time getting to. Be wary of where you put this one, because if the other person has a queen and yours gets taken, you'll be at a disadvantage. Think smart.");
    _put_raw(1800, "Kings are the most vital piece in the game. It can only move one space in any horizontal, vertical, or diagonal direction. If an opposing piece can take the king within a move, the king is put in check, meaning you have to find a way to stop the opposing piece from getting to your king. If there is no possible way to avoid your king being taken, the result is a checkmate and other player wins.");
    _put_raw(3000, "React Chess Programmers: Noah Tibben-Lembke and Connor Fogarty");
    _put_raw(3100, "Knight Practice");
    _put_raw(3120, "Bishop Practice");
    _put_raw(3140, "Rook Practice");
    _put_raw(3160, "Checkmate Practice #1");
    _put_raw(3182, "Checkmate Practice #2");
    _put_raw(3204, "Checkmate Practice #3");
    _put_raw(2500, "0");
    _put_raw(2502, "1");
    _put_raw(2504, "2");
    _put_raw(2506, "3");
    _put_raw(2508, "4");
    _put_raw(2510, "5");
    _put_raw(2512, "6");
    _put_raw(2514, "7");
}

void StartPlaying(string s, BoardUpdate &b1){
    int checkmate = 0;
    bool inCheck = false;
    cerr << "P" << player % 2 + 1 << ": ";
    //while (checkmate < 8) {
    char *x = new char[3];
    char *xpos = new char[2];
    char *pos = new char[3];
    char *temp = new char[2];
     bool validType = false;
    //cerr << "Which piece would you like to use? "; // Type a number and press enter
    x[0]=s[0];
    x[1]=s[1];
    x[2] = '\0';
    cerr << "Your piece is: " << x<< endl;
    pos[0]=s[3];
    pos[1]=s[4];
    pos[2]='\0';
    //if (*pos == 'x') break;
    cerr<< "position to move to is: "<< pos<<endl;
    temp[1]=pos[0];
    temp[0]=pos[1];
    for (int i = 0; i < 2; i++) xpos[i] = x[i] - '0';
    if (b1.board[x[1]-'0'][x[0]-'0'] != 0 && b1.board[x[1]-'0'][x[0]-'0']->GetColor() == player % 2) { 
        validType = true; 
         int *pos2;
        pos2 = new int[2];
        for (int i = 0; i < 2; i++) pos2[i] = temp[i] - '0';
        if (temp[0] - '0' < 8 && temp[0] - '0' > -1 && temp[1] - '0' < 8 && temp[1] - '0' > -1) {
            if (b1.board[xpos[1]][xpos[0]]->IsValid(pos2) == true) {
                Piece *p2 = 0;
                if (b1.board[xpos[1]][xpos[0]]->CanITakeThis(pos2) == true) p2 = b1.board[pos2[0]][pos2[1]];
                int pl = b1.board[xpos[1]][xpos[0]]->Move(temp, player); 
                bool kCheck = b1.IsInCheck(k);
                bool KCheck = b1.IsInCheck(K);
                if (kCheck == true || KCheck == true) {
                    if (inCheck == true || (player % 2 == 0 && kCheck == true) || (player % 2 == 1 && KCheck == true)) { //undoes move if it either doesn't get current player out of check or gets themselves into check
                        Piece *p1;
                        p1 = b1.board[pos2[0]][pos2[1]];
                        p1->Remove();
                        if (p2 != 0) p2->AddToBoard(b1.board, temp);
                        char *pos1 = new char[2];
                        pos1[0] = x[1];
                        pos1[1] = x[0];
                        p1->AddToBoard(b1.board, pos1);
                        cerr << "You are in check!" << endl;
                        if (pl != player) pl--;
                        if (inCheck == false) {
                            cerr << "You can't put yourself into check!" << endl;
                        } else {
                            cerr << "That didn't get you out of check!" << endl;
                        } 
                    } else inCheck = true;
                } else inCheck = false;
            } else cerr << "You can't move that way!" << endl;
        } 
    } else {
        cerr << "You can't move that piece!" << endl;
        _put_char(76, '1');
    }
}


void ScreenUpdate(BoardUpdate &b1) {
    _put_char(0, '2');
    for (int i=0; i<8; i++) {
        add_yaml("numberlabel.yaml",{{"x", 2500+2*i},{"left", 31+5*i},{"top", 24}});
        add_yaml("numberlabel.yaml",{{"x", 2500+2*i},{"left", 27.5},{"top", 30+9*i}});
    }

    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++) {
            const char ic = i;
            //std::cerr<<"row: "<<i<<" and column: "<<j<<std::endl;
            
            if (b1.board[i][j] == 0) {
                if (i%2==0 && j%2==1) add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(163,98,32)"},{"x","0"}}); //the buttons can now recognize what part of the row they are on
                else if (i%2==1 && j%2==0)add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(163,98,32)"},{"x", "0"}});
                else add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(75,38,0)"},{"x", "0"}});
            }
            else if (i%2==0 && j%2==1) add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(163,98,32)"},{"x", b1.board[i][j]->GetImg()}});
            else if (i%2==1 && j%2==0) add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(163,98,32)"},{"x", b1.board[i][j]->GetImg()}});
            else add_yaml("squarea0.yaml", {{"id0",ic},{"id1",j},{"left", 30+5*j },{"top", 25+9*i},{"color", "rgb(75,38,0)"},{"x", b1.board[i][j]->GetImg()}});
        }
    }
}

void BoardStore(const BoardUpdate &b1){
    int memCounter=3000;
    //std::cerr<<"boardstore called"<<std::endl;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            //std::cerr<<"row: "<<i<<" and column: "<<j<<std::endl;
            if (b1.board[i][j] ==0) {
                _put_char(memCounter, '0');
            }
            else {
                char name= b1.board[i][j]->GetName();
                //std::cerr<<"name: "<<name<<std::endl;
                _put_char(memCounter, name);
            }
            memCounter++;
        }//std::cerr<< "end of a row"<<std::endl;
    }
}

void BoardPull(BoardUpdate &b1){
    int memCounter=3000;
    char *pos = new char[2];
    //std::cerr<<"pos created"<<std::endl;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            pos[0]=i + '0';
            pos[1]=j + '0';
            //std::cerr<<"row: "<<i<<" and column: "<<j<<std::endl;
            //std::cerr<< convertToString(pos, 2) << std::endl;
            if ( _get_char(memCounter)== '0') {
                b1.board[i][j] =0;
            }
            else if(_get_char(memCounter)== 'p'){
                new Pawn(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'n'){
                new Knight(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'b'){
                new Bishop(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'q'){
                new Queen(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'k'){
                k = new King(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'r'){
                new Rook(pos, b1.board, 0);
            }else if(_get_char(memCounter)== 'P'){
                new Pawn(pos, b1.board, 1);
            }else if(_get_char(memCounter)== 'N'){
                new Knight(pos, b1.board, 1);
            }else if(_get_char(memCounter)== 'B'){
                new Bishop(pos, b1.board, 1);
            }else if(_get_char(memCounter)== 'Q'){
                new Queen(pos, b1.board, 1);
            }else if(_get_char(memCounter)== 'K'){
                K = new King(pos, b1.board, 1);
            }else if(_get_char(memCounter)== 'R'){
                new Rook(pos, b1.board, 1);
            }
            memCounter++;
        }
    }
}

int main() {
    _init(); 

    BoardUpdate b1;
    b1.BoardArrayInit();
    b1.BlankInit();
    b1.StandardInit();
    //BoardStore(b1);
    //BoardPull(b1);
    //ScreenUpdate(b1);
    //return 0;
    
    
    //b1.StandardInit();
    /* If we declare this here, we can still input coordinates. If we input it in StandardInit, the coordinates stop working*/
    //std::cerr<<b1.board[0][0]->GetImg()<<std::endl;    
    
    if(_just_starting()) {
        _put_char(0, '0');
        _put_raw(2200, "8");
        initGlobalMem();
        _put_char(75, '0');
        _put_char(76, '0');
    } else BoardPull(b1);

    if(_get_char(0)=='0') add_yaml("TitlePage.yaml");
    else if(_get_char(0)=='1') add_yaml("Settings.yaml");
    else if(_get_char(0)=='2') {
        add_yaml("2player.yaml");
        
    }
    else if(_get_char(0)=='3') add_yaml("HowToPlay.yaml");
    
    if (_received_event()) {
        if (_event_id_is("2_player")) {
            std::cerr << "2 Player\n";
            _put_char(0, '2');
            //add_yaml("2player.yaml", {{"a0", "BRook.png"}});
        } else if (_event_id_is("Settings")) {
            std::cerr << "Settings\n";
            _put_char(0, '1');
            //add_yaml("Settings.yaml");
        } else if (_event_id_is("Title_Page")){
            _put_char(0, '0');
            //add_yaml("TitlePage.yaml");
        } else if (_event_id_is("StandardInit")){
            _put_char(75, '0');
            BoardStore(b1);
            ScreenUpdate(b1);
        }else if (_event_id_is("How_To_Play")){
            _put_char(0, '3');
            std::cerr<<"How to Play page\n";
        }else if(_event_id_is("input")) {
            if (_get_char(76) == '0') player = 0;
            else player = 1;
            string s = _global_mem + 2200;
            //std::cerr<<"you typed " << s <<std::endl;
            
            //b1.StandardInit();
            //BoardPull(b1);
            StartPlaying(s,b1);
            //BoardStore(b1);
            ScreenUpdate(b1);
            if (_get_char(76) == '0') _put_char(76, '1');
            else _put_char(76, '0');
        }else if (_event_id_is("KnightPractice")){
            _put_char(75, '1');
            b1.BlankInit();
            b1.KnightPractice();
            ScreenUpdate(b1);
        }else if (_event_id_is("BishopPractice")){
            _put_char(75, '2');
            b1.BlankInit();
            b1.BishopPractice();
            ScreenUpdate(b1);
        }else if (_event_id_is("RookPractice")){
            _put_char(75, '3');
            b1.BlankInit();
            b1.RookPractice();
            ScreenUpdate(b1);
        }else if(_event_id_is("CheckmatePractice1")){
            _put_char(75, '4');
            b1.BlankInit();
            b1.CheckmatePractice1();
            ScreenUpdate(b1);
        }else if(_event_id_is("CheckmatePractice2")){
            _put_char(75, '5');
            b1.BlankInit();
            b1.CheckmatePractice2();
            ScreenUpdate(b1);
        }else if(_event_id_is("CheckmatePractice3")){
            _put_char(75, '3');
            b1.BlankInit();
            b1.CheckmatePractice3();
            ScreenUpdate(b1);
        }else if (_event_id_is("a",0)){
            std::cerr<<"a0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",0)){
            std::cerr<<"b0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",0)){
            std::cerr<<"c0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",0)){
            std::cerr<<"d0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",0)){
            std::cerr<<"e0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",0)){
            std::cerr<<"f0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",0)){
            std::cerr<<"g0\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",0)){
            std::cerr<<"h0\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",1)){
            std::cerr<<"a1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",1)){
            std::cerr<<"b1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",1)){
            std::cerr<<"c1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",1)){
            std::cerr<<"d1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",1)){
            std::cerr<<"e1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",1)){
            std::cerr<<"f1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",1)){
            std::cerr<<"g1\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",1)){
            std::cerr<<"h1\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",2)){
            std::cerr<<"a2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",2)){
            std::cerr<<"b2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",2)){
            std::cerr<<"c2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",2)){
            std::cerr<<"d2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",2)){
            std::cerr<<"e2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",2)){
            std::cerr<<"f2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",2)){
            std::cerr<<"g2\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",2)){
            std::cerr<<"h2\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",3)){
            std::cerr<<"a3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",3)){
            std::cerr<<"b3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",3)){
            std::cerr<<"c3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",3)){
            std::cerr<<"d3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",3)){
            std::cerr<<"e3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",3)){
            std::cerr<<"f3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",3)){
            std::cerr<<"g3\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",3)){
            std::cerr<<"h3\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",4)){
            std::cerr<<"a4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",4)){
            std::cerr<<"b4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",4)){
            std::cerr<<"c4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",4)){
            std::cerr<<"d4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",4)){
            std::cerr<<"e4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",4)){
            std::cerr<<"f4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",4)){
            std::cerr<<"g4\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",4)){
            std::cerr<<"h4\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",5)){
            std::cerr<<"a5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",5)){
            std::cerr<<"b5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",5)){
            std::cerr<<"c5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",5)){
            std::cerr<<"d5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",5)){
            std::cerr<<"e5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",5)){
            std::cerr<<"f5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",5)){
            std::cerr<<"g5\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",5)){
            std::cerr<<"h5\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",6)){
            std::cerr<<"a6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",6)){
            std::cerr<<"b6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",6)){
            std::cerr<<"c6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",6)){
            std::cerr<<"d6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",6)){
            std::cerr<<"e6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",6)){
            std::cerr<<"f6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",6)){
            std::cerr<<"g6\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",6)){
            std::cerr<<"h6\n";
            ScreenUpdate(b1);
        }
        else if (_event_id_is("0",7)){
            std::cerr<<"a7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("1",7)){
            std::cerr<<"b7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("2",7)){
            std::cerr<<"c7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("3",7)){
            std::cerr<<"d7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("4",7)){
            std::cerr<<"e7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("5",7)){
            std::cerr<<"f7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("6",7)){
            std::cerr<<"g7\n";
            ScreenUpdate(b1);
        }else if (_event_id_is("7",7)){
            std::cerr<<"h7\n";
            ScreenUpdate(b1); 
        }
    }
    BoardStore(b1);
    _quit();
}
