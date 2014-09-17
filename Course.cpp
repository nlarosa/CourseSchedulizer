// Nicholas LaRosa
// CSE 20212, Final project
//
// Implementation for Course class
// Includes non-default constructor to populate
// HTML parser to gather non-CSV data
// Linker with Section instances

#define HTML_PART1 "https://was.nd.edu/reg/srch/ClassSearchServlet?CRN="
#define HTML_PART2 "&TERM="
#define HTML_PART3 "&P=000000"
#define HTML_OUTPUT ".html"

#include <ctype.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Section.h"
#include "Course.h"
#include "Date.h"

using namespace std;

Course::Course( string IDfield, string titleField, string creditsField ) 
{
	department = parseDepartment( IDfield );
//	cout << "Department: " << department << endl;
	
	courseID = parseCourseID( IDfield );
//	cout << "Course ID: " << courseID << endl;
	
	ID = parseID( IDfield );
//	cout << "ID: " << ID << endl;

	credits = parseCredits( creditsField );
//	cout << "Credits: " << credits << endl;

	courseString = string("Course Number: ") + courseID + '\n' + string("Course Title: ") + titleField + '\n' + string("Total Credits: ") + creditsField + '\n';
//	cout << courseString << endl;
}

string Course::parseDepartment( string deptField )		
{
	string hold;

	for( string::iterator i = deptField.begin(); i != deptField.end(); ++i )
	{
		if( !isdigit(*i) && *i != '-' )	hold += *i;		// we only want alphabetical characters
	}

	return hold;
}

string Course::parseCourseID( string IDfield )
{
	string hold;	

	for( string::iterator i = IDfield.begin(); i != IDfield.end(); ++i )
	{
		if( *i == '-' )		break;				// store string up to section number
		else			hold += *i;
	}

	return hold;
}

int Course::parseID( string IDfield )
{
	int hold = 0;
	int count = 1;

	vector<int> holdVec;

	for( string::iterator i = IDfield.begin(); i != IDfield.end(); ++i )
	{
		if( isdigit(*i) )	holdVec.push_back(*i-'0');	// store all integer characters except section
		else if( *i == '-' )	break;
	}
	
	vector<int>::reverse_iterator r;

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r ) 		// reverse iterator - construct ID
	{
		hold += (count * (*r));
		count *= 10;
	}

	return hold;
}

double Course::parseCredits( string creditsField )			// we are assuming a course can be more than 10 credits (just in case) 
{
	int hold = 0;
	double count = 1;

	bool foundDecimal = false;
	int countDecimal = 0;						// we will count the number of digits after decimal point (if any)

	vector<int> holdVec;

	for( string::iterator i = creditsField.begin(); i != creditsField.end(); ++i )
	{
		if( isdigit(*i) )	holdVec.push_back(*i-'0');
		else if( *i == '.' )	holdVec.push_back(-1);		// we will represent decimal point by -1
	}
	
	vector<int>::iterator i;
	
	for( i = holdVec.begin(); i != holdVec.end(); ++i )
	{
		if( *i == -1 )			foundDecimal = true;
		else if( foundDecimal )		countDecimal++;		// count number of digits after the decimal point
	}	

	if( foundDecimal )	count = pow(10,-1*countDecimal);	// change multiplier if we have a decimal, otherwise will remain 1

	vector<int>::reverse_iterator r;	

	for( r = holdVec.rbegin(); r != holdVec.rend(); ++r ) 		// reverse iterator - construct credits
	{
		hold += (count * (*r));
		count *= 10;
	}

	return hold;
}

void Course::addSection( string IDfield, string openField, string sizeField, string Xfield, string CRNfield, string profField, string timeField, string startField, string endTime, string roomField )
{	
	sections.push_back( Section( IDfield, openField, sizeField, Xfield, CRNfield, profField, timeField, startField, endTime, roomField ) );					// add section to a vector of Section objects
}

void Course::print()						// prints out the obtained information
{
	cout << courseString << endl;
} 	

string Course::getCourseID()
{
	return courseID;
}

string Course::getDepartment()
{
	return department;
}

int Course::getID()
{
	return ID;
}

double Course::getCredits()
{
	return credits;

}

void Course::parseHTML( int currentTerm )			// generate HTML address and parse important information
{
	int ourCRN;
	string HTMLaddress;
	string shellStr;

	string strCRN;						// will need CRN and Term in string form to construct HTML
	string strTerm;

	stringstream intToString;				// stringstream used to convert from integer to string

	for( int i = 0; i < sections.size(); i++ )
	{
		if( sections[i].getTerm() == currentTerm )	// there exists a section during this term
		{
			ourCRN = sections[i].getCRN();
			
			intToString.str("");
			intToString << ourCRN;
			strCRN = intToString.str();
	
			intToString.str("");
			intToString << currentTerm;
			strTerm = intToString.str();	
			
			HTMLaddress = HTML_PART1 + strCRN + HTML_PART2 + strTerm + HTML_PART3;
		
			shellStr = string("curl '") + HTMLaddress + "' > " + HTML_OUTPUT;

			system(shellStr.c_str());		// generates HTML course using curl command, writes to file named .html

			// BEGIN PARSING - prereqs
			
			/*	
			ifstream htmlFile;
			htmlFile.open(HTML_OUTPUT);		// open file just written to: .html
			string currentLine;	

			bool insideScript = false;
			bool insideCoReq = false;
			bool insidePreReq = false;
			bool insideAttrib = false;	

			bool dashFound = false;		// work with attributes
			bool oFound = false;		// work with coreqs and prereqs (find "or")

			while( !htmlFile.eof() )
			{
				getline( htmlFile, currentLine );	// store current line in currentLine string
				
				if( !currentLine.empty() )
				{
					if( !insideScript && !insideCoReq && !insidePreReq && !insideAttrib )
					{					
						if( currentLine.find("<script") != string::npos )		// checking for matches to keywords
						{	
							insideScript = true; 
							continue; 		
						}
						else if( currentLine.find("</script>") != string::npos )	
						{
							insideScript = false;
							continue;
						}
						else if( currentLine.find("Attributes") != string::npos )	
						{
							insideAttrib = true;
							continue;
						}
						else if( currentLine.find("Prerequisites") != string::npos )	
						{
							insidePreReq = true;
							continue;
						}
						else if( currentLine.find("Corequisites") != string::npos )	
						{
							insideCoReq = true;
							continue;
						}
						
					}
					else				// Now we will check which section we are in	
					{	
						if( insideScript )	continue;		// skip lines inside script
						else if( insideAttrib )	
						{
							else if( currentLine.find("<BR>") != string::npos )
							{
								insideAttrib = false;
								continue;
							}

							string hold = string("");		// hold the current attribute	

							for( string::iterator i = currentLine.begin(); i != currentLine.end(); ++i )
							{
								if( *i == '-' )
								{
									attributes.push_back(hold); 	
									dashFound = true;
								}								
								else if( *i = ',' )	
								{
									hold = string("");		// reset string at each comma	
									dashFound = false;		// reset dashFound
								}
								else if( dashFound )			continue;
								else if( isdigit(*i) || isalpha(*i) )	hold += *i;	// capture chars after comma, before dash
							}
						}
						else if( insideCoReq )
						{
							else if( currentLine.find("<BR>") != string::npos )
							{
								insideCoReq = false;
								continue;
							}
							
							string hold = string("");
		
							for( string::iterator i = currentLine.begin(); i != currentLine.end(); ++i )
							{
								if( *i == 'o' )
								{
									corequisites.push_back(hold); 	
									oFound = true;
								}								
								else if( *i = 'r' )	
								{
									hold = string("");		// reset string at each comma	
									dashFound = false;		// reset dashFound
								}
								else if( dashFound )			continue;
								else if( isdigit(*i) || isalpha(*i) )	hold += *i;	// capture chars after comma, before dash
							}
						}
					}
				}
				*/
		}				
	}
}
				
