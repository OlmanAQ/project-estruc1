#include <iostream>

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
    Semester* next;      // Link to the next node (Semester) in the list
    Semester* previous;  // Link to the previous node (Semester) in the list
    struct SubListCourse* myCourses;  // Link to the courses that are offered in that semester
    struct SubListTalks* myTalks;     // Link to the general talks that take place in that semester

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


struct SubListAssignment{  // Work in progress
    int id;
    int percentage;
    string name;
    string kind;
    //bool status; ?
    //Date
    SubListAssignment* next;  // Link to the next node (Assignment) in the Sub-list

    //Constructor

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


struct SubListTalk{  // Work in progress
    string name;
    //bool status; ?
    //Date
    SubListTalk* next;  // Link to the next node (Talk) in the Sub-list

    //Constructor

};  // There is no "first" as such, since it is a Sub-list


struct SubListCourse{
    SubListCourse* next;  // Link to the next node (Course) in the Sub-list
    Course* enC;       // Link to the corresponding course

    SubListCourse(Course* c){
        next = NULL;
        enC = c;
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


bool insertSemester( int period, int year){  // Method that inserts a new student in the "Semester" list (ordered insertion)

    if(firstSemester == NULL){       // If the list is empty, then the new node is created and it becomes the first one
        Semester* newSemester = new Semester(period,year);
        firstSemester = newSemester;  // The first node is updated
        return true;
    }

    if(searchSemester(year, period) != NULL){  // If the given "year and period" is repeated (that semester is already registered), the insertion can't be performed
        return false;                        // So, "false" is returned
    }

    Semester* newSemester = new Semester(period, year);  // The new node (Semester) is created

    if(year <= firstSemester->year && period < firstSemester->period ){  // Case #1: the year and period of the new semester are the lowest

        newSemester->next = firstSemester;          // So, the new semester is inserted at the beginning of the list
        firstSemester->previous =newSemester;
        firstSemester = newSemester;                // The first node is updated
        return true;
    }

    Semester* nextAux = firstSemester->next;  // Auxiliary variable that will be useful in order to tour the list
    Semester* preAux = firstSemester;     // Auxiliary variable that will be useful in order to place the new student in the proper position

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
    preAux->next = newSemester;  // So, the new student is inserted at the end of the list
    newSemester->previous =preAux;
    return true;
}


bool modifySemester(int y, int p, int np){  // Falta documentar (Olman)
    Semester* aux = searchSemester(y,p);  // The teacher is searched using the "searchTeacher" method

    if(aux != NULL){
        aux->period = np;   // If the teacher is registered, then his information is modified
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

SubListCourse* searchCourSe(Course * auxC, Semester * auxS){


    if(auxS->myCourses == NULL){
        return NULL;
    }

    SubListCourse*auxLC = auxS->myCourses;


    if(auxLC->enC->code == auxC->code){
        return auxLC;
    }


    while(auxLC != NULL){
        if(auxLC->enC->code == auxC->code){
            return auxLC;
        }
        auxLC= auxLC->next;
    }
    return NULL;
}



bool courseSemester(int yeard, int period, string code){

    Course* auxCource = searchCourse(code);
    Semester* auxSemester = searchSemester(yeard, period);

    if((auxSemester == NULL) || (auxCource == NULL)){
        return false;
    }
    SubListCourse*auxL = searchCourSe(auxCource, auxSemester);
    if(auxL != NULL){
        return false;
    }


    SubListCourse*sbC = new SubListCourse(auxCource);
    sbC->next = auxSemester->myCourses;
    auxSemester->myCourses = sbC;

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

    insertSemester(1,2020);
    insertSemester(1,2021);
    insertSemester(1,2022);
    insertSemester(2,2020);
    insertSemester(2,2021);
    insertSemester(2,2022);

    insertCourse("Data structures", "IC2001", 4);
    insertCourse("Object-oriented programming", "IC2101", 4);
    insertCourse("Algebra", "MA1103", 4);
    insertCourse("English", "CI1230", 3);
    insertCourse("Oral communication", "CI1107", 2);

    assignGroupToCourse(50, "IC2001");  // Data structures
    assignGroupToCourse(51, "IC2001");  // Data structures
    assignGroupToCourse(52, "MA1103");  // Algebra
    assignGroupToCourse(51, "MA1103");  // Algebra
    assignGroupToCourse(47, "CI1230");  // English
    assignGroupToCourse(48, "CI1230");  // English
    assignGroupToCourse(51, "IC2101");  // Object-oriented programming
    assignGroupToCourse(50, "IC2101");  // Object-oriented programming
    assignGroupToCourse(10, "CI1107");  // Oral communication
    assignGroupToCourse(11, "CI1107");  // Oral communication

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



    assignCourseToSemester(2020, 1, "IC2001");
    assignCourseToSemester(2020, 1, "IC2001");
    assignCourseToSemester(2020, 10, "IC2001");
    assignCourseToSemester(2020, 1, "MA1103");
    assignCourseToSemester(2020, 2, "IC2001");
    assignCourseToSemester(2020, 2, "IC2101");
    assignCourseToSemester(2021, 1, "IC2001");
    assignCourseToSemester(2021, 2, "IC2001");
    assignCourseToSemester(2022, 1, "IC2001");
    assignCourseToSemester(2022, 2, "IC2001");
    assignCourseToSemester(2022, 2, "CI1107");
    assignCourseToSemester(2022, 2, "CI1230");


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


void showCourseSemester(){
    cout<<"\n~~~~~~~~ Showing Courses in Semester ~~~~~~~~\n";

    Semester* auxS = firstSemester;

    while(auxS != NULL){

        cout << "\nYeard: " << auxS->year << endl;
        cout << "\nPeriod: " << auxS->period << endl;
        cout << "\n--------------------------------------------------------------------------------------" << endl;



    if(auxS != NULL & auxS->myCourses != NULL){

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




int main(){
    loadData();




    showAdmins();
    showTeachers();
    showStudents();

    showSemesters();
    showCourses();


    showCoursesGroups();
    showTeachersGroups();
    showStudentsGroups();
    showCourseSemester();

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
