#ifndef __StudentList__
#define __StudentList__
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

class StudentList{
public: 
  //methods
   StudentList(std::string filePath);
   Student getValedictorian();
   std::vector<Student> getHonorRollStudents();
   std::vector<Student> getFailingStudents();
private:
   std::vector<Student> students;
};

class NoValedictorian:public std::exception{
public: 
   const char * what() const throw(){
      return "No valedictorian";
   }
};

#endif