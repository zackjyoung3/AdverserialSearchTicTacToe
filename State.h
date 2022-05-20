#ifndef ADVERSERIALSEARCHTICTACTOE_STATE_H
#define ADVERSERIALSEARCHTICTACTOE_STATE_H
#include <iostream>

using namespace std;

// enum for the player
enum Player{MIN, MAX};

// abstract class of a State in a Game
class State
{
public:
    State(Player);
    virtual ~State() {};
    virtual void print(ostream& str) const = 0;
    friend ostream& operator<< (ostream& out, const State& s) {
        s.print(out);
        return out;
    }
    Player get_player();
    Player get_adversary();
    void set_player(Player);
protected:
    Player player;

};

#endif //ADVERSERIALSEARCHTICTACTOE_STATE_H
