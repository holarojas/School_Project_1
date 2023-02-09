/*
Final Project Milestone 1
Module: Status
Filename: Status.cpp
Version 1.0
Author: Martha Rocio Rojas Martinez
Student ID: 112073218

Revision History
-----------------------------------------------------------
Date      Reason
2022/03/15  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include "Status.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	//Constructor
	Status::Status()
	{
		m_desc = nullptr;
		m_code = 0;
	}

	//Constructor with description argument
	Status::Status(char* desc)
	{
		ut.alocpy(m_desc, desc);
		m_code = 0;
	}

	//Copy Constructor
	Status::Status(const Status& inObj)
	{
		ut.alocpy(m_desc, inObj.m_desc);
		m_code = inObj.m_code;
	}

	//Destructor to reutilize
	void Status::destruct()
	{
		delete[] m_desc;
		m_desc = nullptr;
	}

	//Destructor
	Status::~Status()
	{
		destruct();
	}

	//Assignment overload when Object assigned to a character array
	Status& Status::operator=(std::string desc)
	{
		ut.alocpy(m_desc, desc.c_str());
		return *this;
	}

	//Assignment overload when Object assigned to an int
	Status& Status::operator=(int code)
	{
		m_code = code;
		return *this;
	}

	//Type Conversion Operator. Casting a Status object to an integer
	Status::operator int() const
	{
		return m_code;
	}

	//Type Conversion Operator. Casting a Status object to a constant character pointer
	Status::operator const char* () const
	{
		return m_desc;
	}

	//Type Conversion Operator. Casting a Status object to a boolean.
	Status::operator bool() const
	{
		//Should return true if the description is null and false if it is not.
		return (m_desc == nullptr);
	}

	//Method that safely deallocates the description and sets the code to zero
	Status& Status::clear()
	{
		if (m_desc != nullptr) {
			delete[] m_desc;
			m_desc = nullptr;
		}
		m_code = 0;
		return *this;
	}

	//It should print the Status conly if it is in an invalid state.
	std::ostream& Status::print(std::ostream& ostr) const
	{
		if (this)
		{
			if (m_code != 0) {
				ostr << "ERR#" << m_code << ": " << m_desc;
			}
			else {
				ostr << m_desc;
			}
		}
		return ostr;
	}

	//Helper insertion operator overload
	std::ostream& operator<<(std::ostream& ostr, const Status& inObj)
	{
		inObj.print(ostr);
		return ostr;
	}
}