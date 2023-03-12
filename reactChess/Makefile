all:	a.out

PieceDriver:  PieceDriver.o Piece.o
	g++ -Wall -o PieceDriver PieceDriver.o Piece.o
 
Piece.o:  Piece.cpp Piece.h
	g++ -Wall -g -c Piece.cpp
 
PieceDriver.o:  PieceDriver.cpp Piece.h 
	g++ -Wall -c PieceDriver.cpp
 
BoardUpdate.o:  BoardUpdate.cpp BoardUpdate.h
	g++ -Wall -g -c BoardUpdate.cpp
 
BoardUpdateDriver.o:  BoardUpdateDriver.cpp BoardUpdate.h 
	g++ -Wall -o BoardUpdateDriver.cpp
 
BoardUpdateDriver:  BoardUpdateDriver.o BoardUpdate.o
	g++ -Wall -o BoardUpdateDriver BoardUpdateDriver.o BoardUpdate.o
 
ChessDriver.o:  ChessDriver.cpp BoardUpdate.h Piece.h
	g++ -Wall -c ChessDriver.cpp
 
ChessDriver:    ChessDriver.o BoardUpdate.o Piece.o
	g++ -Wall -o ChessDriver ChessDriver.o BoardUpdate.o Piece.o

a.out:	WebDriver.o BoardUpdate.o Piece.o Settings.yaml TitlePage.yaml 2player.yaml squarea0.yaml
	g++ -Wall -g WebDriver.o BoardUpdate.o Piece.o ../react.o -lcurl

WebDriver.o:	WebDriver.cpp Piece.h BoardUpdate.h
	g++ -Wall -g -c WebDriver.cpp	
