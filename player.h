#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>

using namespace std;

class Player {

public:
	Board *board;
	Side player_side;
	
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

	vector<Move *> validMoves(Board *board, Side side);
	
	int compute_score(Board *input_board, Side side, Move *move);
	
	Move *\minimax(Board *input_board, Side player_side);
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
