//view header

#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;


/*  {}   \n    []    */


class View1
{
	private:
	    
	    vector <string> leters = {"a","b","c","d","e","f","g","h"};
	    vector <string> numbers= {"1","2","3","4","5","6","7","8"};
	    map<string,int>::const_iterator itr1;
	    
	 public:
	    
	    View1()=default;
 	    void drawMap(map<string,int> & c);   // const
 	    
	
};
