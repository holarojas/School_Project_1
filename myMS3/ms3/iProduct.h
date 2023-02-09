/*
Final Project Milestone 3
Module: iProduct
Filename: iProduct.h
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
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
#include "Status.h"

namespace sdds
{
	//iProduct is an interface for an Item in the application
	class iProduct
	{
		
		
	public:
		// Destructor
		virtual ~iProduct()
		{
		};
		// To read the Stock-Keeping Unit from console before main data entry
		virtual int readSku(std::istream& istr) = 0;
		// To reduce the quantity on hand
		virtual int operator-=(int qty) = 0;
		// To increase the quantity on hand
		virtual int operator+=(int qty) = 0;
		// Returns the price of the produce
		virtual operator double()const = 0;
		// Returns if the iProduct is in a good state
		virtual operator bool()const = 0;
		// Returns the number of products needed
		virtual int qtyNeeded()const = 0;
		// Retuns the quantity on hand
		virtual int qty()const = 0;
		// Determines if the iProduct is displayed in a linear format or descriptive format
		virtual void linear(bool isLinear) = 0;
		// Saves the iProduct into a file
		virtual std::ofstream& save(std::ofstream& ofstr)const = 0;
		// Loads an iProduct from a file
		virtual std::ifstream& load(std::ifstream& ifstr) = 0;
		// Displays the iProduct on the screen
		virtual std::ostream& display(std::ostream& ostr)const = 0;
		// Reads the iProduct from the console
		virtual std::istream& read(std::istream& istr) = 0;
		// Return true if the sku is a match to the iProduct's sku
		virtual bool operator==(int sku)const = 0;
		// Returns true if the description is found in the iPorduct's description
		virtual bool operator==(const char* description)const = 0;
	};

	std::ostream& operator<<(std::ostream& ostr, const iProduct& inObj);
	std::istream& operator>>(std::istream& istr, iProduct& inObj);

}

#endif // !SDDS_IPRODUCT_H
