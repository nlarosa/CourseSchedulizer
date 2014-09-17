// Nicholas LaRosa
// CSE 20212, Final Project
//
// Interface for Date class
// Holds weekly course time information

#ifndef DATE_H
#define DATE_H

#include <ctype.h>	
#include <iostream>
#include <string>

using namespace std;

class Date
{
	public:
		Date( string, string, string );	// non-default constructor, input csv course string
		bool conflicts( Date & );	// test if two dates overlap (true if not compatible)

		void print();

		int getDays();			// days during the week course meets		
		int getTerm();			// returns the year and semester code -- ex. 201300 (Summer 2013), 201310 (Fall 2013), 201320 (Spring 2014)

		int getBeginDate();		// calendar start and end dates	
		int getBeginMonth();
		int getEndDate();

		int getBeginTime();		// course start and end times
		int getEndTime();

	private:	
		string dateString;

		int dayToPrime( char );		// helper function... Monday: 3, Tuesday: 5, Wednesday: 7, Thursday: 11, Friday: 13

		int weekDays;			// the weekly meeting days are stored as a product of primes
		int parseWeekDays( string );
	
		int beginTime;
		int parseBeginTime( string );	

		int endTime;
		int parseEndTime( string );
	
		int beginDate;
		int beginMonth;			// record the month to see which semester we are in...
		int parseBeginDate( string );

		int endDate;
		int parseEndDate( string );
};

#endif	
