// Nicholas LaRosa
// CSE 20212, Final
//
// Interface for Section class
//
// Section corresponds to a unique instance of a course
// Differentiated by instructor, room number, and time

#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>
#include <vector>
//#include "Course.h"
#include "Date.h"

using namespace std;

//class Course;

class Section
{
	public:
		Section( string, string, string, string, string, string, string, string, string, string );
		bool conflicts( const Section* );	// test if two sections have a time conflict
		//void setCourse( Course* );		// sets the section's course outline to a Course pointer
		void print();

		int getCRN();				
		int getID();				// number after department in Course ID
		int getSection();			// gets section number

		string getCourseID();
		string getProfessor();
		string getClassRoom();		

		int getCredits();
		int getClassSize();		

		bool isOpen();
		bool isXlist();

		int getTerm();				// returns term from Date instance
	
	private:
		string sectionString;

		int sectionNumber;
		int parseSectionNumber( string );		

		int CRN;
		int parseCRN( string );

		int classSize;
		int parseSize( string );
		
		bool open;
		bool parseOpen( string );

		bool Xlist;
		bool parseXlist( string );

		string professor;
		string parseProf( string );		

		string classRoom;
		string parseClass( string );

		Date classDate;				// composition with Date class
};

#endif
