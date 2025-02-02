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

// تابع ویرایش دانشجو
void editStudent(int index) {
    if (index < 0 || index >= studentCount) {
        cout << "فهرست دانشجویی نامعتبر است.\n";
        return;
    }
    cout << "نام کامل جدید را وارد کنید: ";
    cin.ignore();
    getline(cin, students[index].name);
    cout << "شناسه دانشجویی جدید را وارد کنید: ";
    cin >> students[index].userid;
    cout << "رشته جدید را وارد کنید: ";
    cin.ignore();
    getline(cin, students[index].major);
    cout << "اطلاعات دانش آموز با موفقیت به روز شد.\n";
}

// تابع حذف دانشجو
void deleteStudent(int index) {
    if (index < 0 || index >= studentCount) {
        cout << "فهرست دانشجویی نامعتبر است.\n";
        return;
    }
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;
    cout << "دانش آموز با موفقیت حذف شد.\n";
}

// تابع ویرایش درس
void editCourse(Student& s, int courseIndex) {
    if (courseIndex < 0 || courseIndex >= s.courseCount) {
        cout << "فهرست دروس نامعتبر است.\n";
        return;
    }
    cout << "نام درس جدید را وارد کنید: ";
    cin.ignore();
    getline(cin, s.courses[courseIndex].coursename);
    cout << "نمره جدید را وارد کنید: ";
    cin >> s.courses[courseIndex].grade;
    cout << "تعداد واحد جدید را وارد کنید: ";
    cin >> s.courses[courseIndex].credits;
    cout << "اطلاعات درس با موفقیت به روز شد.\n";
}

// تابع حذف درس
void deleteCourse(Student& s, int courseIndex) {
    if (courseIndex < 0 || courseIndex >= s.courseCount) {
        cout << "فهرست دروس نامعتبر است.\n";
        return;
    }
    for (int i = courseIndex; i < s.courseCount - 1; i++) {
        s.courses[i] = s.courses[i + 1];
    }
    s.courseCount--;
    cout << "درس با موفقیت حذف شد.\n";
}

int main() {
    int n;
    cout << "تعداد دانشجویان را وارد کنید: ";
    cin >> n;

    // ثبت اطلاعات دانشجویان
    for (int i = 0; i < n; i++) {
        readStudent();
    }
    readCourse();

    // منو
    while (true) {
         cout << "\nیک گزینه رو انتخاب کنید:‌ \n";
        cout << "1. لیست کردن تمام دانشجویان\n";
        cout << "2. لیست کردن دانشجویان بر اساس رشته\n";
        cout << "3. چاپ کارنامه\n";
        cout << "4. ویرایش دانشجو\n";
        cout << "5. حذف دانشجو\n";
        cout << "6. ویرایش درس\n";
        cout << "7. حذف درس\n";
        cout << "8. خروج\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            listStudents();
        } else if (choice == 2) {
            cout << "رشته را وارد کنید: ";
            string majorFilter;
            cin.ignore();
            getline(cin, majorFilter);
            listStudents(majorFilter);
        } else if (choice == 3) {
            int studentIndex;
            cout << "فهرست دانشجویی را وارد کنید (0 to " << studentCount - 1 << "): ";
            cin >> studentIndex;
            if (studentIndex >= 0 && studentIndex < studentCount) {
                printReportCard(students[studentIndex]);
            } else {
                cout << "فهرست دانشجویی نامعتبر است.\n";
            }
        } else if (choice == 4) {
            int studentIndex;
            cout << "فهرست دانشجویی را برای ویرایش وارد کنید (0 to " << studentCount - 1 << "): ";
            cin >> studentIndex;
            editStudent(studentIndex);
        } else if (choice == 5) {
            int studentIndex;
            cout << "فهرست دانشجویی را برای حذف وارد کنید (0 to " << studentCount - 1 << "): ";
            cin >> studentIndex;
            deleteStudent(studentIndex);
        } else if (choice == 6) {
            int studentIndex, courseIndex;
            cout << "فهرست دانشجویی را وارد کنید (0 to " << studentCount - 1 << "): ";
            cin >> studentIndex;
            if (studentIndex >= 0 && studentIndex < studentCount) {
                cout << "فهرست دروس را وارد کنید (0 to " << students[studentIndex].courseCount - 1 << "): ";
                cin >> courseIndex;
                editCourse(students[studentIndex], courseIndex);
            } else {
                cout << "فهرست دانشجویی نامعتبر است.\n";
            }
        } else if (choice == 7) {
            int studentIndex, courseIndex;
            cout << "فهرست دانشجویی را وارد کنید (0 to " << studentCount - 1 << "): ";
            cin >> studentIndex;
            if (studentIndex >= 0 && studentIndex < studentCount) {
                cout << "فهرست دروس را وارد کنید (0 to " << students[studentIndex].courseCount - 1 << "): ";
                cin >> courseIndex;
                deleteCourse(students[studentIndex], courseIndex);
            } else {
                cout << "فهرست دانشجویی نامعتبر است.\n";
            }
        } else if (choice == 8) {
            break;
        } else {
            cout << "انتخاب نامعتبر است، دوباره امتحان کنید.\n";
        }
    }

    return 0;
}