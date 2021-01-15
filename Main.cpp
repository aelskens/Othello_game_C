#include <iostream>
#include <vector>
#include <string>
#include "Map.h"

using std::cout;
using std::endl;
using std::vector;
using std::cin;

/**
 * Fonction qui permet de transformer un string en un string dont tous les caractères sont en minuscule
 * */
string minuscule(string c)
{
	for ( int i=0; i <= c.length(); i++ )
	{
		if (c[i]>='A' && c[i]<='Z')
			c[i] += 'a' - 'A';
	}
	return c;
}


int main()
{
								/** Affichage du debut de jeu **/
								
	cout << "##################       OTHELLO GAME       ##################" << endl;
	cout << "" << endl;
	cout << " 		      by Arthur Elskens," << endl;
	cout << "			 Ammar Hasan" << endl;
	cout << " 		      and Manal Ouahhabi" << endl;
	cout << "" << endl;
	string p1, p2;
	cout << "Please choose a type of player for the Black Player: ";
	cin >> p1;
	p1 = minuscule(p1);
	while ( p1 != "human" && p1 != "ai" && p1 != "folder" )
	{
		cout << "Allowed choices are: Human or AI or Folder" << endl;
		cout << "Please choose a type of player for the Black Player: ";
		cin >> p1;
		p1 = minuscule(p1);
	}
	cout << "Please choose a type of player for the White Player: ";
	cin >> p2;
	p2 = minuscule(p2);
	while ( p2 != "human" && p2 != "ai" && p2 != "folder")
	{
		cout << "Allowed choices are: Human or AI or Folder" << endl;
		cout << "Please choose a type of player for the White Player: ";
		cin >> p2;
		p2 = minuscule(p2);
	}
	
	Map map1(p1, p2);
	map1.printMap1();
	
	map1.getPlayer()->setOpponant_pointer(map1.getOpponant());
	map1.getOpponant()->setOpponant_pointer(map1.getPlayer());
	
	
					/** Boucle principale du jeu **/
			
	while(!map1.getEnd())
	{
		map1.enter_validate_apply_movement();
		if (map1.getOpponant()->getType_of_player()==2)    // écriture dans le fichier de sortie
		{
			Folder* player_Folder = static_cast<Folder*>( map1.getOpponant());
			player_Folder->putFileOut(map1.getPlayer()->getLast_move());
		}
		map1.switchPlayer();
		map1.printMap1();	
	}
	
						/** Fin du jeu **/
						
	 
				/** Fermeture des fichiers si necessaires **/
				
	if(map1.getPlayer()->getType_of_player()==2)
	{
		Folder* player_Folder = static_cast<Folder*>( map1.getPlayer());
		player_Folder->closeFolders();
	}
	if(map1.getOpponant()->getType_of_player()==2)
	{
		Folder* player_Folder = static_cast<Folder*>( map1.getOpponant());
		player_Folder->closeFolders();
	}
	
	return 0;
}
