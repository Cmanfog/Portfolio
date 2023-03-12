# React Chess


CN Inc. 
Connor Fogarty, Noah Tibben-Lembke
React Chess

The Files themselves (make ChessDriver; ./ChessDriver) allow a user to play fully interactive chess, with move-checking functions to see if moves are valid for each piece, to see if they're blocked by any other pieces, and to see if check or checkmate is reached.

The webstie (../bridge.py in one terminal, make all in the other) is limited by the fact that the baord resets itself every time we send information back and forth between the server and client, so only one move can be made at a time. 

Noah contributed the creation of BoardUpdate methods as well as most of the React framework and yaml files.

Connor contribute the creation of the Piece class and subclasses as well as the most of the logic behind moving pieces (isinCheck, isTaken, etc) and the framework of the code in the C++ terminal.

Both of us have checked and mingled in each other's work.