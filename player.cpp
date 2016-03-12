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
    
    opponent_side = BLACK;
	if (side == BLACK) //Sets computer color
	{
		opponent_side = WHITE;
	}	

	Board *new_board = new Board();
	board = new_board;
	using_minimax = false;
    /* 
     * 
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
vector<Move> Player::validMoves(Board *input_board, Side side) {
	vector<Move> result;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			Move move = Move(x,y);
			if(input_board->checkMove(&move, side))
			{
				result.push_back(move);
			}
		}
	}
	return result;
}

double Player::compute_piece_diff(Side player_side, Side opp_side, Board *temp)
{
	double piece_diff;
	if(temp->count(player_side) > temp->count(opp_side))
	{
		piece_diff = 100.0 * double(temp->count(player_side))/(temp->count(player_side) + temp->count(opp_side));
	}
	else if(temp->count(player_side) == temp->count(opp_side))
	{
		piece_diff = 0.0;
	}
	else
	{
		piece_diff = -100.0 * double(temp->count(opp_side))/(temp->count(player_side) + temp->count(opp_side));
	}
	return piece_diff;
	
}

double Player::compute_corner_occ(Side player_side, Side opp_side, Board *temp)
{
	int player_corner = 0;
	int opp_corner = 0;
	double corner_occ = 0;
	if (temp->get(player_side, 0, 0))
	{
		player_corner++;
	}
	else if (temp->get(opp_side, 0, 0))
	{
		opp_corner++;
	}
	if (temp->get(player_side, 0, 7))
	{
		player_corner++;
	}
	else if (temp->get(opp_side, 0, 7))
	{
		opp_corner++;
	}
	if (temp->get(player_side, 7, 0))
	{
		player_corner++;
	}
	else if (temp->get(opp_side, 7, 0))
	{
		opp_corner++;
	}
	if (temp->get(player_side, 7, 7))
	{
		player_corner++;
	}
	else if (temp->get(opp_side, 7, 7))
	{
		opp_corner++;
	}
	corner_occ = 25.0 * player_corner - 25 * opp_corner;
	return corner_occ;
}

double Player::compute_corner_adj(Side player_side, Side opp_side, Board *temp)
{
	int player_adj = 0;
	int opp_adj = 0;
	double corner_adj = 0;
	if(!(temp->occupied(0,0)))
	{
		if (temp->get(player_side, 0, 1))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 0, 1))
		{
			opp_adj++;
		}
		if (temp->get(player_side, 1, 0))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 1, 0))
		{
			opp_adj++;
		}		
		if (temp->get(player_side, 1, 1))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 1, 1))
		{
			opp_adj++;
		}			
	}
	
	if(!(temp->occupied(0,7)))
	{
		if (temp->get(player_side, 0, 6))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 0, 6))
		{
			opp_adj++;
		}
		if (temp->get(player_side, 1, 7))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 1, 7))
		{
			opp_adj++;
		}		
		if (temp->get(player_side, 1, 6))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 1, 6))
		{
			opp_adj++;
		}			
	}
	
	if(!(temp->occupied(7,0)))
	{
		if (temp->get(player_side, 7, 1))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 7, 1))
		{
			opp_adj++;
		}
		if (temp->get(player_side, 6, 0))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 6, 0))
		{
			opp_adj++;
		}		
		if (temp->get(player_side, 6, 1))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 6, 1))
		{
			opp_adj++;
		}			
	}
	
	if(!(temp->occupied(7,7)))
	{
		if (temp->get(player_side, 7, 6))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 7, 6))
		{
			opp_adj++;
		}
		if (temp->get(player_side, 6, 7))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 6, 7))
		{
			opp_adj++;
		}		
		if (temp->get(player_side, 6, 6))
		{
			player_adj++;
		}
		else if (temp->get(opp_side, 6, 6))
		{
			opp_adj++;
		}			
	}
	
	corner_adj = -12.5 * player_adj + 12.5 * opp_adj;
	return corner_adj;
}

double Player::compute_mobility(Side player_side, Side opp_side, Board *temp)
{
	int player_moves = validMoves(temp, player_side).size();
	int opp_moves = validMoves(temp, opp_side).size();
	double mobility = 0.0;
	if(player_moves > opp_moves)
	{
		mobility = 100.0 * double(player_moves)/(player_moves + opp_moves);
	}
	else if(player_moves == opp_moves)
	{
		mobility = 0.0;
	}
	else
	{
		mobility = -100.0 * double(opp_moves)/(player_moves + opp_moves);
	}
	return mobility;
}

double Player::compute_frontiers(Side player_side, Side opp_side, Board *temp)
{
	int player_frontier = 0;
	int opp_frontier = 0;
	double frontiers = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			bool is_frontier = false;
			if (temp->occupied(i,j))
			{
				if(temp->onBoard(i, j+1) && !temp->occupied(i, j+1))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i+1, j+1) && !temp->occupied(i+1, j+1))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i+1, j) && !temp->occupied(i+1, j))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i-1, j+1) && !temp->occupied(i-1, j+1))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i, j-1) && !temp->occupied(i, j-1))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i-1, j) && !temp->occupied(i-1, j))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i-1, j-1) && !temp->occupied(i-1, j-1))
				{
					is_frontier = true;
				}
				else if(temp->onBoard(i+1, j-1) && !temp->occupied(i+1, j-1))
				{
					is_frontier = true;
				}
			}
			if(is_frontier)
			{
				if(is_frontier)
				{
					if(temp->get(player_side, i, j))
					{
						player_frontier++;
					}
					else
					{
						opp_frontier++;
					}
				}
			}
		}
	}
	
	if(player_frontier > opp_frontier)
	{
		frontiers = -100.0 * double(player_frontier)/(player_frontier + opp_frontier);
	}
	else if (player_frontier == opp_frontier)
	{
		frontiers = 0;
	}
	else
	{
		frontiers = 100.0 * double(opp_frontier)/(player_frontier + opp_frontier);
	}
	return frontiers;
}

double Player::compute_squares(Side player_side, Side opp_side, Board *temp)
{
	double squares = 0;
	int boardWeights[8][8] = {
        {20, -3, 11, 8, 8, 11, -3, 20}, 
        {-3, -7, -4, 1, 1, -4, -7, -3}, 
        {11, -4,  2, 2, 2,  2, -4, 11}, 
        { 8,  1,  2,-3,-3,  2,  1,  8}, 
        { 8,  1,  2,-3,-3,  2,  1,  8}, 
        {11, -4,  2, 2, 2,  2, -4, 11}, 
        {-3, -7, -4, 1, 1, -4, -7, -3}, 
        {20, -3, 11, 8, 8, 11, -3, 20} 
	};
	int colorCoefficient[8][8];
	for (int i = 0; i < 8; i++)
	{
		for(int j = 0 ; j < 8; j++)
		{
			if(temp->get(player_side, i, j))
			{
				colorCoefficient[i][j] = 1;
			}
			else if(temp->get(opp_side, i, j))
			{
				colorCoefficient[i][j] = -1;
			}
			else
			{
				colorCoefficient[i][j] = 0;
			}
			squares += colorCoefficient[i][j]*boardWeights[i][j];
		}
	}
	return squares;
}

double Player::compute_score2(Board *temp, Side player_side)
{
	double score = 0.0;
	Side opp_side;
	if(player_side == BLACK)
	{
		opp_side = WHITE;
		score = temp->countBlack() - temp->countWhite();
	}
	else
	{
		opp_side = BLACK;
		score = temp->countWhite() - temp->countBlack();
	}
	
	
	double piece_diff = compute_piece_diff(player_side, opp_side, temp);
	double corner_occ = compute_corner_occ(player_side, opp_side, temp);
	double corner_adj = compute_corner_adj(player_side, opp_side, temp);
	double mobility = compute_mobility(player_side, opp_side, temp);
	double frontiers = compute_frontiers(player_side, opp_side, temp);
	double squares = compute_squares(player_side, opp_side, temp);
	

	score = 10 * piece_diff + 801.724 * corner_occ + 382.026 * corner_adj + 78.922 * mobility + 74.396 * frontiers + 10 * squares;
	return score;
}

tuple<double, Move> Player::minimax_ab(Board* current, int depth, bool player, double a, double b)
{
	Side side;                                                                                                             
	if (player)
	{
		side = player_side;
	}
	else
	{
		side = opponent_side;
	}
	// Get children of node
	vector <Move> validMoves1 = validMoves(current, side);
	
	// Base case
	if (depth == 0 || validMoves1.empty() == true)
	{
		double score;
		score = compute_score2(current, player_side);
		tuple <double, Move> result (score, Move (-1,-1));
		return result;
	}

	double best_score;
	if (player)
	{
		best_score = -9999999;
	}
	else
	{
		best_score = 9999999;
	}
	Move best_move (-1, -1);
		
	for (unsigned int i = 0; i < validMoves1.size(); i++)
	{
		
		Board *temp = current->copy();
		temp->doMove(&(validMoves1[i]), side);
		
		if (player)
		{
			tuple <double, Move> child = minimax_ab(temp, depth - 1, false, a, b);
			if (get<0>(child) > best_score)
			{
				best_move = validMoves1[i];
				best_score = get<0>(child);
			}
			a = max(best_score, a);
			if (b <= a)
			{
				delete temp;
				break;
			}
		}
		else
		{
			tuple <double, Move> child = minimax_ab(temp, depth - 1, true, a, b);
			if (get<0>(child) <  best_score)
			{
				best_move = validMoves1[i];	
				best_score = get<0>(child);	
			}
			b = min(best_score, b);
			if (b <= a)
			{
				delete temp;
				break;
			}
		}
		delete temp;
	}
	tuple <double, Move> result (best_score, best_move);
	return result;
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
    
    int plies = 8;


	Move *best_move = new Move (-1, -1);
	
	board->doMove(opponentsMove, opponent_side); //Updates board with opponents moves
	
	if (board->countBlack() == 2 && board->countWhite() == 2 && player_side == BLACK)
	{
		Move *first_move = new Move(3, 2);
		board->doMove(first_move, player_side);
		delete best_move;
		return first_move;
	}
	if (!(board->hasMoves(player_side)))
	{
		delete best_move;
		return NULL;
	}
	
	tuple <double, Move> result = minimax_ab(board, plies, true, -9999999.0, 9999999.0);
	*best_move = get<1> (result);
	
	board->doMove(best_move, player_side);
	return best_move;
}
