/*
Final Project Milestone 3
Module: iProduct
Filename: iProduct.cpp
Version 1.0
Author: Martha Rocio Rojas Martinez
Student ID: 112073218

Revision History
-----------------------------------------------------------
Date      Reason
2022/03/25  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "iProduct.h"

using namespace std;
namespace sdds
{
	//Overload insertion operator to call the display method
	std::ostream& operator<<(std::ostream& ostr, const iProduct& inObj)
	{
		inObj.display(ostr);
		return ostr;
	}

	//Overload extraction operator to call to read method
	std::istream& operator>>(std::istream& istr, iProduct& inObj)
	{
		inObj.read(istr);
		return istr;
	}
}