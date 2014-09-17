// Nicholas LaRosa
// CSE 20212, Final Project
//
// Implementation of Section class
//
// Section will be constructed at each line of the CSV file
// If it's corresponding Course does not exist, the Course
// constructor will also be called
// In all cases, the Section is paired with a Course via reference

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "Section.h"
#include "Course.h"
//#include "Date.h"

using namespace std;

Section::Section( string IDfield, string openField, string sizeField, string Xfield, string CRNfield, string profField, string timeField, string startField, string endTime, string roomField ) : classDate( timeField, startField, endTime )
{
	sectionNumber = parseSectionNumber( IDfield );			// set all data members and member initialize Date instance
//	cout << "Section: " << sectionNumber << endl;	

	open = parseOpen( openField );
//	cout << "Open? " << open << endl;

	classSize = parseSize( sizeField );
//	cout << "Class Size: " << classSize << endl;
	
	Xlist = parseXlist( Xfield );
//	cout << "Xlist? " << Xlist << endl;

	CRN = parseCRN( CRNfield );
//	cout << "CRN: " << CRN << endl;

	professor = parseProf( profField );
//	cout << "Professor: " << professor << endl;

	classRoom = parseClass( roomField );	
//	cout << "Class room: " << classRoom << endl;

	stringstream conversion;					// this stringstream will be used to convert the section integer to string
	conversion << sectionNumber;
	
	sectionString = string("Section Number: ") + conversion.str() + '\n' + string("CRN: ") + CRNfield + '\n' + string("Professor: ") + profField + '\n' + string("Location: ") + roomField + '\n';

//	cout << sectionString << endl;
}

int Section::parseSectionNumber( string IDfield )
{
	bool dashFound = false;
	int hold = 0;
	int count = 1;

	vector<int> holdList;						

	for( string::iterator i = IDfield.begin(); i != IDfield.end(); ++i )	
	{
		if( *i == '-' )				dashFound = true;		
		else if( dashFound && isdigit(*i) )	holdList.push_back(*i-'0');
	}

	vector<int>::reverse_iterator r;

	for( r = holdList.rbegin(); r != holdList.rend(); ++r )		// reverse iterator - construct section
        {
		hold += (count * (*r));
		count *= 10;	
	}

	return hold;
}

int Section::parseCRN( string CRNfield )
{
	int hold = 0;
	int count = 1;
	
	vector<int> holdVec;

	for( string::iterator i = CRNfield.begin(); i != CRNfield.end(); ++i )	
	{
		if( isdigit(*i) )	holdVec.push_back(*i-'0');	// store all integer characters in CRNfield
	}

	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )		// reverse iterator - construct CRN
        {
		hold += (count * (*r));
		count *= 10;	
	}

	return hold;
}

int Section::parseSize( string sizeField )
{
	int hold = 0;
	int count = 1;
	
	vector<int> holdVec;

	for( string::iterator i = sizeField.begin(); i != sizeField.end(); ++i )	
	{
		if( isdigit(*i) )	holdVec.push_back(*i-'0');	// store all integer characters in sizeField
	}

	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r )		// reverse iterator - construct size
        {
		hold += (count * (*r));
		count *= 10;	
	}

	return hold;
}

bool Section::parseOpen( string openField )
{
	if( openField.length() > 0 )	
	{
		if( openField[0] == 'O' )	return true;		// 'O' indicates spots are open in the class
		else				return false;
	}
	else					return false;
}

bool Section::parseXlist( string Xfield )
{
	if( Xfield.length() > 0 )
	{
		if( Xfield[0] == 'Y' )		return true;		// 'Y' indicates the section is on Xlist
		else				return false;
	}	
	else					return false;
}

string Section::parseProf( string profField )
{
	return profField;						// no manipulation necessary
}

string Section::parseClass( string roomField )
{
	return roomField;						// no manipulation necessary
}

int Section::getTerm()
{
	return classDate.getTerm();
} 

int Section::getCRN()
{	
	return CRN;
}

void Section::print()
{
	cout << sectionString << endl;

	classDate.print();						// print Date class instance as well 
} 
