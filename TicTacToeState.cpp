#include "TicTacToeState.h"

// constructor with the player whose turn it is in that state passed in as a parameter
TicTacToeState ::TicTacToeState(Player player) : State(player)
{

}

// destructor
TicTacToeState :: ~TicTacToeState()
{

}

// constructor that will fill in all the tiles from s with the tile associated with int filled in by the player in s
TicTacToeState ::TicTacToeState(TicTacToeState* s, int fill_in) : State(s->get_adversary())
{
    for(int i = 0; i < 9; i++)
    {
        tiles[i] = s->tiles[i];
    }
    if(s->get_player() == MIN)
    {
        tiles[fill_in] = -1;
    }
    else
    {
        tiles[fill_in] = 1;
    }
}

// print
void TicTacToeState :: print(ostream& out) const
{
    for(int i = 0; i < 9; i++)
    {
        if(tiles[i] == 1)
        {
            out << "X";
        }
        else if(tiles[i] == -1)
        {
            out << "O";
        }
        else
        {
            out << " ";
        }

        if(i % 3 == 0 || i % 3 == 1)
        {
            out << " | ";
        }
        else if(i != 8)
        {
            out << "\n---------\n";
        }
    }
}

// get the tiles that have not been filled in
vector<int> TicTacToeState ::get_available_tiles()
{
    vector<int> available;
    for(int i = 0; i < 9; i++)
    {
        if(tiles[i] == 0)
        {
            available.push_back(i+1);
        }
    }

    return available;
}

// determine if there is a win and if there is return True with the winner or false w arbitrary Player
pair<bool, Player> TicTacToeState ::is_win()
{
    // have to check if there is horizontal, vertical or diagonal win
    pair<bool, Player> horizontal = is_horizontal_win();
    if(horizontal.first)
    {
        return horizontal;
    }
    pair<bool, Player> vertical = is_vertical_win();
    if(vertical.first)
    {
        return vertical;
    }
    pair<bool, Player> diagonal = is_diagonal_win();
    if(diagonal.first)
    {
        return diagonal;
    }

    return pair<bool, Player>(false, MAX);
}

// check if there is a horizontal win
pair<bool, Player> TicTacToeState :: is_horizontal_win()
{
    int horizontal = 0;
    for(int i = 0; i < 9; i++)
    {
        horizontal += tiles[i];
        if((i % 3) == 2)
        {
            if(horizontal == 3)
            {
                return pair<bool, Player>(true, MAX);
            }
            else if(horizontal == -3)
            {
                return pair<bool, Player>(true, MIN);
            }
            horizontal = 0;
        }
    }

    return pair<bool, Player>(false, MAX);
}

// check if there is a vertical win
pair<bool, Player> TicTacToeState:: is_vertical_win()
{
    int vertical = 0;
    for(int i = 0; i < 3; i++)
    {
        vertical += tiles[i];
        for(int j = 1; j < 3; j++)
        {
            vertical += tiles[3*j + i];
        }

        if(vertical == 3)
        {
            return pair<bool, Player>(true, MAX);
        }
        else if(vertical == -3)
        {
            return pair<bool, Player>(true, MIN);
        }
        vertical = 0;
    }

    return pair<bool, Player>(false, MAX);
}

// check if there is a diagonal win
pair<bool, Player> TicTacToeState::  is_diagonal_win()
{
    int diagonal = 0;
    for(int i = 0; i < 9; i+= 4)
    {
        diagonal += tiles[i];
    }

    if(diagonal == 3)
    {
        return pair<bool, Player>(true, MAX);
    }
    else if(diagonal == -3)
    {
        return pair<bool, Player>(true, MIN);
    }

    diagonal = 0;
    for(int i = 2; i < 7; i+= 2)
    {
        diagonal += tiles[i];
    }

    if(diagonal == 3)
    {
        return pair<bool, Player>(true, MAX);
    }
    else if(diagonal == -3)
    {
        return pair<bool, Player>(true, MIN);
    }

    return pair<bool, Player>(false, MAX);
}

// check if all of the tiles of this state are filled
bool TicTacToeState ::is_full()
{
    for(int i = 0; i < 9; i++)
    {
        if(tiles[i] == 0)
        {
            return false;
        }
    }
    return true;
}

// returns how many possible winning sequences are unblocked for num_tiles
// used in the Heuristic Evaluation function
int TicTacToeState ::unblocked(int num_tiles, Player p)
{
    int player_sign;
    if(p == MAX)
    {
        player_sign = 1;
    }
    else
    {
        player_sign = -1;
    }
    return (unblocked_horizontal(num_tiles, player_sign)
            + unblocked_vertical(num_tiles, player_sign)
            + unblocked_diagonal(num_tiles, player_sign));
}

// determine how many unblocked potential horizontal wins there are with num_tiles for this player
int TicTacToeState :: unblocked_horizontal(int num_tiles, int player_sign)
{
    int unblocked_count = 0;

    for(int i = 0; i < 9; i += 3)
    {
        int horizontal = 0;
        bool unblocked = true;
        for(int j = i; j < i+3; j++)
        {
            if(tiles[j] == player_sign)
            {
                horizontal++;
            }
            else if(tiles[j] == 0)
            {

            }
            else
            {
                unblocked = false;
            }
        }

        if(unblocked && (horizontal == num_tiles))
        {
            unblocked_count++;
        }
    }

    return unblocked_count;
}

// determine how many unblocked potential vertical wins there are with num_tiles for this player
int TicTacToeState :: unblocked_vertical(int num_tiles, int player_sign)
{
    int unblocked_count = 0;

    for(int i = 0; i < 3; i++)
    {
        int vertical = 0;
        bool unblocked = true;
        for(int j = 0; j < 3; j++)
        {
            if(tiles[3*j + i] == player_sign)
            {
                vertical++;
            }
            else if(tiles[3*j + i] == 0)
            {

            }
            else
            {
                unblocked = false;
            }
        }

        if(unblocked && (vertical == num_tiles))
        {
            unblocked_count++;
        }
        vertical = 0;
    }

    return unblocked_count;
}

// determine how many unblocked potential diagonal wins there are with num_tiles for this player
int TicTacToeState :: unblocked_diagonal(int num_tiles, int player_sign)
{
    int unblocked_count = 0;

    int diagonal = 0;
    bool unblocked = true;
    for(int i = 0; i < 9; i+= 4)
    {
        if(tiles[i] == player_sign)
        {
            diagonal++;
        }
        else if(tiles[i] == 0)
        {

        }
        else
        {
            unblocked = false;
        }
    }

    if(unblocked && (diagonal == num_tiles))
    {
        unblocked_count++;
    }

    diagonal = 0;
    unblocked = true;
    for(int i = 2; i < 7; i+= 2)
    {
        if(tiles[i] == player_sign)
        {
            diagonal++;
        }
        else if(tiles[i] == 0)
        {

        }
        else
        {
            unblocked = false;
        }
    }

    if(unblocked && (diagonal == num_tiles))
    {
        unblocked_count++;
    }

    return unblocked_count;
}
