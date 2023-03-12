#include "Piece.h"


Piece::Piece(const char *p, Piece ***b, char n, int c) {
	name = n;
	board = b;
	pos = new int[2];
	for (int i = 0; i < 2; i++) {
		pos[i] = p[i] - '0';
	}
	if ( c == 0 || c==1) color = c;
	else {
		std::cerr<<"Invalid piece color"<<std::endl;
		color = 0;
	}
	if (c == 1) name = n - 32;
	board[pos[0]][pos[1]] = this; //pos[0] is a row, pos[1] is a column
}

Piece::Piece() {
	color = 0;
	name = 'p';
	pos = new int[2];
	board = 0;
}

Piece::Piece(char n) {
	color = 0;
	name = n;
	pos = new int[2];
	board = 0;
}

Piece::~Piece() {
	delete [] pos;
	board = 0;
}
int Piece::GetColor() {
	return color;
}

int *Piece::GetPosition() {
	return pos;
}

int Piece::Move(const char *p, int player) {
	int pl = player;
	int *pos2;
	pos2 = new int[2];
	for (int i = 0; i < 2; i++) {
		pos2[i] = p[i] - '0';
	}
	//if (color == board[pos2[0]][pos2[1]]->GetColor()) {std::cout<<"yeah the're the same"<<std::endl;}	
	if (CanITakeThis(pos2) == true) { //for moving to spaces with opposing pieces
		Take(pos2);
		AddToBoard(board, p);
		pl++;
	}
	else if (board[pos2[0]][pos2[1]] == 0) { //for moving to blank spaces
		board[pos[0]][pos[1]] = 0;
		for (int i = 0; i < 2; i++) pos[i] = pos2[i];
		AddToBoard(board, p);
		pl++;
	}
	else std::cerr << "You can't take your own piece!" << std::endl; //when trying to move to a space with a piece of the same color
	return pl;
}
void Piece::AddToBoard(Piece ***b, const char *p) { 
	board = b;
	for (int i = 0; i < 2; i++) pos[i] = p[i] - '0';
	board[pos[0]][pos[1]] = this;
}

bool Piece::CanITakeThis (int *pos2){
	if(board[pos2[0]][pos2[1]] != 0 &&  color != board[pos2[0]][pos2[1]]->GetColor()) return true;
	return false;
}
void Piece::Take(int *pos2) { 
	std::cerr << "A(n) " << board[pos2[0]][pos2[1]]->GetName() << " has been taken!" << std::endl; //for some reason this doesn't work right
	board[pos[0]][pos[1]] = 0;
	for (int i = 0; i < 2; i++) pos[i] = pos2[i];
}

Piece &Piece::Remove() { //used for testing whether or not check is about to occur
	board[pos[0]][pos[1]] = 0;
	return *this;
}

Pawn::Pawn (const char *p, Piece ***b, int c) : Piece(p, b, 'p', c) {
	if (c==0){img+= "BPawn.png";}
	else if (c==1) {img+= "WPawn.png";}
}

Pawn::Pawn() : Piece('p') {
	img+= "BPawn.png";
}

Pawn::~Pawn () {
	img = "0";
}

bool Pawn::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (GetColor() == 0) {
		if (pos2[0] - pos[0] == 1) {
			if (pos[1] == pos2[1] && board[pos2[0]][pos2[1]] == 0) return true; //move forward one space
			if ((pos[1] - pos2[1] == 1 || pos2[1] - pos[1] == 1) && CanITakeThis(pos2) == true) return true; //steal another piece in diagonal direction
		}
		if (pos[0] == 1 && pos2[0] - pos[0] == 2 && pos[1] == pos2[1] && board[pos2[0]][pos2[1]] == 0 && board[2][pos[1]] == 0) return true; //move foward two spaces (when just starting)
	}
	else {
		if (pos[0] - pos2[0] == 1) {
			if (pos[1] == pos2[1] && board[pos2[0]][pos2[1]] == 0) return true; //move forward one space
			if ((pos[1] - pos2[1] == 1 || pos2[1] - pos[1] == 1) && CanITakeThis(pos2) == true) return true; //steal another piece in diagonal direction
		}
		if (pos[0] == 6 && pos[0] - pos2[0] == 2 && pos[1] == pos2[1] && board[pos2[0]][pos2[1]] == 0 && board[5][pos[1]] == 0) return true; //move foward two spaces (when just starting)
	}
	return false;
}

const char *Pawn::Ruleset() {
	const char *p = "Pawns are the most common piece in the game. At the start of the game, they are able to move one or two spaces forward. Afterwards, they can only move forward one space as long as there is nothing in front of them. They can also move by capturing other pieces that are in front of them diagonally.";
	return p;
}

std::string Pawn::GetImg() {return img;}

Rook::Rook (const char *p, Piece ***b, int c) : Piece(p, b, 'r', c) {
	if (c==0){img+= "BRook.png";}
	else if (c==1) {img+= "WRook.png";}
}

Rook::Rook() : Piece('r') {img+= "BRook.png";}

Rook::~Rook () {
	img = "0";
}

bool Rook::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (pos2[0] == pos[0]) {
		if (pos[1] < pos2[1]) {
			for (int j = pos[1] + 1; j < pos2[1]; j++) {
				if (board[pos[0]][j] != 0) return false; // makes sure there's no other pieces on way to destination
			}
		}
		if (pos[1] > pos2[1]) {
			for (int j = pos2[1] + 1; j < pos[1]; j++) {
				if (board[pos[0]][j] != 0) return false;
			}
		}
		return true; // moving horizontally
	} 
	if (pos2[1] == pos[1]) {
		if (pos[0] < pos2[0]) {
			for (int i = pos[0] + 1; i < pos2[0]; i++) {
				if (board[i][pos[1]] != 0) return false; 
			}
		}
		if (pos[0] > pos2[0]) {
			for (int i = pos2[0] + 1; i < pos[0]; i++) {
				if (board[i][pos[1]] != 0) return false; 
			}
		}
		return true; // moving vertically
	}
	return false;
}

const char *Rook::Ruleset() {
	const char *r = "Rooks can be found on the each corner of the board. They are capable of moving horizontally or vertically for as many empty spaces as the player desires.";
	return r;
}

std::string Rook::GetImg() {return img;}

Bishop::Bishop (const char *p, Piece ***b, int c) : Piece(p, b, 'b', c) {
	if (c==0){img+= "BBishop.png";}
	else if (c==1) {img+= "WBishop.png";}
}

Bishop::Bishop() : Piece('b') {img+= "BBishop.png";}

Bishop::~Bishop () {
	img = "0";
}

bool Bishop::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (pos2[0] == pos[0] || pos2[1] == pos[1]) return false; // a bishop should never move to a space in the same row or column as where it started.
	if ((pos2[0] - pos[0]) / (pos2[1] - pos[1]) == 1)  {
		if (pos[0] < pos2[0]) {
			int i = pos[0] + 1, j = pos[1] + 1;
			while (board[i][j] != board[pos2[0]][pos2[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j++;
			}
		}
		if (pos2[0] < pos[0]) {
			int i = pos2[0] + 1, j = pos2[1] + 1;
			while (board[i][j] != board[pos[0]][pos[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j++;
			}
		}
		return true; //moving diagonally
	}
	if ((pos2[0] - pos[0]) / (pos2[1] - pos[1]) == -1) {
		if (pos[0] < pos2[0]) {
			int i = pos[0] + 1, j = pos[1] - 1;
			while (board[i][j] != board[pos2[0]][pos2[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j--;
			}
		}
		if (pos2[0] < pos[0]) {
			int i = pos2[0] + 1, j = pos2[1] - 1;
			while (board[i][j] != board[pos[0]][pos[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j--;
			}
		}
		return true; //moving diagonally 
	}
	return false;
}

const char *Bishop::Ruleset() {
	const char *b = "Bishops are capable of moving in any direction diagonally across the board. Here's a tip: If a bishop is on a darker space, it can only go to other darker spaces. Same thing if it's on a lighter space.";
	return b;
}

std::string Bishop::GetImg() {return img;}

Knight::Knight (const char *p, Piece ***b, int c) : Piece(p, b, 'n', c) {
	if (c==0){img+= "BKnight.png";}
	else if (c==1) {img+= "WKnight.png";}
}

Knight::Knight() : Piece('n') {img+= "BRook.png";}

Knight::~Knight () {
	img = "0";
}

bool Knight::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (pos2[0] - pos[0] == 1 || pos[0] - pos2[0] == 1) {
		if (pos2[1] - pos[1] == 2 || pos[1] - pos2[1] == 2) return true;
	}
	if (pos2[1] - pos[1] == 1 || pos[1] - pos2[1] == 1) {
		if (pos2[0] - pos[0] == 2 || pos[0] - pos2[0] == 2) return true;
	}
	return false;
}

const char *Knight::Ruleset() {
	const char *n = "Despite the fact that knights are represented by mere horses and not their riders, these pieces are capable of going places other pieces can't. Knights can only move to another space that one space apart in one direction and two spaces apart in the direction perpendicular to it. Basically, if you can make L-shape to your destination, you can go there. ";
	return n;
}

std::string Knight::GetImg() {return img;}

Queen::Queen (const char *p, Piece ***b, int c) : Piece(p, b, 'q', c) {
	if (c==0){img+= "BQueen.png";}
	else if (c==1) {img+= "WQueen.png";}
}

Queen::Queen() : Piece('q') {img += "BQueen.png";}

Queen::~Queen () {
	img = "0";
}

bool Queen::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (pos2[0] == pos[0]) {
		if (pos[1] < pos2[1]) {
			for (int j = pos[1] + 1; j < pos2[1]; j++) {
				if (board[pos[0]][j] != 0) return false; // for/while loops in the isValid methods make sure there's no other pieces on way to destination
			}
		}
		if (pos[1] > pos2[1]) {
			for (int j = pos2[1] + 1; j < pos[1]; j++) {
				if (board[pos[0]][j] != 0) return false;
			}
		}
		return true; // moving horizontally
	} 
	if (pos2[1] == pos[1]) {
		if (pos[0] < pos2[0]) {
			for (int i = pos[0] + 1; i < pos2[0]; i++) {
				if (board[i][pos[1]] != 0) return false; 
			}
		}
		if (pos[0] > pos2[0]) {
			for (int i = pos2[0] + 1; i < pos[0]; i++) {
				if (board[i][pos[1]] != 0) return false; 
			}
		}
		return true; // moving vertically
	}
	if ((pos2[0] - pos[0]) / (pos2[1] - pos[1]) == 1)  {
		if (pos[0] < pos2[0]) {
			int i = pos[0] + 1, j = pos[1] + 1;
			while (board[i][j] != board[pos2[0]][pos2[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j++;
			}
		}
		if (pos2[0] < pos[0]) {
			int i = pos2[0] + 1, j = pos2[1] + 1;
			while (board[i][j] != board[pos[0]][pos[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j++;
			}
		}
		return true; //moving diagonally
	}
	if ((pos2[0] - pos[0]) / (pos2[1] - pos[1]) == -1) {
		if (pos[0] < pos2[0]) {
			int i = pos[0] + 1, j = pos[1] - 1;
			while (board[i][j] != board[pos2[0]][pos2[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j--;
			}
		}
		if (pos2[0] < pos[0]) {
			int i = pos2[0] + 1, j = pos2[1] - 1;
			while (board[i][j] != board[pos[0]][pos[1]]) {
				if (board[i][j] != 0) return false;
				i++;
				j--;
			}
		}
		return true; //moving diagonally 
	}
	return false;
}

const char *Queen::Ruleset() {
	const char *q = "Queens are by far the most powerful and versatile pieces in the game. They can move in any direction horizontally, vetically or diagonally, meaning they can go places that other pieces like bishops or rooks would have a hard time getting to. Be wary of where you put this one, because if the other person has a queen and yours gets taken, you'll be at a disadvantage. Think smart.";
	return q;
}

std::string Queen::GetImg() {return img;}

King::King (const char *p, Piece ***b, int c) : Piece(p, b, 'k', c) {
	if (c==0){img+= "BKing.png";}
	else if (c==1) {img+= "WKing.png";}
}

King::King() : Piece('k') {img+= "BKing.png";}

King::~King () {
	img = "0";
}

bool King::IsValid(int *pos2) {
	int *pos = GetPosition();
	if (pos2[1] == pos[1]) {
		if (pos2[0] - pos[0] == 1 || pos[0] - pos2[0] == 1) return true; // moves one space horizontally
	}
	if (pos2[0] == pos[0]) {
		if (pos2[1] - pos[1] == 1 || pos[1] - pos2[1] == 1) return true; // moves one space vertically
	}
	if ((pos2[1] - pos[1] == 1 || pos[1] - pos2[1] == 1) && (pos2[0] - pos[0] == 1 || pos[0] - pos2[0] == 1)) return true; // moves one space diagonally
	return false;
}

const char *King::Ruleset() {
	const char *k = "Kings are the most vital piece in the game. It can only move one space in any horizontal, vertical, or diagonal direction. If an opposing piece can take the king within a move, the king is put in check, meaning you have to find a way to stop the opposing piece from getting to your king. If there is no possible way to avoid your king being taken, the result is a checkmate and other player wins.";
	return k;
}

std::string King::GetImg() {return img;}
