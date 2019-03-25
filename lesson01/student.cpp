
#include <iostream>
#include "student.h"

using namespace std;


// Define static class members
const double Physicist::pi = 3.141593;
int StudentFopf::faculty = 2;

// Define Student methodsa
Student::Student(int age_)
{
	age = age_;
}

void Student::Print()
{
	cout << "I'm Student" << endl;
}

// Define StudentFopf methods
StudentFopf::StudentFopf(): // Initialization list:
	Student(18),            // construct base classes or class members
	obshaga(6)
{
}

StudentFopf::StudentFopf(int _obshaga):
	Student(18),
	obshaga(_obshaga)
{
}

StudentFopf::~StudentFopf()
{
	// free all resources
}

void StudentFopf::PrintFopf() const
{
	cout << "I'm FOPF" << faculty << endl;
	faculty = 1;
}

// static method
void StudentFopf::Hello()
{
	cout << "Hello Physics!" << faculty << endl;
}


int main()
{
	Student st1(20);    // Construct object with single argument
	st1.Print();
	
	StudentFopf stf;    // Construct object using constructor without variables
	stf.PrintFopf();
    // stf.Print();  // Not allowed, Student is a private base class
	stf.PrintPi();  // OK, public inheritance

    // Here we trying to use static methods and members.
    // They are not connected with real objects
	StudentFopf::Hello();
	StudentFopf::faculty = 10;
	StudentFopf::Hello();
    // Physicist::pi = 3.0; // Not allowed, private and const

	return 0;
}
