/*
Final Project Milestone 3
Module: Item
Filename: Item.h
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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"


namespace sdds
{
	//An Item is a concrete iProduct to keep track of the quantity and on-hand-quantity items to be prepared for shipping
	class Item: public iProduct
	{
		double m_price;
		int m_qtyOnHand;
		int m_neededQty;	//This int is the target amount for the item to be acquired.
		char* m_descr;		//Description of the item
		bool m_linear;		//Boolean flag to dictate to the display if the next output is going to be linear to descriptive

		void setEmpty();			

	protected:
		Status m_itemState; //Hold the state of the Item object
		int m_SKU;		//Hold the Stock-Keeping Unit number

		bool linear();		

	public:
		Item(); //= default;
		~Item();
		Item(const Item& inObj);
		Item& operator=(const Item& inObj);

		int qtyNeeded() const;
		int qty() const;
		operator double() const;
		operator bool() const;

		int operator-=(int qty);
		int operator+=(int qty);
		void linear(bool isLinear);

		void clear();

		bool operator==(int sku) const;
		bool operator==(const char* description) const;

		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);				
		std::ostream& display(std::ostream& ostr) const;
		int readSku(std::istream& istr);
		std::istream& read(std::istream& istr);

	};

	//A Perishable is a concrete Item that has an expiry date
	class Perishable
	{

	};
}

#endif // !SDDS_ITEM_H
