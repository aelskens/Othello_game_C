#include "Player.h"


Player::Player(int c)
{
	color = c;
}


int Player::getColor() const{return color;}
int Player::getNumber_of_token() const{return number_of_token;}
void Player::setNumber_of_token(int i){number_of_token = number_of_token + i;}
int Player::getType_of_player() const{return type_of_player;}
void Player::setOpponant_pointer(Player* o){opponant_pointer = o;}
string Player::getLast_move()const {return last_move;}
void Player::setLast_move(string lm){last_move=lm;}       


/**
 * Fonction membre de la classe Player qui renvoie -1 ou 1 selon le signe du int pris en paramètre
 * */
int Player::sign_of_operator(int c)
{
	int s = 1;
	if ( c < 0 )
		s = -1;
	return s;
}

/**
 * Fonction membre de la classe Player qui renvoie une position (string) modifiée selon les deux paramètres c et o
 * */
 
string Player::alter_position(string pos, int c, int o)
{
	pos[c] = char(int(pos[c]) + o);
	return pos;
}

/**
 * Fonction membre de la classe Player qui transforme le conteneur du plateau de jeu pris par référence
 * selon différents paramètres:
 * pos est le string depuis lequel les pions sont changés de couleur
 * clr est la nouvelle couleur qui sera assigniée aux pions changés
 * i, o, p permettent de repérer les positions des pions à changer
 * */
 
void Player::apply_color(map<string, int>& b, string pos, int clr, int i, int o, int p = 0)
{
	int m = 1;
	if ( p == 0 )
		m = 0;
	for ( int j = 1; j < abs(o); j++ )
	{
		b[alter_position(alter_position(pos, i, sign_of_operator(o)*j), 1, sign_of_operator(p)*j*m)] = clr;
		if ( clr == getColor() )
		{
			number_of_token += 1;
			opponant_pointer->setNumber_of_token(-1);
		}
		else
		{
			number_of_token -= 1;
			opponant_pointer->setNumber_of_token(1);
		}
	}
} 
/**
 * Fonction membre de la classe Player, celle-ci a deux modes et deux applications:
 * Mode 0: la fonction est utilisée dans le but de déterminer si une position donnée est un mouvement possible pour les direction Nord, Sud, Est et Ouest
 * Mode 1: la fonction permet de vérifier l'applicabilité d'un mouvement et appelle la fonction apply_color() pour l'appliquer dans les mêmes directions
 * Application 1: player = 0 cette fonction s'applique pour le joueur dont c'est le tour de jouer
 * Application 2: player = 1 cette fonction s'applique pour l'adversaire du joueur dont c'est le tour de jouer
 * */

bool Player::cross_validate_movement(string pos, map<string, int>& b, int mode = 0, int player = 0) //mode 0=search; mode 1=execute; player 0=player; player 1=opponant
{
	bool check_move = false;
	int clr = color;
	int clr_opp = opponant_pointer->getColor();
	if ( player != 0 )
	{
		clr = opponant_pointer->getColor();
		clr_opp = color;
	}
	int size = 8;
	int factor = 96;
	for ( int i = 0; i <= 1; i++ )
	{
		if ( i == 1 )
			factor = 48;
		int k = 0;
		for ( int j = -1; j <= 1; j=j+2 )
		{
			int o = j;
			if ( o > 0 )
				k = size + 1;
			if ( b[alter_position(pos, i, o)] == clr_opp )
			{
				o = o + sign_of_operator(o);
				while ( abs(o) < abs(k - (int(pos[i])-factor)) )
				{
					if ( b[alter_position(pos, i, o)] )
					{
						if ( b[alter_position(pos, i, o)] == clr )
						{
							if ( mode == 0 )
								return true;
							else
							{
								b[pos] = clr;
								apply_color(b, pos, clr, i, o);
								check_move = true;
								o = o + sign_of_operator(o)*size;
							}
						}
						else
							o = o + sign_of_operator(o);
					}
					else if ( b.find(alter_position(pos, i, o)) != b.end() && b[alter_position(pos, i, o)] == 0 )
					{
						b.erase(alter_position(pos, i, o));
						o = o + sign_of_operator(o)*size;
					}
				}
			}
			else if ( b.find(alter_position(pos, i, o)) != b.end() && b[alter_position(pos, i, o)] == 0 )
				b.erase(alter_position(pos, i, o));
		}
	}
	return check_move;
}

/**
 * Fonction membre de la classe Player, celle-ci a deux modes et deux applications
 * Mode 0: la fonction est utilisée dans le but de déterminer si une position donnée est un mouvement possible pour les direction Nord-Ouest, Nord-Est, Sud-Est et Sud-Ouest
 * Mode 1: la fonction permet de vérifier l'applicabilité d'un mouvement et appelle la fonction apply_color() pour l'appliquer dans les mêmes directions
 * Application 1: player = 0 cette fonction s'applique pour le joueur dont c'est le tour de jouer
 * Application 2: player = 1 cette fonction s'applique pour l'adversaire du joueur dont c'est le tour de jouer
 * */
 
bool Player::diagonal_validate_movement(string pos, map<string, int>& b, int mode = 0, int player = 0)
{
	bool check_move = false;
	int clr = color;
	int clr_opp = opponant_pointer->getColor();
	if ( player != 0 )
	{
		clr = opponant_pointer->getColor();
		clr_opp = color;
	}
	int size = 8;
	for ( int i = -1; i <= 1; i=i+2 )
	{
		for ( int j = -1; j <= 1; j=j+2)
		{
			int o = i, p = j;
			int k = 0, l = 0;
			if ( o > 0 )
				k = size + 1;
			if ( p > 0 )
				l = size + 1;
			if ( b[alter_position(alter_position(pos, 0, o), 1, p)] == clr_opp )
			{
				o = o + sign_of_operator(o);
				while ( abs(o) < abs(k - (int(pos[0])-96)) && abs(o) < abs(l - (int(pos[1])-48)) )
				{
					if ( b[alter_position(alter_position(pos, 0, o), 1, abs(o)*sign_of_operator(p))] )
					{
						if ( b[alter_position(alter_position(pos, 0, o), 1, abs(o)*sign_of_operator(p))] == clr )
						{
							if ( mode == 0 )
								return true;
							else
							{
								b[pos] = clr;
								apply_color(b, pos, clr, 0, o, abs(o)*sign_of_operator(p));
								check_move = true;
								o = o + sign_of_operator(o)*size;
							}
						}
						else
						{
							o = o + sign_of_operator(o);
						}
					}
					else if ( b.find(alter_position(alter_position(pos, 0, o), 1, abs(o)*sign_of_operator(p))) != b.end() && b[alter_position(alter_position(pos, 0, o), 1, abs(o)*sign_of_operator(p))] == 0 ) 
					{
						b.erase(alter_position(alter_position(pos, 0, o), 1, abs(o)*sign_of_operator(p)));
						o = o + sign_of_operator(o)*size;
					}
				}
			}
			else if ( b.find(alter_position(alter_position(pos, 0, o), 1, p)) != b.end() && b[alter_position(alter_position(pos, 0, o), 1, p)] == 0 )
				b.erase(alter_position(alter_position(pos, 0, o), 1, p));
		}
	}
	return check_move;
}

/**
 * Fonction membre de la classe Player qui assure la possibilité d'une position à pouvoir être jouée
 * Utilise à la fois les fonctions cross_validate_movement() et diagonal_validate_movement() définies ci-dessus dans le mode 0
 * */

bool Player::validate_movement(string pos, map<string, int> b, int player = 0)
{
	if ( !cross_validate_movement(pos, b, 0, player) )
		return diagonal_validate_movement(pos, b, 0, player);
	return true;
}

/**
 * Fonction membre de la classe Player qui vérifie l'applicabilité d'une position et l'exécute dans le cas positif
 * Utilise à la fois les fonctions cross_validate_movement() et diagonal_validate_movement() définies ci-dessus dans le mode 1
 * */

bool Player::execute_movement(string pos, map<string, int>& b, int player = 0)
{
	bool check_move = false;
	bool check_cross = cross_validate_movement(pos, b, 1, player);
	bool check_diagonal = diagonal_validate_movement(pos, b, 1, player);
	if ( check_cross || check_diagonal )
	{
		check_move = true;
		if ( player == 0 )
			number_of_token += 1;
		else
			opponant_pointer->setNumber_of_token(1);
	}
	return check_move;
}

/**
 * Fonction membre de la classe Player qui vérifie l'appartenance d'une position dans l'intervalle du plateau
 * */
 
bool Player::check_position_board(string pos)
{
	if ( int(pos[0]) >= 97 && int(pos[0]) <= 104 && int(pos[1]) >= 49 && int(pos[1]) <= 56 )
		return true;
	return false;
}

/**
 * Fonction membre de la classe Player crée un set contenant toutes les positions acceptables à jouer
 * Application 1: player = 0 cette fonction s'applique pour le joueur dont c'est le tour de jouer
 * Application 2: player = 1 cette fonction s'applique pour l'adversaire du joueur dont c'est le tour de jouer
 * */

set<string> Player::compute_legal_moves(map<string,int> b, int player = 0)
{
	int clr = color;
	if ( player != 0 )
		clr = opponant_pointer->getColor();
	set<string> legal_moves;
	for ( map<string,int>::iterator it = b.begin(); it != b.end(); it++ )
	{
		if ( it->second != clr )
		{
			for ( int i = -1; i <= 1; i=i+2 )
			{
				if ( b.find(alter_position(it->first, 0, i)) == b.end() && check_position_board(alter_position(it->first, 0, i)) )
				{
					if ( validate_movement(alter_position(it->first, 0, i), b, player) )
						legal_moves.insert(alter_position(it->first, 0, i));
				}
				if ( b.find(alter_position(alter_position(it->first, 0, i), 1, abs(i))) == b.end() && check_position_board(alter_position(alter_position(it->first, 0, i), 1, abs(i))) )
				{
					if ( validate_movement(alter_position(alter_position(it->first, 0, i), 1, abs(i)), b, player) )
						legal_moves.insert(alter_position(alter_position(it->first, 0, i), 1, abs(i)));
				}
				if ( b.find(alter_position(alter_position(it->first, 0, i), 1, -abs(i))) == b.end() && check_position_board(alter_position(alter_position(it->first, 0, i), 1, -abs(i))) )
				{
					if ( validate_movement(alter_position(alter_position(it->first, 0, i), 1, -abs(i)), b, player) )
						legal_moves.insert(alter_position(alter_position(it->first, 0, i), 1, -abs(i)));
				}
				if ( b.find(alter_position(it->first, 1, i)) == b.end() && check_position_board(alter_position(it->first, 1, i)) )
				{
					if ( validate_movement(alter_position(it->first, 1, i), b, player) )
						legal_moves.insert(alter_position(it->first, 1, i));
				}
			}
		}
	}
	return legal_moves;
}


Human::Human(int c)    
{
	color = c;
	type_of_player = 0;
}


AI::AI(int c )
{
	color = c;
	type_of_player = 1;
}

/**
 * Fonction membre de la sous-classe AI qui permet de mélanger de façon aléatoire un conteneur vector 
 * et d'en créer un unordered_set
 * */
unordered_set<string> AI::randomise_set(vector<string> v)
{
	unordered_set<string> randomised_set;
    std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle(v.begin(), v.end(), g);
	for ( vector<string>::iterator it = v.begin(); it != v.end(); it++ )
		randomised_set.insert(*it);
	return randomised_set;
}

/**
 * Fonction membre de la sous-classe AI crée un vector contenant toutes les positions acceptables à jouer puis avec randomise_set() crée un unordered_set
 * Application 1: player = 0 cette fonction s'applique pour le joueur dont c'est le tour de jouer
 * Application 2: player = 1 cette fonction s'applique pour l'adversaire du joueur dont c'est le tour de jouer
 * */

unordered_set<string> AI::minmax_compute_legal_moves(map<string,int> b, int player = 0)
{
	int clr = color;
	if ( player != 0 )
		clr = opponant_pointer->getColor();
	unordered_set<string> unordered_legal_moves;
	vector<string> legal_moves;
	for ( map<string,int>::iterator it = b.begin(); it != b.end(); it++ )
	{
		if ( it->second != clr )
		{
			for ( int i = -1; i <= 1; i=i+2 )
			{
				if ( b.find(alter_position(it->first, 0, i)) == b.end() && check_position_board(alter_position(it->first, 0, i)) )
				{
					if ( validate_movement(alter_position(it->first, 0, i), b, player) )
						legal_moves.push_back(alter_position(it->first, 0, i));
				}
				if ( b.find(alter_position(alter_position(it->first, 0, i), 1, abs(i))) == b.end() && check_position_board(alter_position(alter_position(it->first, 0, i), 1, abs(i))) )
				{
					if ( validate_movement(alter_position(alter_position(it->first, 0, i), 1, abs(i)), b, player) )
						legal_moves.push_back(alter_position(alter_position(it->first, 0, i), 1, abs(i)));
				}
				if ( b.find(alter_position(alter_position(it->first, 0, i), 1, -abs(i))) == b.end() && check_position_board(alter_position(alter_position(it->first, 0, i), 1, -abs(i))) )
				{
					if ( validate_movement(alter_position(alter_position(it->first, 0, i), 1, -abs(i)), b, player) )
						legal_moves.push_back(alter_position(alter_position(it->first, 0, i), 1, -abs(i)));
				}
				if ( b.find(alter_position(it->first, 1, i)) == b.end() && check_position_board(alter_position(it->first, 1, i)) )
				{
					if ( validate_movement(alter_position(it->first, 1, i), b, player) )
						legal_moves.push_back(alter_position(it->first, 1, i));
				}
			}
		}
	}
	unordered_legal_moves = randomise_set(legal_moves);
	return unordered_legal_moves;
}

/**
 * Fonction membre de la sous-classe AI qui calcule l'heuristique d'un état à l'aide d'un tableau de poids
 * */
int AI::heuristic_static_weights(map<string,int> b)
{
	int total = 0;
	for ( map<string,int>::iterator it = b.begin(); it != b.end(); it++ )
	{
		int index = (int(it->first[0])-97)*8+int(it->first[1])-49;
		if ( it->second == getColor() )
			total += weighted_positions[index];
		else
			total -= weighted_positions[index];	
	}
	return total;
}

/**
 * Fonction membre de la sous-classe AI qui calcule l'heuristique d'un état par la parité des jetons
 * */
float AI::heuristic_token_parity_normed(map<string,int> b)
{
	int ai_number_of_token = getNumber_of_token();
	int opponant_number_of_token = opponant_pointer->getNumber_of_token();
	float token_parity_normed = 0;
	if ( ai_number_of_token+opponant_number_of_token != 0 )
		token_parity_normed = 100*((ai_number_of_token-opponant_number_of_token)/(ai_number_of_token+opponant_number_of_token));
	return token_parity_normed;
}

/**
 * Fonction membre de la sous-classe AI qui calcule l'heuristique d'un état basé sur la capture des coins
 * */
float AI::heuristic_corners_captured_normed(map<string,int> b)
{
	string corners[4] = {"a1", "a8", "h1", "h8"};
	float ai_corners=0, opponant_corners=0;
	for ( int i = 0; i < 4; i++ )
	{
		if ( b[corners[i]] == color )
			ai_corners += 3;
		else if ( validate_movement(corners[i], b, 0) )
			ai_corners += 1;
		else
			ai_corners -= 1;
		if ( b[corners[i]] == opponant_pointer->getColor() )
			opponant_corners += 3;
		else if ( validate_movement(corners[i], b, 1) )
			opponant_corners += 1;
		else
			opponant_corners -= 1;
	}
	float corners_captured_normed = 0;
	if ( ai_corners+opponant_corners != 0)
		corners_captured_normed = 100*((ai_corners-opponant_corners)/(ai_corners+opponant_corners));
	return corners_captured_normed;	
}

/**
 * Fonction membre de la sous-classe AI qui calcule l'heuristique d'un état basé sur la mobilité actuelle des joueurs
 * */
float AI::heuristic_actual_mobility_normed(map<string,int> b)
{
	set<string> ai_moves = compute_legal_moves(b, 0);
	set<string> opponant_moves = compute_legal_moves(b, 1);
	float actual_mobility_normed = 0;
	float ai_nmbr_moves = ai_moves.size(), op_nmbr_moves = opponant_moves.size();
	if ( ai_nmbr_moves+op_nmbr_moves != 0 )
		actual_mobility_normed = 100*((ai_nmbr_moves-op_nmbr_moves)/(ai_nmbr_moves+op_nmbr_moves));
	return actual_mobility_normed;
}

/**
 * Fonction membre de la sous-classe AI qui calcule l'heuristique d'un état par combinaison linéaire des deux valeurs renvoyées par les deux fonctions précédentes
 * */
float AI::heuristics_othello(map<string,int> b)
{
	return heuristic_token_parity_normed(b)+10*heuristic_static_weights(b)+heuristic_actual_mobility_normed(b)+heuristic_corners_captured_normed(b);
}


/**
 * Fonction membre de la sous-classe AI qui cherche le score maximal de l'AI dans les mouvements possibles
 * */
pair<float, string> AI::max_score(map<string,int> b, int depth, int alpha, int beta)
{
	pair <float, string> score_move (0, " ");
	if ( depth == 0 )
	{
		score_move.first = heuristics_othello(b);
		return score_move;
	}
	unordered_set<string> moves = minmax_compute_legal_moves(b);
	string best_move = "00";
	if ( depth == 5 && moves.size() == 1 )
	{
		auto it = moves.begin();
		score_move.second = *it;
		return score_move;
	}
	int player_nbr_token = getNumber_of_token();
	int opponant_nbr_token = opponant_pointer->getNumber_of_token();
	int score = -infinity;
	int best_score = -infinity;
	for ( auto it = moves.begin(); it != moves.end(); it++ )
	{
		number_of_token = player_nbr_token;
		opponant_pointer->setNumber_of_token(opponant_nbr_token-opponant_pointer->getNumber_of_token());
		map<string, int> b_copy = b;
		execute_movement(*it, b_copy, 0);
		score = min_score(b_copy, depth-1, alpha, beta);
		if ( score >= best_score )
		{
			best_score = score;
			best_move = *it;
		}
		if ( best_score >= beta )
		{
			score_move.first = best_score;
			score_move.second = *it;
			return score_move;
		}
		alpha = max(alpha, best_score);
	}
	score_move.first = best_score;
	score_move.second = best_move;
	number_of_token = player_nbr_token;
	opponant_pointer->setNumber_of_token(opponant_nbr_token-opponant_pointer->getNumber_of_token());
	return score_move;
}

/**
 *  Fonction membre de la sous-classe AI qui cherche à minimiser le score de l'AI
 * */
float AI::min_score(map<string,int> b, int depth, int alpha, int beta)
{
	if ( depth == 0 )
		return heuristics_othello(b);
	int player_nbr_token = getNumber_of_token();
	int opponant_nbr_token = opponant_pointer->getNumber_of_token();
	unordered_set<string> moves = minmax_compute_legal_moves(b, 1);
	int score = infinity;
	for ( auto it = moves.begin(); it != moves.end(); it++ )
	{
		number_of_token = player_nbr_token;
		opponant_pointer->setNumber_of_token(opponant_nbr_token-opponant_pointer->getNumber_of_token());
		map<string, int> b_copy = b;
		execute_movement(*it, b_copy, 1);
		score = min(float(score), max_score(b_copy, depth-1, alpha, beta).first);
		if ( score <= alpha )
			return score;
		beta = min(beta, score);
	}
	number_of_token = player_nbr_token;
	opponant_pointer->setNumber_of_token(opponant_nbr_token-opponant_pointer->getNumber_of_token());
	return score;
}

/**
 * Fonction membre de la sous-classe AI qui est l'implémentation même de l'algorithme d'élagage alpha-bêta
 *  Appelle la fonction max_score() qui appelle à son tour la fonction min_score() qui appelle ensuite à nouveau max_score() et ce jusqu'à un état final
 * */
string AI::alpha_beta_pruning_minimax(map<string,int> b, int depth)
{
	int player_nbr_token = getNumber_of_token();
	int opponant_nbr_token = opponant_pointer->getNumber_of_token();
	string best_move = max_score(b, depth, -infinity, infinity).second;
	number_of_token = player_nbr_token;
	opponant_pointer->setNumber_of_token(opponant_nbr_token-opponant_pointer->getNumber_of_token());
	return best_move;
}


			
Folder::Folder(int c)
{
	color = c;                                     
	type_of_player = 2;
	if (c==88){
		nom_fichier_in = "./noir.txt";
		nom_fichier_out = "./blanc.txt";
		ofstream fichier_out;
	    ifstream fichier_in;
	}
	creatFolders();
}

/**
 * Fonction qui ouvre un fichier en lecture et un autre en écriture
 * */
void Folder::creatFolders()
{	
	
	while (!fichier_in.is_open())
	{
		cout << "Attente du l'adversaire (fichier "<<nom_fichier_in<< " indisponible)" << endl;
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		fichier_in.open(nom_fichier_in);
	}
	
	fichier_out.open(nom_fichier_out);  
}

/**
 * Fonction permettant de lire/attendre le coup joué dans le fichier ouvert en lecture
 * */
void Folder::getFileIn(string *pos)
{
	
	string rep;
	cout<<"waiting for a correct answer in the file "<< nom_fichier_in<<endl;
	while (!(getline(fichier_in,rep)))
			{
				// Echec de la lecture - Effacement des flags d'erreur			
				fichier_in.clear();
				fichier_in.sync();
				// Ajout d'une temporisation avant de réessayer
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
	
	*pos=rep;
}

/**
 * Fonction qui permet d'écrire dans un fichier
 * */
void Folder::putFileOut(string pos)
{
	fichier_out << pos <<endl;
	
}


void Folder::closeFolders()
{
	fichier_out.close();
	fichier_in.close();
}
