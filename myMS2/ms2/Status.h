/*
Final Project Milestone 1
Module: Status
Filename: Status.h
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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

namespace sdds
{
	//A class to keep track of the state of an object by holding the description of the state and an optional status code.
	class Status
	{
		char* m_desc;
		int m_code;

	public:
		Status();
		explicit Status(char* desc);
		Status(const Status& inObj);
		~Status();
		void destruct();

		//Status& operator=(const Status& inObj);
		Status& operator=(std::string desc);
		Status& operator=(int code);

		operator int() const;
		operator const char*() const;
 		operator bool() const;

		Status& clear();

		std::ostream& print(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream&, const Status& inObj);
}
#endif // !SDDS_STATUS_H
