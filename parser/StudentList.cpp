#include "StudentList.h"
#include <fstream>
#include <algorithm>

using std::ifstream, std::string, std::sort;

StudentList::StudentList(string filePath){
   ifstream studentFile(filePath);
   string lineContents;
   //read while its not eof
   while(!studentFile.eof()){
      getline(studentFile,lineContents);
      //create student based on each input from file
      Student s(lineContents);
      //adding students to the vector
      students.push_back(s);
   }
   studentFile.close();

   //after having the students, sort them based on gpa with the lambda function:
   sort(students.begin(),students.end(), [](Student &s1, Student &s2){
                                                                        return s1.getGPA()>s2.getGPA();
                                                                     });
}

Student StudentList::getValedictorian(){
   if(students.size()==0 || students.at(0).getGPA()<65) throw NoValedictorian();
   //since the constructor sorts the elements, i can get the highest one at index 0
   return students.at(0);
}