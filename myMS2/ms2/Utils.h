/*
Final Project Milestone 1
Module: Utils
Filename: Utils.h
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

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
   // Testing date values for application testing and debugging
   // these values must not change at submission time.
   const int sdds_testYear = 2022;
   const int sdds_testMon = 03;
   const int sdds_testDay = 31;
   
   class Utils {
      bool m_testMode = false;
   public:
      
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);

      void alocpy(char*& destination, const char* source);
      int getInt(const char* prompt);
      int getInt(int min, int max, const char* prompt, const char* errMes);
   };

   extern Utils ut; // Provides global access to the ut instance in the Utils.cpp file
}

#endif // !SDDS_UTILS_H
