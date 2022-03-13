//Author: Nathan Zou
//Date: 3/13/22
//Student List using a hash table
//Done with help from Chris Zou and Stefan Ene
/* Online Resources Used:
        https://www.cplusplus.com/reference/fstream/fstream/
        https://www.geeksforgeeks.org/c-program-hashing-chaining/
        https://www.geeksforgeeks.org/hashing-set-2-separate-chaining/
        https://www.journaldev.com/35238/hash-table-in-c-plus-plus
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <time.h>

using namespace std;

struct student {
    char firstName[51];
    char lastName[51];
    float GPA;
    int ID;
    student* next;
    student* prev;
};

void ADD(student** list, student* newStudent, int size);
void PRINT(student** list, int size);
void DELETE(student** list, int ID, int size);
bool checkCollision(student** list, int size);

int main() {
    bool running = true;
    char command[10];
    int randomID = 0;
    srand(time(NULL));
    randomID = rand() % 999999 + 1; //generates random ID value
    student** list = new student * [100];
    int size = 100;
    cout << "Hash Table for Student List" << endl << endl;
    while (running == true) {
        cout << "Options: ADD, ADDRAND, PRINT, DELETE, QUIT" << endl;
        cin.get(command, 10);
        cin.clear();
        cin.ignore(10000, '\n');
        if (strcmp(command, "ADD") == 0 || strcmp(command, "Add") == 0) { //Add a student manually
            cout << endl << "Manually Adding New Student" << endl << endl;
            student* newStudent = new student();
            newStudent->next = NULL;
            newStudent->prev = NULL;
            cout << "Enter Students First Name: ";
            cin >> newStudent->firstName;
            cin.clear();
            cin.ignore(51, '\n');
            cout << "Enter Students Last Name: ";
            cin >> newStudent->lastName;
            cin.clear();
            cin.ignore(51, '\n');
            cout << "Enter Students ID Number: ";
            cin >> newStudent->ID;
            cin.clear();
            cin.ignore(51, '\n');
            cout << "Enter Students GPA: ";
            cin >> newStudent->GPA;
            cin.clear();
            cin.ignore(51, '\n');
            ADD(list, newStudent, size);
            cout << "Student Added." << endl << endl;
            //Balance if there is collision
            if (checkCollision(list, size)) {
                cout << endl << "Rehashing Hash Table" << endl;
                student** temp = new student * [size]; //create temp array
                for (int i = 0; i < size; i++) {
                    temp[i] = list[i];
                }
                int newSize = 2 * size;
                list = new student * [newSize]; //recreate list to double
                for (int i = 0; i < newSize; i++) {
                    list[i] = NULL;
                }
                //re-add all students to the newly sized list
                for (int i = 0; i < size; i++) {
                    if (temp[i] != NULL) {
                        student* move = temp[i];
                        if (move->next != NULL) {
                            student* newNext = move->next;
                            move->next = NULL;
                            newNext->prev = NULL;
                            ADD(list, newNext, newSize);
                            if (newNext->next != NULL) {
                                student* newNextTwo = newNext->next;
                                newNext->next = NULL;
                                newNextTwo->prev = NULL;
                                ADD(list, newNextTwo, newSize);
                            }
                        }
                        ADD(list, move, newSize);
                    }
                }
                delete[] temp;
                size = newSize;
            }
        }
        else if (strcmp(command, "ADDRAND") == 0 || strcmp(command, "Addrand") == 0) {
            int num;
            char** firstname = new char* [20];
            char** lastname = new char* [20];
            for (int i = 0; i < 20; i++) {
                firstname[i] = new char[51];
                lastname[i] = new char[51];
            }
            cout << endl << "Number of students to add: ";
            cin >> num;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl;
            ifstream myfile("firstNames.txt");
            int lineNum = 0;
            char first[51];
            while (lineNum < 20) {
                myfile.getline(first, 51);
                strcpy(firstname[lineNum], first);
                lineNum++;
            }
            ifstream myfile1("lastNames.txt");
            char last[51];
            lineNum = 0;
            while (lineNum < 20) {
                myfile1.getline(last, 51);
                strcpy(lastname[lineNum], last);
                lineNum++;
            }
            while (num > 0) {
                student* newStudent = new student();
                int randomFirst = rand() % 19;
                int randomLast = rand() % 19;
                strcpy(newStudent->firstName, firstname[randomFirst]);
                strcpy(newStudent->lastName, lastname[randomLast]);
                newStudent->ID = randomID;
                newStudent->GPA = (float)rand() / (RAND_MAX) * 5;
                randomID = randomID + 100;
                ADD(list, newStudent, size);

                if (checkCollision(list, size)) {
                    cout << endl << "Rehashing Hash Table" << endl;
                    student** temp = new student * [size];
                    for (int i = 0; i < size; i++) {
                        temp[i] = list[i];
                    }
                    int newSize = 2 * size;
                    list = new student * [newSize];
                    for (int i = 0; i < newSize; i++) {
                        list[i] = NULL;
                    }
                    for (int i = 0; i < size; i++) {
                        if (temp[i] != NULL) {
                            student* move = temp[i];
                            if (move->next != NULL) {
                                student* newNext = move->next;
                                move->next = NULL;
                                newNext->prev = NULL;
                                ADD(list, newNext, newSize);
                                if (newNext->next != NULL) {
                                    student* newNextTwo = newNext->next;
                                    newNext->next = NULL;
                                    newNextTwo->prev = NULL;
                                    ADD(list, newNextTwo, newSize);
                                }
                            }
                            ADD(list, move, newSize);
                        }
                    }
                    delete[] temp;
                    size = newSize;
                }
                num--;
            }
        }
        else if (strcmp(command, "PRINT") == 0 || strcmp(command, "Print") == 0) {
            PRINT(list, size);
            cout << endl;
        }
        else if (strcmp(command, "DELETE") == 0 || strcmp(command, "Delete") == 0) { //Delete command, with delete a student by ID number, if there is multiple students with the same number, the first will be deleted
            cout << "Input the ID of the student you wish to delete from the list: ";
            int input;
            cin >> input;
            cin.clear();
            cin.ignore(10000, '\n');
            DELETE(list, input, size);
        }
        else if (strcmp(command, "QUIT") == 0 || strcmp(command, "Quit") == 0) { //Quit command, leaves program/ends program
            cout << "Quitting Hash Table." << endl;
            running = false;
        }
        else {
            cout << "Invalid input, try again." << endl << endl;
        }
    }
}

void ADD(student** list, student* newStudent, int size) { //Add function, used to manually add students in
    int index = (newStudent->ID) % size;
    //Puts new student in current array
    if (list[index] == NULL) {
        //No collision, add to list
        list[index] = newStudent;
    }
    else {
        //Collision, add as the next pointer
        if ((list[index])->next == NULL) {
            //No previous collisions
            (list[index])->next = newStudent;
            (list[index]->next)->prev = (list[index])->next;
        }
        else {
            //Already a collision there
            ((list[index])->next)->next = newStudent;
            (((list[index])->next)->next)->prev = ((list[index])->next)->next;
        }
    }
}

void PRINT(student** list, int size) { //Print function, prints out all students in the table with their associated ID numbers and GPA
    for (int i = 0; i < size; i++) {
        student* current = list[i];
        if (current != NULL) {
            cout << current->firstName << " ";
            cout << current->lastName << " ";
            cout << "#" << current->ID << " GPA: ";
            cout << fixed << setprecision(2) << current->GPA << endl;
            student* next = current->next;
            if (next != NULL) {
                cout << '\t' << next->firstName << " ";
                cout << next->lastName << " ";
                cout << "#" << next->ID << " GPA: ";
                cout << fixed << setprecision(2) << next->GPA << endl;
            }
        }
    }
}

void DELETE(student** list, int ID, int size) { //Delete functions, deletes students from table by taking ID number
    int x = ID % size;
    if (list[x] == NULL) {
        cout << endl << "No such student." << endl;
    }
    else {
        if (list[x]->ID == ID) {
            //if ID found, delete
            if (list[x]->next == NULL) {
                list[x] = NULL;
            }
            else {
                //replace with next in collision
                student* newCurrent = list[x]->next;
                newCurrent->prev = NULL;
                list[x] = newCurrent;
            }
        }
        else {
            if (list[x]->next == NULL) {
                cout << endl << "No such student." << endl;
            }
            else {
                if (list[x]->next->ID == ID) {
                    //if found, then delete
                    list[x]->next = NULL;
                }
                else {
                    cout << "No such student." << endl;
                }
            }
        }
    }
}

bool checkCollision(student** list, int size) { //checkCollision function, checks that there are not two different values at a given location in the table
    bool newList = false; //True if there is a need to make a new list
    int CC = 0;
    while (newList == false && CC < size) {
        if (list[CC] != NULL) {
            if ((list[CC])->next != NULL) {
                if (((list[CC])->next)->next != NULL) {
                    newList = true;
                }
            }
        }
        CC++;
    }
    return newList;
}
