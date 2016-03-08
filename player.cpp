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
    int best_score = -1000;
    Move *best_move = NULL;
    Side opponent_side = BLACK;
    if (player_side == BLACK) //Sets computer color
    {
		opponent_side = WHITE;
	}
	
	board->doMove(opponentsMove, opponent_side); //Updates board with opponents moves
	
	vector<Move *> moves = validMoves(board, player_side);
	
	for(unsigned int i = 0; i < moves.size(); i++)
	{	
		if(board->checkMove(moves[i], player_side))
		{
			int score = compute_score(board, player_side, moves[i]);
			if (score > best_score)
			{
				delete best_move;
				best_move = moves[i];
				best_score = score;
			}
			else
			{
				delete moves[i];
			}
		}
	}
	
	if (best_score != -1000)
	{
		board->doMove(best_move, player_side);
		return best_move;
	}
     
    return NULL;
}
