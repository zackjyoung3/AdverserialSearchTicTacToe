#ifndef ADVERSERIALSEARCHTICTACTOE_TICTACTOE_H
#define ADVERSERIALSEARCHTICTACTOE_TICTACTOE_H
#include "Game.h"
#include "TicTacToeState.h"
#include "TicTacToeAction.h"
#include <random>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

// TicTacToe inherits from abstract base class Game
class TicTacToe : public Game
{
public:
    TicTacToe(Player, int max_depth = numeric_limits<int>::max());
    ~TicTacToe() {delete currentState;}
    void init(Player);
    list<Action*> actions(State *s);
    State* result(State *s, Action *a);
    bool isTerminal(State *s);
    double utility(State *s, Player p = MAX);
    bool isCutoff(State *s, int d);
    double eval(State *s, Player p) const;
    void print(ostream& out) const;
    void obtain_action();
    bool finished();
};
#endif //ADVERSERIALSEARCHTICTACTOE_TICTACTOE_H
