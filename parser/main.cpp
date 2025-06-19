#include <iostream>
#include <exception>
#include "Student.h"
#include "StudentList.h"

using std::cout, std::endl, std::exception, std::string;

void printStudentInfo(Student s){
   cout<<"Name:"<<s.getName()<<endl;
   cout<<"Id:"<<s.getId()<<endl;
   cout<<"Gpa"<<s.getGPA()<<endl;
}

int main(int argc, const char * argv[]){

   try{

      if(argc!=2){
         cout<<"Usage: student info PATH_TO_STUDENT_FILE"<<endl;
         return -1;
      }

      string path(argv[1]);
      StudentList list(path);

      cout<<"Valedictorian"<<endl;
      //if getValedictorian has no students, it throws already an exception which gets caught later
      printStudentInfo(list.getValedictorian());

      cout<<"Honor students"<<endl;
      for(int i=0;i<list.getHonorRollStudents().size();i++){
         printStudentInfo(list.getHonorRollStudents()[i]);
      }

      cout<<"Failing students"<<endl;
      for(int i=0;i<list.getFailingStudents().size();i++){
         printStudentInfo(list.getFailingStudents()[i]);
      }

   }catch(exception &e){
      cout<<"**************"<<endl;
      cout<<e.what()<<endl;
      cout<<"**************"<<endl;
   }
   return 0;
}