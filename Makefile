CC = g++
CFLAGS = -Wall -g

game: main.o Action.o State.o Game.o TicTacToeAction.o TicTacToeState.o TicTacToe.o Search.o
	$(CC) $(CFLAGS) -o game main.o Action.o State.o Game.o TicTacToeAction.o TicTacToeState.o TicTacToe.o Search.o

main.o: main.cpp TicTacToe.h Search.h
	$(CC) $(CFLAGS) -c main.cpp

TicTacToe.o: TicTacToe.h Game.h TicTacToeState.h TicTacToeAction.h

Search.o: Search.h Game.h

Game.o: Game.h Action.h State.h

State.o: State.h

Action.o: Action.h

TicTacToeAction.o: TicTacToeAction.h Action.h

TicTacToeState.o: TicTacToeState.h State.h

clean:
	$(RM) game *.o *~


