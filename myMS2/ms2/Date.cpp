/*
Final Project Milestone 1
Module: Date
Filename: Date.cpp
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
#include <ctime>
#include <iomanip>
#include "Date.h"
//#include "Status.h"
#include "Utils.h"

using namespace std;
namespace sdds
{
	//This function validates the year, month and day
	bool Date::validate()
	{
		int currYear = 0, currMonth = 0, currDay = 0;
		ut.getSystemDate(&currYear, &currMonth, &currDay);
		bool valid = true;

		if (valid && (m_year < currYear || m_year > MAX_YEAR_VAL)) {
			m_state = "Invalid year in date";
			m_state = 1;
			valid = false;
		}
		else if (valid && (m_month < 1 || m_month > 12)) {
			m_state = "Invalid month in date";
			m_state = 2;
			valid = false;
		}
		else if (valid && (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year))) {
			m_state = "Invalid day in date";
			m_state = 3;
			valid = false;
		}
		else {
			m_state.clear();
		}
		return valid;
	}

	//Method to return a unique integer value tied to the date.
	int Date::uniqueDateValue() const
	{
		int date = m_year * 372 + m_month * 31 + m_day;
		return date;
	}

	//Constructor. No arguments
	Date::Date()
	{
		m_format = true;
		ut.getSystemDate(&m_year, &m_month, &m_day);
		
	}

	//Constructor. 3 Arguments
	Date::Date(int year, int month, int day)
	{
		m_format = true;
		m_year = year;
		m_month = month;
		m_day = day;
		validate();
	}

	//Public method to access uniqueDateValue() private function
	int Date::getUniqueDate() const
	{
		int date = uniqueDateValue();
		return date;
	}

	//Helper Functions. Overloaded == operator
	bool operator==(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() == right.getUniqueDate());
	}

	//Helper Functions. Overloaded != operator
	bool operator!=(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() != right.getUniqueDate());
	}

	//Helper Functions. Overloaded < operator
	bool operator<(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() < right.getUniqueDate());
	}

	//Helper Functions. Overloaded > operator
	bool operator>(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() > right.getUniqueDate());
	}

	//Helper Functions. Overloaded <= operator
	bool operator<=(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() <= right.getUniqueDate());
	}

	//Helper Functions. Overloaded >= operator
	bool operator>=(const Date& left, const Date& right)
	{
		return (left.getUniqueDate() >= right.getUniqueDate());
	}

	//Accessor method. Returns a constant reference to the State of the Date
	const Status& Date::state()
	{
		return m_state;
	}

	//Set the formatted flag (attribute) of the Date.
	Date& Date::formatted(bool addFormat)
	{
		m_format = addFormat;
		return *this;
	}

	//Bool Conversion Overload. If the Date object is casted to a boolean, the state of the date object is returned.
	Date::operator bool() const
	{
		return m_state;
	}

	std::ostream& Date::write(std::ostream& ostr) const
	{
		if (m_format) {
			ostr << m_year << "/" << setw(2) << setfill('0') << m_month << "/" << m_day;
		}
		else {
			double twoDigitYr = m_year % 100;
			ostr << twoDigitYr << setw(2) << setfill('0') << m_month << m_day;
		}
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Date& inObj)
	{
		inObj.write(ostr);
		return ostr;
	}

	std::istream& Date::read(std::istream& istr)
	{
		delete[] m_state;
		
		int input;
		istr >> input;

		if (input > 0001 && input < 9999) {
			ut.getSystemDate(&m_year, nullptr, nullptr);
			m_month = input / 100;
			m_day = input % 100;
			if (!validate()) {
				istr.setstate(ios::failbit);
			}
			
		}
		else if (input > 100000 && input < 999999) {
			m_year = input / 10000;
			m_month = (input % 10000) / 100;
			m_day = (input % 10000) % 100;
			m_year += 2000;
			if (!validate()) {
				istr.setstate(ios::failbit);
			}
		}
		else {
			istr.setstate(ios::failbit);
			m_state = "Invalid date value";
		}

		return istr;
	}

	std::istream& operator>>(std::istream& istr, Date& inObj)
	{
		inObj.read(istr);
		return istr;
	}

}