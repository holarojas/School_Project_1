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
2022/04/06	Added Menu 1,2,3 and 7 functionalities
2022/04/07  Added Menu 4 functionality
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
#include "Perishable.h"


using namespace std;
namespace sdds
{
	//Private function. Returns an unsigned integer that is the user's selection of an option in the main menu of the system
	unsigned int AidMan::menu() const
	{
		
		string appName = "Aid Management System";
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
		m_iProdItems = 0;
		for (int i = 0; i < sdds_max_num_items; i++) {
			m_iProdPtrs[i] = nullptr;
		}
	}

	//Default Destructor
	AidMan::~AidMan()
	{
		delete[] m_fileName;
		m_fileName = nullptr;
		deallocate();
	}

	//Runs the whole application
	void AidMan::run()
	{
		bool exit = false;		
		string temp = { 0 };

		//Variables for Menu Opt #1:
		char userSelect[2] = { 0 };
		int rowId = 0;

		do {
			unsigned int selection = menu();
			if (m_fileName == nullptr && selection != 7) {
				selection = 7;
			}
			switch (selection) {
			case 1:
				//List Items
				cout << endl << "****List Items****" << endl;
				list();
				//Ask the user for the next action
				cout << "Enter row number to display details or <ENTER> to continue:\n> ";
				cin.ignore();
				cin.read(userSelect, 1);
				userSelect[1] = '\0';
				if (strcmp(userSelect, "\n") == 0) {
					//If input is [Enter] do nothing
					cout << endl;
				}
				else { //If input is a row Number, then display that row information
					rowId = stoi(userSelect);
					m_iProdPtrs[rowId - 1]->linear(false);
					cout << *m_iProdPtrs[rowId - 1] << endl;
				}

				break;
			case 2:
				//Add Item
				cout << endl << "****Add Item****" << endl;
				addItem();
				break;
			case 3:
				//Remove Item
				cout << endl << "****Remove Item****" << endl;
				doActionByDescr("remove");
				break;
			case 4:
				//Update Quantity
				cout << endl << "****Update Quantity****" << endl;
				doActionByDescr("update");
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
				cout << endl << "****New/Open Aid Database****" << endl;
				cout << "Enter file name: ";
				cin >> temp;
				ut.alocpy(m_fileName, temp.c_str());
				load();
				cout << m_iProdItems << " records loaded!" << endl << endl;
				break;
			case 0:
				//Exit
				exit = true;
				cout << "Exiting Program!" << endl;
				break;
			}

		} while (exit == false);

		save();
	}

	//Method for saving data records in file
	void AidMan::save()
	{
		if (m_fileName != nullptr) {
			ofstream file(m_fileName); //Appending at the end
			for (int i = 0; i < m_iProdItems; i++) {
				m_iProdPtrs[i]->save(file);
				file << endl;
			}
		} 
		//If the filename attribute is null, this function does nothing.
	}

	//Method to deallocate all the memory allocated by the class
	void AidMan::deallocate()
	{
		if (m_iProdItems > 0) {
			for (int i = 0; i < m_iProdItems; i++) {
				delete m_iProdPtrs[i];
				m_iProdPtrs[i] = nullptr;
			}
			delete[] m_fileName;
			m_iProdItems = 0;
		}
		
	}

	//Method to load data records from a file and returns true if at least one record is loaded
	bool AidMan::load()
	{
		bool recAdded = false;
		int selection = 0, idx = 0;
		iProduct* blankItem = new Item;
		iProduct* blankPerish = new Perishable;

		ifstream file(m_fileName);
		if (!file.is_open()) { //If opening the file was not successful
			cout << "Failed to open " << m_fileName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!\n0- Exit" << endl;
			selection = ut.getInt(0, 1, "> ", nullptr);
			if (selection == 1) {
				//Create an empty file under the same name
				ofstream newFile(m_fileName);
			}
		}
		else { //If opening the file was successful			
			do {

				if (file.peek() == '1' || file.peek() == '2' || file.peek() == '3') { //If the upcoming record is perishable
					
					//Create a new Perishable item in the next available iProduct pointers element.
					m_iProdPtrs[idx] = new Perishable;
					if (m_iProdPtrs[idx] != nullptr) { //If the allocation was a success
						m_iProdPtrs[idx]->load(file);
						if (m_iProdPtrs[idx]) { //Loaded item is checked to be in a good state
							m_iProdItems++;
							idx++; 
							recAdded = true;
						}
						else { //If in bad state, loaded item is deleted
							m_iProdPtrs[idx] = blankItem;
						}
					}
				}
				else if (file.peek() == '4' || file.peek() == '5' || file.peek() == '6' || file.peek() == '7' || file.peek() == '8' || file.peek() == '9') { //If the upcoming record is non-perishable
					//Create an Item in the next available iProduct pointers.					
					m_iProdPtrs[idx] = new Item;
					if (m_iProdPtrs[idx] != nullptr) { //If the allocation was a success
						m_iProdPtrs[idx]->load(file);
						if (m_iProdPtrs[idx]) { //Loaded item is checked to be in a good state
							m_iProdItems++;
							idx++;
							recAdded = true;
						}
						else { //If in bad state, loaded item is deleted
							m_iProdPtrs[idx] = blankPerish;
						}
					}
				}
				else { //If the next character is not recognized as a valid digit
					//The ifstream is set into an invalid state
					file.setstate(ios::failbit);
				}
			} while (!file.eof());
		}

		delete blankItem;
		delete blankPerish;
		
		return recAdded;
	}

	//If the user press enter, go back to the main menu otherwise display the selected item in a non-linear format.
	//(The integer entry for the row number must be fool-proof)
	int AidMan::list(const char* sub_desc)
	{
		ofstream outFile(m_fileName);
		int recsDisplayed = 0;
	
		bool isEmpty = (m_iProdItems == 0) ? true : false; //Validate if list is empty
		if (!isEmpty) {

			//Display Header
			cout.width(4);
			cout << "ROW" << " | ";
			cout.width(5);
			cout << "SKU " << " | ";
			cout.width(35);
			cout << left << "Description" << " | ";
			cout.width(4);
			cout << "Have" << " | ";
			cout.width(4);
			cout << "Need" << " | ";
			cout.width(7);
			cout << " Price " << " | ";
			cout.width(6);
			cout << left << "Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			if (sub_desc == nullptr) { //If nullptr, print all the items in linear format
				for (int i = 0; i < m_iProdItems; i++) {
					m_iProdPtrs[i]->linear(true);
					cout.width(4);
					cout << right << i + 1;
					cout << " | " << *m_iProdPtrs[i] << endl;
					recsDisplayed++;
				}
			}
			else if (sub_desc != nullptr) { //If not nullptr
				//Print only the items containing the sub_desc in their desc, in linear format
				for (int i = 0; i < m_iProdItems; i++) {
					if (*m_iProdPtrs[i] == sub_desc) { //If sub_desc is found in the Product's description
						m_iProdPtrs[i]->linear(true);
						cout.width(4);
						cout << right << i + 1;
						cout << " | " << *m_iProdPtrs[i] << endl;
						recsDisplayed++;
					}
				}
			}
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------";
				
		} else {
			cout << "The list is emtpy!" << endl;
		}
		cout << endl;
		return recsDisplayed;
	}

	//Loops through all the iProduct Pointers elements and if the SKU is a match it will return the index.
	//Otherwise it will return -1.
	int AidMan::search(int sku) const
	{
		int idx = 0;
		ifstream file(m_fileName);

		for (int i = 0; i < m_iProdItems; i++) {
			if (*m_iProdPtrs[i] == sku) { //If sku was found in the records
				idx = i;
				i = m_iProdItems;
			}
			else {
				idx = -1;
			}
		}

		return idx;
	}

	//Add a new Item with previous validation to see if SKU already exists
	void AidMan::addItem()
	{
		int selection;
		int inSKU;

		if (m_fileName == nullptr) {
			cout << "No data file is open!" << endl;
		}
		else if (m_iProdItems == sdds_max_num_items) {
			cout << "Database full!" << endl;

		}
		else {
			cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit" << endl;
			selection = ut.getInt(0, 2, "> ", nullptr);

			if (selection == 0) {
				cout << "Aborted\n";
			}
			else {

				if (selection == 1) { // Perishable
					m_iProdPtrs[m_iProdItems] = new Perishable;
				}
				else if (selection == 2) { //Non-Perishable Item
					m_iProdPtrs[m_iProdItems] = new Item;
				}
				inSKU = m_iProdPtrs[m_iProdItems]->readSku(cin);
				
				if (search(inSKU) == -1) { //SKU was not found in records
					m_iProdPtrs[m_iProdItems]->read(cin);
					cout << endl;
					if (m_iProdPtrs[m_iProdItems]) { //If in good state
						m_iProdItems++;
					}
					else {
						//Otherwise, the allocated item is displayed and then deleted
						delete m_iProdPtrs[m_iProdItems];
					}
				}
				else {
					cout << "Sku: " << inSKU << " is already in the system, try updating quantity instead.\n" << endl;
					delete m_iProdPtrs[m_iProdItems];
				}
			}
		}
	}

	//Search an Item by asking the user for a description
	//Call the needed function to perform the selected action for an Item: remove/update
	void AidMan::doActionByDescr(const char* action)
	{
		string inDescr = { 0 };
		int inSKU;
		int idxFound;

		cout << "Item description: ";
		cin >> inDescr;

		if (list(inDescr.c_str()) > 0) { //List the items containing the string obtained by the user
			inSKU = ut.getInt(10000, 99999, "Enter SKU: ", nullptr);
			idxFound = search(inSKU);
			if (idxFound == -1) { //inSKU was not found in the records
				cout << "SKU not found!\n";
			}
			else { //inSKU was found in the records
				if (strcmp(action, "remove") == 0) { //If the action is to REMOVE an item
					remove(idxFound);
				}
				else if (strcmp(action, "update") == 0) { //If the action is to UPDATE an item
					updateQty(idxFound);
				}
			}
		}
		else {
			cout << "No matches found!\n";
		}
	}

	//Deletes the iProduct at index in iProduct Pointers
	//Then shifts all the iProducts to left once and reduces number of iProduct Items by one.
	void AidMan::remove(int index)
	{
		int confirm;
		int reps = (m_iProdItems - 1) - index; //Amount of places from index to end of array

		cout << "Following item will be removed: " << endl;
		m_iProdPtrs[index]->linear(false);
		m_iProdPtrs[index]->display(cout);
		cout << endl;
		cout << "Are you sure?\n1- Yes!\n0- Exit\n";
		confirm = ut.getInt(0, 1, "> ", nullptr);

		switch (confirm) {
		case 1: //Yes! - Deletes the product record
			delete m_iProdPtrs[index]; //Delete the allocated memory of the product I will remove
			for (int i = 0; i < reps; i++) {
				m_iProdPtrs[index + i] = m_iProdPtrs[index + (i + 1)]; //Copy the pointer from the right place to the left place
			}
			m_iProdPtrs[m_iProdItems - 1] = nullptr; //The last product is now copied to the place on the left, so we need to point the previous last product to NULL because that place is available now
			m_iProdItems--; //We need to subtract 1 to the total of products
			cout << "Item removed!\n" << endl;
			break;
		case 0: //Exit without deleting.
			cout << "Aborted!\n" << endl;
			break;
		}
	}

	//Update quantity values of items
	void AidMan::updateQty(int index)
	{
		int confirm;
		int maxNeeded;
		int inputQty;

		cout << "1- Add\n2- Reduce\n0- Exit\n";
		confirm = ut.getInt(0, 2, "> ", nullptr);

		switch (confirm) {
		case 1: //Add - Quantity is increased by the entered amount.
			maxNeeded = m_iProdPtrs[index]->qtyNeeded() - m_iProdPtrs[index]->qty(); //Get the max amount of Qty to be a fullfilled item
			if (maxNeeded == 0) { //If product is already fulfilled
				cout << "Quantity Needed already fulfilled!\n" << endl;
			}
			else {
				inputQty = ut.getInt(1, maxNeeded, "Quantity to add: ", nullptr);
				*m_iProdPtrs[index] += inputQty;
				cout << inputQty << " items added!\n" << endl;
			}
			break;
		case 2: //Reduce - Quantity is reduced by the entered amount
			if (m_iProdPtrs[index]->qty() == 0) { //If we don't have qtyOnHand
				cout << "Quaintity on hand is zero!\n" << endl;
			}
			else {
				inputQty = ut.getInt(1, m_iProdPtrs[index]->qty(), "Quantity to reduce: ", nullptr);
				*m_iProdPtrs[index] -= inputQty;
				cout << inputQty << " items removed!\n" << endl;
			}
			break;
		case 0: //Exit without updating
			cout << "Aborted!\n" << endl;
			break;
		}
	}
}