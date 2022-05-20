#ifndef ADVERSERIALSEARCHTICTACTOE_GAME_H
#define ADVERSERIALSEARCHTICTACTOE_GAME_H
#include "State.h"
#include "Action.h"
#include <limits>
#include <list>

using namespace std;

// abstract class for a Game
class Game{
public:
    // constructor
    Game(int max_depth = numeric_limits<int>::max());
    // virtual destructor
    virtual ~Game(){}
    virtual void init(Player) = 0;
    Player to_move(State *s);
    void set_current_state(State *s);
    // return the current state
    State* get_current_state() {return currentState;};
    virtual list<Action*> actions(State *s) = 0;
    virtual State* result(State *s, Action *a) = 0;
    virtual bool isTerminal(State *s) = 0;
    // utility function that determines the utility of terminal states for players
    virtual double utility(State *s, Player p) = 0;
    virtual bool isCutoff(State *s, int d) = 0;
    // Heuristic evaluation function so that in heuristic MiniMax, we can evaluate
    // nonterminal states
    virtual double eval(State *s, Player p = MAX) const = 0;
    virtual void print(ostream& out) const = 0;
    virtual bool finished() = 0;
    virtual void obtain_action() = 0;
    friend ostream& operator<< (ostream& out, const Game& game)
    {
        game.print(out);
        return out;
    }
protected:
    Player player;
    State *currentState;
    int max_depth;
};

#endif //ADVERSERIALSEARCHTICTACTOE_GAME_H
