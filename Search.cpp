#include "Search.h"

// Constructor with the game and state to search from passed in
Search ::Search(Game *game, State *s)
{
    this->game = game;
    this->s = s;
}

// function MiniMax returns the action to be taken
Action* Search :: MiniMax()
{
    player = game->to_move(s);
    pair<double, Action*> value_move = Max_Value(game,s);
    return value_move.second;
}

// function Max_Value returns a utility, move pair under the assumption that both players are playing optimally
pair<double, Action*> Search :: Max_Value(Game *game, State *state)
{
    // if the state is a terminal state, return the utility for the player
    if(game->isTerminal(state))
    {
        double utility = game->utility(state, player);
        delete state;
        return pair<double, Action*>(utility, nullptr);
    }

    pair<double, Action*> v_move(-numeric_limits<double>::infinity(), nullptr);
    // obtain the actions available from this state
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        // obtain a utility, move pair from Min_Value
        pair<double, Action*> v2_a2 = Min_Value(game,game->result(state, *a));
        delete v2_a2.second;

        // if the utility from the result of the move is greater than the best so far => update v_move
        if(v2_a2.first > v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;
        }
        else
        {
            delete *a;
        }
    }

    if(state != s)
    {
        delete state;
    }

    return v_move;
}

// function Min_Value returns a utility, move pair under the assumption that both players are playing optimally
pair<double, Action*> Search :: Min_Value(Game *game, State *state)
{
    // if the state is a terminal state then return the utility of that state
    if(game->isTerminal(state))
    {
        double utility = game->utility(state, player);
        delete state;
        return pair<double, Action*>(utility, nullptr);
    }
    pair<double, Action*> v_move(numeric_limits<double>::infinity(), nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions to find the action such that the utility for the max player
    // is minimized
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<double, Action*> v2_a2 = Max_Value(game,game->result(state, *a));
        delete v2_a2.second;
        if(v2_a2.first < v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;
        }
        else
        {
            delete *a;
        }
    }

    delete state;
    return v_move;
}

// function Aggressive MiniMax returns the action to be taken
// with actions that have equal utility, the agent will prefer to take actions
// where the utility was attained at a lower depth in the game tree
Action* Search :: Aggressive_MiniMax()
{
    player = game->to_move(s);
    pair<pair<double,int>, Action*> value_move = Aggressive_Max_Value(game,s, 1);
    return value_move.second;
}

// function Aggressive Max_Value returns a utility, depth, and move
pair<pair<double,int>, Action*> Search :: Aggressive_Max_Value(Game *game, State *state, int depth)
{
    // same as normal Max_Value but now also returns the depth
    if(game->isTerminal(state))
    {
        pair<double,int> temp(game->utility(state, player), depth);
        delete state;
        return pair<pair<double,int>, Action*>(temp, nullptr);
    }
    pair<double,int> init(-numeric_limits<double>::infinity(), numeric_limits<int>::infinity());
    pair<pair<double,int>, Action*> v_move(init, nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<pair<double,int>, Action*> v2_a2 = Aggressive_Min_Value(game,game->result(state, *a), depth+1);
        delete v2_a2.second;
        // note that here there is the second comparison, so the agent will value an action that leads to
        // attaining the same utility quicker, along with moves that are of greater utility than have been
        // observed thus far
        if(v2_a2.first.first > v_move.first.first ||
        (v2_a2.first.first == v_move.first.first && v2_a2.first.second < v_move.first.second))
        {
            v_move.first.first = v2_a2.first.first;
            v_move.first.second = v2_a2.first.second;
            delete v_move.second;
            v_move.second = *a;
        }
        else
        {
            delete *a;
        }
    }

    if(state != s)
    {
        delete state;
    }
    return v_move;
}

// function Aggressive Min_Value returns a utility, depth, and move
pair<pair<double,int>, Action*> Search :: Aggressive_Min_Value(Game *game, State *state, int depth)
{
    // same as normal Min_Value but now also returns the depth
    if(game->isTerminal(state))
    {
        pair<double,int> temp(game->utility(state, player), depth);
        delete state;
        return pair<pair<double,int>, Action*>(temp, nullptr);
    }
    pair<double,int> init(numeric_limits<double>::infinity(), numeric_limits<int>::infinity());
    pair<pair<double,int>, Action*> v_move(init, nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<pair<double,int>, Action*> v2_a2 = Aggressive_Max_Value(game,game->result(state, *a), depth+1);
        delete v2_a2.second;
        // again preferring actions that minimize the Max Player's utility and those where this minimization
        // of the Max player's utility is achieved at a lesser depth
        if(v2_a2.first.first < v_move.first.first ||
           (v2_a2.first.first == v_move.first.first && v2_a2.first.second < v_move.first.second))
        {
            v_move.first.first = v2_a2.first.first;
            v_move.first.second = v2_a2.first.second;
            delete v_move.second;
            v_move.second = *a;
        }
        else
        {
            delete *a;
        }
    }

    delete state;
    return v_move;
}

// function Alpha Beta returns an action
// uses alpha beta pruning
Action* Search :: Alpha_Beta()
{
    player = game->to_move(s);
    pair<double, Action*> value_move = Max_Value(game,s, -numeric_limits<double>::infinity(),
                                                 numeric_limits<double>::infinity());
    return value_move.second;
}

// function Max_Value with Alpha Beta Pruning where we will prune large parts of the game tree
// that make no difference to the outcome of search
pair<double, Action*> Search :: Max_Value(Game *game, State *state, double alpha, double beta)
{
    // return utility if the state is a terminal state
    if(game->isTerminal(state))
    {
        double utility = game->utility(state, player);
        delete state;
        return pair<double, Action*>(utility, nullptr);
    }
    pair<double, Action*> v_move(-numeric_limits<double>::infinity(), nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<double, Action*> v2_a2 = Min_Value(game,game->result(state, *a), alpha, beta);
        delete v2_a2.second;
        if(v2_a2.first > v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;

            // now updating alpha if necessary ie the value of the best choice that we have
            // found thus far in the path for Max
            alpha = max(alpha, v_move.first);
        }
        else
        {
            delete *a;
        }

        // in Alpha Beta Pruning, beta is the value of the best move that we have found along the path for
        // Min, thus we want value of at most Beta
        if(v_move.first >= beta)
        {
            if(state != s)
            {
                delete state;
            }
            for(a; a != available_actions.end(); ++a)
            {
                if(*a != v_move.second)
                    delete *a;
            }
            return v_move;
        }
    }

    if(state != s)
    {
        delete state;
    }
    return v_move;
}

// function Min_Value with Alpha Beta Pruning where we will prune large parts of the game tree
// that make no difference to the outcome of search
pair<double, Action*> Search :: Min_Value(Game *game, State *state, double alpha, double beta)
{
    // return if isTerminal
    if(game->isTerminal(state))
    {
        double utility = game->utility(state, player);
        delete state;
        return pair<double, Action*>(utility, nullptr);
    }
    pair<double, Action*> v_move(numeric_limits<double>::infinity(), nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<double, Action*> v2_a2 = Max_Value(game,game->result(state, *a), alpha, beta);
        delete v2_a2.second;
        if(v2_a2.first < v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;

            // update beta if necessary
            beta = min(beta, v_move.first);
        }
        else
        {
            delete *a;
        }

        // value must be at least alpha, the best choice that we have found along the path for Max
        if(v_move.first <= alpha)
        {
            delete state;
            for(a; a != available_actions.end(); ++a)
            {
                if(*a != v_move.second)
                    delete *a;
            }
            return v_move;
        }
    }

    delete state;
    return v_move;
}

// function Heuristic MiniMax with Alpha Beta Pruning
// we expand the game tree until isCutoff is true at which point we apply a heuristic evaluation function
// and thus can stop expanding the game tree at a certain depth even if the state is not terminal
Action* Search :: Heuristic_MiniMax()
{
    player = game->to_move(s);
    pair<double, Action*> value_move = Max_Value(game,s, -numeric_limits<double>::infinity(),
                                                 numeric_limits<double>::infinity(), 1);
    return value_move.second;
}

// function Max_Value return utility, move pair for Heuristic MiniMax
pair<double, Action*> Search :: Max_Value(Game *game, State *state, double alpha, double beta, int depth)
{
    // note that now we check to see if state is cutoff
    // ie either is terminal or is the maximum depth specified
    if(game->isCutoff(state, depth))
    {
        // now using a heuristic evaluation function so we can evaluate non terminal states
        double eval = game->eval(state, player);
        delete state;
        return pair<double, Action*>(eval, nullptr);
    }
    pair<double, Action*> v_move(-numeric_limits<double>::infinity(), nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<double, Action*> v2_a2 = Min_Value(game,game->result(state, *a), alpha, beta, depth+1);
        delete v2_a2.second;
        if(v2_a2.first > v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;

            alpha = max(alpha, v_move.first);
        }
        else
        {
            delete *a;
        }

        if(v_move.first >= beta)
        {
            delete state;
            for(a; a != available_actions.end(); ++a)
            {
                if(*a != v_move.second)
                    delete *a;
            }

            return v_move;
        }
    }

    if(state != s)
    {
        delete state;
    }
    return v_move;
}

// function Min_Value return utility, move pair for Heuristic MiniMax
pair<double, Action*> Search :: Min_Value(Game *game, State *state, double alpha, double beta, int depth)
{
    // check if the state is a cutoff state
    if(game->isCutoff(state, depth))
    {
        // if it is eval the state
        double eval = game->eval(state, player);
        delete state;
        return pair<double, Action*>(eval, nullptr);
    }
    pair<double, Action*> v_move(numeric_limits<double>::infinity(), nullptr);
    list<Action*> available_actions = game->actions(state);
    list<Action*>::iterator a;
    // iterate over the actions
    for(a = available_actions.begin(); a != available_actions.end(); ++a)
    {
        pair<double, Action*> v2_a2 = Max_Value(game,game->result(state, *a), alpha, beta, depth+1);
        delete v2_a2.second;
        if(v2_a2.first < v_move.first)
        {
            v_move.first = v2_a2.first;
            delete v_move.second;
            v_move.second = *a;

            beta = min(beta, v_move.first);
        }
        else
        {
            delete *a;
        }

        if(v_move.first <= alpha)
        {
            delete state;
            for(a; a != available_actions.end(); ++a)
            {
                if(*a != v_move.second)
                    delete *a;
            }

            return v_move;
        }
    }

    delete state;
    return v_move;
}