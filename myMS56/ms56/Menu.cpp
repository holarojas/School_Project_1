/*
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	//Default Constructor
	Menu::Menu()
	{
		m_menuCont = nullptr;
		m_optNum = 0;
	}

	//Constructor
	Menu::Menu(unsigned int inOptNum, std::string inMenuCont)
	{
		if (inOptNum > MAX_OPT_NUM || strlen(inMenuCont.c_str()) == 0) {
			//Menu is rendered invalid
			delete[] m_menuCont;
			m_menuCont = nullptr;
			m_optNum = 0;
		}
		m_optNum = inOptNum;
		m_menuCont = nullptr;
		m_menuCont = new char[strlen(inMenuCont.c_str()) + 1];
		strcpy(m_menuCont, inMenuCont.c_str());
	}

	//Destructor
	Menu::~Menu()
	{
		delete[] m_menuCont;
		m_menuCont = nullptr;
	}

	//Display menu content and wait for user input
	unsigned int Menu::run() const
	{
		cout << m_menuCont << "0- Exit" << endl;
		return ut.getInt(0, m_optNum, "> ", nullptr); 
	}
}