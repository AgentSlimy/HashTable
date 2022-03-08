#include <iostream>
#include <cstring>
#include <iomanip>

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
void DELETE();
bool checkCollision();

int main() {
  bool running = true;
  char command[10];
  int randomID = 6;
  int TS = 0; //Number of times "ADD" has been used
  student** list = new student*[100];
  int size = 100;
  cout << "Hash Table for Student List" << endl << endl;
  while (running == true) {
    cout << "Options: ADD, ADDRAND, PRINT, DELETE, QUIT" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    
    if (strcmp(command, "ADD") == 0 || strcmp(command, "Add") == 0) {
      cout << endl << "Manually Adding New Student" << endl << endl;
      TS++;
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
    }
    else if (strcmp(command, "ADDRAND") == 0 || strcmp(command, "Addrand") == 0) {
      cout << "add rand" << endl;
    }
    else if (strcmp(command, "PRINT") == 0 || strcmp(command, "Print") == 0) {
      if (TS == 0) {
	cout << "Table is EMPTY, add some students first." << endl << endl;
      }
      else {
	cout << endl;
	PRINT(list, size);
	cout << endl;
      }
    }
    else if (strcmp(command, "DELETE") == 0 || strcmp(command, "Delete") == 0) {
      cout << "delete" << endl;
    }
    else if (strcmp(command, "QUIT") == 0 || strcmp(command, "Quit") == 0) {
      cout << "Quitting Hash Table." << endl;
      running = false;
    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}

void ADD(student** list, student* newStudent, int size) {
  int index = (newStudent->ID) % size;
  if (list[index] == NULL) {
    list[index] = newStudent;
  }
  else {
    if ((list[index])->next == NULL) {
      (list[index])->next = newStudent;
      (list[index]->next)->prev = (list[index])->next;
    }
    else {
      ((list[index])->next)->next = newStudent;
      (((list[index])->next)->next)->prev = ((list[index])->next)->next;
    }
  }
}

void PRINT(student** list, int size) {
  for (int i = 0; i < size; i++) {
    student* current = list[i];
    if (current != NULL) {
      cout << current->firstName << " " << current->lastName << " ";
      cout << "#" << current->ID << " GPA: " << fixed << setprecision(2) << current->GPA << endl;
      student* next = current->next;
      if (next != NULL) {
	cout << '\t' << next->firstName << " " << next->lastName << " ";
	cout << "#" << next->ID << " GPA: " << fixed << setprecision(2) << next->GPA << endl;
      }
      cout << endl;
    }
  }
}

void DELETE() {

}

//bool checkCollition() {}
