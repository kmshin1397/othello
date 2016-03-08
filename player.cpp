#include "player.h"

// Test change for git commit. //
// Test change number 2 for git commit. //


/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    player_side = side;
	Board *new_board = new Board();
	board = new_board;
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
}

/*
 * Checks for valid moves and returns a vector of pointers to those valid
 * moves.
 * 
 * param: current Board board
 * param: Side side of player whose turn it is
 */
vector<Move *> Player::validMoves(Board *input_board, Side side) {
	vector<Move *> result;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			Move *move = new Move(x,y);
			if(input_board->checkMove(move, side))
			{
				result.push_back(move);
			}
		}
	}
	return result;
}

int Player::compute_score(Board *input_board, Side side, Move *move)
{
	int score = 0;
	Board *temp = input_board->copy();
	temp -> doMove(move, side);
	if(side == BLACK)
	{
		score = temp->countBlack() - temp->countWhite();
	}
	else
	{
		score = temp->countWhite() - temp->countBlack();
	}
	delete temp;
	return score;
}

Move *Player::minimax()
{
	// 2-ply minimax
	int min_gain;
	int max_min;
	int best_move = 0;

	vector <int> min_gains;

	//for every valid move
	vector <Move *> validMoves1 = validMoves(board, player_side);
	for (unsigned int i = 0; i < validMoves1.size(); i++)
	{

		Board *temp = board->copy();
		temp->doMove(validMoves1[i], player_side);
		
		//for every valid move from valid move
		vector <Move *> validMoves2 = validMoves(temp, player_side);
		for (unsigned int j = 0; j < validMoves2.size(); j++)
		{
			//check score
			int score = compute_score(temp, player_side, validMoves2[j]) ;
			if (score < min_gain)
			{
				min_gain = score;
			}
		}
		// Record minimum gain of each branch
		min_gains.push_back(min_gain);
	}

	// Find maximum min gain
	max_min = min_gains[0];
	for (unsigned int i = 0; i < min_gains.size(); i++)
	{
		if (min_gains[i] > max_min)
		{
			max_min = min_gains[i];
			best_move = i;
		}
	}
	return validMoves1[best_move];
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
 
 
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    
    Move *best_move = NULL;
    Side opponent_side = BLACK;
    if (player_side == BLACK) //Sets computer color
    {
		opponent_side = WHITE;
	}
	
	board->doMove(opponentsMove, opponent_side); //Updates board with opponents moves
	
	vector<Move *> moves = validMoves(board, player_side);
	if (moves.size() == 0)
	{
		return NULL;
	}
	
	best_move = minimax();
    
    board->doMove(best_move, player_side);
	return best_move;
}

