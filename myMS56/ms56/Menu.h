/*
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author: Martha Rocio Rojas Martinez
Student ID: 112073218

Revision History
-----------------------------------------------------------
Date      Reason
2022/03/21  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H


namespace sdds
{
	const unsigned int MAX_OPT_NUM = 15;
	class Menu
	{
		unsigned int m_optNum;	//Unsigned integer that holds the number of available options. i.e. 3
		char* m_menuCont;		//Dynamically allocated text that contains the list of the options the user can select from. i.e. "1- Orange Juice\n2- Water\n3- Apple Juice\n" <-menu content
		
	public:
		Menu();
		Menu(unsigned int inOptNum, std::string inMenuCont);
		Menu(const Menu& src) = delete; //Prevent copying any instance of the class
		void operator=(const Menu& src) = delete; //Prevent assignment any instance of the class
		~Menu();

		unsigned int run() const;
	};
}

#endif