/*
Final Project Milestone 2
Module: AidMan
Filename: AidMan.h
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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"

namespace sdds
{

	class AidMan
	{
		char* m_fileName;
		Menu m_mainMenu = {7, "1- List Items\n"
								"2- Add Item\n"
								"3- Remove Item\n"
								"4- Update Quantity\n"
								"5- Sort\n"
								"6- Ship Items\n"
								"7- New/Open Aid Database\n"
								"---------------------------------\n" };

		unsigned int menu() const;

	public:
		AidMan();
		AidMan(const AidMan& src) = delete;  //Prevent copying any instance of the class
		void operator=(const AidMan&) = delete;  //Prevent assignment any instance of the class
		~AidMan();
		void run();
	};
}

#endif // !SDDS_AIDMAN_H
