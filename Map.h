#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <map>
#include <vector>
#include "View1.h"
#include "Player.h"


using std::map;
using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::ostream;


/*  {}   \n    []    */


class Map
{
	private: 
		map<string,int> board;
		Player* player;
		Player* opponant;
		int size_of_board = 8;
		bool check = false;
		bool end = false;
		string lastpos = "z1";
	    View1 view;
	 public:
	    Map(string p1, string p2);
		Player* getPlayer() const;
		void setPlayer(Player* p);
		Player* getOpponant() const;
		void setOpponant(Player* p);
		int getSize_of_board() const;
		string minuscule(string c);
		string human_enter_validate_apply_movement(int type);  
		string ai_enter_validate_apply_movement();
		void enter_validate_apply_movement();    
		bool getEnd();
		void setEnd(bool b);
	    void printMap1();
	    string namePlayer(int color);
	    void switchPlayer();
	    void determine_winner(string np, string no);
};
