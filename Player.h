#include <string>
#include <cstring>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <vector>
#include <iostream>

#include <fstream>
#include <chrono>
#include <thread>
using std::ifstream;
using std::ofstream;
using std::getline;


using std::cout;
using std::endl;

#define infinity std::numeric_limits<int>::max()

using std::string;
using std::map;
using std::set;
using std::min;
using std::max;
using std::pair;
using std::unordered_set;
using std::vector;

class Player
{
	protected: 
		int color;
		int number_of_token=2;
		int type_of_player; //0=Human; 1=AI; 2=Folder
		Player* opponant_pointer=NULL;
		string last_move;    		
	public:
		Player(int c=88);
		int getColor() const;
		int getNumber_of_token() const;
		void setNumber_of_token(int i);
		int getType_of_player() const;
		void setOpponant_pointer(Player* o);
		int sign_of_operator(int c);
		string alter_position(string pos, int c, int o);
		void apply_color(map<string, int>& b, string pos, int color, int i, int o, int p);
		bool cross_validate_movement(string pos, map<string, int>& b, int mode, int player);
		bool diagonal_validate_movement(string pos, map<string, int>& b, int mode, int player);
		bool validate_movement(string pos, map<string, int> b, int player);
		bool execute_movement(string pos, map<string, int>& b, int player);
		bool check_position_board(string pos);
		set<string> compute_legal_moves(map<string, int> b, int player);
		string getLast_move() const;         
		void setLast_move(string lm);		 

};

class Human : public Player
{
	public:
		Human(int c=88);
};

class AI : public Player
{
	private:
		int weighted_positions[64] = {20, -3, 11, 8, 8, 11, -3, 20, -3, -7, -4, 1, 1, -4, -7, -3, 11, -4, 2, 2, 2, 2, -4, 11, 8, 1, 2, -3, 
			-3, 2, 1, 8, 8, 1, 2, -3, -3, 2, 1, 8, 11, -4, 2, 2, 2, 2, -4, 11, -3, -7, -4, 1, 1, -4, -7, -3, 20, -3, 11, 8, 8, 11, -3, 20};
	public:
		AI(int c=88);
		unordered_set<string> randomise_set(vector<string> v);
		unordered_set<string> minmax_compute_legal_moves(map<string,int> b, int player);
		int heuristic_static_weights(map<string,int> b);
		float heuristic_token_parity_normed(map<string,int> b);
		float heuristic_corners_captured_normed(map<string,int> b);
		float heuristic_actual_mobility_normed(map<string,int> b);
		float heuristics_othello(map<string,int> b);
		pair<float, string> max_score(map<string,int> b, int depth, int alpha, int beta);
		float min_score(map<string,int> b, int depth, int alpha, int beta);
		string alpha_beta_pruning_minimax(map<string,int> b, int depth);		
};

class Folder : public Player
{  											
	protected:
		string nom_fichier_in = "./blanc.txt";
		string nom_fichier_out = "./noir.txt";
		ofstream fichier_out ;
	    ifstream fichier_in ;
	public:
		Folder(int c=88);
		void creatFolders();
		void getFileIn(string *pos);
		void putFileOut(string pos);
		void closeFolders();
};
