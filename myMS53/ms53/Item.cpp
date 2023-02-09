/*
Final Project Milestone 3
Module: Item
Filename: Item.cpp
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
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include "Item.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	//Set all attributes to zero, nullptr or false
	void Item::setEmpty()
	{
		m_price = 0.0;
		m_qtyOnHand = 0;
		m_neededQty = 0;
		m_descr = nullptr;
		m_linear = false;
		m_SKU = 0;
	}

	//Query that returns the linear flag of the item
	bool Item::linear() const
	{
		return m_linear;
	}

	//Default Constructor. Sets all attributes to zero, nullptr and false.
	Item::Item()
	{
		setEmpty();
	}

	//Destructor
	Item::~Item()
	{
		delete[] m_descr;
		m_descr = nullptr;
	}

	//Copy Constructor
	Item::Item(const Item& inObj)
	{
		setEmpty();
		if (m_descr != nullptr) {
			m_descr = nullptr;
		}
		delete[] m_descr;
		//setEmpty();

		m_price = inObj.m_price;
		m_qtyOnHand = inObj.m_qtyOnHand;
		m_neededQty = inObj.m_neededQty;
		if (inObj.m_descr != nullptr) {
			ut.alocpy(m_descr, inObj.m_descr);
		}
		m_linear = inObj.m_linear;
		m_SKU = inObj.m_SKU;
		m_itemState = inObj.m_itemState; //Not sure if this should go because I don't have the operator = overload in Status class
	}

	//Overload assignment operator
	Item& Item::operator=(const Item& inObj)
	{
		//Make sure this is not a self copy
		if (&(*this) != &inObj) {
			//Do exactly the same as copy constructor
			delete[] m_descr;
			setEmpty();

			m_price = inObj.m_price;
			m_qtyOnHand = inObj.m_qtyOnHand;
			m_neededQty = inObj.m_neededQty;
			if (inObj.m_descr != nullptr) {
				ut.alocpy(m_descr, inObj.m_descr);
			}
			m_linear = inObj.m_linear;
			m_SKU = inObj.m_SKU;
		}
		else {
			delete[] m_descr;
			setEmpty();
		}
		return *this;
	}

	//-----------------------------------------------------------------------
	//VIRTUAL PUBLIC QUERY iPRODUCT OVERRIDES
	//Returns the needed-quantity attribute
	int Item::qtyNeeded() const
	{
		return m_neededQty;
	}

	//Returns the on-hand quantity attribute
	int Item::qty() const
	{
		return m_qtyOnHand;
	}

	//Returns the price
	Item::operator double() const
	{
		return m_price;
	}

	//Returns the state of object being good
	Item::operator bool() const
	{
		return m_itemState;
	}


	//VIRTUAL PUBLIC MODIFIER iPRODUCT OVERRIDES
	//Reduces the on-hand quantity by the received value
	int Item::operator-=(int qty)
	{
		m_qtyOnHand -= qty;
		return m_qtyOnHand;
	}

	//Increases the on-hand quantity by the received value
	int Item::operator+=(int qty)
	{
		m_qtyOnHand += qty;
		return m_qtyOnHand;
	}

	//Sets the linear flag attribute to true or false
	void Item::linear(bool isLinear)
	{
		m_linear = isLinear;
	}
	//-----------------------------------------------------------------------
	
	//Sets the state of the Item object back to good, by resetting the state attribute
	void Item::clear()
	{
		//Casting a Status object to a boolean should return true if the description is null and false if it is not. 
		//Which means if the Status has no description, the owner class is in a valid state. (No news is good news.)
		m_itemState.clear();
	}

	//VIRTUAL OPERATOR == iPRODUCT OVERRIDES
	//The integer comparison returns true if the SKU attribute matches the received value
	bool Item::operator==(int sku) const
	{
		return m_SKU == sku;
	}
	
	//The constant character pointer comparison searches in the description of the item for the appearance of the received Cstring.
		//If a match was found it returns true.
		//If any of the descriptions (The Items or the received value) are null 
		//or the match is not found, it will return false.
	bool Item::operator==(const char* description) const
	{
		bool result = false;
		string temp(m_descr); //Convert char* to string, so we can use find() function

		if (temp.find(description) != string::npos) {
			result = true;
		}

		return result;
	}

	//-----------------------------------------------------------------------
	//VIRTUAL INPUT/OUTPUT METHODS iPRODUCT OVERRIDES
	//If the state of the Item is good, it will write the SKU, description, on-hand quantity, needed quantity and price 
	//in tab-separated format.
	std::ofstream& Item::save(std::ofstream& ofstr) const
	{
		if(m_itemState) //If state is true it should mean it is in a valid state
		{
			//The price should be written with 2 digits  after the decimal point
			ofstr << m_SKU << "\t" << m_descr << "\t" << m_qtyOnHand << "\t" << m_neededQty << "\t" << fixed << setprecision(2) << m_price;
			//No newline is added
		}
		//If the state is no good, it will do nothing
		return ofstr;
	}

	//
	std::ifstream& Item::load(std::ifstream& ifstr)
	{
		m_itemState.clear();
	
		if (m_descr != nullptr) {
			delete[] m_descr;
			m_descr = nullptr;
		}
		
		m_descr = nullptr;

		if (ifstr.peek() != EOF) {
		//The tab separated SKU, description, on-hand quantity, needed quantity and price are read into their corresponding
		//attributes and then single character is discarded from the file.
			string temp = { 0 };

			getline(ifstr, temp, '\t');
			m_SKU = atoi(temp.c_str());

			getline(ifstr, temp, '\t');
			ut.alocpy(m_descr, temp.c_str());

			getline(ifstr, temp, '\t');
			m_qtyOnHand = atoi(temp.c_str());

			getline(ifstr, temp, '\t');
			m_neededQty = atoi(temp.c_str());

			//getline(ifstr, temp, '\n');
			//getline(ifstr, temp, '\t');
			//m_price = stod(temp.c_str());
			
			int beginPos = ifstr.tellg();
			getline(ifstr, temp, '\t');
			if (temp.find('\n') != string::npos) { //If find a new line in temp string
				ifstr.seekg(beginPos, ios_base::beg); //I set the position back at the beginning of the line
				getline(ifstr, temp, '\n'); //I read until a new line
			}
			m_price = stod(temp.c_str());

			
		}
		else {
			//If we've reached the EOF then ignore a character and that'll set
			//ifstr in a fail state, so we can get out of the while loop in descriptive()
			ifstr.ignore(1);
		}

		if (ifstr.fail()) {
			m_itemState = "Input file stream read failed!";
		}
		return ifstr;
	}

	//If the state is bad, you print the state
	//If the state is good you print the Items
	std::ostream& Item::display(std::ostream& ostr) const
	{
		if (m_descr != nullptr) {
			if (m_itemState) {
				if (m_linear) {
					//If in linear format
					ostr << setfill(' '); //Because in Date.cpp we have setfill to zeros. We change it back here to space.
					ostr.width(5);
					ostr << m_SKU << " | ";
					if (strlen(m_descr) <= 35) {
						ostr << m_descr;
						for (unsigned int i = 0; i < 35 - strlen(m_descr); i++) {
							ostr << " ";
						}
					}
					else {
						for (int i = 0; i < 35; i++) {
							ostr << m_descr[i];
						}
					}
					ostr << " | ";
					ostr.width(4);
					ostr << m_qtyOnHand;
					ostr << " | ";
					ostr.width(4);
					ostr << m_neededQty;
					ostr << " | ";
					ostr.width(7);
					ostr.precision(2);
					ostr << fixed << m_price;
					ostr << " |";
				}
				else {
					//If in descriptive format
					ostr << "AMA Item:" << endl;
					ostr << m_SKU << ": " << m_descr << endl;
					ostr << "Quantity Needed: " << m_neededQty << endl;
					ostr << "Quantity Available: " << m_qtyOnHand << endl;
					ostr << "Unit Price: $" << m_price << endl;
					int qtyNotOnHand = m_neededQty - m_qtyOnHand;
					ostr << fixed << setprecision(2) << "Needed Purchase Fund: $" << (qtyNotOnHand)*m_price << endl;
				}
			}
			else {
				//If the state is bad
				m_itemState.print(ostr);
			}
		}
		
		
		return ostr;
	}

	//Reads the SKU from the screen. It makes sure the SKU number begins with digits 4 to 9 and it is 5 digits long
	int Item::readSku(std::istream& istr)
	{
		m_SKU = ut.getInt(40000, 99999, "SKU: ", "Invalid Integer");
		return m_SKU;
	}

	//Will first prompt  the user with the title "AMA Item" and then displays the SKU and reads the rest of the information
	//in a full-proof way (the same as SKU)
	std::istream& Item::read(std::istream& istr)
	{
		string temp = { 0 };

		delete[] m_descr;
		m_itemState.clear();
		istr.ignore(2000, '\n');

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_SKU << endl;
		cout << "Description: ";
		
		//istr >> noskipws >> temp;
		getline(istr, temp);
		ut.alocpy(m_descr, temp.c_str());
		m_neededQty = ut.getInt(1, 9999, "Quantity Needed: ", "Invalid Integer");
		m_qtyOnHand = ut.getInt(0, m_neededQty, "Quantity On Hand: ", "Invalid Integer");
		m_price = ut.getDouble(0.00, 9999.00, "Unit Price: $", "Invalid number");
		if (istr.fail()) {
			m_itemState = "Console entry failed!";
		}
		return istr;
	}
	//-----------------------------------------------------------------------
}