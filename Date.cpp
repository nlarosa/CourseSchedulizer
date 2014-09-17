// Nicholas LaRosa
// CSE 20212, Final Project
//
// Implementation for Date class

#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Date.h"

using namespace std;

Date::Date( string weekField, string beginField, string endField )		// non-default constructor for Date class
{
	weekDays = parseWeekDays( weekField );					// initialize data members
//	cout << "Week days: " << weekDays << endl;
	
	beginTime = parseBeginTime( weekField );
//	cout << "Beginning time: " << beginTime << endl;
				
	endTime = parseEndTime( weekField );
//	cout << "Ending time: " << endTime << endl;

	beginDate = parseBeginDate( beginField );
//	cout << "Beginning date: " << beginDate << endl;

	endDate = parseEndDate( endField );
//	cout << "Ending date: " << endDate << endl;
	
	dateString = string("Weekly Meeting Times: ") + weekField + '\n' + string("Beginning Date: ") + beginField + '\n' + string("Ending Date: ") + endField + '\n';
//	cout << dateString << endl;
}

int Date::parseWeekDays( string weekField )
{
	int hold = 1;

	for( string::iterator i = weekField.begin(); i != weekField.end(); ++i )
	{
		if( *i == '-' )			break;				// exit at first dash
		else if( isalpha(*i) )		hold *= dayToPrime(*i);		// record days by multipling product of primes
	}	

	return hold;	
}

int Date::parseBeginTime( string weekField )					// begin time occurs after dash in week field
{
	int dashCount = 0;
	int count = 1;
	int hold = 0;
	bool PM = false;

	vector<int> holdVec;

	for( string::iterator i = weekField.begin(); i != weekField.end(); ++i )
	{
		if( *i == '-' )			dashCount++;			// keep track of number of dashes passed
		else if( dashCount == 1 )					// retrieve the beginning time
		{
			if( isdigit(*i) ) 	holdVec.push_back(*i-'0');
			else if( *i == 'P' ) 	PM = true;			// we need to know PM or AM
		}
	}
	
	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )			// reverse iterator - beginTime
	{
		hold += (count * (*r));
		count *= 10;							// increase factor by ten at each pass to construct integer
	}
	
	if( PM && hold < 1200 )			hold += 1200;			// military time
	else if( !PM )				hold %= 1200;
	
	return hold;
}

int Date::parseEndTime( string weekField )					// end time occurs after second dash in week field
{
	int dashCount = 0;
	int count = 1;
	int hold = 0;
	bool PM = false;

	vector<int> holdVec;

	for( string::iterator i = weekField.begin(); i != weekField.end(); ++i )
	{
		if( *i == '-' )			dashCount++;			// keep track of number of dashes passed
		else if( dashCount == 2 )					// retrieve the end time
		{
			if( isdigit(*i) ) 	holdVec.push_back(*i-'0');
			else if( *i == 'P' ) 	PM = true;			// we need to know PM or AM
		}
	}
	
	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )			// reverse iterator - endTime
	{
		hold += (count * (*r));
		count *= 10;							// increase factor by ten at each pass to construct integer
	}
	
	if( PM && hold < 1200 )			hold += 1200;			// military time
	else if( !PM )				hold %= 1200;
	
	return hold;
}

int Date::parseBeginDate( string beginField )
{
	int hold = 0;
	int count = 1;

	beginMonth = 0;
	bool foundSlash = false;	// month is before first slash	

	vector<int> holdVec;
	vector<int> monthVec;		// we will parse solely the month

	for( string::iterator i = beginField.begin(); i != beginField.end(); ++i )
	{
		if( isdigit(*i) ) 	
		{
			holdVec.push_back(*i-'0');		// add all digits to vector

			if( !foundSlash )	monthVec.push_back(*i-'0');	// add digits before slash to month vector
		}
		else if( *i == '/' )	foundSlash = true;
	}
	
	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )			// reverse iterator - beginDate
	{
		hold += (count * (*r));
		count *= 10;							// increase factor by ten at each pass to construct integer
	}
	count = 1;

	for( r = monthVec.rbegin(); r != monthVec.rend(); ++r )			// reverse iterator - beginMonth
	{
		beginMonth += (count * (*r));
		count *= 10;							// increase factor by ten at each pass to construct integer
	}

	return hold;
}

int Date::parseEndDate( string endField )
{
	int hold = 0;
	int count = 1;
	
	vector<int> holdVec;

	for( string::iterator i = endField.begin(); i != endField.end(); ++i )
	{
		if( isdigit(*i) ) 	holdVec.push_back(*i-'0');		// add all digits to vector
	}
	
	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )			// reverse iterator - endDate
	{
		hold += (count * (*r));
		count *= 10;							// increase factor by ten at each pass to construct integer
	}

	return hold;
}

int Date::dayToPrime( char dayInput )		// inputs day character, return corresponding prime
{
	switch( dayInput )
	{
		case 'M':			// Monday
			return 3;
			break;
		case 'T':			// Tuesday
			return 5;
			break;
		case 'W':			// Wednesday
			return 7;
			break;
		case 'R':			// Thursday
			return 11;
			break;
		case 'F':			// Friday
			return 13;
			break;
		default:
			return 1;
			break;
	}
}

void Date::print()					// prints the formatted string of date information
{
	cout << dateString << endl;

//	cout << beginTime << endl;
//	cout << endTime << endl;
}

bool Date::conflicts( Date &comparedDate )		// tests if two classes overlap (true if not compatible with same schedule)
{
	if( this->getTerm() == comparedDate.getTerm() )
	{
		if( beginTime == 0 || comparedDate.beginTime == 0 )			return false;		// if either times are TBA, do not conflict

		else if( ( beginTime <= comparedDate.beginTime && endTime >= comparedDate.beginTime ) 
			|| ( beginTime <= comparedDate.endTime && endTime >= comparedDate.endTime ) )		// if the times overlap in any way...
		{												// return true if the days of the week are the same
			if( weekDays % 3 == 0 && comparedDate.weekDays % 3 == 0 )	return true;		// both occur on Monday
			else if( weekDays % 5 == 0 && comparedDate.weekDays % 5 == 0 )	return true; 		// both occur on Tuesday
			else if( weekDays % 7 == 0 && comparedDate.weekDays % 7 == 0 )	return true;		// both occur on Wednesday
			else if( weekDays % 11 == 0 && comparedDate.weekDays % 11 == 0 )return true;		// both occur on Thursday
			else if( weekDays % 13 == 0 && comparedDate.weekDays % 13 == 0 )return true;		// both occur on Friday
		}
	}

	return false;	
}

int Date::getBeginMonth()
{
	return beginMonth;
}

int Date::getDays()
{
	return weekDays;
}

int Date::getBeginTime()
{
	return beginTime;
}

int Date::getEndTime()
{
	return endTime;
}

int Date::getBeginDate()
{
	return beginDate;
}

int Date::getEndDate()
{
	return endDate;
}

int Date::getTerm()				// will return the term (of beginDate, because both dates should be the same)
{
	int hold = 0;

	hold += (beginDate % 10000) * 100;	// add year * 100 to get 201300, for example

	if( beginMonth >= 1 && beginMonth <= 4 )	// beginning date between January and April = Spring
	{
		hold -= 100;			// Spring term written as (year before)20
		hold += 20;			// last two digits of Spring are 20
	}
	else if( beginMonth >= 8 && beginMonth <= 12 )	// beginning date between August and December = Fall
	{
		hold += 10;			// last two digits of Fall are 10
	}

	return hold;				// else, it is the Summer semester, which has last two digits 00
}

/*
int main()
{
	Date testDate1("LAW75800-01*,Appalachia Externship,1,OP,6,2,,24718,\"Jones, Robert Toms Smedley, CynthiaHamilton, Anne\",TBA,1/14/2013,4/30/2013,TBA");

	testDate1.print();

	Date testDate2("ACCT20100-01,Accountancy I,3,CL,31,0,Y,22485,\"Burks, Jeffrey\",T R - 11:00A - 12:15P,1/15/2013,5/1/2013,DeBartolo Hall 320");

	testDate2.print();
}
*/	
