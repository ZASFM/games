#include "StudentList.h"
#include <fstream>
#include <algorithm>

#define FAILING_GRADE 65
#define HONOR_GRADE 90

using std::ifstream, std::string, std::sort, std::vector;

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
   if(students.size()==0 || students.at(0).getGPA()<FAILING_GRADE ) throw NoValedictorian();
   //since the constructor sorts the elements, i can get the highest one at index 0
   return students.at(0);
}

vector<Student> StudentList::getHonorRollStudents(){
   vector<Student> toReturn;

   //filtering the students with gpa>90
   for(int i=0;i<this->students.size();i++){
      if(students[i].getGPA()>=HONOR_GRADE){
         toReturn.push_back(students[i]);
      }
   }

   return toReturn;
}

vector<Student> StudentList::getFailingStudents(){
   vector<Student> toReturn;

   //iterating through student list via an iterator
   for(vector<Student>::reverse_iterator iter=students.rbegin();iter<students.rend();iter++){
      if(iter->getGPA()>=FAILING_GRADE){
         break;
      }else{
         toReturn.push_back(*iter);
      }
   }

   return toReturn;
}