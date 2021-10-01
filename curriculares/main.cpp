#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Project for the management of curricular activities that can be carried out per semester in a university
// Authors: Hugo Mendez Barrantes and Olman


struct Administrator{
    string name;
    string password;
    Administrator* next;  // Link to the next node (Administrator) in the list

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
    Teacher* next;      // Link to the next node (Teacher) in the list
    Teacher* previous;  // Link to the previous node (Teacher) in the list
    struct SubListGroup* myGroups;  // Link to the teacher's assigned groups

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
    Student* next;  // Link to the next node (Student) in the list
    struct SubListGroup* myGroups;            // Link to the groups to which the student belongs
    struct SubListAssignment* myAssignments;  // Sub-list in which the student records his completed assignments
    struct SubListTalk* myTalks;              // Sub-list in which the student registers his attendance to the general talks

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
    string modality;
    Semester* next;      // Link to the next node (Semester) in the list
    Semester* previous;  // Link to the previous node (Semester) in the list
    struct SubListCourse* myCourses;  // Link to the courses that are offered in that semester
    struct SubListTalk* myTalks;     // Link to the general talks that take place in that semester

    Semester(int p, int y, string m){
        period = p;
        year = y;
        modality = m;
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
    Course* next;  // Link to the next node (Course) in the list
    struct SubListGroup* myGroups;  // Link to the course's groups

    Course(string n, string c, int cred){
        name = n;
        code = c;
        credits = cred;
        next = NULL;
        myGroups = NULL;
    }

}*firstCourse;  // Simple circular list


struct SubListAssignment{
    int id;
    int grade;
    string name;
    string kind;
    int day, month, year, hour;
    SubListGroup* myGroup;    // Link to the group
    SubListAssignment* next;  // Link to the next node (Assignment) in the Sub-list

    SubListAssignment(int i, string n, string k, int d, int m, int y, int h){
        id = i;
        name = n;
        kind = k;
        day = d;
        month = m;
        year = y;
        hour = h;
        next = NULL;

    }


};  // There is no "first" as such, since it is a Sub-list


struct SubListGroup{
    int groupId;
    bool status;
    SubListGroup* next;  // Link to the next node (Group) in the Sub-list
    Course* course;      // Link to the group's course

    SubListAssignment* tasks;     // Link to the "tasks" Sub-list of the group
    SubListAssignment* projects;  // Link to the "projects" Sub-list of the group
    SubListAssignment* tests;     // Link to the "tests" Sub-list of the group
    SubListAssignment* tours;     // Link to the "tours" Sub-list of the group

    SubListGroup(int id){
        groupId = id;
        status = false;
        next = NULL;
        course = NULL;
        tasks = NULL;
        projects = NULL;
        tests = NULL;
        tours = NULL;
    }

};  // There is no "first" as such, since it is a Sub-list


struct SubListTalk{
    int id;
    string name;
    int year;
    int month;
    int day;
    int hour;
    SubListTalk* next;  // Link to the next node (Talk) in the Sub-list


    //Constructor
    SubListTalk(int i, string n, int y, int m, int d, int h){
        name = n;
        year = y;
        month = m;
        day = d;
        id = i;
        hour = h;
        next = NULL;
    }

};  // There is no "first" as such, since it is a Sub-list


struct SubListCourse{
    SubListCourse* next;  // Link to the next node (Course) in the Sub-list
    Course* enC;          // Link to the corresponding course

    SubListCourse(Course* c){
        next = NULL;
        enC = c;
    }

};  // There is no "first" as such, since it is a Sub-list


//------------------------------------------ End of structures --> Start of methods ------------------------------------------

//---------------------------------------------------- Needed prototypes -----------------------------------------------------
void mainMenu();
void login();
void adminsMenu();
void adminReports();
void managementTS();
void managementSC();
void managementGroups();
void usersMenu();
void usersLogin(int section);
void teachersMenu(Teacher* teacher);
void teacherReports(Teacher* teacher);
void studentsMenu(Student* student);
void managementAssignments(Teacher* teacher);
void managementTalks(Teacher* teacher);
//----------------------------------------------------------------------------------------------------------------------------


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


Semester* searchSemester(int year, int period){  // The method that searches for a semester through its year and its period
    Semester* aux = firstSemester;

    while(aux != NULL){                 // The semester list is toured
        if(aux->year == year && aux->period == period){  // Years and periods are compared
            return aux;                 // In case the years and periods match, then the semester is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the semester is not found, then "NULL" is returned
}


bool insertSemester( int period, int year, string modality){   // Method that inserts a new semester in the "Semester" list (ordered insertion)

    if(firstSemester == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Semester* newSemester = new Semester(period, year, modality);
        firstSemester = newSemester;  // The first node is updated
        return true;
    }

    if(searchSemester(year, period) != NULL ){  // If the given "year and period" is repeated (that semester is already registered), the insertion can't be performed
        return false;                        // So, "false" is returned
    }
    if(period != 1 && period != 2){
        return false;
    }

    Semester* newSemester = new Semester(period, year, modality);  // The new node (Semester) is created

    if(year <= firstSemester->year && period < firstSemester->period ){  // Case #1: the year and period of the new semester are the lowest

        newSemester->next = firstSemester;          // So, the new semester is inserted at the beginning of the list
        firstSemester->previous =newSemester;
        firstSemester = newSemester;                // The first node is updated
        return true;
    }

    Semester* nextAux = firstSemester->next;  // Auxiliary variable that will be useful in order to tour the list
    Semester* preAux = firstSemester;     // Auxiliary variable that will be useful in order to place the new semester in the proper position

    while(nextAux != NULL){                      // Case #2: the year and the period of the new semester are not the lowest but neither the highest
        if((year < nextAux->year) || ((year == nextAux->year) & (period < nextAux->period))){  // In this case, a loop is created in order to find the semesters that go before and after the new one
            preAux->next = newSemester;       // The "preAux" node, points to the new node
            newSemester->next = nextAux;          // The new node, points to the "nextAux" node
            newSemester->previous = preAux;     // The new node, points to the "preAux" node
            nextAux->previous = newSemester;    // The "nextAux" node, points to the new node
            return true;
        }
        preAux = nextAux;
        nextAux = nextAux->next;
    }
                                 // Case #3: the year and the period of the new semester are the highest
    preAux->next = newSemester;  // So, the new semester is inserted at the end of the list
    newSemester->previous =preAux;
    return true;
}


bool modifySemester(int y, int p, string newModality){  // Falta documentar (Olman)
    Semester* aux = searchSemester(y,p);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){
        aux->modality = newModality;   // If the teacher is registered, then his information is modified
        return true;
    }

    return false;  // If the teacher is not registered, then "false" is returned
}


Course* searchCourse(string code){  // The method that searches for a semester through his code
    if(firstCourse->code == code){
        return firstCourse;
    }

    Course* aux = firstCourse->next;

    while(aux != firstCourse){                       // The course list is toured
        if(aux->code == code){  // Codes are compared
            return aux;                       // In case the codes match, then the course is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the course is not found, then "NULL" is returned
}


bool insertCourse(string n, string c, int credis){  // Method that inserts a new teacher in the "Course" list (insertion at the end)

    if(firstCourse == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Course* newCourse = new Course(n,c,credis);
        firstCourse = newCourse;  // The first node is updated
        firstCourse->next =firstCourse;
        return true;
    }

    if(searchCourse(c) != NULL){  // If the given "code" is repeated (that means, that course is already registered) then the insertion can't be performed
        return false;               // So, "false" is returned
    }

    Course* newCourse = new Course(n, c, credis);  // Otherwise, the new node is inserted at the end of the list
    Course * aux = firstCourse;

    while(aux->next != firstCourse){
        aux = aux->next;
    }

    aux->next = newCourse;
    newCourse->next = firstCourse;
    return true;
}


bool modifyCourse(string code, string newName){  // Method that modifies the name of a registered course

    Course*aux = searchCourse(code);  // The course is searched using the "searchCourse" method

    if(aux != NULL){
        aux->name = newName;   // If the course is registered, then his information is modified
        return true;
    }

    return false;  // If the course is not registered, then "false" is returned
}


bool deleteCourse(string code){        // Method that deletes a registered course from the list
    Course* aux = searchCourse(code);  // The course is searched using the "searchCourse" method

    if(aux != NULL){  // If the course is registered, then it will be deleted

        if(aux == firstCourse){  // It is validated if it was the first node
            if(aux->next == firstCourse){
                firstCourse= NULL;
                return true;
            }

            Course* preAux = firstCourse;

            while(preAux->next!= firstCourse){
                preAux = preAux->next;
            }

            preAux->next = firstCourse->next;
            firstCourse = firstCourse->next;
            return true;
        }

        Course* preAux = firstCourse;  // Auxiliary variable that will be useful in order to find the course that goes before the course we want to delete

        while(preAux->next != aux){  // Loop that finds the course who goes before the student we want to delete
            preAux = preAux->next;
        }
        preAux->next = aux->next;    // Finally, the course is deleted from the list
        return true;
    }

    return false;  // If the course is not registered, then "false" is returned
}


SubListGroup* searchGroupInCourse(int groupId, Course* course){  // Method that search for a group into a specific course
    SubListGroup* aux = course->myGroups;

    while(aux != NULL){               // The "SubListGroup" of the course is toured
        if(aux->groupId == groupId){  // Group IDs are compared
            return aux;               // In case the IDs matches, then the group is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the group is not found, then "NULL" is returned
}


int assignGroupToCourse(int groupId, string code){  // Method that adds a new group to a given course (ordered insertion in the Sub-list)
    Course* course = searchCourse(code);

    if(course != NULL){

        if(course->myGroups == NULL){     //La sublista está vacía
            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;
            course->myGroups = newGroup;
            return 0;
        }

        if(searchGroupInCourse(groupId, course) == NULL){  // la sublista tiene al menos un elemento

            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;

            if(groupId < course->myGroups->groupId){    // inserción al inicio
                newGroup->next = course->myGroups;
                course->myGroups = newGroup;
                return 0;
            }

            SubListGroup* aux = course->myGroups->next;  // inserción en medio
            SubListGroup* preAux = course->myGroups;

            while(aux != NULL){
                if(groupId < aux->groupId){
                    preAux->next = newGroup;
                    newGroup->next = aux;
                    return 0;
                }
                preAux = aux;
                aux = aux->next;
            }

            preAux->next = newGroup;  // inserción al final
            return 0;
        }

        return 2;  // El grupo ya existe en dicho curso
    }

    return 1;  // el curso no existe
}


SubListGroup* searchGroupInTeacher(int groupId, Course* course, Teacher* teacher){  // Method that finds out if a teacher is in charge of a specific group
    SubListGroup* aux = teacher->myGroups;

    while(aux != NULL){                                        // The "SubListGroup" of the teacher is toured
        if(aux->groupId == groupId && aux->course == course){  // Group IDs and courses are compared
            return aux;                                        // In case both matches, then the group is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the group is not found, then "NULL" is returned
}


int assignGroupToTeacher(int groupId, string courseCode, int teacherId){  // Method that relates a teacher to a specific group (using a Sub-list)

    Teacher* teacher = searchTeacher(teacherId);
    if(teacher == NULL){
        return 1;
    }

    Course* course = searchCourse(courseCode);
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(groupId, course);  // Verifica que ese curso tenga el grupo
    if(group == NULL){
        return 3;
    }

    if(group->status == false){

        if(teacher->myGroups == NULL){  //El profe no tiene grupos
            group->status = true;

            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;
            teacher->myGroups = newGroup;
            return 0;
        }

        if(searchGroupInTeacher(groupId, course, teacher) == NULL){  //El profe tiene al menos un grupo
            group->status = true;

            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;
            newGroup->next = teacher->myGroups;
            teacher->myGroups = newGroup;
            return 0;
        }

        return 5; // EL profe ya tiene el grupo
    }

    return 4;  //Otro profe tiene el grupo
}


int deleteTeacherGroup(int groupId, string courseCode, int teacherId){  // Method that removes a specific group from a teacher's Sub-list of groups

    Teacher* teacher = searchTeacher(teacherId);
    if(teacher == NULL){
        return 1;
    }

    Course* course = searchCourse(courseCode);
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(groupId, course);  // Verifica que ese curso tenga el grupo
    if(group == NULL){
        return 3;
    }

    SubListGroup* groupToDelete = searchGroupInTeacher(groupId, course, teacher);  // Verifica si el profe está a cargo del grupo
    if(groupToDelete == NULL){
        return 4;
    }

    group->status = false;

    if(groupToDelete == teacher->myGroups){       // En caso de que sea el primer elemento
        teacher->myGroups = groupToDelete->next;
        return 0;
    }

    SubListGroup* preGroup = teacher->myGroups;   // En caso de que sea un elemento medio o el último

    while(preGroup->next != groupToDelete){
        preGroup = preGroup->next;
    }

    preGroup->next = groupToDelete->next;
    return 0;
}


SubListGroup* searchGroupInStudent(int groupId, Course* course, Student* student){  // Method that finds out if a student belongs to a specific group
    SubListGroup* aux = student->myGroups;

    while(aux != NULL){                                        // The "SubListGroup" of the student is toured
        if(aux->groupId == groupId && aux->course == course){  // Group IDs and courses are compared
            return aux;                                        // In case both matches, then the group is returned
        }
        aux = aux->next;
    }

    return NULL;  // In case the group is not found, then "NULL" is returned
}


int assignGroupToStudent(int groupId, string courseCode, int studentCard){  // Method that relates a student to a specific group (using a Sub-list)

    Student* student = searchStudent(studentCard);
    if(student == NULL){
        return 1;
    }

    Course* course = searchCourse(courseCode);
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(groupId, course);  // Verifica que ese curso tenga el grupo
    if(group == NULL){
        return 3;
    }

    if(group->status == true){

        if(student->myGroups == NULL){  // El estudiante no está en ningun grupo
            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;
            student->myGroups = newGroup;
            return 0;
        }

        if(searchGroupInStudent(groupId, course, student) == NULL){  //El estudiante tiene al menos un grupo matriculado
            SubListGroup* newGroup = new SubListGroup(groupId);
            newGroup->course = course;
            newGroup->next = student->myGroups;
            student->myGroups = newGroup;
            return 0;
        }

        return 5; // El estudiante ya se encuentra en el grupo
    }

    return 4;  // El grupo no tiene profesor asignado, entonces aún no se puede matricular
}


int deleteStudentGroup(int groupId, string courseCode, int studentCard){  // Method that removes a specific group from a student's Sub-list of groups

    Student* student = searchStudent(studentCard);
    if(student == NULL){
        return 1;
    }

    Course* course = searchCourse(courseCode);
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(groupId, course);  // Verifica que ese curso tenga el grupo
    if(group == NULL){
        return 3;
    }

    SubListGroup* groupToDelete = searchGroupInStudent(groupId, course, student); // Verifica si el estudiante está en el grupo
    if(groupToDelete == NULL){
        return 4;
    }

    if(groupToDelete == student->myGroups){       // En caso de que sea el primer elemento
        student->myGroups = groupToDelete->next;
        return 0;
    }

    SubListGroup* preGroup = student->myGroups;   // En caso de que sea un elemento medio o el último

    while(preGroup->next != groupToDelete){
        preGroup = preGroup->next;
    }

    preGroup->next = groupToDelete->next;
    return 0;
}


SubListCourse* searchCourseInSemester(Course * auxC, Semester * auxS){

    if(auxS->myCourses == NULL){
        return NULL;
    }

    SubListCourse* auxLC = auxS->myCourses;

    while(auxLC != NULL){
        if(auxLC->enC->code == auxC->code){
            return auxLC;
        }
        auxLC= auxLC->next;
    }
    return NULL;
}


int assignCourseToSemester(int yeard, int period, string code){
    Course* auxCourse = searchCourse(code);
    Semester* auxSemester = searchSemester(yeard, period);

    if((auxSemester == NULL) || (auxCourse == NULL)){
        return 1;
    }

    SubListCourse* auxL = searchCourseInSemester(auxCourse, auxSemester);
    if(auxL != NULL){
        return 2;
    }

    SubListCourse* newSc = new SubListCourse(auxCourse);

    if(auxSemester->myCourses == NULL){
        auxSemester->myCourses = newSc;
        return 0;
    }

    newSc->next = auxSemester->myCourses;
    auxSemester->myCourses = newSc;
    return 0;
}


SubListAssignment* searchAssignment(SubListGroup* group, int id, string kind){
    SubListAssignment* auxA;

    if((kind == "task") || (kind == "Task")){
        auxA = group->tasks;

    } else if((kind == "project") || (kind == "Project")){
        auxA = group->projects;

    } else if((kind == "test") || (kind == "Test")){
        auxA = group->tests;

    } else{
        auxA = group->tours;
    }

    while(auxA != NULL){
        if(auxA->id == id){
            return auxA;
        }
        auxA = auxA->next;
    }

    return NULL;
}


void setAssignmentInKind(SubListAssignment* newAs, string kind, SubListGroup* groupTeacher, SubListGroup* group){
    if((kind == "task") || (kind == "Task")){
        groupTeacher->tasks = newAs;
        group->tasks = groupTeacher->tasks;
    }
    else if((kind == "project") || (kind == "Project")){
        groupTeacher->projects = newAs;
        group->projects = groupTeacher->projects;
    }
    else if((kind == "test") || (kind == "Test")){
        groupTeacher->tests = newAs;
        group->tests = groupTeacher->tests;
    } else{
        groupTeacher->tours = newAs;
        group->tours = groupTeacher->tours;
    }
}


void updateGroupAssignments(string kind, SubListGroup* groupToC, SubListGroup* group){
    if((kind == "task") || (kind == "Task")){
        group->tasks = groupToC->tasks;
    }
    else if((kind == "project") || (kind == "Project")){
        group->projects = groupToC->projects;
    }
    else if((kind == "test") || (kind == "Test")){
        group->tests = groupToC->tests;
    } else{
        group->tours = groupToC->tours;
    }
}


void updateStudentAssignments(string kind, SubListGroup* groupToC){
    Student* aux = firstStudent;

    while(aux != NULL){
        SubListGroup* group = aux->myGroups;

        while(group != NULL){
            if((group->groupId == groupToC->groupId) && (group->course == groupToC->course)){
                updateGroupAssignments(kind, groupToC, group);
            }

            group = group->next;
        }

        aux = aux->next;
    }
}


int assignAssignment(Teacher* teacher, string courseCode, int idG, int idA, string kind, string name, int day, int month, int year, int hour){

    if((kind != "task") && (kind != "Task") && (kind != "project") && (kind != "Project") && (kind != "test") && (kind != "Test") && (kind != "tour") && (kind != "Tour")){
        return 1;
    }

    if((month > 12) || (month < 1 ) || (day > 31) || (day < 1)){
        return 2;
    }

    if(hour < 1 || hour > 24){
        return 3;
    }

    Course* course = searchCourse(courseCode); //Curso no existe
    if(course == NULL){
        return 4;
    }

    Semester* semester;
    if(month < 7){
        semester = searchSemester(year, 1);
    } else{
        semester = searchSemester(year, 2);
    }
    if(searchCourseInSemester(course, semester) == NULL){  //El curso no se imparte en el semestre actual
        return 5;
    }

    SubListGroup* group = searchGroupInCourse(idG, course); //Grupo no existe en dicho curso
    if(group == NULL){
        return 6;
    }

    SubListGroup* groupTeacher = searchGroupInTeacher(idG, course, teacher); //Teacher no pertenece al grupo
    if(groupTeacher == NULL){
        return 7;
    }

    SubListAssignment* activity = searchAssignment(groupTeacher, idA, kind); // La actividad ya esta registrada
    if(activity != NULL){
        return 8;
    }

    SubListAssignment*newAs = new SubListAssignment(idA, name, kind, day, month, year, hour);
    newAs->myGroup = group;
    SubListAssignment*auxAS;

    if((kind == "task") || (kind == "Task")){
        auxAS = groupTeacher->tasks;
    }
    else if((kind == "project") || (kind == "Project")){
        auxAS = groupTeacher->projects;
    }
    else if((kind == "test") || (kind == "Test")){
        auxAS = groupTeacher->tests;
    }
    else{
        auxAS = groupTeacher->tours;
    }

    if(auxAS == NULL){
        setAssignmentInKind(newAs, kind, groupTeacher, group);
        updateStudentAssignments(kind, groupTeacher);
        return 0;
    }

    if((month < auxAS->month) || ((month == auxAS->month) && (day < auxAS->day)) || ((month == auxAS->month) && (day == auxAS->day) && (hour <= auxAS->hour))){
        newAs->next = auxAS;
        setAssignmentInKind(newAs, kind, groupTeacher, group);
        updateStudentAssignments(kind, groupTeacher);
        return 0;
    }

    SubListAssignment* auxAsnext = auxAS->next;
    while(auxAsnext != NULL){
        if((month < auxAsnext->month) || ((month == auxAsnext->month) && (day < auxAsnext->day )) || ((month == auxAsnext->month) && (day == auxAsnext->day) && (hour <= auxAsnext->hour))){
            auxAS->next = newAs;
            newAs->next = auxAsnext;
            updateGroupAssignments(kind, groupTeacher, group); // Las tareas del grupo de curso quedan igual a las del profe
            updateStudentAssignments(kind, groupTeacher);
            return 0;
        }
        auxAS = auxAsnext;
        auxAsnext = auxAsnext->next;
    }

    auxAS->next = newAs;
    updateGroupAssignments(kind, groupTeacher, group); // Las tareas del grupo de curso quedan igual a las del profe
    updateStudentAssignments(kind, groupTeacher);
    return 0;
}


int modifyAssignment(Teacher* teacher, string courseCode, int idG, int idA, string kind, string newName){

    if((kind != "task") && (kind != "Task") && (kind != "project") && (kind != "Project") && (kind != "test") && (kind != "Test") && (kind != "tour") && (kind != "Tour")){
        return 1;
    }

    Course* course = searchCourse(courseCode); //Curso no existe
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(idG, course); //Grupo no existe en dicho curso
    if(group == NULL){
        return 3;
    }

    SubListGroup* groupTeacher = searchGroupInTeacher(idG, course, teacher); //Teacher no pertenece al grupo
    if(groupTeacher == NULL){
        return 4;
    }

    SubListAssignment*auxA = searchAssignment(groupTeacher, idA, kind);  // The course is searched using the "searchCourse" method

    if(auxA != NULL){
        auxA->name = newName;   // If the course is registered, then his information is modified
        return 0;
    }
    return 5;
}


int deleteAssignment(Teacher* teacher, string courseCode, int idG, int idA, string kind){

    if((kind != "task") && (kind != "Task") && (kind != "project") && (kind != "Project") && (kind != "test") && (kind != "Test") && (kind != "tour") && (kind != "Tour")){
        return 1;
    }

    Course* course = searchCourse(courseCode); //Curso no existe
    if(course == NULL){
        return 2;
    }

    SubListGroup* group = searchGroupInCourse(idG, course); //Grupo no existe en dicho curso
    if(group == NULL){
        return 3;
    }

    SubListGroup* groupTeacher = searchGroupInTeacher(idG, course, teacher); //Teacher no pertenece al grupo
    if(groupTeacher == NULL){
        return 4;
    }

    SubListAssignment* activity = searchAssignment(groupTeacher, idA, kind); //La actividad no existe
    if(activity == NULL){
        return 5;
    }


    if(activity == groupTeacher->tasks){       // En caso de que sea el primer elemento
        groupTeacher->tasks = groupTeacher->tasks->next;
        return 0;
    }
    if(activity == groupTeacher->tests){       // En caso de que sea el primer elemento
        groupTeacher->tests = groupTeacher->tests->next;
        return 0;
    }
    if(activity == groupTeacher->tours){       // En caso de que sea el primer elemento
        groupTeacher->tours = groupTeacher->tours->next;
        return 0;
    }
    if(activity == groupTeacher->projects){       // En caso de que sea el primer elemento
        groupTeacher->projects = groupTeacher->projects->next;
        return 0;
    }

    SubListAssignment*auxAS;
    //ocupo saber en cual de las cuatros  sublista es

    if((kind == "task") || (kind == "Task")){
        auxAS = groupTeacher->tasks;
    }
    else if((kind == "project") || (kind == "Project")){
        auxAS = groupTeacher->projects;
    }
    else if((kind == "test") || (kind == "Test")){
        auxAS = groupTeacher->tests;
    }
    else{
        auxAS = groupTeacher->tours;
    }

    while(auxAS->next != activity){
        auxAS = auxAS->next;
    }

    auxAS->next = activity->next;
    return 0;

}


SubListTalk* searchTalkSemester(Semester* auxS, int id){
    SubListTalk*auxT = auxS->myTalks;
    while(auxT != NULL){
        if(id == auxT->id){
            return auxT;
        }
        auxT = auxT->next;
    }
    return NULL;
}


int assignTalkToSemester(int id, int year, int period, string name, int m, int d, int h){
    Semester*auxS = searchSemester(year, period);

    if(auxS == NULL){
        return 1;
    }
    if((m > 12) || (m < 1 ) || (d > 31) || (d < 1)){
        return 2;
    }
    if(((period==1) && (m > 6)) || ((period==2) && (m <= 6))){
        return 3;
    }
    if(h < 1 || h > 24){
        return 4;
    }

    SubListTalk*aux = searchTalkSemester(auxS, id);
    if(aux != NULL){
        return 5;
    }

    else{
        SubListTalk*newTalk = new SubListTalk(id, name, year, m, d, h);
        if(auxS->myTalks == NULL){
            auxS->myTalks = newTalk;
            return 0;
        }
        SubListTalk* auxT = auxS->myTalks;

        if((m < auxT->month) || ((m == auxT->month) && (d < auxT->day)) || ((m == auxT->month) && (d == auxT->day) && (h <= auxT->hour))){
            newTalk->next = auxT;
            auxS->myTalks = newTalk;
            return 0;
        }
        SubListTalk* auxTNext = auxS->myTalks->next;
        while(auxTNext != NULL){
            if((m < auxTNext->month) || ((m == auxTNext->month) && (d < auxTNext->day )) || ((m == auxT->month) && (d == auxT->day) && (h <= auxT->hour))){
                auxT->next = newTalk;
                newTalk->next = auxTNext;
                return 0;
            }
            auxT = auxTNext;
            auxTNext = auxTNext->next;
        }
        auxT->next = newTalk;
        return 0;
    }
}


bool modifyTalk(int id, string newName, int year, int period){  // Method that modifies the name of a registered talks
    Semester*auxS = searchSemester(year, period);
    if(auxS == NULL){
        return false;
    }

    SubListTalk*aux = searchTalkSemester(auxS, id);  // The course is searched using the "searchCourse" method

    if(aux != NULL){
        aux->name = newName;   // If the course is registered, then his information is modified
        return true;
    }

    return false;  // If the course is not registered, then "false" is returne
}


int deleteTalk(int id, int year, int period){  // Method that modifies the name of a registered talks

    Semester*auxS = searchSemester(year, period);
    if(auxS == NULL){
        return 1;
    }

    SubListTalk*talkDelete = searchTalkSemester(auxS, id);  // The course is searched using the "searchCourse" method

    if(talkDelete == NULL){
       return 2;
    }

    if(talkDelete == auxS->myTalks){       // En caso de que sea el primer elemento
        auxS->myTalks = talkDelete->next;
        return 0;
    }

    SubListTalk* preTalk = auxS->myTalks;   // En caso de que sea un elemento medio o el último

    while(preTalk->next != talkDelete){
        preTalk = preTalk->next;
    }

    preTalk->next = talkDelete->next;
    return 0;
}


SubListAssignment* searchAssignmentStudent(Student* student, int id, string kind, Course* course){
    SubListAssignment* auxA = student->myAssignments;

    while(auxA != NULL){
        if((id == auxA->id) && (kind == auxA->kind) && (course == auxA->myGroup->course)){
            return auxA;
        }
        auxA = auxA->next;
    }

    return NULL;
}


int registerCoAssignment(Student* student, string courseCode, int idG, int idA, string kind, int year, int month, int day, int hour){
    if((kind != "task") && (kind != "Task") && (kind != "project") && (kind != "Project") && (kind != "test") && (kind != "Test") && (kind != "tour") && (kind != "Tour")){
        return 1;
    }

    Course* course = searchCourse(courseCode); //Curso no existe
    if(course == NULL){
        return 2;
    }

    Semester* semester;
    if(month < 7){
        semester = searchSemester(year, 1);
    } else{
        semester = searchSemester(year, 2);
    }
    if(searchCourseInSemester(course, semester) == NULL){  //El curso no se imparte en el semestre actual
        return 3;
    }

    SubListGroup* group = searchGroupInCourse(idG, course); //Grupo no existe en dicho curso
    if(group == NULL){
        return 4;
    }

    SubListGroup* groupStudent = searchGroupInStudent(idG, course, student); //Estudiante no pertenece al grupo
    if(groupStudent == NULL){
        return 5;
    }

    SubListAssignment* activity = searchAssignment(group, idA, kind); //La actividad no existe
    if(activity == NULL){
        return 6;
    }

    if(student->myAssignments == NULL){   // EL estudiante no ha registrado ninguna actividad
        SubListAssignment* newA = new SubListAssignment(idA, activity->name, kind, day, month, year, hour);
        srand((unsigned)time(0));
        int grade = (rand()%90)+10;
        newA->grade = grade;
        newA->myGroup = group;
        student->myAssignments = newA;
        return 0;
    }

    if(searchAssignmentStudent(student, idA, kind, course) == NULL){ //El estudiante no ha registrado dicha actividad como completada
        SubListAssignment* newA = new SubListAssignment(idA, activity->name, kind, day, month, year, hour);
        srand((unsigned)time(0));
        int grade = (rand()%90)+10;
        newA->grade = grade;
        newA->myGroup = group;
        newA->next = student->myAssignments;
        student->myAssignments = newA;
        return 0;
    }

    return 7; // El estudiante ya registro la actividad como completada
}


SubListTalk* searchTalkStudent(Student* student, int id, int year, int month){
    SubListTalk* auxT = student->myTalks;

    while(auxT != NULL){
        if((id == auxT->id) && (year == auxT->year) && (month == auxT->month)){
            return auxT;
        }
        auxT = auxT->next;
    }
    return NULL;
}


int registerAtteTalk(Student* student, int id, int year, int period){
    Semester* semester = searchSemester(year, period);  //Semestre no esta registrado
    if(semester == NULL){
        return 1;
    }

    SubListTalk* talk = searchTalkSemester(semester, id); // La charla no existe en el semestre
    if(talk == NULL){
        return 2;
    }

    if(student->myTalks == NULL){  // El estudiante no ha asistido a ninguna charla
        SubListTalk* newT = new SubListTalk(id, talk->name, talk->year, talk->month, talk->day, talk->hour);
        student->myTalks = newT;
        return 0;
    }

    if(searchTalkStudent(student, id, talk->year, talk->month) == NULL){  //El estudiante no ha registrado la asistencia a la charla
        SubListTalk* newT = new SubListTalk(id, talk->name, talk->year, talk->month, talk->day, talk->hour);
        newT->next = student->myTalks;
        student->myTalks = newT;
        return 0;
    }

    return 3; // El estudiante ya registro la asistencia en la charla
}


void loadData(){  // Method that loads the initial data for the efficient performance of the application
    insertAdmin("Hugo Mendez", "ladiv2002");
    insertAdmin("Olman", "olmanAQ");
    insertAdmin("Lorena", "Lvalerio");
    insertAdmin("Emma", "E21");
    insertAdmin("Samantha", "S22");

    insertTeacher("Diego", 208310022, "San Carlos");
    insertTeacher("Jairo", 207250011, "Cartago");
    insertTeacher("Carlos", 208320334, "Alajuela");
    insertTeacher("Nancy", 204520224, "Cartago");
    insertTeacher("Hellen", 209320221, "San Carlos");

    insertStudent("Antonio", 20201802, "San Carlos");
    insertStudent("Valeria", 20201101, "Alajuela");
    insertStudent("Anthony", 20211503, "Cartago");
    insertStudent("Helena", 20211909, "Alajuela");
    insertStudent("Andrew", 20211406, "San Carlos");

    insertSemester(1, 2021, "virtual");
    insertSemester(2, 2021, "virtual");
    insertSemester(1, 2022, "virtual");
    insertSemester(2, 2022, "virtual");
    insertSemester(1, 2023, "virtual");
    insertSemester(2, 2023, "virtual");

    insertCourse("Data structures", "IC2001", 4);
    insertCourse("Object-oriented programming", "IC2101", 4);
    insertCourse("Algebra", "MA1103", 4);
    insertCourse("English", "CI1230", 3);
    insertCourse("Oral communication", "CI1107", 2);

    assignGroupToCourse(50, "IC2001");  // Data structures --> 50
    assignGroupToCourse(51, "IC2001");  // Data structures --> 51
    assignGroupToCourse(52, "MA1103");  // Algebra --> 52
    assignGroupToCourse(51, "MA1103");  // Algebra --> 51
    assignGroupToCourse(47, "CI1230");  // English --> 47
    assignGroupToCourse(48, "CI1230");  // English --> 48
    assignGroupToCourse(51, "IC2101");  // Object-oriented programming --> 51
    assignGroupToCourse(50, "IC2101");  // Object-oriented programming --> 50
    assignGroupToCourse(10, "CI1107");  // Oral communication --> 10
    assignGroupToCourse(11, "CI1107");  // Oral communication --> 11

    assignGroupToTeacher(50, "IC2001", 208310022);  // Diego  --> Data structures --> 50
    assignGroupToTeacher(51, "IC2101", 208310022);  // Diego  --> Object-oriented programming --> 51
    assignGroupToTeacher(51, "IC2001", 207250011);  // Jairo  --> Data structures --> 51
    assignGroupToTeacher(50, "IC2101", 207250011);  // Jairo  --> Object-oriented programming --> 50
    assignGroupToTeacher(52, "MA1103", 208320334);  // Carlos --> Algebra --> 52
    assignGroupToTeacher(51, "MA1103", 208320334);  // Carlos --> Algebra --> 51
    assignGroupToTeacher(47, "CI1230", 204520224);  // Nancy  --> English --> 47
    assignGroupToTeacher(48, "CI1230", 204520224);  // Nancy  --> English --> 48
    assignGroupToTeacher(10, "CI1107", 209320221);  // Hellen --> Oral communication --> 10
    assignGroupToTeacher(11, "CI1107", 209320221);  // Hellen --> Oral communication --> 11

    assignGroupToStudent(50, "IC2001", 20201802);  // Antonio --> Data structures --> 50
    assignGroupToStudent(47, "CI1230", 20201802);  // Antonio --> English --> 47
    assignGroupToStudent(50, "IC2001", 20201101);  // Valeria --> Data structures --> 50
    assignGroupToStudent(10, "CI1107", 20201101);  // Valeria --> Oral communication --> 10
    assignGroupToStudent(50, "IC2001", 20211503);  // Anthony --> Data structures --> 50
    assignGroupToStudent(51, "MA1103", 20211503);  // Anthony --> Algebra --> 51
    assignGroupToStudent(50, "IC2001", 20211909);  // Helena  --> Data structures --> 50
    assignGroupToStudent(51, "IC2101", 20211909);  // Helena  --> Object-oriented programming --> 51
    assignGroupToStudent(50, "IC2001", 20211406);  // Andrew  --> Data structures --> 50
    assignGroupToStudent(48, "CI1230", 20211406);  // Andrew  --> English --> 48

    assignCourseToSemester(2021, 1, "IC2001");  // Data structures --> first period --> 2021
    assignCourseToSemester(2021, 1, "IC2101");  // Object-oriented programming --> first period --> 2021
    assignCourseToSemester(2021, 1, "MA1103");  // Algebra --> first period --> 2021
    assignCourseToSemester(2021, 1, "CI1107");  // Oral Communication --> first period --> 2021
    assignCourseToSemester(2021, 1, "CI1230");  // English --> first period --> 2021
    assignCourseToSemester(2021, 2, "IC2001");  // Data structures --> second period --> 2021
    assignCourseToSemester(2021, 2, "IC2101");  // Object-oriented programming --> second period --> 2021
    assignCourseToSemester(2021, 2, "MA1103");  // Algebra --> second period --> 2021
    assignCourseToSemester(2021, 2, "CI1107");  // Oral Communication --> second period --> 2021
    assignCourseToSemester(2021, 2, "CI1230");  // English --> second period --> 2021

    assignCourseToSemester(2022, 1, "IC2001");  // Data structures --> first period --> 2022
    assignCourseToSemester(2022, 1, "CI1107");  // Oral communication --> first period --> 2022
    assignCourseToSemester(2022, 2, "IC2001");  // Data structures --> second period --> 2022
    assignCourseToSemester(2022, 2, "CI1230");  // English --> second period --> 2022
    assignCourseToSemester(2023, 1, "IC2001");  // Data structures --> first period --> 2023
    assignCourseToSemester(2023, 1, "MA1103");  // Algebra --> first period --> 2023
    assignCourseToSemester(2023, 2, "IC2001");  // Data structures --> second period --> 2023
    assignCourseToSemester(2023, 2, "IC2101");  // Object-oriented programming --> second period --> 2023

    assignTalkToSemester(1, 2021, 1, "Healthy food", 2, 5, 9);
    assignTalkToSemester(2, 2021, 1, "Odontology", 3, 5,  10);
    assignTalkToSemester(3, 2021, 1, "Psychology", 4, 10, 10);
    assignTalkToSemester(4, 2021, 1, "Biotechnology", 4, 25,  11);
    assignTalkToSemester(5, 2021, 1, "Physical conditioning", 6, 5,  11);
    assignTalkToSemester(1, 2021, 2, "Healthy food", 8, 5, 13);
    assignTalkToSemester(2, 2021, 2, "Emotional intelligence", 7, 10, 15);
    assignTalkToSemester(3, 2021, 2, "Healthy habits", 9, 7, 11);
    assignTalkToSemester(4, 2021, 2, "Sport and recreation", 7, 2,  10);
    assignTalkToSemester(5, 2021, 2, "Robotics", 11, 5, 9);

    registerAtteTalk(searchStudent(20201802), 1, 2021, 1);  // Antonio's attended talks
    registerAtteTalk(searchStudent(20201802), 2, 2021, 1);
    registerAtteTalk(searchStudent(20201802), 3, 2021, 1);

    registerAtteTalk(searchStudent(20211503), 2, 2021, 1);  // Anthony's attended talks
    registerAtteTalk(searchStudent(20211503), 3, 2021, 1);
    registerAtteTalk(searchStudent(20211503), 4, 2021, 1);

    registerAtteTalk(searchStudent(20211909), 1, 2021, 1);  // Helena's attended talks
    registerAtteTalk(searchStudent(20211909), 3, 2021, 1);
    registerAtteTalk(searchStudent(20211909), 5, 2021, 1);

    registerAtteTalk(searchStudent(20211406), 1, 2021, 1);  // Andrew's attended talks
    registerAtteTalk(searchStudent(20211406), 3, 2021, 1);
    registerAtteTalk(searchStudent(20211406), 5, 2021, 1);

    registerAtteTalk(searchStudent(20201101), 1, 2021, 1);  // Valeria's attended talks
    registerAtteTalk(searchStudent(20201101), 2, 2021, 1);
    registerAtteTalk(searchStudent(20201101), 3, 2021, 1);
    registerAtteTalk(searchStudent(20201101), 4, 2021, 1);
    registerAtteTalk(searchStudent(20201101), 5, 2021, 1);

    assignAssignment(searchTeacher(208310022), "IC2001", 50, 1, "task", "short task #1", 10, 2, 2021, 23); // Teacher Diego assignments
    assignAssignment(searchTeacher(208310022), "IC2001", 50, 2, "task", "short task #2", 20, 2, 2021, 23);
    assignAssignment(searchTeacher(208310022), "IC2001", 50, 1, "test", "test #1", 25, 3, 2021, 10);
    assignAssignment(searchTeacher(208310022), "IC2001", 50, 1, "tour", "tour #1", 29, 3, 2021, 10);
    assignAssignment(searchTeacher(208310022), "IC2001", 50, 1, "project", "project #1", 25, 4, 2021, 23);
    assignAssignment(searchTeacher(208310022), "IC2101", 51, 1, "task", "short task #1", 10, 1, 2021, 20);
    assignAssignment(searchTeacher(208310022), "IC2101", 51, 2, "task", "short task #2", 20, 1, 2021, 20);
    assignAssignment(searchTeacher(208310022), "IC2101", 51, 1, "project", "project #1", 25, 4, 2021, 20);
    assignAssignment(searchTeacher(208310022), "IC2101", 51, 1, "test", "test #1", 25, 2, 2021, 10);
    assignAssignment(searchTeacher(208310022), "IC2101", 51, 1, "tour", "tour #1", 29, 2, 2021, 10);

    assignAssignment(searchTeacher(207250011), "IC2001", 51, 1, "task", "short task #1", 15, 2, 2021, 23); // Teacher Jairo assignments
    assignAssignment(searchTeacher(207250011), "IC2001", 51, 2, "task", "short task #2", 25, 2, 2021, 23);
    assignAssignment(searchTeacher(207250011), "IC2001", 51, 1, "test", "test #1", 25, 3, 2021, 10);
    assignAssignment(searchTeacher(207250011), "IC2001", 51, 1, "tour", "tour #1", 30, 3, 2021, 10);
    assignAssignment(searchTeacher(207250011), "IC2001", 51, 1, "project", "project #1", 25, 4, 2021, 23);
    assignAssignment(searchTeacher(207250011), "IC2101", 50, 1, "task", "short task #1", 15, 1, 2021, 20);
    assignAssignment(searchTeacher(207250011), "IC2101", 50, 2, "task", "short task #2", 20, 1, 2021, 20);
    assignAssignment(searchTeacher(207250011), "IC2101", 50, 1, "project", "project #1", 25, 4, 2021, 20);
    assignAssignment(searchTeacher(207250011), "IC2101", 50, 1, "test", "test #1", 25, 2, 2021, 10);
    assignAssignment(searchTeacher(207250011), "IC2101", 50, 1, "tour", "tour #1", 30, 2, 2021, 10);

    assignAssignment(searchTeacher(208320334), "MA1103", 51, 1, "task", "short task #1", 15, 2, 2021, 23); // Teacher Carlos assignments
    assignAssignment(searchTeacher(208320334), "MA1103", 51, 1, "test", "test #1", 25, 3, 2021, 10);
    assignAssignment(searchTeacher(208320334), "MA1103", 51, 1, "tour", "tour #1", 30, 3, 2021, 10);
    assignAssignment(searchTeacher(208320334), "MA1103", 51, 1, "project", "project #1", 25, 4, 2021, 23);
    assignAssignment(searchTeacher(208320334), "MA1103", 52, 1, "task", "short task #1", 15, 1, 2021, 20);
    assignAssignment(searchTeacher(208320334), "MA1103", 52, 1, "test", "test #1", 25, 2, 2021, 10);
    assignAssignment(searchTeacher(208320334), "MA1103", 52, 1, "tour", "tour #1", 30, 3, 2021, 10);
    assignAssignment(searchTeacher(208320334), "MA1103", 52, 1, "project", "project #1", 25, 4, 2021, 20);

    assignAssignment(searchTeacher(204520224), "CI1230", 47, 1, "task", "short task #1", 15, 2, 2021, 23); // Teacher Nancy assignments
    assignAssignment(searchTeacher(204520224), "CI1230", 47, 1, "test", "test #1", 25, 3, 2021, 10);
    assignAssignment(searchTeacher(204520224), "CI1230", 47, 1, "tour", "tour #1", 30, 3, 2021, 10);
    assignAssignment(searchTeacher(204520224), "CI1230", 47, 1, "project", "project #1", 25, 4, 2021, 23);
    assignAssignment(searchTeacher(204520224), "CI1230", 48, 1, "task", "short task #1", 15, 1, 2021, 20);
    assignAssignment(searchTeacher(204520224), "CI1230", 48, 1, "test", "test #1", 25, 2, 2021, 10);
    assignAssignment(searchTeacher(204520224), "CI1230", 48, 1, "tour", "tour #1", 30, 3, 2021, 10);
    assignAssignment(searchTeacher(204520224), "CI1230", 48, 1, "project", "project #1", 25, 4, 2021, 20);

    assignAssignment(searchTeacher(209320221), "CI1107", 10, 1, "task", "short task #1", 10, 2, 2021, 23); // Teacher Hellen assignments
    assignAssignment(searchTeacher(209320221), "CI1107", 10, 1, "test", "test #1", 21, 3, 2021, 10);
    assignAssignment(searchTeacher(209320221), "CI1107", 10, 1, "tour", "tour #1", 10, 4, 2021, 10);
    assignAssignment(searchTeacher(209320221), "CI1107", 10, 1, "project", "project #1", 21, 4, 2021, 23);
    assignAssignment(searchTeacher(209320221), "CI1107", 11, 1, "task", "short task #1", 10, 1, 2021, 20);
    assignAssignment(searchTeacher(209320221), "CI1107", 11, 1, "test", "test #1", 21, 2, 2021, 10);
    assignAssignment(searchTeacher(209320221), "CI1107", 11, 1, "tour", "tour #1", 10, 5, 2021, 10);
    assignAssignment(searchTeacher(209320221), "CI1107", 11, 1, "project", "project #1", 21, 5, 2021, 20);

    registerCoAssignment(searchStudent(20201802), "IC2001", 50, 1, "task", 2021, 2, 10, 20);  // Antonio completed assignments
    registerCoAssignment(searchStudent(20201802), "IC2001", 50, 1, "project", 2021, 4, 25, 20);
    registerCoAssignment(searchStudent(20201802), "CI1230", 47, 1, "task", 2021, 2, 15, 20);
    registerCoAssignment(searchStudent(20201802), "CI1230", 47, 1, "tour", 2021, 3, 30, 10);

    registerCoAssignment(searchStudent(20211503), "IC2001", 50, 1, "task", 2021, 2, 10, 21);  // Anthony completed assignments
    registerCoAssignment(searchStudent(20211503), "IC2001", 50, 2, "task", 2021, 2, 19, 21);
    registerCoAssignment(searchStudent(20211503), "MA1103", 51, 1, "task", 2021, 2, 15, 21);
    registerCoAssignment(searchStudent(20211503), "MA1103", 51, 1, "test", 2021, 3, 25, 10);

    registerCoAssignment(searchStudent(20211909), "IC2001", 50, 1, "task", 2021, 2, 10, 21);  // Helena completed assignments
    registerCoAssignment(searchStudent(20211909), "IC2001", 50, 2, "project", 2021, 4, 25, 21);
    registerCoAssignment(searchStudent(20211909), "IC2101", 51, 1, "task", 2021, 1, 10, 21);
    registerCoAssignment(searchStudent(20211909), "IC2101", 51, 1, "tour", 2021, 2, 29, 21);

    registerCoAssignment(searchStudent(20211406), "IC2001", 50, 1, "task", 2021, 2, 10, 21);  // Andrew completed assignments
    registerCoAssignment(searchStudent(20211406), "IC2001", 50, 2, "task", 2021, 2, 20, 21);
    registerCoAssignment(searchStudent(20211406), "IC2001", 50, 1, "test", 2021, 3, 25, 10);
    registerCoAssignment(searchStudent(20211406), "IC2001", 50, 1, "tour", 2021, 3, 29, 10);
    registerCoAssignment(searchStudent(20211406), "IC2001", 50, 1, "project", 2021, 4, 25, 21);

    registerCoAssignment(searchStudent(20201101), "IC2001", 50, 1, "task", 2021, 2, 10, 18);  // Valeria completed assignments
    registerCoAssignment(searchStudent(20201101), "IC2001", 50, 2, "task", 2021, 2, 20, 18);
    registerCoAssignment(searchStudent(20201101), "IC2001", 50, 1, "test", 2021, 3, 25, 10);
    registerCoAssignment(searchStudent(20201101), "IC2001", 50, 1, "tour", 2021, 3, 29, 10);
    registerCoAssignment(searchStudent(20201101), "IC2001", 50, 1, "project", 2021, 4, 25, 18);
    registerCoAssignment(searchStudent(20201101), "CI1107", 10, 1, "task", 2021, 2, 10, 18);
    registerCoAssignment(searchStudent(20201101), "CI1107", 10, 1, "test", 2021, 3, 21, 10);
    registerCoAssignment(searchStudent(20201101), "CI1107", 10, 1, "tour", 2021, 4, 10, 10);
    registerCoAssignment(searchStudent(20201101), "CI1107", 10, 1, "project", 2021, 4, 21, 18);

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

    if(aux != NULL){
        do{
            cout << "\nName: " << aux->name << endl;
            cout << "\nCode: " << aux->code << endl;
            cout << "\nCredits " << aux->credits << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            aux = aux->next;
        }while(aux != firstCourse);
    }
}


void showCoursesGroups(){
    Course* aux = firstCourse;

    if(aux != NULL){
        do{
            cout<< "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Course ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout<< "\nName: " << aux->name << endl;
            cout<< "\n--------------------------------------- Groups ---------------------------------------\n";

            SubListGroup* groups = aux->myGroups;

            while(groups != NULL){
                cout << "\nGroup: " << groups->groupId << endl;
                cout << "\n--------------------------------------------------------------------------------------" << endl;
                groups = groups->next;
            }

            cout << "\n" << endl;
            aux = aux->next;

        }while(aux != firstCourse);
    }
}


void showTeachersGroups(){
    Teacher* aux = firstTeacher;

    while(aux != NULL){
        cout<< "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teacher ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<< "\nName: " << aux->name << endl;
        cout<< "\n--------------------------------------- Groups  ---------------------------------------\n";

        SubListGroup* groups = aux->myGroups;

        while(groups != NULL){
            cout << "\n" << groups->course->name << " --> Group " << groups->groupId << endl;
            cout << "\n---------------------------------------------------------------------------------------" << endl;
            groups = groups->next;
        }

        cout << "\n" << endl;
        aux = aux->next;
    }
}


void showStudentsGroups(){
    Student* aux = firstStudent;

    while(aux != NULL){
        cout<< "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<< "\nName: " << aux->name << "  <-------->  Student card: " << aux->studentCard << endl;
        cout<< "\n--------------------------------------- Groups  ---------------------------------------\n";

        SubListGroup* groups = aux->myGroups;

        while(groups != NULL){
            cout << "\n" << groups->course->name << " --> Group " << groups->groupId << endl;
            cout << "\n---------------------------------------------------------------------------------------" << endl;
            groups = groups->next;
        }

        cout << "\n" << endl;
        aux = aux->next;
    }
}


void showCoursesSemesters(){
    cout<<"\n~~~~~~~~ Showing Courses in Semester ~~~~~~~~\n";

    Semester* auxS = firstSemester;

    while(auxS != NULL){

        cout << "\nYeard: " << auxS->year << endl;
        cout << "\nPeriod: " << auxS->period << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;



    if(auxS != NULL && auxS->myCourses != NULL){

        SubListCourse*cs = auxS->myCourses;

    while(cs != NULL){


        cout << "\nCourse: " << cs->enC->name << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;
        cs=cs->next;
    }
    }
    auxS=auxS->next;
    }
}


void showTalkSemester(){
    cout<<"\n~~~~~~~~ Showing Talks in Semester ~~~~~~~~\n";

    Semester* auxS = firstSemester;

    while(auxS != NULL){

        cout << "\nSemester" << endl;
        cout << "\nYeard: " << auxS->year << endl;
        cout << "\nPeriod: " << auxS->period << endl;
        cout<<"\nTalks" << endl;
        SubListTalk*TS = auxS->myTalks;

        while(TS != NULL){
            cout << "\nName: " << TS->name << endl;
            cout << "\nDate: " << TS->day << "/" << TS->month << "/" << TS->year << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            TS=TS->next;
        }
        auxS=auxS->next;
    }
    cout << "\n--------------------------------------------------------------------------------------" << endl;
}


void registerAdmin(){
    system("CLS");
    cout << endl <<"----------------------->> Registering a new administrator <<-----------------------" << endl;
    string name;
    string password;
    char k = '0';

    cout << endl <<"---> Enter the new administrator's name: ";
    cin >> name;

    cout << endl <<"---> Enter the new administrator's password: ";
    cin >> password;

    if(insertAdmin(name, password)){
        cout << endl <<"\n~ Administrator has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        adminsMenu();

    } else{
        cout << endl <<"\n----------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"*** It was not possible to register, that password belongs to a registered administrator ***\n";
        cout << endl <<"----------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerAdmin();

        } else{
            adminsMenu();
        }
    }

}


void registerTeacher(){
    system("CLS");
    cout << endl <<"-------------------------->> Registering a new teacher <<--------------------------" << endl;
    string name;
    int id;
    string location;
    char k = '0';

    cout << endl <<"---> Enter the new teacher's name: ";
    cin >> name;

    cout << endl <<"---> Enter the new teacher's identification: ";
    cin >> id;

    cout << endl <<"---> Enter the new teacher's location: ";
    cin >> location;

    if(insertTeacher(name, id, location)){
        cout << endl <<"\n~ Teacher has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"****** It was not possible to register, because that teacher is already registered ******\n";
        cout << endl <<"******              ~ You should try to use another identification ~               ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerTeacher();

        } else{
            managementTS();
        }
    }

}


void modifyingTeacher(){
    system("CLS");
    cout << endl <<"-------------------------->> Modifying a teacher <<--------------------------" << endl;
    int id;
    string newLocation;
    char k = '0';

    cout << endl <<"---> Enter the teacher's identification: ";
    cin >> id;

    cout << endl <<"---> Enter the new location of the teacher: ";
    cin >> newLocation;

    if(modifyTeacher(id, newLocation)){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to modify, because that teacher is not registered    ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingTeacher();

        } else{
            managementTS();
        }
    }
}


void removeTeacher(){
    system("CLS");
    cout << endl <<"-------------------------->> Removing a teacher <<--------------------------" << endl;
    int id;
    char k = '0';

    cout << endl <<"---> Enter the teacher's identification: ";
    cin >> id;

    if(deleteTeacher(id)){
        cout << endl <<"\n~ Teacher has been removed successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to remove, because that teacher is not registered    ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeTeacher();

        } else{
            managementTS();
        }
    }
}


void registerStudent(){
    system("CLS");
    cout << endl <<"-------------------------->> Registering a new student <<--------------------------" << endl;
    string name;
    int sc;
    string location;
    char k = '0';

    cout << endl <<"---> Enter the new student's name: ";
    cin >> name;

    cout << endl <<"---> Enter the new student's student card: ";
    cin >> sc;

    cout << endl <<"---> Enter the new student's location: ";
    cin >> location;

    if(insertStudent(name, sc, location)){
        cout << endl <<"\n~ Student has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"****** It was not possible to register, because that student is already registered ******\n";
        cout << endl <<"******               ~ You should try to use another student card ~                ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerStudent();

        } else{
            managementTS();
        }
    }
}


void modifyingStudent(){
    system("CLS");
    cout << endl <<"-------------------------->> Modifying a student <<--------------------------" << endl;
    int sc;
    string newLocation;
    char k = '0';

    cout << endl <<"---> Enter the student's student card: ";
    cin >> sc;

    cout << endl <<"---> Enter the new location of the student: ";
    cin >> newLocation;

    if(modifyStudent(sc, newLocation)){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to modify, because that student is not registered    ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingStudent();

        } else{
            managementTS();
        }
    }
}


void removeStudent(){
    system("CLS");
    cout << endl <<"-------------------------->> Removing a student <<--------------------------" << endl;
    int sc;
    char k = '0';

    cout << endl <<"---> Enter the student's student card: ";
    cin >> sc;

    if(deleteStudent(sc)){
        cout << endl <<"\n~ Student has been removed successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTS();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to remove, because that student is not registered    ******\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeStudent();

        } else{
            managementTS();
        }
    }
}


void managementTS(){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------>> Teacher and Students Management <<------------------------" << endl;
    cout << endl <<"                                  Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new teacher \n";
    cout << endl <<"2. ---> Modify the location of a registered teacher \n";
    cout << endl <<"3. ---> Remove a teacher \n";
    cout << endl <<"4. ---> Register a new student \n";
    cout << endl <<"5. ---> Modify the location of a registered student \n";
    cout << endl <<"6. ---> Remove a student \n";
    cout << endl <<"7. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerTeacher();

    } else if(k == '2'){
        modifyingTeacher();

    } else if(k == '3'){
        removeTeacher();

    } else if(k == '4'){
        registerStudent();

    } else if(k == '5'){
        modifyingStudent();

    } else if(k == '6'){
        removeStudent();

    } else if(k == '7'){
        adminsMenu();

    } else{
        managementTS();
    }
}


void registerSemester(){
    system("CLS");
    cout << endl <<"-------------------------->> Registering a new semester <<--------------------------" << endl;
    int year;
    int period;
    string modality;
    char k = '0';

    cout << endl <<"---> Enter the year of the new semester: ";
    cin >> year;

    cout << endl <<"---> Enter the period of the new semester (remember that period can only be 1 or 2): ";
    cin >> period;

    cout << endl <<"---> Enter the modality of the new semester: ";
    cin >> modality;

    if(insertSemester(period, year, modality)){
        cout << endl <<"\n~ Semester has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n--------------------------------------------------------------------------------------------" << endl;

        if(period == 1 || period == 2){
            cout << endl <<"******  It was not possible to register, because that semester is already registered  ******\n";
        } else {
            cout << endl <<"****** It was not possible to register, because the period was out of the valid range ******\n";
            cout << endl <<"******                ~ Remember that the period can only be 1 or 2 ~                 ******\n";
        }

        cout << endl <<"--------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerSemester();

        } else{
            managementSC();
        }
    }
}


void modifyingSemester(){
    system("CLS");
    cout << endl <<"-------------------------->> Modifying a semester <<--------------------------" << endl;
    int year;
    int period;
    string newModality;
    char k = '0';

    cout << endl <<"---> Enter the semester's year: ";
    cin >> year;

    cout << endl <<"---> Enter the semester's period: ";
    cin >> period;

    cout << endl <<"---> Enter the new modality of the semester: ";
    cin >> newModality;

    if(modifySemester(year, period, newModality)){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to modify, because that semester is not registered    ******\n";
        cout << endl <<"------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingSemester();

        } else{
            managementSC();
        }
    }
}


void registerCourse(){
    system("CLS");
    cout << endl <<"-------------------------->> Registering a new course <<--------------------------" << endl;
    string name;
    string code;
    int credits;
    char k = '0';

    cout << endl <<"---> Enter the new course's name: ";
    cin >> name;

    cout << endl <<"---> Enter the new course's code: ";
    cin >> code;

    cout << endl <<"---> Enter the number of credits for the new course: ";
    cin >> credits;

    if(insertCourse(name, code, credits)){
        cout << endl <<"\n~ Course has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"****** It was not possible to register, because that course is already registered ******\n";
        cout << endl <<"******                   ~ You should try to use another code ~                   ******\n";
        cout << endl <<"----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerCourse();

        } else{
            managementSC();
        }
    }
}


void modifyingCourse(){
    system("CLS");
    cout << endl <<"-------------------------->> Modifying a course <<--------------------------" << endl;
    string code;
    string newName;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    cout << endl <<"---> Enter the new name of the course: ";
    cin >> newName;

    if(modifyCourse(code, newName)){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to modify, because that course is not registered    ******\n";
        cout << endl <<"----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingCourse();

        } else{
            managementSC();
        }
    }
}


void removeCourse(){
    system("CLS");
    cout << endl <<"-------------------------->> Removing a course <<--------------------------" << endl;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    if(deleteCourse(code)){
        cout << endl <<"\n~ Course has been removed successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to remove, because that course is not registered    ******\n";
        cout << endl <<"----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeCourse();

        } else{
            managementSC();
        }
    }
}


void assignCoToS(){
    system("CLS");
    cout << endl <<"-------------------------->> Assigning a course to a semester <<--------------------------" << endl;
    int year;
    int period;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the semester's year: ";
    cin >> year;

    cout << endl <<"---> Enter the semester's period: ";
    cin >> period;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = assignCourseToSemester(year, period, code);

    if(result == 0){
        cout << endl <<"\n~ The course has been assigned successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementSC();

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"***  It was not possible to assign, because that semester or that course is not registered  ***\n";
        } else {
            cout << endl <<"*** It was not possible to assign, because that course is already assigned to that semester ***\n";
        }

        cout << endl <<"-----------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            assignCoToS();

        } else{
            managementSC();
        }
    }
}


void managementSC(){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------>> Semester and Courses Management <<------------------------" << endl;
    cout << endl <<"                                  Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new semester \n";
    cout << endl <<"2. ---> Modify a registered semester \n";
    cout << endl <<"3. ---> Register a new course \n";
    cout << endl <<"4. ---> Modify a registered course \n";
    cout << endl <<"5. ---> Remove a course \n";
    cout << endl <<"6. ---> Assign a course to a semester \n";
    cout << endl <<"7. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerSemester();

    } else if(k == '2'){
        modifyingSemester();

    } else if(k == '3'){
        registerCourse();

    } else if(k == '4'){
        modifyingCourse();

    } else if(k == '5'){
        removeCourse();

    } else if(k == '6'){
        assignCoToS();

    } else if(k == '7'){
        adminsMenu();

    } else{
        managementSC();
    }

}


void registerGroup(){
    system("CLS");
    cout << endl <<"-------------------------->> Registering a new group <<--------------------------" << endl;
    int groupId;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the ID of the new group: ";
    cin >> groupId;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = assignGroupToCourse(groupId, code);

    if(result == 0){
        cout << endl <<"\n~ The group has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementGroups();

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******  It was not possible to register, because that course is not registered   ******\n";
        } else {
            cout << endl <<"****** It was not possible to register, because that group is already registered ******\n";
            cout << endl <<"******                ~ You should try to use another group ID ~                 ******\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerGroup();

        } else{
            managementGroups();
        }
    }
}


void assignGrToT(){
    system("CLS");
    cout << endl <<"-------------------------->> Assigning a group to a teacher <<--------------------------" << endl;
    int teacherId;
    int groupId;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the teacher's identification: ";
    cin >> teacherId;

    cout << endl <<"---> Enter the group's ID: ";
    cin >> groupId;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = assignGroupToTeacher(groupId, code, teacherId);

    if(result == 0){
        cout << endl <<"\n~ The group has been assigned to the teacher successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementGroups();

    } else{
        cout << endl <<"\n-------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******     It was not possible to assign, because that teacher is not registered     ******\n";
        } else if(result == 2){
            cout << endl <<"******     It was not possible to assign, because that course is not registered      ******\n";
        } else if(result == 3){
            cout << endl <<"***   It was not possible to assign, because the course has not registered that group   ***\n";
        } else if(result == 4){
            cout << endl <<"***  It was not possible to assign, because another teacher is in charge of the group   ***\n";
        } else {
            cout << endl <<"*** It was not possible to assign, because the group is already assigned to the teacher ***\n";
        }

        cout << endl <<"-------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            assignGrToT();

        } else{
            managementGroups();
        }
    }
}


void removeTeacherFromG(){
    system("CLS");
    cout << endl <<"-------------------------->> Removing a teacher from a group <<--------------------------" << endl;
    int teacherId;
    int groupId;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the teacher's identification: ";
    cin >> teacherId;

    cout << endl <<"---> Enter the group's ID: ";
    cin >> groupId;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = deleteTeacherGroup(groupId, code, teacherId);

    if(result == 0){
        cout << endl <<"\n~ The teacher has been removed from the group successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementGroups();

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******   It was not possible to remove, because that teacher is not registered   ******\n";
        } else if(result == 2){
            cout << endl <<"******   It was not possible to remove, because that course is not registered    ******\n";
        } else if(result == 3){
            cout << endl <<"*** It was not possible to remove, because the course has not registered that group ***\n";
        } else {
            cout << endl <<"******  It was not possible to remove, because the teacher is not in the group   ******\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeTeacherFromG();

        } else{
            managementGroups();
        }
    }
}


void assignGrToS(){
    system("CLS");
    cout << endl <<"-------------------------->> Adding a student to a group <<--------------------------" << endl;
    int sc;
    int groupId;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the student's student card: ";
    cin >> sc;

    cout << endl <<"---> Enter the group's ID: ";
    cin >> groupId;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = assignGroupToStudent(groupId, code, sc);

    if(result == 0){
        cout << endl <<"\n~ The student has been added to the group successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementGroups();

    } else{
        cout << endl <<"\n-------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******      It was not possible to add, because that student is not registered       ******\n";
        } else if(result == 2){
            cout << endl <<"******       It was not possible to add, because that course is not registered       ******\n";
        } else if(result == 3){
            cout << endl <<"***    It was not possible to add, because the course has not registered that group     ***\n";
        } else if(result == 4){
            cout << endl <<"*** It was not possible to add, because the group does not have a teacher in charge yet ***\n";
        } else {
            cout << endl <<"******    It was not possible to add, because the student is already in the group    ******\n";
        }

        cout << endl <<"-------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            assignGrToS();

        } else{
            managementGroups();
        }
    }
}


void removeStudentFromG(){
    system("CLS");
    cout << endl <<"-------------------------->> Removing a student from a group <<--------------------------" << endl;
    int sc;
    int groupId;
    string code;
    char k = '0';

    cout << endl <<"---> Enter the student's student card: ";
    cin >> sc;

    cout << endl <<"---> Enter the group's ID: ";
    cin >> groupId;

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;

    int result = deleteStudentGroup(groupId, code, sc);

    if(result == 0){
        cout << endl <<"\n~ The student has been removed from the group successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementGroups();

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******   It was not possible to remove, because that student is not registered   ******\n";
        } else if(result == 2){
            cout << endl <<"******   It was not possible to remove, because that course is not registered    ******\n";
        } else if(result == 3){
            cout << endl <<"*** It was not possible to remove, because the course has not registered that group ***\n";
        } else {
            cout << endl <<"******  It was not possible to remove, because the student is not in the group   ******\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeStudentFromG();

        } else{
            managementGroups();
        }
    }
}


void managementGroups(){
    system("CLS");
    char k = '0';

    cout << endl <<"----------------------------->> Groups Management <<-----------------------------" << endl;
    cout << endl <<"                                Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new group \n";
    cout << endl <<"2. ---> Assign group to a teacher \n";
    cout << endl <<"3. ---> Remove a teacher from a group \n";
    cout << endl <<"4. ---> Assign group to a student \n";
    cout << endl <<"5. ---> Remove a student from a group \n";
    cout << endl <<"6. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerGroup();

    } else if(k == '2'){
        assignGrToT();

    } else if(k == '3'){
        removeTeacherFromG();

    } else if(k == '4'){
        assignGrToS();

    } else if(k == '5'){
        removeStudentFromG();

    } else if(k == '6'){
        adminsMenu();

    } else{
        managementGroups();
    }
}


void showStudentsWithoutD(){
    system("CLS");
    char k = '0';
    cout << endl <<"------------>> Showing students who have not registered any delivery in some course <<------------" << endl;

    Student* aux = firstStudent;

    while(aux != NULL){

        SubListGroup* group = aux->myGroups;

        while(group != NULL){
            if((group->tasks != NULL) || (group->tests != NULL) || (group->tours != NULL) || (group->projects != NULL)){

                int c = 0;
                SubListAssignment* completedA = aux->myAssignments;

                while(completedA != NULL){
                    if((searchAssignment(group, completedA->id, completedA->kind) != NULL) && (searchAssignmentStudent(aux, completedA->id, completedA->kind, group->course) != NULL)){
                        c ++;
                    }

                    completedA = completedA->next;
                }

                if(c == 0){
                    cout<<  "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    cout<<  "\nName: " << aux->name << "  <-------->  Student card: " << aux->studentCard << endl;
                    cout << "\nHas not delivered any assignment in " << group->course->name << " --> Group " << group->groupId << endl;
                    cout << "\n--------------------------------------------------------------------------------------------------" << endl;
                }
            }

            group = group->next;
        }

        aux = aux->next;
    }

    cout << endl <<"~ Press any key to turn back to administrator reports: ";
    cin >> k;
    adminReports();
}


void showTalksWithMoreA(){
    cout << "hola";

}


void adminReports(){
    system("CLS");
    char k = '0';

    cout << endl <<"-------------------------------->> Administrator Reports <<--------------------------------" << endl;
    cout << endl <<"                                     Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Consult the students who have not registered any delivery in some course \n";
    cout << endl <<"2. ---> Consult the three general talks with the most student attendance of a semester x \n";
    cout << endl <<"3. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        showStudentsWithoutD();

    } else if(k == '2'){
        showTalksWithMoreA();

    } else if(k == '3'){
        adminsMenu();

    } else{
        adminReports();
    }

}


void adminsMenu(){
    system("CLS");
    char k = '0';

    cout << endl <<"--------------------------->> Administrators Menu <<---------------------------" << endl;
    cout << endl <<"                               Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new administrator \n";
    cout << endl <<"2. ---> Manage teacher and students \n";
    cout << endl <<"3. ---> Manage semester and courses \n";
    cout << endl <<"4. ---> Manage groups \n";
    cout << endl <<"5. ---> Reports \n";
    cout << endl <<"6. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerAdmin();

    } else if(k == '2'){
        managementTS();

    } else if(k == '3'){
        managementSC();

    } else if(k == '4'){
        managementGroups();

    } else if(k == '5'){
        adminReports();

    } else if(k == '6'){
        mainMenu();

    } else{
        adminsMenu();
    }

}


void tryPassword(){
    system("CLS");
    char k = '0';

    cout << endl <<"--------------------------------------------------------------------------------------" << endl;
    cout << endl <<"********************************** Invalid password **********************************" << endl;
    cout << endl <<"--------------------------------------------------------------------------------------" << endl;
    cout << endl <<"---> Digit 1: to try again \n";
    cout << endl <<"---> Digit 2: to turn back to main menu \n";
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        login();

    } else if(k == '2'){
        mainMenu();

    } else{
        tryPassword();
    }

}


void login(){
    system("CLS");
    string password;

    cout << endl <<"--------------------------------------------------------------------------------------------" << endl;
    cout << endl <<" You have selected the administrator section, so we have to verify you are an administrator " << endl;
    cout << endl <<"--------------------------------------------------------------------------------------------" << endl;
    cout << endl <<"Please enter your password: ";
    cin >> password;

    if(searchAdmin(password) == NULL){
        tryPassword();
    } else{
        adminsMenu();
    }

}


void registerAssignment(Teacher* teacher){  //
    system("CLS");
    cout << endl <<"-------------------->> Registering a new assignment in a group <<--------------------" << endl;
    string code;
    int idG, idA;
    string kind;
    string name;
    int month, day, hour;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = ltm->tm_year + 1900;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;
    cout << endl <<"---> Enter the group's ID: ";
    cin >> idG;
    cout << endl <<"---> Enter the ID of the new assignment: ";
    cin >> idA;
    cout << endl <<"---> Enter the type (task, project, test or tour) of assignment: ";
    cin >> kind;
    cout << endl <<"---> Enter the name of the new assignment: ";
    cin >> name;
    cout << endl <<"<<----------- Now, enter the delivery date ------------>> ";
    cout << endl <<"<< The current year will be taken as the delivery year >> \n";
    cout << endl <<"---> Month (1 to 12): ";
    cin >> month;
    cout << endl <<"---> Day (1 to 31): ";
    cin >> day;
    cout << endl <<"---> Enter the delivery time (24 hour format) of the assignment: ";
    cin >> hour;

    int result = assignAssignment(teacher, code, idG, idA, kind, name, day, month, year, hour);

    if(result == 0){
        cout << endl <<"\n~ The assignment has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementAssignments(teacher);

    } else{
        cout << endl <<"\n--------------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"**************************** ERROR: The assignment type is not valid *****************************\n";
        } else if(result == 2){
            cout << endl <<"*********************** ERROR: The day or month was out of the valid range ***********************\n";
        } else if(result == 3){
            cout << endl <<"************************* ERROR: The time is not in the requested format *************************\n";
        } else if(result == 4){
            cout << endl <<"******        It was not possible to register, because that course is not registered        ******\n";
        } else if(result == 5){
            cout << endl <<"*** It was not possible to register, because that course is not taught in the current semester ***\n";
        } else if(result == 6){
            cout << endl <<"******  It was not possible to register, because the course has not registered that group   ******\n";
        } else if(result == 7){
            cout << endl <<"******     It was not possible to register, because you are not in charge of that group     ******\n";
        } else{
            cout << endl <<"******    It was not possible to register, because the assignment is already registered     ******\n";
        }

        cout << endl <<"--------------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerAssignment(teacher);

        } else{
            managementAssignments(teacher);
        }
    }
}


void modifyingAssignment(Teacher* teacher){
    system("CLS");
    cout << endl <<"---------------------------->> Modifying an assignment <<----------------------------" << endl;
    string code;
    int idG, idA;
    string kind;
    string newName;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;
    cout << endl <<"---> Enter the group's ID: ";
    cin >> idG;
    cout << endl <<"---> Enter the assignment's ID: ";
    cin >> idA;
    cout << endl <<"---> Enter the assignment's type (task, project, test or tour): ";
    cin >> kind;
    cout << endl <<"---> Enter the new name of the assignment: ";
    cin >> newName;

    int result = modifyAssignment(teacher, code, idG, idA, kind, newName);

    if(result == 0){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementAssignments(teacher);

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"*********************** ERROR: The assignment type is not valid ***********************\n";
        } else if(result == 2){
            cout << endl <<"******   It was not possible to modify, because that course is not registered    ******\n";
        } else if(result == 3){
            cout << endl <<"*** It was not possible to modify, because the course has not registered that group ***\n";
        } else if(result == 4){
            cout << endl <<"***   It was not possible to modify, because you are not in charge of that group    ***\n";
        } else {
            cout << endl <<"****** It was not possible to modify, because that assignment is not registered  ******\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingAssignment(teacher);

        } else{
            managementAssignments(teacher);
        }
    }
}


void removeAssignment(Teacher* teacher){
    system("CLS");
    cout << endl <<"---------------------->> Removing an assignment from a group <<----------------------" << endl;
    string code;
    int idG, idA;
    string kind;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;
    cout << endl <<"---> Enter the group's ID: ";
    cin >> idG;
    cout << endl <<"---> Enter the assignment's ID: ";
    cin >> idA;
    cout << endl <<"---> Enter the assignment's type (task, project, test or tour): ";
    cin >> kind;

    int result = deleteAssignment(teacher, code, idG, idA, kind);

    if(result == 0){
        cout << endl <<"\n~ The assignment has been removed from the group successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementAssignments(teacher);

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"*********************** ERROR: The assignment type is not valid ***********************\n";
        } else if(result == 2){
            cout << endl <<"******   It was not possible to remove, because that course is not registered    ******\n";
        } else if(result == 3){
            cout << endl <<"*** It was not possible to remove, because the course has not registered that group ***\n";
        } else if(result == 4){
            cout << endl <<"***   It was not possible to remove, because you are not in charge of that group    ***\n";
        } else {
            cout << endl <<"****** It was not possible to remove, because that assignment is not registered  ******\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeAssignment(teacher);

        } else{
            managementAssignments(teacher);
        }
    }
}


void managementAssignments(Teacher* teacher){
    system("CLS");
    char k = '0';

    cout << endl <<"--------------------------->> Assignments Management <<---------------------------" << endl;
    cout << endl <<"                                 Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new assignment in a group \n";
    cout << endl <<"2. ---> Modify a registered assignment \n";
    cout << endl <<"3. ---> Remove a registered assignment from a group \n";
    cout << endl <<"4. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerAssignment(teacher);

    } else if(k == '2'){
        modifyingAssignment(teacher);

    } else if(k == '3'){
        removeAssignment(teacher);

    } else if(k == '4'){
        teachersMenu(teacher);

    } else{
        managementAssignments(teacher);
    }
}


void registerTalk(Teacher* teacher){
    system("CLS");
    cout << endl <<"------------------>> Registering a new general talk in a semester <<------------------" << endl;
    int id, year, period, month, day, hour;
    string name;
    char k = '0';

    cout << endl <<"---> Enter the ID of the new talk: ";
    cin >> id;
    cout << endl <<"---> Enter the semester's year: ";
    cin >> year;
    cout << endl <<"---> Enter the semester's period: ";
    cin >> period;
    cout << endl <<"---> Enter the name of the new talk: ";
    cin >> name;
    cout << endl <<"---> Enter the month (1 to 12) in which the talk will takes place: ";
    cin >> month;
    cout << endl <<"---> Enter the day (1 to 31) in which the talk will takes place: ";
    cin >> day;
    cout << endl <<"---> Enter the start time (24 hour format) of the talk: ";
    cin >> hour;

    int result = assignTalkToSemester(id, year, period, name, month, day, hour);

    if(result == 0){
        cout << endl <<"\n~ The talk has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTalks(teacher);

    } else{
        cout << endl <<"\n--------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"*** It was not possible to register, because that semester is not registered ***\n";
        } else if(result == 2){
            cout << endl <<"************** ERROR: The day or month was out of the valid range **************\n";
        } else if(result == 3){
            cout << endl <<"********* ERROR: The month does not coincide with the semester period  *********\n";
        } else if(result == 4){
            cout << endl <<"**************** ERROR: The time is not in the requested format ****************\n";
        } else{
            cout << endl <<"*** It was not possible to register, because the talk is already registered  ***\n";
        }

        cout << endl <<"--------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            registerTalk(teacher);

        } else{
            managementTalks(teacher);
        }
    }
}


void modifyingTalk(Teacher* teacher){
    system("CLS");
    cout << endl <<"---------------------------->> Modifying a general talk <<----------------------------" << endl;
    int id, year, period;
    string newName;
    char k = '0';

    cout << endl <<"---> Enter the semester's year: ";
    cin >> year;
    cout << endl <<"---> Enter the semester's period: ";
    cin >> period;
    cout << endl <<"---> Enter the talk's ID: ";
    cin >> id;
    cout << endl <<"---> Enter the new name of the talk: ";
    cin >> newName;

    if(modifyTalk(id, newName, year, period)){
        cout << endl <<"\n~ Changes have been made successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTalks(teacher);

    } else{
        cout << endl <<"\n-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"*** It was not possible to modify, because the semester or the talk is not registered ***\n";
        cout << endl <<"-----------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            modifyingTalk(teacher);

        } else{
            managementTalks(teacher);
        }
    }
}


void removeTalk(Teacher* teacher){
    system("CLS");
    cout << endl <<"------------------------->> Removing a talk from a semester <<-------------------------" << endl;
    int id, year, period;
    char k = '0';

    cout << endl <<"---> Enter the semester's year: ";
    cin >> year;
    cout << endl <<"---> Enter the semester's period: ";
    cin >> period;
    cout << endl <<"---> Enter the talk's ID: ";
    cin >> id;

    int result = deleteTalk(id, year, period);

    if(result == 0){
        cout << endl <<"\n~ The talk has been removed from the semester successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        managementTalks(teacher);

    } else{
        cout << endl <<"\n------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******    It was not possible to remove, because that semester is not registered    ******\n";
        } else {
            cout << endl <<"*** It was not possible to remove, because that talk is not registered in the semester ***\n";
        }

        cout << endl <<"------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            removeTalk(teacher);

        } else{
            managementTalks(teacher);
        }
    }
}


void managementTalks(Teacher* teacher){
    system("CLS");
    char k = '0';

    cout << endl <<"-------------------------->> General Talks Management <<--------------------------" << endl;
    cout << endl <<"                                 Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register a new talk \n";
    cout << endl <<"2. ---> Modify a registered talk \n";
    cout << endl <<"3. ---> Remove a registered talk \n";
    cout << endl <<"4. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        registerTalk(teacher);

    } else if(k == '2'){
        modifyingTalk(teacher);

    } else if(k == '3'){
        removeTalk(teacher);

    } else if(k == '4'){
        teachersMenu(teacher);

    } else{
        managementTalks(teacher);
    }
}


void teacherReport1(){
    cout << endl <<"";

}


void teacherReport2(Teacher* teacher){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------------------>>Teacher Report 2<<-----------------------------------" << endl;

    cout<< "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Teacher ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<< "\nTeacher: " << teacher->name << endl;
    cout<< "\n--------------------------------------- Groups  ---------------------------------------\n";

    SubListGroup* groups = teacher->myGroups;

    while(groups != NULL){

        cout << "\n" << groups->course->name << " --> Group " << groups->groupId << endl;
        SubListAssignment*auxTasks = groups->tasks;
        cout<< "\n--------------------------------------- Tasks  ---------------------------------------\n";
        if(auxTasks == NULL){
            cout<< "\nNot founds" << endl;
        }
        while(auxTasks != NULL){
            cout<< "\nName: " << auxTasks->name << " --> Id " << auxTasks->id << endl;
            cout << "\nDate: " << auxTasks->day << "/" << auxTasks->month << "/" << auxTasks->year << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            auxTasks= auxTasks->next;
        }

        SubListAssignment*auxTest = groups->tests;
        cout<< "\n--------------------------------------- Tests  ---------------------------------------\n";
        if(auxTest == NULL){
            cout<< "\nNot founds" << endl;
        }
        while(auxTest != NULL){
            cout << "\nName: " << auxTest->name << " --> Id " << auxTest->id << endl;
            cout << "\nDate: " << auxTest->day << "/" << auxTest->month << "/" << auxTest->year << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            auxTest= auxTest->next;
        }

        SubListAssignment*auxProjects = groups->projects;
        cout<< "\n--------------------------------------- Projects  ---------------------------------------\n";
        if(auxProjects == NULL){
            cout<< "\nNot founds" << endl;
        }
        while(auxProjects != NULL){
            cout << "\nName: " << auxProjects->name << " --> Id " << auxProjects->id << endl;
            cout << "\nDate: " << auxProjects->day << "/" << auxProjects->month << "/" << auxProjects->year << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            auxProjects= auxProjects->next;
        }


        SubListAssignment*auxTours = groups->tours;
        cout<< "\n--------------------------------------- Tours  ---------------------------------------\n";
        if(auxTours == NULL){
            cout<< "\nNot founds" << endl;
        }
        while(auxTours != NULL){
            cout << "\nName: " << auxTours->name << " --> Id " << auxTours->id << endl;
            cout << "\nDate: " << auxTours->day << "/" << auxTours->month << "/" << auxTours->year << endl;
            cout << "\n--------------------------------------------------------------------------------------" << endl;
            auxTours= auxTours->next;
        }

        cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        groups = groups->next;
    }

    cout << endl << " Press any key to back reports: ";
    cin >> k;

    teacherReports(teacher);


}


void teacherReport3(){
    cout << endl <<"";

}


void teacherReport4(Teacher* teacher){

    system("CLS");
    char k = '0';
    int id, year, period;

    cout << endl <<"------------------------------------>>Teacher Report 4<<-----------------------------------" << endl;


    cout << endl <<"---> Enter the current semester year: ";
    cin >> year;
    cout << endl <<"---> Enter the current semester period: ";
    cin >> period;

    Semester*aS = searchSemester(year, period);

    if(aS == NULL){
        cout << endl <<"\n--------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"******    It was not possible to report, because that semester is not registered    ******\n";
        cout << endl <<"--------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            teacherReport4(teacher);
        }
        else{
            teacherReports(teacher)
        }
    }
    else{

    }
}

void teacherReport5(){
    cout << endl <<"";

}


void teacherReport6(){
    cout << endl <<"";

}


void teacherReports(Teacher* teacher){
    system("CLS");
    char k = '0';

    cout << endl <<"----------------------------------->> Teacher Reports <<-----------------------------------" << endl;
    cout << endl <<"                                     Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Report 1 \n";
    cout << endl <<"2. ---> Report 2 \n";
    cout << endl <<"3. ---> Report 3 \n";
    cout << endl <<"4. ---> Report 4 \n";
    cout << endl <<"5. ---> Report 5 \n";
    cout << endl <<"6. ---> Report 6 \n";
    cout << endl <<"7. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        teacherReport1();

    } else if(k == '2'){
        teacherReport2(teacher);

    } else if(k == '3'){
        teacherReport3();

    } else if(k == '4'){
        teacherReport4();

    } else if(k == '5'){
        teacherReport5();

    } else if(k == '6'){
        teacherReport6();

    } else if(k == '7'){
        teachersMenu(teacher);

    } else{
        teacherReports(teacher);
    }
}


void teachersMenu(Teacher* teacher){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------------>> Teacher Menu <<------------------------------" << endl;
    cout << endl <<"                               Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Manage assignments \n";
    cout << endl <<"2. ---> Manage talks \n";
    cout << endl <<"3. ---> Reports \n";
    cout << endl <<"4. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        managementAssignments(teacher);

    } else if(k == '2'){
        managementTalks(teacher);

    } else if(k == '3'){
        teacherReports(teacher);

    } else if(k == '4'){
        usersMenu();

    } else{
        teachersMenu(teacher);
    }

}


void completeAssignment(Student* student){ //
    system("CLS");
    cout << endl <<"--------------------->> Registering an assignment as completed <<---------------------" << endl;
    string code;
    int idG, idA;
    string kind;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = ltm->tm_year + 1900;
    int month = ltm->tm_mon + 1;
    int day = ltm->tm_mday;
    int hour = ltm->tm_hour;
    char k = '0';

    cout << endl <<"---> Enter the course's code: ";
    cin >> code;
    cout << endl <<"---> Enter the group's ID: ";
    cin >> idG;
    cout << endl <<"---> Enter the assignment's ID: ";
    cin >> idA;
    cout << endl <<"---> Enter the assignment's type (task, project, test or tour): ";
    cin >> kind;

    int result = registerCoAssignment(student, code, idG, idA, kind, year, month, day, hour);

    if(result == 0){
        cout << endl <<"\n~ You have registered the assignment as completed successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        studentsMenu(student);

    } else{
        cout << endl <<"\n---------------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"***************************** ERROR: The assignment type is not valid *****************************\n";
        } else if(result == 2){
            cout << endl <<"******        It was not possible to register, because that course is not registered         ******\n";
        } else if(result == 3){
            cout << endl <<"*** It was not possible to register, because that course is not taught in the current semester  ***\n";
        } else if(result == 4){
            cout << endl <<"***      It was not possible to register, because the course has not registered that group      ***\n";
        } else if(result == 5){
            cout << endl <<"******          It was not possible to register, because you are not in that group           ******\n";
        } else if(result == 6){
            cout << endl <<"***   It was not possible to register, because that assignment is not registered in the group   ***\n";
        } else{
            cout << endl <<"*** It was not possible to register, because you already registered the assignment as completed ***\n";
        }

        cout << endl <<"---------------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            completeAssignment(student);

        } else{
            studentsMenu(student);
        }
    }
}


void attendTalk(Student* student){
    system("CLS");
    cout << endl <<"-------------------->> Registering attendance at a general talk <<--------------------" << endl;
    int id, year, period;
    char k = '0';

    cout << endl <<"---> Enter the talk's ID: ";
    cin >> id;
    cout << endl <<"---> Enter the current semester year: ";
    cin >> year;
    cout << endl <<"---> Enter the current semester period: ";
    cin >> period;

    int result = registerAtteTalk(student, id, year, period);

    if(result == 0){
        cout << endl <<"\n~ Your attendance to the talk has been registered successfully! \n";
        cout << endl <<"~ Press any key to continue: ";
        cin >> k;
        studentsMenu(student);

    } else{
        cout << endl <<"\n--------------------------------------------------------------------------------------------" << endl;

        if(result == 1){
            cout << endl <<"******    It was not possible to register, because that semester is not registered    ******\n";
        } else if(result == 2){
            cout << endl <<"*** It was not possible to register, because that talk is not registered in the semester ***\n";
        } else{
            cout << endl <<"*** It was not possible to register, because you already registered the talk as attended ***\n";
        }

        cout << endl <<"--------------------------------------------------------------------------------------------" << endl;
        cout << endl <<"---> Digit 1: to try again \n";
        cout << endl <<"---> Press a different key to turn back \n";
        cout << endl <<"Option: ";
        cin >> k;

        if(k == '1'){
            attendTalk(student);

        } else{
            studentsMenu(student);
        }
    }
}


void showCrashes(Student* student){
    cout << endl <<"";

}


void studentsMenu(Student* student){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------------>> Student Menu <<------------------------------" << endl;
    cout << endl <<"                               Select an option \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Register completed assignment \n";
    cout << endl <<"2. ---> Register attended talk \n";
    cout << endl <<"3. ---> Consult the scheduled assignments by week x, to identify crashes \n";
    cout << endl <<"4. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        completeAssignment(student);

    } else if(k == '2'){
        attendTalk(student);

    } else if(k == '3'){
        showCrashes(student);

    } else if(k == '4'){
        usersMenu();

    } else{
        studentsMenu(student);
    }

}


void tryIdOrSc(int section){
    system("CLS");
    char k = '0';

    cout << endl <<"---------------------------------------------------------------------------------------" << endl;
    if(section == 1){
        cout << endl <<"********************************** Teacher not found **********************************" << endl;

    } else{
        cout << endl <<"********************************** Student not found **********************************" << endl;
    }
    cout << endl <<"---------------------------------------------------------------------------------------" << endl;

    cout << endl <<"---> Digit 1: to try again \n";
    cout << endl <<"---> Digit 2: to turn back to users menu \n";
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        usersLogin(section);

    } else if(k == '2'){
        usersMenu();

    } else{
        tryIdOrSc(section);
    }
}


void usersLogin(int section){
    system("CLS");
    int id;

    cout << endl <<"-------------------------------------------------------------------------------" << endl;
    if(section == 1){
        cout << endl <<" You have selected the teacher section, so we have to verify you are a teacher " << endl;

    } else{
        cout << endl <<" You have selected the student section, so we have to verify you are a student " << endl;
    }
    cout << endl <<"-------------------------------------------------------------------------------" << endl;

    if(section == 1){
        cout << endl <<"Please enter your identification: ";

    } else{
        cout << endl <<"Please enter your student card: ";
    }

    cin >> id;

    if(section == 1){
        Teacher* teacher = searchTeacher(id);
        if(teacher == NULL){
            tryIdOrSc(1);
        } else{
            teachersMenu(teacher);
        }

    } else{
        Student* student = searchStudent(id);
        if(student == NULL){
            tryIdOrSc(2);
        } else{
            studentsMenu(student);
        }

    }
}


void usersMenu(){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------------->> Users Menu <<-------------------------------" << endl;
    cout << endl <<"                              Select one section \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Teachers \n";
    cout << endl <<"2. ---> Students \n";
    cout << endl <<"3. ---> Turn back \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        usersLogin(1);

    } else if(k == '2'){
        usersLogin(2);

    } else if(k == '3'){
        mainMenu();

    } else{
        usersMenu();
    }

}


void mainMenu(){
    system("CLS");
    char k = '0';

    cout << endl <<"------------------------------->> Main Menu <<-------------------------------" << endl;
    cout << endl <<"                             Select one section \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"1. ---> Administrators \n";
    cout << endl <<"2. ---> Users \n";
    cout << endl <<"3. ---> Exit \n";
    cout << endl <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl <<"Option: ";
    cin >> k;

    if(k == '1'){
        login();

    } else if(k == '2'){
        usersMenu();

    } else if(k == '3'){
        system("CLS");
        return;

    } else{
        mainMenu();
    }

}


int main(){
    loadData();
    mainMenu();

/*
    showAdmins();
    showTeachers();
    showStudents();
    showSemesters();
    showCourses();

    showCoursesGroups();
    showTeachersGroups();
    showStudentsGroups();
    showCoursesSemesters(); */

    //deleteTeacherGroup(50, "IC2001", 208310022);
    //showTeachersGroups();

    //deleteStudentGroup(50, "IC2001", 20201101);
    //deleteStudentGroup(50, "IC2001", 20211909);
    //showStudentsGroups();

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
