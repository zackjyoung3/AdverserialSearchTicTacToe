#ifndef ADVERSERIALSEARCHTICTACTOE_SEARCH_H
#define ADVERSERIALSEARCHTICTACTOE_SEARCH_H
#include "Game.h"
#include <utility>
#include <limits>
#include <list>

using namespace std;

// generic search class for adversarial search in a Game from a State
class Search{
public:
    Search(Game*, State*);
    Action* MiniMax();
    Action* Aggressive_MiniMax();
    Action* Alpha_Beta();
    Action* Heuristic_MiniMax();
private:
    pair<double,Action*> Max_Value(Game*, State*);
    pair<double,Action*> Min_Value(Game*, State*);
    pair<pair<double,int>, Action*> Aggressive_Max_Value(Game*, State*, int depth);
    pair<pair<double, int>, Action*> Aggressive_Min_Value(Game*, State*, int depth);
    pair<double,Action*> Max_Value(Game*, State*,double,double);
    pair<double,Action*> Min_Value(Game*, State*,double,double);
    pair<double,Action*> Max_Value(Game*, State*,double,double, int);
    pair<double,Action*> Min_Value(Game*, State*,double,double, int);
    Game *game;
    State *s;
    Player player;
};

#endif //ADVERSERIALSEARCHTICTACTOE_SEARCH_H
