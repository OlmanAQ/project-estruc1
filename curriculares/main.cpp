#include <iostream>

using namespace std;

// Project for the management of curricular activities that can be carried out per semester in a university
// Authors: Hugo M�ndez Barrantes and Olman Acu�a


struct Administrator{
    string name;
    string password;
    Administrator *next;  // Link to the next node (Administrator) in the list

    Administrator(string n, string p){
        name = n;
        password = p;
        next = NULL;
    }

}*firstAdmin;  // Simple list


struct Teacher{
    string name;
    int identification;
    Teacher *next;      // Link to the next node (Teacher) in the list
    Teacher *previous;  // Link to the previous node (Teacher) in the list
    struct SubListGroup *myGroups;  // Link to the teacher's assigned groups

    Teacher(string n, int id){
        name = n;
        identification = id;
        next = NULL;
        previous = NULL;
        myGroups = NULL;
    }

}*firstTeacher;  // Double list


struct Student{
    string name;
    int studentCard;
    Student *next;  // Link to the next node (Student) in the list
    struct SubListGroup *myGroups;            // Link to the groups to which the student belongs
    struct SubListAssignment *myAssignments;  // Sub-list in which the student records his completed assignments
    struct SubListTalk *myTalks;              // Sub-list in which the student registers his attendance to the general talks

    Student(string n, int sc){
        name = n;
        studentCard = sc;
        next = NULL;
        myGroups = NULL;
        myAssignments = NULL;
        myTalks = NULL;
    }

}*firstStudent;  // Simple list


struct Semester{
    int period;
    int year;
    Semester *next;      // Link to the next node (Semester) in the list
    Semester *previous;  // Link to the previous node (Semester) in the list
    struct SubListCourse *myCourses;  // Link to the courses that are offered in that semester
    struct SubListTalks *myTalks;     // Link to the general talks that take place in that semester

    Semester(int p, int y){
        period = p;
        year = y;
        next = NULL;
        previous = NULL;
        myCourses = NULL;
        myTalks = NULL;
    }

}*firstSemester;  // Double list


struct Course{
    string name;
    string code;
    int credits;
    Course *next;  // Link to the next node (Course) in the list
    struct SubListGroup *myGroups;  // Link to the course's groups

    Course(string n, string code, int credits){
        name = n;
        code = code;
        credits = credits;
        next = NULL;
        myGroups = NULL;
    }

}*firstCourse;  // Simple circular list


struct SubListAssignment{  // Work in progress
    int id;
    int percentage;
    string name;
    string kind;
    //bool status; ?
    //Date
    SubListAssignment *next;  // Link to the next node (Assignment) in the Sub-list

    //Constructor

};  // There is no "first" as such, since it is a Sub-list


struct SubListGroup{
    int id;
    SubListGroup *next;  // Link to the next node (Group) in the Sub-list
    Course *course;      // Link to the group's course

    SubListAssignment *tasks;     // Link to the "tasks" Sub-list of the group
    SubListAssignment *projects;  // Link to the "projects" Sub-list of the group
    SubListAssignment *tests;     // Link to the "tests" Sub-list of the group
    SubListAssignment *tours;     // Link to the "tours" Sub-list of the group

    SubListGroup(int id){
        id = id;
        next = NULL;
        course = NULL;
        tasks = NULL;
        projects = NULL;
        tests = NULL;
        tours = NULL;
    }

};  // There is no "first" as such, since it is a Sub-list


struct SubListTalk{  // Work in progress
    string name;
    //bool status; ?
    //Date
    SubListTalk *next;  // Link to the next node (Talk) in the Sub-list

    //Constructor

};  // There is no "first" as such, since it is a Sub-list


struct SubListCourse{
    SubListCourse *next;  // Link to the next node (Course) in the Sub-list
    Course *course;       // Link to the corresponding course

    SubListCourse(){
        next = NULL;
        course = NULL;
    }

};  // There is no "first" as such, since it is a Sub-list


//------------------------------------------ End of structures --> Start of methods ------------------------------------------


int main()
{
    return 0;
}
