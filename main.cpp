// Nicholas LaRosa
// CSE 20212, Final Project
//
// Main driver program for testing purposes

#include <iostream>
#include <string>
#include "Section.h"
#include "Course.h"
#include "Date.h"

using namespace std;

int main()
{
	Course parent("ACCT20100-01", "Accountancy I", "3");
	parent.addSection("ACCT20100-01", "CL", "31", "", "22485", "Burks, Jeffrey", "T R - 11:00A - 12:15P", "1/15/2013", "5/1/2013", "DeBartolo Hall 320");	

	parent.parseHTML( 201220 );
	
	return 0;
}	

