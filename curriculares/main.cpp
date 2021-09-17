#include <iostream>

using namespace std;

// Project for the management of curricular activities that can be carried out per semester in a university
// Authors: Hugo M�ndez Barrantes and Olman


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
    string location;
    Teacher *next;      // Link to the next node (Teacher) in the list
    Teacher *previous;  // Link to the previous node (Teacher) in the list
    struct SubListGroup *myGroups;  // Link to the teacher's assigned groups

    Teacher(string n, int id, string l){
        name = n;
        identification = id;
        location = l;
        next = NULL;
        previous = NULL;
        myGroups = NULL;
    }

}*firstTeacher;  // Double list


struct Student{
    string name;
    int studentCard;
    string location;
    Student *next;  // Link to the next node (Student) in the list
    struct SubListGroup *myGroups;            // Link to the groups to which the student belongs
    struct SubListAssignment *myAssignments;  // Sub-list in which the student records his completed assignments
    struct SubListTalk *myTalks;              // Sub-list in which the student registers his attendance to the general talks

    Student(string n, int sc, string l){
        name = n;
        studentCard = sc;
        location = l;
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


Administrator* searchAdmin(string password){  // Method that search for an administrator through his password
    Administrator* aux = firstAdmin;

    while(aux != NULL){                 // The administrator list is toured
        if(aux->password == password){  // Passwords are compared
            return aux;                 // If the password matches, then the administrator is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the administrator is not found, then "NULL" is returned
}


bool insertAdmin(string name, string password){  // Method that inserts a new administrator in the "Administrator" list (insertion at the start)

    if(firstAdmin == NULL){     // If the list is empty, then the new node is created and it becomes the first one
        Administrator* newAdmin = new Administrator(name, password);
        firstAdmin = newAdmin;  // The first node is updated
        return true;
    }

    if(searchAdmin(password) != NULL){  // If the password is already taken (that means, the administrator is already registered) then the insertion can't be performed
        return false;                   // So, "false" is returned
    }

    Administrator* newAdmin = new Administrator(name, password);  // Otherwise, the new node is inserted at the beginning of the list
    newAdmin->next = firstAdmin;  // Insertion is done at the beginning
    firstAdmin = newAdmin;        // The first node is updated
    return true;
}


Teacher* searchTeacher(int id){  // Method that search for a teacher through his identification
    Teacher* aux = firstTeacher;

    while(aux != NULL){                 // The teacher list is toured
        if(aux->identification == id){  // Identifications are compared
            return aux;                 // In case the identifications matches, then the teacher is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the teacher is not found, then "NULL" is returned
}


bool insertTeacher(string name, int id, string location){  // Method that inserts a new teacher in the "Teacher" list (insertion at the start)

    if(firstTeacher == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Teacher* newTeacher = new Teacher(name, id, location);
        firstTeacher = newTeacher;  // The first node is updated
        return true;
    }

    if(searchTeacher(id) != NULL){  // If the given "id" is repeated (that means, that teacher is already registered) then the insertion can't be performed
        return false;               // So, "false" is returned
    }

    Teacher* newTeacher = new Teacher(name, id, location);  // Otherwise, the new node is inserted at the beginning of the list
    newTeacher->next = firstTeacher;      // The "next" link of the new node, points to the first node
    firstTeacher->previous = newTeacher;  // The "previous" link of the first node, points to the new node
    firstTeacher = newTeacher;            // The first node is updated
    return true;
}


bool modifyTeacher(int id, string newLocation){  // Method that modifies the location of a registered teacher
    Teacher* aux = searchTeacher(id);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){
        aux->location = newLocation;   // If the teacher is registered, then his information is modified
        return true;
    }

    return false;  // If the teacher is not registered, then "false" is returned
}


bool deleteTeacher(int id){  // Method that deletes a registered teacher from the list
    Teacher* aux = searchTeacher(id);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){  // If the teacher is registered, then it will be deleted

        if(aux == firstTeacher){       // It is validated if it was the first node
            firstTeacher = firstTeacher->next;
            if(firstTeacher != NULL){  // Then, it is validated if it was the only node
                firstTeacher->previous = NULL;
            }
            return true;
        }
                                          // In this case, it has already been validated that the node was not the first one
        aux->previous->next = aux->next;
        if(aux->next != NULL){            // Finally, it is validated if it was the last node
            aux->next->previous = aux->previous;
        }
        return true;
    }

    return false;  // If the teacher is not registered, then "false" is returned
}


Student* searchStudent(int studentCard){  // Method that search for a student through his student card
    Student* aux = firstStudent;

    while(aux != NULL){                       // The student list is toured
        if(aux->studentCard == studentCard){  // Student cards are compared
            return aux;                       // In case the student cards matches, then the student is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the student is not found, then "NULL" is returned
}


bool insertStudent(string name, int studentCard, string location){  // Method that inserts a new student in the "Student" list (ordered insertion)

    if(firstStudent == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Student* newStudent = new Student(name, studentCard, location);
        firstStudent = newStudent;  // The first node is updated
        return true;
    }

    if(searchStudent(studentCard) != NULL){  // If the given "student card" is repeated (that student is already registered) then the insertion can't be performed
        return false;                        // So, "false" is returned
    }

    Student* newStudent = new Student(name, studentCard, location);  // The new node (Student) is created

    if(studentCard < firstStudent->studentCard){  // Case #1: the student card of the new student is the lowest
        newStudent->next = firstStudent;          // So, the new student is inserted at the beginning of the list
        firstStudent = newStudent;                // The first node is updated
        return true;
    }

    Student* aux = firstStudent->next;  // Auxiliary variable that will be useful in order to tour the list
    Student* preAux = firstStudent;     // Auxiliary variable that will be useful in order to place the new student in the proper position

    while(aux != NULL){                      // Case #2: the student card of the new student is not the lowest but neither the highest
        if(studentCard < aux->studentCard){  // In this case, a loop is created in order to find the students that go before and after the new one
            preAux->next = newStudent;       // The "preAux" node, points to the new node
            newStudent->next = aux;          // The new node, points to the "aux" node
            return true;
        }
        preAux = aux;
        aux = aux->next;
    }
                                // Case #3: the student card of the new student is the highest
    preAux->next = newStudent;  // So, the new student is inserted at the end of the list
    return true;
}


bool modifyStudent(int studentCard, string newLocation){  // Method that modifies the location of a registered student
    Student* aux = searchStudent(studentCard);  // The student is searched using the "searchStudent" method

    if(aux != NULL){
        aux->location = newLocation;  // If the student is registered, then his information is modified
        return true;
    }

    return false;  // If the student is not registered, then "false" is returned
}


bool deleteStudent(int studentCard){  // Method that deletes a registered student from the list
    Student* aux = searchStudent(studentCard);  // The student is searched using the "searchStudent" method

    if(aux != NULL){  // If the student is registered, then it will be deleted

        if(aux == firstStudent){  // It is validated if it was the first node
            firstStudent = firstStudent->next;
            return true;
        }

        Student* preAux = firstStudent;  // Auxiliary variable that will be useful in order to find the student that goes before the student we want to delete

        while(preAux->next != aux){  // Loop that finds the student who goes before the student we want to delete
            preAux = preAux->next;
        }
        preAux->next = aux->next;    // Finally, the student is deleted from the list
        return true;
    }

    return false;  // If the student is not registered, then "false" is returned
}


Semester* searchSemester(int year, int period){  // Method that search for a teacher through his identification
    Semester* aux = firstSemester;

    while(aux != NULL){                 // The teacher list is toured
        if(aux->year == year && aux->period == period){  // Identifications are compared
            return aux;                 // In case the identifications matches, then the teacher is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the teacher is not found, then "NULL" is returned
}


bool insertSemester(int year, int period){  // Method that inserts a new student in the "Student" list (ordered insertion)

    if(firstSemester == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Semester* newSemester = new Semester(period,year);
        firstSemester = newSemester;  // The first node is updated
        return true;
    }

    if(searchSemester(year, period) != NULL){  // If the given "student card" is repeated (that student is already registered) then the insertion can't be performed
        return false;                        // So, "false" is returned
    }

    Semester* newSemester = new Semester(period,year);  // The new node (Student) is created

    if(year <= firstSemester->year && period <= firstSemester->period){  // Case #1: the student card of the new student is the lowest
        newSemester->next = firstSemester;          // So, the new student is inserted at the beginning of the list
        firstSemester->previous =newSemester;
        firstSemester = newSemester;                // The first node is updated
        return true;
    }

    Semester* nextAux = firstSemester->next;  // Auxiliary variable that will be useful in order to tour the list
    Semester* preAux = firstSemester;     // Auxiliary variable that will be useful in order to place the new student in the proper position




    while(nextAux != NULL){                      // Case #2: the student card of the new student is not the lowest but neither the highest
        if(year <= nextAux->year && period <= nextAux->period){  // In this case, a loop is created in order to find the students that go before and after the new one
            preAux->next = newSemester;       // The "preAux" node, points to the new node
            newSemester->next = nextAux;          // The new node, points to the "aux" node
            newSemester->previous = preAux;
            nextAux->previous = newSemester;

            return true;
        }
        preAux = nextAux;
        nextAux = nextAux->next;
    }
                                // Case #3: the student card of the new student is the highest
    preAux->next = newSemester;  // So, the new student is inserted at the end of the list
    newSemester->previous =preAux;
    return true;
}

bool modifySemester(int y, int p, int np){  // Method that modifies the location of a registered teacher
    Semester* aux = searchSemester(y,p);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){
        aux->period = np;   // If the teacher is registered, then his information is modified
        return true;
    }

    return false;  // If the teacher is not registered, then "false" is returned
}

Course* searchCourse(string code){  // Method that search for a student through his student card
    Course* aux = firstCourse;

    while(aux != NULL){                       // The student list is toured
        if(aux->code == code){  // Student cards are compared
            return aux;                       // In case the student cards matches, then the student is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the student is not found, then "NULL" is returned
}

bool insertCourse(string n, string c, int credis){  // Method that inserts a new teacher in the "Teacher" list (insertion at the start)

    if(firstCourse == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Course* newCourse = new Course(n,c,credis);
        firstCourse = newCourse;  // The first node is updated
        return true;
    }

    if(searchCourse(c) != NULL){  // If the given "id" is repeated (that means, that teacher is already registered) then the insertion can't be performed
        return false;               // So, "false" is returned
    }

    Course* newCourse = new Course(n, c, credis);  // Otherwise, the new node is inserted at the beginning of the list
    newCourse->next = firstCourse;      // The "next" link of the new node, points to the first node
    Course * aux = firstCourse;

            while(aux->next!= firstCourse){
                aux = aux->next;
            }

            aux->next = newCourse;

    return true;
}



bool modifyCourse(string code, string name){  // Method that modifies the location of a registered teacher

    Course*aux = searchCourse(code);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){
        aux->code = code;   // If the teacher is registered, then his information is modified
        return true;
    }

    return false;  // If the teacher is not registered, then "false" is returned
}

bool deleteCourse(string code){  // Method that deletes a registered student from the list
    Course* aux = searchCourse(code);  // The student is searched using the "searchStudent" method

    if(aux != NULL){  // If the student is registered, then it will be deleted

        if(aux == firstCourse){  // It is validated if it was the first node
            firstCourse = firstCourse->next;
            Course* nextAux = firstCourse->next;

            while(nextAux->next!= firstCourse)
                nextAux = nextAux->next;

            nextAux->next = firstCourse;

            return true;
        }

        Course* preAux = firstCourse;  // Auxiliary variable that will be useful in order to find the student that goes before the student we want to delete

        while(preAux->next != aux){  // Loop that finds the student who goes before the student we want to delete
            preAux = preAux->next;
        }
        preAux->next = aux->next;    // Finally, the student is deleted from the list
        return true;
    }

    return false;  // If the student is not registered, then "false" is returned
}




void loadData(){  // Method that loads the initial data for the efficient performance of the application
    insertAdmin("Hugo Mendez", "ladiv2002");
    insertAdmin("Olman", "olmanAQ");
    insertAdmin("Lorena", "Lvalerio");
    insertAdmin("Emma", "E21");
    insertAdmin("Samantha", "S22");

    insertTeacher("Diego", 208310022, "San Carlos");
    insertTeacher("Hellen", 209320221, "San Carlos");
    insertTeacher("Jairo", 207250011, "Cartago");
    insertTeacher("Nancy", 204520224, "Cartago");
    insertTeacher("Carlos", 208320334, "Alajuela");

    insertStudent("Antonio", 20201802, "San Carlos");
    insertStudent("Valeria", 20201101, "Alajuela");
    insertStudent("Anthony", 20211503, "Cartago");
    insertStudent("Helena", 20211909, "Alajuela");
    insertStudent("Andrew", 20211406, "San Carlos");

    insertSemester(2020,1);
    insertSemester(2022, 1);
    insertSemester(2021, 1);


    insertCourse("Estructura de datos", "a", 4);


}



// ------------------------------------------------------- Tests -------------------------------------------------------

void showAdmins(){
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Showing Administrators ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Administrator* aux = firstAdmin;

    while(aux != NULL){
        cout << "\nName: " << aux->name << endl;
        aux = aux->next;
    }
}


void showTeachers(){
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Showing Teachers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Teacher* aux = firstTeacher;

    while(aux != NULL){
        cout << "\nName: " << aux->name << endl;
        cout << "\nIdentification: " << aux->identification << endl;
        cout << "\nLocation: " << aux->location << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;
        aux = aux->next;
    }
}


void showStudents(){
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Showing Students ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Student* aux = firstStudent;

    while(aux != NULL){
        cout << "\nName: " << aux->name << endl;
        cout << "\nStudent card: " << aux->studentCard << endl;
        cout << "\nLocation: " << aux->location << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;
        aux = aux->next;
    }
}


void showSemesters(){
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Showing Semesters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Semester* aux = firstSemester;

    while(aux != NULL){
        cout << "\nYeard: " << aux->year << endl;
        cout << "\nPeriod: " << aux->period << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;
        aux = aux->next;
    }
}

void showCourses(){
    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Showing Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Course* aux = firstCourse;

    while(aux != NULL){
        cout << "\nName: " << aux->name << endl;
        cout << "\nCode: " << aux->code << endl;
        cout << "\nCredits " << aux->credits << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;
        aux = aux->next;
    }
}

int main(){
    loadData();
    showAdmins();
    showTeachers();
    showStudents();
    showSemesters();
    showCourses();

    //modifyTeacher(208310022, "Cartago");  // Diego moves to Cartago
    //modifyStudent(20201802, "Cartago");   // Antonio moves to Cartago
    //deleteTeacher(208320334);  // RIP Carlos
    //deleteStudent(20211503);   // RIP Anthony

    //cout << "\n------------------------------------ After some changes ------------------------------------" << endl;
    //showAdmins();
    //showTeachers();
    //showStudents();
    return 0;
}
