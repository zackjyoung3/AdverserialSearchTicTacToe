#include <iostream>
#include "TicTacToe.h"
#include "Search.h"
#include <chrono>

using namespace std;
using chrono::high_resolution_clock;
using chrono::duration_cast;
using chrono::duration;
using chrono::milliseconds;

// enum that represents what search is specified by the command line arguments
enum SearchType{MM, AMM, AB, HMM};

// main
int main(int argc, char *argv[])
{
    // User has to enter valid args
    if(argc != 2 && argc != 3)
    {
        cout << "Error! Program must be run with either just the option of which search function to play or"
                "\nadditionally can have optional option -t to print the time taken to obtain the action in search\n";
        cout << "Please enter one of the following...\n-mm - MiniMax\n-amm - Aggressive MiniMax\n";
        cout << "-ab - Alpha-Beta\n-hmm - Heuristic MiniMax with Alpha-Beta Pruning\n";
        return 1;
    }
    // boolean flag for if the user specified that they wish to see the time that it takes to obtain actions
    bool timed = false;

    // if argc == 3 => argv[2] must be the time option
    if(argc == 3)
    {
        string time_option= argv[2];
        if(time_option != "-t")
        {
            cout << "Error! Program must be run with either just the option of which search function to play or"
                    "\nadditionally can have optional option -t to print the time taken to obtain the action in search\n";
            return 1;
        }
        timed = true;
    }

    // obtain the search specified by the command line option
    string searchType = argv[1];
    SearchType st;
    if(searchType == "-mm")
    {
        st = MM;
    }
    else if(searchType == "-amm")
    {
        st = AMM;
    }
    else if(searchType == "-ab")
    {
        st = AB;
    }
    else if(searchType == "-hmm")
    {
        st = HMM;
    }
    // user hasn't entered a valid option
    else
    {
        cout << "Error! The option entered for the search is not valid\n";
        cout << "Please enter one of the following...\n-mm - MiniMax\n-amm - Aggressive MiniMax\n";
        cout << "-ab - Alpha-Beta\n-hmm - Heuristic MiniMax with Alpha-Beta Pruning\n";
        return 1;
    }

    // create a new game of TicTacToe
    Game *newGame = new TicTacToe(MAX, 5);
    // print the initial state of the game
    cout << "New Game:\n" << *newGame << endl;
    // play until the game is finished
    while(!newGame->finished())
    {
        Action *action;
        // obtain the action using the search function specified and print the time that the search took if
        // the time option was used
        switch (st) {
            case MM:
            {
                Search search(newGame, newGame->get_current_state());
                auto t1 = high_resolution_clock::now();
                action = search.MiniMax();
                auto t2 = high_resolution_clock::now();
                duration<double, std::milli> ms_double = t2 - t1;
                if(timed)
                    cout << ms_double.count() << "ms" << endl;
                break;
            }
            case AMM:
            {
                Search search(newGame, newGame->get_current_state());
                auto t1 = high_resolution_clock::now();
                action = search.Aggressive_MiniMax();
                auto t2 = high_resolution_clock::now();
                duration<double, std::milli> ms_double = t2 - t1;
                if(timed)
                    cout << ms_double.count() << "ms" << endl;
                break;
            }
            case AB:
            {
                Search search(newGame, newGame->get_current_state());
                auto t1 = high_resolution_clock::now();
                action = search.Alpha_Beta();
                auto t2 = high_resolution_clock::now();
                duration<double, std::milli> ms_double = t2 - t1;
                if(timed)
                    cout << ms_double.count() << "ms" << endl;
                break;
            }
            case HMM:
            {
                Search search(newGame, newGame->get_current_state());
                auto t1 = high_resolution_clock::now();
                action = search.Heuristic_MiniMax();
                auto t2 = high_resolution_clock::now();
                duration<double, std::milli> ms_double = t2 - t1;
                if(timed)
                    cout << ms_double.count() << "ms" << endl;
                break;
            }
        }
        // change the game's state to the result obtained from taking the action obtained
        // from the search function in the current state
        newGame->set_current_state(newGame->result(newGame->get_current_state(), action));
        delete action;
        cout << "\nResult: \n" << *newGame << endl;
        // if the agent's action did not result in the game being complete, then obtain a user action
        if(!newGame->finished())
        {
            newGame->obtain_action();
            cout << "\nResult: \n" << *newGame << endl;
        }
    }

    delete newGame;
}
