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
	int compute_score_ply2(Board *input_board, Side side, Move *move);
	int compute_score2(Board *input_board, Side side, Move *move);
	int simple_score(Board *input_board, Side side, Move *move);
	
	Move *minimax();
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    bool using_minimax;
};

#endif
