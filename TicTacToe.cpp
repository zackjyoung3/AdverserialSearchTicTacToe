#include "TicTacToe.h"

// constructor for TicTacToe with the player and max search depth for Heuristic MiniMax passed in
TicTacToe :: TicTacToe(Player player, int max_depth) : Game(max_depth)
{
    init(player);
}

// init
void TicTacToe :: init(Player player)
{
    currentState = new TicTacToeState(player);
}

// function actions returns a list of Actions available from this state
list<Action*> TicTacToe ::actions(State *s)
{
    list<Action*> available_actions;
    vector<int> open_tiles = dynamic_cast<TicTacToeState*>(s)->get_available_tiles();
    vector<int>::iterator it;

    // note that there is randomization so that if there are multiple actions with highest utility
    // we don't just choose the same one every time
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(open_tiles.begin(), open_tiles.end(), default_random_engine(seed));

    for(it = open_tiles.begin(); it != open_tiles.end(); ++it)
    {
        available_actions.push_back(new TicTacToeAction(*it, s->get_player()));
    }

    return available_actions;
}

// transition model, specifies the state that results from taking an action in a particular state
State* TicTacToe :: result(State *s, Action *a)
{
    return new TicTacToeState(dynamic_cast<TicTacToeState*>(s),dynamic_cast<TicTacToeAction*>(a)->get_action_num()-1);
}

// test for if the TicTacToe state is a terminal state
bool TicTacToe :: isTerminal(State *s)
{
    TicTacToeState *ttt_state =dynamic_cast<TicTacToeState*>(s);
    if(ttt_state->is_win().first)
    {
        return true;
    }
    else if(ttt_state->is_full())
    {
        return true;
    }

    return false;
}

// returns the utility of the state for the player
double TicTacToe :: utility(State *s, Player p)
{
    TicTacToeState *ttt_state =dynamic_cast<TicTacToeState*>(s);
    // if there is a winner return the utility of +1 if the player is the max player and -1
    // if the player is the min player
    pair<bool, Player> win = ttt_state->is_win();
    if(win.first)
    {
        if(win.second == p)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    // if neither player won, it is a draw and give utility 0
    else
    {
        return 0;
    }
}

// performs the cutoff test for heuristic minimax
bool TicTacToe :: isCutoff(State *s, int d)
{
    if(isTerminal(s))
    {
        return true;
    }
    else if(d == max_depth)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Heuristic evaluation function for TicTacToe
double TicTacToe :: eval(State *s, Player p) const
{
    TicTacToeState *ttt_state =dynamic_cast<TicTacToeState*>(s);
    return (100*ttt_state->unblocked(3, MAX) + 10*ttt_state->unblocked(2, MAX) + ttt_state->unblocked(1, MAX)
            - (100*ttt_state->unblocked(3, MIN) + 10*ttt_state->unblocked(2, MIN) + ttt_state->unblocked(1, MIN)));
}

// prints the TicTacToe board
void TicTacToe ::print(ostream &out) const
{
    currentState->print(out);
}

// method for obtaining and taking an action specified by the user
void TicTacToe ::obtain_action()
{
    cout << "Please enter the space that you wish to fill from the available spaces(Note top row is (1,2,3),\nmiddle (4,5,6)"
            " and bottom is (7,8,9)):";
    int space;
    cin >> space;
    list<Action*> available_actions = actions(currentState);
    list<Action*>::iterator a;

    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        if(dynamic_cast<TicTacToeAction*>(*a)->get_action_num() == space)
        {
            Action *action = new TicTacToeAction(space, currentState->get_player());
            State *temp = currentState;
            currentState = result(currentState,action);
            delete temp;
            for(a; a != available_actions.end(); ++a)
            {
                delete *a;
            }
            delete action;
            return;
        }
        delete *a;
    }

    cout << "Please enter a valid action from those remaining!" << endl;
    cout << *this << endl;
    obtain_action();
}

// returns if the game is finished
bool TicTacToe :: finished()
{
    if(isTerminal(currentState))
    {
        return true;
    }
    return false;
}