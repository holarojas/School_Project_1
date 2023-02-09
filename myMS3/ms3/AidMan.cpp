/*
Final Project Milestone 2
Module: AidMan
Filename: AidMan.cpp
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
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"


using namespace std;
namespace sdds
{
	//Private function. Returns an unsigned integer that is the user's selection of an option in the main menu of the system
	unsigned int AidMan::menu() const
	{
		
		string appName = "Aid Management System Version 0.1";
		Date appDate;

		cout << appName << endl;
		cout << "Date: " << appDate << endl;
		if (m_fileName == nullptr) {
			cout << "Data file: " << "No file" << endl;
		}
		else {
			cout << "Data file: " << m_fileName << endl;
		}
		cout << "---------------------------------" << endl;

		//Run the main menu and return the selection made by the user
		
		return m_mainMenu.run();
	}


	//Default Constructor
	AidMan::AidMan()
	{
		m_fileName = nullptr;
	}


	//Default Destructor
	AidMan::~AidMan()
	{
		delete[] m_fileName;
		m_fileName = nullptr;
	}

	//Runs the whole application
	void AidMan::run()
	{
		bool exit = false;
		do {
			unsigned int selection = menu();
			switch (selection) {
			case 1:
				//List Items
				cout << endl << "****List Items****" << endl << endl;
				break;
			case 2:
				//Add Item
				cout << endl << "****Add Item****" << endl << endl;
				break;
			case 3:
				//Remove Item
				cout << endl << "****Remove Item****" << endl << endl;
				break;
			case 4:
				//Update Quantity
				cout << endl << "****Update Quantity****" << endl << endl;
				break;
			case 5: 
				//Sort
				cout << endl << "****Sort****" << endl << endl;
				break;
			case 6:
				//Ship Items
				cout << endl << "****Ship Items****" << endl << endl;
				break;
			case 7:
				//New/Open Aid Database
				cout << endl << "****New/Open Aid Database****" << endl << endl;
				break;
			case 0:
				//Exit
				exit = true;
				cout << "Exiting Program!" << endl;
				break;
			}

		} while (exit == false);
	}
	
}