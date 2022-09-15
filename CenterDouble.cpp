//
// CenterDouble.cpp
//
//

#include "CenterDouble.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std; 

std::string centerDouble(double value, unsigned int width)
{
	stringstream my_stringstream; 
	string my_string; 

	my_stringstream << value; 
	my_string = my_stringstream.str(); 

	if (my_string.length() >= width)
	{
		return my_string; 
	}
	else
	{
		unsigned int diff = width - my_string.length(); 
		if (diff % 2 == 0)
		{
			unsigned int add = 0.5 * diff; 
			string str(add, ' '); 
			string str_final = str + my_string + str; 
			return str_final; 
		}
		else
		{
			unsigned int add_left = 0.5 * diff; 
			string str_left(add_left, ' ');

			unsigned int add_right = add_left + 1; 
			string str_right(add_right, ' '); 

			string str_final = str_left + my_string + str_right; 
			return str_final; 
		}
	}
}

std::string centerDouble(double value)
{
	return centerDouble(value, 79); 
}
