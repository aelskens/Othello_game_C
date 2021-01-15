#include "Map.h"


Map::Map(string p1, string p2)
{
	if ( p1 == "human" )
	{
		Human* pX = new Human();
		player = pX;
	}
	else if ( p1 == "ai" )
	{
		AI* pX = new AI();
		player = pX;
	}
	else
	{
		Folder* pX = new Folder();
		player = pX;
	}
	if ( p2 == "human" )
	{
		Human* pO = new Human(79);
		opponant = pO;
	}
	else if ( p2 == "ai" )
	{
		AI* pO = new AI(79);
		opponant = pO;
	}
	else
	{
		Folder* pO = new Folder(79);
		opponant = pO;
	}
	
	board.insert(pair<string, int> ("d4", 79));
	board.insert(pair<string, int> ("e5", 79));

	board.insert(pair<string, int> ("d5", 88));
	board.insert(pair<string, int> ("e4", 88));
}


Player* Map::getPlayer() const{return player;}
void Map::setPlayer(Player* p){player = p;}
Player* Map::getOpponant() const{return opponant;}
void Map::setOpponant(Player* p){opponant = p;}
int Map::getSize_of_board() const{return size_of_board;}

/**
 * Fonction membre de la classe Map qui permet de transformer un string en un string dont tous les caractères sont en minuscule
 * */
string Map::minuscule(string c)
{
	for ( int i=0; i <= c.length(); i++ )
	{
		if (c[i]>='A' && c[i]<='Z')
			c[i] += 'a' - 'A';
	}
	return c;
}

/**
 * Fonction membre de la classe Map qui permet de récupérer un string depuis le terminal ou bien depuis un fichier pour les sous-classes Human et Folder
 * Appelle également des fonctions membres de la classe Player pour donner une liste de mouvements possibles, vérifier et appliquer de positions entrées 
 * */
string Map::human_enter_validate_apply_movement(int type)    
{
	string pos;
	string np = namePlayer(player->getColor());
	cout << np << ": Please enter a valid position: ";  
	if(type==0)
		cin >> pos;          						  
	else 
	{
		Folder* player_Folder = static_cast<Folder*>( player );
		player_Folder->getFileIn(&pos);
	}
	pos = minuscule(pos);
	if ( pos != "00")
	{
		while ( board[pos] != 0 || int(pos[0]) < 97 || int(pos[0]) >= 97+getSize_of_board() || int(pos[1]) <= 48 || int(pos[1]) > 48+getSize_of_board() || pos.length() > 2)
			{
				if ( board[pos] == 0 )
					board.erase(pos);
				if ( pos == "help" )
				{
					set<string> legal_moves = player->compute_legal_moves(board, 0);
					if ( legal_moves.size() == 0 )
						cout << "There are no possible moves." << endl;
					else
					{
						cout << "Movements that can be played: ";
						for ( set<string>::iterator it = legal_moves.begin(); it != legal_moves.end(); it++ )
							cout << *it << " ";
						cout << endl;
					}
				}
				else
					cout << "Invalid position. ";
				cout << "Please enter a valid position: ";
				if ( type == 0 )
					cin >> pos;          						  
				else 
				{
					Folder* player_Folder = static_cast<Folder*>( player );
					player_Folder->getFileIn(&pos);
				}
				pos = minuscule(pos);
				if ( pos == "00" )
					break;
			}
		if ( pos != "00" )
			check = player->execute_movement(pos, board, 0);
	}
	if ( pos == "00" )
		check = true;
	if ( check == false )
	{
		board.erase(pos);
		cout << "Invalid movement." << endl;
		pos = human_enter_validate_apply_movement(type);     
	}
			
	return pos;
}

/**
 * Fonction membre de la classe Map qui permet de récupérer une position renvoyée par la fonction membre alpha_beta_pruning_minimax() de la sous-classe AI
 * */
string Map::ai_enter_validate_apply_movement()
{
	string np = namePlayer(player->getColor());
	AI* player_ai = static_cast<AI*>( player );
	int depth = 5;
	if ( 64-board. size() < 5 )
		depth = 64-board.size();
	string pos = player_ai->alpha_beta_pruning_minimax(board, depth);
	if ( pos != "00" )
		player->execute_movement(pos, board, 0);
	return pos;	
}

/**
 * Fonction membre de la classe Map qui permet de récupérer et exécuter les mouvements pour tous les types de joueurs et vérifie si le jeu est fini
 * Fait appelle aux deux fonctions membres human_enter_validate_apply_movement() et ai_enter_validate_apply_movement()
 * Pour déterminer le vainquer, appelle la fonction membre determine_winner() définie plus bas
 * */
void Map::enter_validate_apply_movement()
{
	string pos;                                               
	string np = namePlayer(player->getColor());
	string no = namePlayer(opponant->getColor());
	if ( player->getType_of_player() == 1 )             
		pos = ai_enter_validate_apply_movement();
	else 
		pos = human_enter_validate_apply_movement(player->getType_of_player());
	player->setLast_move(pos);
	if ( pos == "00" )
		cout << np << "skipped his turn." << endl;
	else
		cout << np << "has entered a valid position: " << pos << endl;									    
	if ( pos == "00"  && pos == lastpos )
	{
		determine_winner(np, no);
		setEnd(true);
	}
	else if ( board.size() == 64 )
	{
		determine_winner(np, no);
		setEnd(true);
	}
	else if ( opponant->getNumber_of_token() == 0 )
	{
		determine_winner(np, no);
		setEnd(true);
	}
	if ( board[pos] || pos == "00")
	{
		lastpos = pos;
		if ( pos == "00" )
			board.erase(pos);
	}
}


void Map::setEnd(bool b){end = b;}
bool Map::getEnd(){return end;}

/**
 * Fonction membre de la classe Map permettant l'affichage dans le terminal du plateau de jeu
 * Appelle la fonction membre drawMap() de la classe View
 * */
void Map::printMap1(){view.drawMap(board);}



/**
 * Fonction membre de la classe Map return le nom du joueur associé au int color pris en paramètre
 * */
string Map::namePlayer(int color){
	if (color == 79)
		return "White player ";
	else
		return "Black player ";
}

/**
 * Fonction membre de la classe Map qui permet de passer du tour du joueur actuel au tour de son adversaire devenant ainsi le "player" actuel
 * */
void Map::switchPlayer()
{
	Player* temp = getPlayer();
	setPlayer(opponant);
	setOpponant(temp);
}	

/**
 * Fonction membre de la classe Map imprime le nom du joueur gagnant avec son nombre de pions ainsi que le perdant et son nombre de pions
 * */
void Map::determine_winner(string np, string no)
{
	if (player->getNumber_of_token() == opponant->getNumber_of_token())
	{
		cout << "It's a draw, nobody has won." << endl;
		cout << "Both players have " << player->getNumber_of_token() << " tokens." << endl;
	}
	else if (player->getNumber_of_token() > opponant->getNumber_of_token())
	{
		cout << np << "has won with a total of " << player->getNumber_of_token() << " tokens." << endl;
		cout << "While " << no << "has lost with " << opponant->getNumber_of_token() << " tokens." << endl;
	}
	else if (opponant->getNumber_of_token() > player->getNumber_of_token())
	{
		cout << no << "has won with a total of " << opponant->getNumber_of_token() << " tokens." << endl;
		cout << "While " << np << "has lost with " << player->getNumber_of_token() << " tokens." << endl;
	}
}
