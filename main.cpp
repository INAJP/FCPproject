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

Student students[MAX_STUDENTS];
int studentCount = 0;

// ورودی اطلاعات دانشجو
void readStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "حداکثر تعداد دانشجویان تکمیل شده است.\n";
        return;
    }
    Student temp;
    cout << "نام کامل دانشجو را وارد کنید: ";
    cin.ignore();
    getline(cin, temp.name);
    cout << "شناسه دانشجو را وارد کنید: ";
    cin >> temp.userid;
    cout << "رشته دانشجو را وارد کنید: ";
    cin.ignore();
    getline(cin, temp.major);
    temp.courseCount = 0;
    students[studentCount++] = temp;
}

// ثبت دروس
void readCourse() {
    for (int i = 0; i < studentCount; i++) {
        int nc;
        cout << "تعداد دروس دانشجو را وارد کنید " << students[i].name << ": ";
        cin >> nc;
        if (nc > MAX_COURSES) {
            cout << "حداکثر تعداد دروس مجاز است" << MAX_COURSES << " دروس اضافه خواهند شد.\n";
            nc = MAX_COURSES;
        }
        for (int j = 0; j < nc; j++) {
            Course c;
            cout << "نام درس را وارد کنید: ";
            cin.ignore();
            getline(cin, c.coursename);
            cout << "نمره درس را وارد کنید " << c.coursename << ": ";
            cin >> c.grade;
            cout << "تعداد واحدهای را وارد کنید " << c.coursename << ": ";
            cin >> c.credits;
            students[i].courses[students[i].courseCount++] = c;
        }
    }
}

// محاسبه معدل
float calculateGPA(const Student& s) {
    float totalCourseCredits = 0;
    float totalWeightedGrades = 0;

    for (int i = 0; i < s.courseCount; i++) {
        totalWeightedGrades += s.courses[i].grade * s.courses[i].credits;
        totalCourseCredits += s.courses[i].credits;
    }

    if (totalCourseCredits == 0) return 0;
    return totalWeightedGrades / totalCourseCredits;
}

// تابع مقایسه برای مرتب‌سازی بر اساس GPA
void sortStudentsByGPA(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (calculateGPA(arr[j]) < calculateGPA(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// لیست کردن دانشجویان
void listStudents(const string& majorFilter = "") {
    Student temp[MAX_STUDENTS];
    for (int i = 0; i < studentCount; i++) {
        temp[i] = students[i];
    }
    sortStudentsByGPA(temp, studentCount);

    cout << "\n==========================================\n";
    cout << "               لیست دانشجویان               \n";
    cout << "==========================================\n";
    cout << setw(20) << left << "نام" << setw(15) << "شناسه" << setw(15) << "رشته" << setw(10) << "معدل" << endl;
    cout << "------------------------------------------\n";

    for (int i = 0; i < studentCount; i++) {
        if (majorFilter.empty() || temp[i].major == majorFilter) {
            cout << setw(20) << left << temp[i].name
                 << setw(15) << temp[i].userid
                 << setw(15) << temp[i].major
                 << setw(10) << fixed << setprecision(2) << calculateGPA(temp[i]) << endl;
        }
    }
    cout << "==========================================\n";
}

// تابع چاپ کارنامه
void printReportCard(const Student& s) {
    cout << "\n==========================================\n";
    cout << "               کارنامه               \n";
    cout << "==========================================\n";
    cout << "نام دانشجو: " << s.name << endl;
    cout << "شناسه دانشجو: " << s.userid << endl;
    cout << "رشته: " << s.major << endl;
    cout << "معدل: " << fixed << setprecision(2) << calculateGPA(s) << endl;
    cout << "------------------------------------------\n";
    cout << "دروس:\n";
    cout << setw(20) << left << "نام درس" << setw(10) << "واحد" << setw(10) << "نمره" << endl;
    cout << "------------------------------------------\n";
    for (int i = 0; i < s.courseCount; i++) {
        cout << setw(20) << left << s.courses[i].coursename
             << setw(10) << s.courses[i].credits
             << setw(10) << s.courses[i].grade << endl;
    }
    cout << "==========================================\n";
}
