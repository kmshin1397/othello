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
	
	int compute_score(Board *input_board, Side side, Move *move);
	int compute_score_ply2(Board *input_board, Side side, Move *move);
	double compute_score2(Board *input_board, Side side);
	int simple_score(Board *input_board, Side side, Move *move);
	double compute_piece_diff(Side player_side, Side opp_side, Board *temp);
	double compute_corner_occ(Side player_side, Side opp_side, Board *temp);
	double compute_corner_adj(Side player_side, Side opp_side, Board *temp);
	double compute_mobility(Side player_side, Side opp_side, Board *temp);
	double compute_frontiers(Side player_side, Side opp_side, Board *temp);
	double compute_squares(Side player_side, Side opp_side, Board *temp);

	tuple<double, Move> minimax_ab(Board* current, int depth, bool player, double a, double b);
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    bool using_minimax;
};

#endif
