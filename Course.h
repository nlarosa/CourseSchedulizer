// Nicholas LaRosa
// CSE 20212, Final Project
//
// Interface for Course class
// Contains all necessary course information

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Section.h"

using namespace std;

//class Section;

class Course
{
	public:
		Course( string, string, string );	// non-default constructor, input csv course string
		void parseHTML( int );			// parses HTML file for prerequisites and corequisites
		void addSection( string, string, string, string, string, string, string, string, string, string );	// adds a Section object to the course's vector
		void print();

		string getCourseID();
		string getDepartment();		

		int getID();				// number after department in Course ID
		double getCredits();
		
	private:
		string courseString;		

		string department;
		string parseDepartment( string );

		string courseID;			// department + ID number
		string parseCourseID( string );		

		int ID;
		int parseID( string );

		double credits;
		double parseCredits( string );

		vector<Section> sections;		// each class has a number of sections	
		vector<string> prereqs;			// corequisites and prerequisites are consistent among sections
		vector<string> coreqs;
		vector<string> attributes;
};

#endif
