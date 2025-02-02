#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 10;

struct Course {
    string coursename;
    float grade;
    int credits;
};

struct Student {
    string name;
    int userid;
    string major;
    Course courses[MAX_COURSES];
    int courseCount;
};