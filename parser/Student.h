#ifndef __Student__
#define __Student__

#include <string>
#include <sstream>

using std::string;

class Student{
public:
   Student(string studentInformation);
   //getters:
   string getFirstName();
   string getLastName();
   string getName();
   int getId();
   double getGPA(); 
private:
   string firstName;
   string lastName;
   int id;
   double gpa;
};

#endif