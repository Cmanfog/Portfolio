#ifndef _PIECE_H_
#define _PIECE_H_
#include<iostream>
#include<string>
 
 
class Piece {
	char name;
	int color;
public:
	int *pos;
	Piece ***board;
	Piece(const char *p, Piece ***b, char n, int c);
	Piece(const char *p, Piece *b, char n, int c);
	Piece(char n);
	Piece();
	//~Piece();
	virtual ~Piece();
	int GetColor();
	int *GetPosition();
	const char GetName() {return this->name;}
	int Move(const char *p, int player);
	virtual bool IsValid(int *pos2) = 0;
	void AddToBoard(Piece ***b, const char *p);
	Piece &Remove();
	bool CanITakeThis (int *pos2);
	void Take(int *pos2);
	virtual std::string GetImg(){return 0;}
	//void TypeToPos(const char *n) { Move(n);}
};

class Pawn : public Piece{
	std::string img;
public:
	Pawn(const char *p, Piece ***b, int c);
	Pawn();
	~Pawn();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
};

class Rook : public Piece{
	std::string img;
public:
	Rook(const char *p, Piece ***b, int c);
	Rook();
	~Rook();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
};

class Bishop : public Piece{
	std::string img;
public:
	Bishop(const char *p, Piece ***b, int c);
	Bishop();
	~Bishop();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
};

class Knight : public Piece{
	std::string img;
public:
	Knight(const char *p, Piece ***b, int c);
	Knight();
	~Knight();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
};

class Queen : public Piece{
	std::string img;
public:
	Queen(const char *p, Piece ***b, int c);
	Queen();
	~Queen();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
};

class King : public Piece{
	std::string img;
public:
	King(const char *p, Piece ***b, int c);
	King();
	~King();
	bool IsValid(int *pos2);
	const char *Ruleset();
	std::string GetImg();
	bool IsInCheck();
};
 
#endif