/*
Final Project Milestone 1
Module: Date
Filename: Date.h
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
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Status.h"

namespace sdds
{
	const int MAX_YEAR_VAL = 2030;

	//A class that encapsulates year, month and day values for date stamping, validation, comparison and date IO purposes.
	class Date
	{
		int m_year; //An integer between the current year and the maximum year value
		int m_month; //An integer between 1 and 12
		int m_day; //An integer between 1 and the number of days in the month based on the year
		Status m_state; //A Status object that holds the validity status of date
		bool m_format; //A boolean value that is set to true to print the date as YYYY/MM/DD or false to print it as YYMMDD

		bool validate();
		int uniqueDateValue() const;

	public:
		Date();
		Date(int year, int month, int day);
		Date(const Date& inObj);
		Date& operator=(const Date& inObj);

		int getUniqueDate() const;
		const Status& state();
		Date& formatted(bool addFormat);
		operator bool() const;

		std::ostream& write(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
	};

	bool operator==(const Date& left, const Date& right);
	bool operator!=(const Date& left, const Date& right);
	bool operator<(const Date& left, const Date& right);
	bool operator>(const Date& left, const Date& right);
	bool operator<=(const Date& left, const Date& right);
	bool operator>=(const Date& left, const Date& right);

	std::ostream& operator<<(std::ostream& ostr, const Date& inObj);
	std::istream& operator>>(std::istream& istr, Date& inObj);
}

#endif // !SDDS_DATE_H
