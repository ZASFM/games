#include <iostream>
#include "Student.h"
#include "StudentList.h"

using std::cout, std::endl;

void printStudentInfo(Student s){
   cout<<"Name:"<<s.getName()<<endl;
   cout<<"Id:"<<s.getId()<<endl;
   cout<<"Gpa"<<s.getGPA()<<endl;
}

int main(int argc, const char * argv[]){
   //Student student("Shafi Bahrami 12345 90.0");
   /* test
      StudentList list("./file.txt");
      for(int i=0;i<list.students.size();i++){
         Student s =list.students.at(i);
         printStudentInfo(s);
      }
   */
   return 0;
}