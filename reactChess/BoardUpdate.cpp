#include "BoardUpdate.h"
#include "Piece.h"
#include<iostream>
#include<cstring>
 


void BoardUpdate::BoardArrayInit() {
    board = new Piece**[dimensions];
    for (int i=0; i<dimensions; i++) {
        board[i] = new Piece*[dimensions];
    }
}
 
void BoardUpdate::BlankInit() { //fills the board array with zeros
    for (int i=0; i<dimensions; i++) {
        for (int j=0; j<dimensions; j++) {
            board[i][j] = 0;
        }
    }
}
 
void BoardUpdate::BoardPrint() { //prints out a representation of the board
    //cerr<< "in BoardPrint:  "<<board[0][0]->GetName()<<endl;
    for (int i=0; i<dimensions; i++) {
        cerr<< i<<' ';
        for (int j=0; j<dimensions; j++) {
            if (board[i][j] == 0) cerr << "_ ";
            else cerr<< board[i][j]->GetName()<< " ";
        }
        cerr<< endl;
    }
    cerr<<"  0 1 2 3 4 5 6 7"<<endl;
    cerr<<endl;
}
 
 
void BoardUpdate::StandardInit() { //puts 'pieces' in the spots they should be
    if(dimensions==8) {
        
        new Rook("00", board, 0); new Rook("07",board, 0); new Knight("01",board, 0); new Knight("06",board, 0);
        new Bishop("02", board, 0); new Bishop("05",board, 0); new Queen("03", board, 0); new King("04",board, 0); //if using terminal create global king pointers
        new Pawn("10", board, 0); new Pawn("11",board, 0); new Pawn("12",board, 0); new Pawn("13",board, 0);
        new Pawn("14", board, 0); new Pawn("15",board, 0); new Pawn("16",board, 0); new Pawn("17",board, 0);
    //different colors would represent different players; right now only works if color = 0, need to be able to make it different colors (or make a different variable to represent opposing sides)
        new Rook("70", board, 1); new Rook("77",board, 1); new Knight("71",board, 1); new Knight("76",board, 1);
        new Bishop("72", board, 1); new Bishop("75",board, 1); new Queen("73",board, 1); new King("74",board, 1);
        new Pawn("60", board, 1); new Pawn("61",board, 1); new Pawn("62",board, 1); new Pawn("63",board, 1);
        new Pawn("64", board, 1); new Pawn("65",board, 1); new Pawn("66",board, 1); new Pawn("67",board, 1);
    }
}

void BoardUpdate::KnightPractice() {
    new Knight("44", board, 0);
}
void BoardUpdate::BishopPractice() {
    new Bishop("44", board, 0);
    new Bishop("34", board, 1);
}
void BoardUpdate::RookPractice() {
    new Rook("22", board, 0);
    new Rook("55", board, 1);
}
void BoardUpdate::CheckmatePractice1() {
    new Rook("00", board, 0), new Queen("03", board, 0), new King("05", board, 0), new Rook("06", board, 0);
    new Pawn("10", board, 0), new Pawn("11", board, 0), new Pawn("12", board, 0), new Knight("14", board, 0);
    new Pawn("23", board, 0), new Pawn("25", board, 0), new Pawn("34", board, 0), new Pawn("36", board, 0), new Knight("32", board, 0);
    new Queen("07", board, 1), new Pawn("42", board, 1), new Pawn("44", board, 1), new Pawn("50", board, 1), new Pawn("52", board, 1), new Pawn("53", board, 1);
    new Pawn("65", board, 1), new Pawn("66", board, 1), new Bishop("26", board, 1), new Bishop("56", board, 1);
    new Rook("73", board, 1), new King("74", board, 1), new Rook("77", board, 1);
}
void BoardUpdate::CheckmatePractice2() {
    new Rook("03", board, 0), new Rook("73", board, 0), new Pawn("10", board, 0), new Pawn("11", board, 0);
    new King("25", board, 0), new Bishop("35", board, 0), new Pawn("26", board, 0), new Pawn("27", board, 0);
    new Rook("14", board, 1), new Rook("74", board, 1), new Bishop("51", board, 1), new Pawn("47", board, 0);
    new Pawn("60", board, 0), new Pawn("62", board, 1), new Pawn("65", board, 1), new Pawn("66", board, 1);
    new King("76", board, 1);
}
void BoardUpdate::CheckmatePractice3() {
    new Pawn("31", board, 1), new Queen("25", board, 1), new Pawn("47", board, 1), new Pawn("56", board, 1), new King("57", board, 1);
    new Pawn("26", board, 0), new Pawn("37", board, 0), new Pawn("43", board, 0), new Queen("73", board, 0), new King("27", board, 0);
}

 
 
void BoardUpdate::Reset(int n) {
    if (n==0) {//resets to empty board
        BlankInit();
    }
    if (n==1) {//resets to standard setup
        StandardInit();
    }
}

/* void BoardUpdate::StartPlaying(){
    int checkmate = 0;
    bool inCheck = false;
    int player = 0;
    while (checkmate < 8) {
        char *x = new char[2];
        char *xpos = new char[2];
        char *pos = new char[2];
        char *temp = new char[2];
        bool validType = false;
        bool firstType = true;
        while (validType == false) {
            cerr << "P" << player % 2 + 1 << ": ";
            if (firstType == false && inCheck == false) cerr << "There's no piece there! Try again." << endl;
            if (inCheck == true) cerr << "Your king's in check! You need to stop the opposing piece from taking your king before you can do anything else!" << endl;
            cerr << "Which piece would you like to use? "; // Type a number and press enter
            cin >> x; // Get user input from the keyboard
            if ( *x== 'x') break;
            if (board[x[1]-'0'][x[0]-'0'] != 0 && board[x[1]-'0'][x[0]-'0']->GetColor() == player % 2) { 
                validType = true;  //checks if the king was selected if in check
            } 
            firstType = false;
        }
        if (strlen(x)==2) cerr << "Your piece is: " << x<< endl<<"What coordinate would you like to move it to? ";
        cin >> pos;
        if (*pos == 'x') break;
        cerr<< "position to move to is: "<< pos<<endl<<endl;
        temp[1]=pos[0];
        temp[0]=pos[1];
        for (int i = 0; i < 2; i++) xpos[i] = x[i] - '0';
	    int *pos2;
	    pos2 = new int[2];
	    for (int i = 0; i < 2; i++) pos2[i] = temp[i] - '0';
        if (temp[0] - '0' < 8 && temp[0] - '0' > -1 && temp[1] - '0' < 8 && temp[1] - '0' > -1) {
            if (board[xpos[1]][xpos[0]]->IsValid(pos2) == true) {
                Piece *p2 = 0;
                if (board[xpos[1]][xpos[0]]->CanITakeThis(pos2) == true) p2 = board[pos2[0]][pos2[1]];
                int pl = board[xpos[1]][xpos[0]]->Move(temp, player); 
                bool kCheck = IsInCheck(k);
                bool KCheck = IsInCheck(K);
                if (kCheck == true || KCheck == true) {
                    if (inCheck == true || (player % 2 == 0 && kCheck == true) || (player % 2 == 1 && KCheck == true)) { //undoes move if it either doesn't get current player out of check or gets themselves into check
                        Piece *p1;
                        p1 = board[pos2[0]][pos2[1]];
                        p1->Remove();
                        if (p2 != 0) p2->AddToBoard(board, temp);
                        char *pos1 = new char[2];
                        pos1[0] = x[1];
                        pos1[1] = x[0];
                        p1->AddToBoard(board, pos1);
                        if (pl != player) pl--;
                        if (inCheck == false) {
                            cerr << "You can't put yourself into check!" << endl;
                        } else {
                            cerr << "That didn't get you out of check!" << endl;
                            checkmate++;
                        }
                    } else inCheck = true;
                } else inCheck = false;
                player = pl;
            } else cerr << "You can't move that way!" << endl;
        } 
        //BoardPrint();
    }
    cerr << "Checkmate! Congratulations P" << player % 2 + 2<< endl;
} */




bool BoardUpdate::IsInCheck(King *k) {
    int *pos = k->GetPosition();
	int i = pos[0] + 1;
	int j = pos[1] + 1;
	while (i < 8 && board[i][pos[1]] == 0) i++;
	if (i < 8) {
    	if (board[i][pos[1]]->IsValid(pos) == true && k->GetColor() != board[i][pos[1]]->GetColor()) return true; //checks threat from downward
	}
	i = pos[0] - 1;
    while (i >= 0 && board[i][pos[1]] == 0) i--;
	if (i >= 0) {
    	if (board[i][pos[1]]->IsValid(pos) == true && k->GetColor() != board[i][pos[1]]->GetColor()) return true; //checks threat from upward
	}
	while (j < 8 && board[pos[0]][j] == 0) j++;
	if (j < 8) {
		if (board[pos[0]][j]->IsValid(pos) == true && k->GetColor() != board[pos[0]][j]->GetColor()) return true; //checks threat from to the right
	}
	j = pos[1] - 1;
	while (j >= 0 && board[pos[0]][j] == 0) j++;
	if (j >= 0) {
		if (board[pos[0]][j]->IsValid(pos) == true && k->GetColor() != board[pos[0]][j]->GetColor()) return true; //checks threat from to the left
	}
	i = pos[0] + 1, j = pos[1] + 1;
	while (i < 8 && j < 8 && board[i][j] == 0) {
		i++; 
		j++;
	}
	if (i < 8 && j < 8) {
		if (board[i][j]->IsValid(pos) == true && k->GetColor() != board[i][j]->GetColor()) return true; //checks threat from lower right
	}
	i = pos[0] - 1, j = pos[1] + 1;
	while (i >= 0 && j < 8 && board[i][j] == 0) {
		i--; 
		j++;
	}
	if (i >= 0 && j < 8) {
		if (board[i][j]->IsValid(pos) == true && k->GetColor() != board[i][j]->GetColor()) return true; //checks threat from upper right
	}
	i = pos[0] + 1, j = pos[1] - 1;
	while (i < 8 && j >= 0 && board[i][j] == 0) {
		i++; 
		j--;
	}
	if (i < 8 && j >= 0) {
		if (board[i][j]->IsValid(pos) == true && k->GetColor() != board[i][j]->GetColor()) return true; //checks threat from lower left
	}
	i = pos[0] - 1, j = pos[1] - 1;
	while (i >= 0 && j >= 0 && board[i][j] == 0) {
		i--; 
		j--;
	}
    //checking knight classes
	if (i >= 0 && j >= 0) {
		if (board[i][j]->IsValid(pos) == true && k->GetColor() != board[i][j]->GetColor()) return true; //checks threat from upper left
	}
    if (pos[0] + 2 < 8 && pos[1] + 1 < 8 && board[pos[0] + 2][pos[1] + 1] != 0) {
        if (board[pos[0] + 2][pos[1] + 1]->IsValid(pos) == true && k->GetColor() != board[pos[0] + 2][pos[1] + 1]->GetColor()) return true;
    }
    if (pos[0] + 2 < 8 && pos[1] - 1 >= 0 && board[pos[0] + 2][pos[1] - 1] != 0) {
        if (board[pos[0] + 2][pos[1] - 1]->IsValid(pos) == true && k->GetColor() != board[pos[0] + 2][pos[1] - 1]->GetColor()) return true;
    }
    if (pos[0] - 2 >= 0 && pos[1] + 1 < 8 && board[pos[0] - 2][pos[1] + 1] != 0) {
        if (board[pos[0] - 2][pos[1] + 1]->IsValid(pos) == true && k->GetColor() != board[pos[0] - 2][pos[1] + 1]->GetColor()) return true;
    }
    if (pos[0] - 2 >= 0 && pos[1] - 1 >= 0 && board[pos[0] - 2][pos[1] - 1] != 0) {
        if (board[pos[0] - 2][pos[1] - 1]->IsValid(pos) == true && k->GetColor() != board[pos[0] - 2][pos[1] - 1]->GetColor()) return true;
    }
    if (pos[0] + 1 < 8 && pos[1] + 2 < 8 && board[pos[0] + 1][pos[1] + 2] != 0) {
        if (board[pos[0] + 1][pos[1] + 2]->IsValid(pos) == true && k->GetColor() != board[pos[0] + 1][pos[1] + 2]->GetColor()) return true;
    }
    if (pos[0] + 2 < 8 && pos[1] - 2 >= 0 && board[pos[0] + 1][pos[1] - 2] != 0) {
        if (board[pos[0] + 1][pos[1] - 2]->IsValid(pos) == true && k->GetColor() != board[pos[0] + 1][pos[1] - 2]->GetColor()) return true;
    }
    if (pos[0] - 1 >= 0 && pos[1] + 2 < 8 && board[pos[0] - 1][pos[1] + 2] != 0) {
        if (board[pos[0] - 1][pos[1] + 2]->IsValid(pos) == true && k->GetColor() != board[pos[0] - 1][pos[1] + 2]->GetColor()) return true;
    }
    if (pos[0] - 1 >= 0 && pos[1] - 2 >= 0 && board[pos[0] - 1][pos[1] - 2] != 0) {
        if (board[pos[0] - 1][pos[1] - 2]->IsValid(pos) == true && k->GetColor() != board[pos[0] - 1][pos[1] - 2]->GetColor()) return true;
    }
	return false; //returns false if there are no threatss
}
