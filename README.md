# AdverserialSearchTicTacToe

To build the program simply type in make.
After building the program to play TicTacToe against an agent playing one of the search algorithms type
./game <search option> [-t]
where <search option> is a required argument and is one of the following
  
-mm for MiniMax
  
-ab for Alpha-Beta Pruning
  
-hmm for Heuristic MiniMax with Alpha-Beta Pruning
  
-amm for Aggressive MiniMax
  
and [-t] is an optional option to display the time that it took for the search to return an action. I recommend running with the -t parameter 
first for MiniMax to see how expensive it is to build the entire game tree, then with alpha-beta pruning to see how much more efficient it is when we 
prune large parts of the game tree that make no difference in the outcome, and finally for Heuristic MiniMax, where we will Search until we have reached
a cutoff state ie a terminal state or we have search to the max depth specified at which point we evaluate the state using a heuristic evaluation function.
  
One thing that I noticed after I had implemented MiniMax was that there would be times when there were 2 moves that would return a utility of 1 for the
Max player and in my implementation, the search does not distinguish between if the victory is from the next move or a sequence of two moves. 
So for example, if there was one move that could be taken to immediately end the game, but there was also another move that could be taken
that would also result in a guarenteed victory in a subsequent turn, if the one that guarenteed the victory in a subsequent term was encountered first
in search, it would be taken since its utility is equal to that of the one that immediately ends the game and thus the utility, move pair would not be 
updated. As a result, I also implemented a Aggressive MiniMax function that still prefers actions that maximize/minimize utility depending on the player,
but if the actions have equal utility it prefers that which obtained the utility at a lesser depth, thus the search will "Aggressively" select
moves that immediately lead to victory if they are present.

