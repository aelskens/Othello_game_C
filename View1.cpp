//Map standard output view

#include "View1.h"

/*  {}   \n    []    */

	    
	    

void View1::drawMap(map<string,int> & c)  //const
{
	//dessine la premiere ligne
	cout<<"   ";
	for (int i=0; i<8;i++){
		cout<< leters[i];
		cout<<"  ";
		}
	cout<<"  "<<endl;
	//dessine les lignes suivantes
	
	for (int i=0;i<8;i++){
		cout<<numbers[i]<<"  ";
		
		
		for(int j=0; j<8;j++){
			string pos =leters[j]+numbers[i];
			if (c.find(pos)!=c.end()){    
				cout<<char(c[pos])<<"  ";   
				}
			else {
				cout<<".  ";
				}
			}
			
			
			
		cout<<numbers[i]<<endl;
		}
	//dessine la premiere ligne mais a la fin
	cout<<"   ";
	for (int i=0; i<8;i++){
		cout<< leters[i];
		cout<<"  ";
		}
	cout<<"  "<<endl;
}

