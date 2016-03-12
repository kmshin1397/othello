For this project, Kyung primarily worked on implementing and improving the minimax section of the code, while Abhishek focused on writing the heuristics. We both worked
on debugging the code together when either of us had trouble with our respective sections, and we also collaborated on merging the two separate sections of the code
(the heurestics and the minimax) together. More specifically we worked on the following:
	Kyung:
		-Implementing minimax
		-Redesigning minimax to be recursive so that we can change the ply at will
		-Implementing alphabeta
		-Updating the makefile
		-Created validmoves function


	Abhishek:
		-implemented simple heurestics 
		-Updated heurestics to include:
			-increased corner weight
			-checks mobility (how many moves opponent has) and limits theres while increasing ours
			-checks frontiers (number of pieces adjacent to an empty square) and limits theres while increasing ours
			-implemented weighted matrix of values for each square
			-assigned weights for each of these characteristics above

	Together:
		-Debugging
		-Merging code
		-Do move function
		-Testing


Our AI has the following improvements:
-alphabeta: makes the progarm go faster by cutting off unecessary branches (less time allows for more plys)
-Added weights to corner to prioritize them (and lowers score if opponent has corners)
-Decreases score for boards with pieces on edges next to corners (and increases score if opponent puts it there) since those pieces are especially bad choices
-Changed make file to use O3 flag in order to reduce time
-Code increases our mobility and decreases opponents mobility since having more moves is generally better since it proviedes more options, which was implemented
	by checking to see how many moves the opponent had and we had and taking the difference (before weighting was applied)
-Code increases number of our frontier spaces (how many pieces have an empty space) while minimizing opponents, which, like mobility, leads to more choices while 
	limiting their choices for next turn.
-Added values based on experimental values found for each square based on how useful that particular position is, and likewise weights the opponents pieces the same way
	but minimizes their board score instead of maximizing it like we do.