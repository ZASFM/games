#include <iostream>
#include "Student.h"

using std::cout, std::endl;

int main(int argc, const char * argv[]){
   Student student("Shafi Bahrami 12345 90.0");
   cout<<student.getName()<<endl;
   cout<<student.getId()<<endl;
   cout<<student.getGPA()<<endl;
   return 0;
}