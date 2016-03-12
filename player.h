#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_map>

using namespace std;

//typedef unordered_map<string, double> memo_type;

class Player {

public:
	Board *board;
	Side player_side;
	Side opponent_side;
	
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

	vector<Move> validMoves(Board *board, Side side);

	double compute_score2(Board *input_board, Side side);
	
	tuple<double, Move> minimax_ab(Board* current, int depth, bool player, double a, double b);
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    bool using_minimax;
};

#endif
