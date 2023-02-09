/*
Final Project Milestone 1
Module: Utils
Filename: Utils.cpp
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
#include <iomanip>
#include <ctime>
#include <string>
#include <string.h>
#include <ctype.h>
#include "Utils.h"

using namespace std;
namespace sdds {
   // The ut object of type Utils that is accessible to any file including "Utils.h" to call the Utils
   // methods
   Utils ut;

   // Puts the system date in test mode, where getSystemDate() function will return 2022, 03, 31
   // or whatever the three constant test dates are set to
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   // This function will be used to get the current system date or the test date if m_testMode is true
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }

   // This function will return the number of days in a month based on the year
   // 1<=mon<=12  year: four digit number (example: 2021)
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   //Safely allocates memory in destination and copies the source into it
   void Utils::alocpy(char*& destination, const char* source)
   {
       if (source != nullptr) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
       else {
           destination = nullptr;
       }
       
   }
   
   //Performs a foolproof entry of an integer
   int Utils::getInt(const char* prompt = nullptr, const char* errMes = nullptr)
   {
       bool isChar = false;
       bool exit = false;
       string inputStr = { 0 };
       int result = 0;
       if (prompt != nullptr) {
           cout << prompt;
           do {      
               isChar = false; //Reset isChar flag to false
               cin >> inputStr;
               for (unsigned int i = 0; i < strlen(inputStr.c_str()); i++) { //Validate if the user input letters
                   if (!isdigit(inputStr[i])) {
                       isChar = true;
                       i = strlen(inputStr.c_str());
                   }
               }
               if (!isChar) { //If the user input a number
                   if (stoi(inputStr) > 0) {
                       result = stoi(inputStr);
                       exit = true;
                   }
               }
               else { 
                   //cout << "Invalid Integer, retry: ";
                   cout << errMes << ", retry: ";
                   cin.clear();
                   cin.ignore(1000, '\n');
               }
           } while (!exit);
       }
       return result;
   }

   //Performs a foolproof entry of an integer within a range.
   int Utils::getInt(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr)
   {
       bool exit = false;
       int input = 0;
       if (prompt != nullptr) {
           do {
               input = getInt(prompt, errMes);
               if (input < min || input > max) {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]:";
                    prompt = " ";  
               }
               else {
                   exit = true;
               }
           } while (!exit);
       }
       return input;
   }


   //Performs a foolproof entry of a Double
   double Utils::getDouble(const char* prompt = nullptr, const char* errMes = nullptr)
   {
       bool isChar = false;
       bool exit = false;
       string inputStr = { 0 };
       double result = 0;
       if (prompt != nullptr) {
           cout << prompt;
           do {
               isChar = false; //Reset isChar flag to false
               cin >> inputStr;
               for (unsigned int i = 0; i < strlen(inputStr.c_str()); i++) { //Validate if the user input letters
                   if (!isdigit(inputStr[i])) {
                       if (int(inputStr[i]) == 46){
                           //Consider it a number
                       }
                       else {
                           isChar = true;
                           i = strlen(inputStr.c_str());
                       }
                   }
               }
               if (!isChar) { //If the user input a number
                   if (stod(inputStr) > 0) {
                       result = stod(inputStr);
                       exit = true;
                   }
               }
               else {
                   cout << errMes << ", retry: ";
                   cin.clear();
                   cin.ignore(1000, '\n');
               }
           } while (!exit);
       }
       return result;
   }

   //Performs a foolproof entry of a double within a range.
   double Utils::getDouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr)
   {
       bool exit = false;
       double input = 0;
       if (prompt != nullptr) {
           do {
               input = getDouble(prompt, errMes);
               if (input < min || input > max) {
                   cout << fixed << setprecision(2) << "Value out of range [" << min << "<=val<=" << max << "]:";
                   prompt = " ";
               }
               else {
                   exit = true;
               }
           } while (!exit);
       }
       return input;
   }
   
}