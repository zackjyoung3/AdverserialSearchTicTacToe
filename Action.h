#ifndef ADVERSERIALSEARCHTICTACTOE_ACTION_H
#define ADVERSERIALSEARCHTICTACTOE_ACTION_H
#include <iostream>

using namespace std;

// abstract class for an action in a game
class Action{
public:
    // default constructor
    Action();
    // virtual destructor
    virtual ~Action() {};
    // virtual print method
    virtual void print(ostream& str) const = 0;
    friend ostream& operator<< (ostream& out, const Action& a)
    {
        a.print(out);
        return out;
    }
};

#endif //ADVERSERIALSEARCHTICTACTOE_ACTION_H
