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
	using_minimax = true;
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

double Player::compute_score2(Board *temp, Side player_side)
{
	double score = 0;
	//Board *temp = input_board->copy();
	//temp -> doMove(move, player_side);
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
	
	
	double corner_occ;
	int player_corner = 0;
	int opp_corner = 0;
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
	
	
	
	
	
	
	
	
	
	
	/*if((move->getX() == 0 || move->getX() == 7) && (move->getY() == 0 || move->getY() == 7))
	{
		score += 10;
	}
	else if(((move->getX() == 0 || move->getX() == 7) && (move->getY() == 1 || move->getY() == 6))
		||  ((move->getY() == 0 || move->getY() == 0) && (move->getX() == 1 || move->getX() == 6)))
	{
		score -= 4;
	}
	else if((move->getX() == 0 || move->getX() == 7) || (move->getY() == 0 || move->getY() == 7))
	{
		score += 2;
	}*/
	
	score = 10 * piece_diff + 801.724 * corner_occ;
	//delete temp;
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
		//string key = current->get_board_string();
		double score;
		/*
		if (memo.count(key) > 0)
		{
			score = memo[key];
		}
		else
		{
			score = compute_score2(current, player_side);
			memo[key] = score;
		}*/
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
	//if(using_minimax || testingMinimax)
	//{
	
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
		//memo_type memo;
		
		tuple <double, Move> result = minimax_ab(board, 7, true, -9999999.0, 9999999.0);
		*best_move = get<1> (result);
		
		board->doMove(best_move, player_side);
		return best_move;
	//}
	/*
	else
	{
		int best_score = -10000000;
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
				int score = compute_score2(board, player_side, moves[i]);
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
		
		if (best_score != -10000000)
		{
			board->doMove(best_move, player_side);
			return best_move;
		}
		
		return NULL;
	}*/
}
