/*
Final Project Milestone 4
Module: Perishable
Filename: Perishable.h
Version 1.0
Author: Martha Rocio Rojas Martinez
Student ID: 112073218

Revision History
-----------------------------------------------------------
Date      Reason
2022/04/03  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{
	//A Perishable item, unlike an Item, has an SKU that starts with digits 1 to 3. (10000 to 39999)
	class Perishable : public Item
	{
		Date m_expDate;		//Expiry date to the Item
		char* m_handInstr;	//Dynamically holds a text for the instructions with which the perishable item should be handled

		void setEmpty();

	public:
		Perishable();
		~Perishable();

		Perishable(const Perishable& inObj);
		Perishable& operator=(const Perishable& inObj);
		operator bool()const;

		const Date& expiry();

		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr) const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);

	};
}

#endif // !SDDS_PERISHABLE_H

