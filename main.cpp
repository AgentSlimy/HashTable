#include <iostream>
#include <cstring>

using namespace std;

struct Student {
  char firstName[51];
  char lastName[51];
  float GPA;
  int ID;
  stud* next;
  stud* prev;
}

int main() {
  bool running = true;
  char command[10];
  cout << "Hash Table for Student List" << endl << endl;
  
  while (running == true) {
    cout << "Options: ADD, PRINT, DELETE, QUIT" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    
    if (strcmp(command, "ADD") == 0 || strcmp(command, "Add") == 0) {
      cout << "add" << endl;
    }
    else if (strcmp(command, "PRINT") == 0 || strcmp(command, "Print") == 0) {
      cout << "print" << endl;
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
