#include<iostream>
#include<string>
#include <stdlib.h>    

using namespace std;
const int numberOfApproriate = 3;
string days[] = {"Sun","Mon","Tue","Wed","Thu"};
string times[] = {"0am","1am","2am","3am","4am","5am","6am","7am","8am","9am","10am","11am","12am","1pm","2pm","3pm","4pm","5pm","6pm","7pm","8pm","9pm","10pm","11pm","12pm"};
struct Node {
  int day;
  int time;
  int id;
  string name;
  Node * next;
  Node * prev;
};
class doctor_clinic {
  public:
    doctor_clinic() {
      head = tail = NULL;
    }
  int AddAtEnd(int day, int time, string name) {
    Node * newNode = new Node();
    newNode -> prev = NULL;
    newNode -> next = NULL;
    newNode -> day = day;
    newNode -> id = generateId();
    newNode -> name = name;
    newNode -> time = time;
    if (tail == NULL) {
      head = tail = newNode;
      return newNode -> id;
    }
    newNode -> prev = tail;
    tail -> next = newNode;
    tail = newNode;
    return newNode -> id;
  }
  void findAllowTime(int day, bool * arr) {
    if (head == NULL)
      return;
    Node * ptr = head;
    while (ptr != NULL) {
      if (ptr -> day == day)
        arr[ptr -> time] = false;
      ptr = ptr -> next;
    }
  }
  void deleteFromBegining() {
    Node * w = head;
    if (head == NULL) {
      cout << "List is empty" << endl;
      return;
    }
    if (head -> next != NULL) {
      head = head -> next;
      head -> prev = NULL;
    } else {
      head = tail = NULL;
    }
    delete w;
  }
  void deleteFromEnd() {
    Node * w = tail;
    if (tail == NULL) {
      cout << "List is empty" << endl;
      return;
    }
    if (tail -> prev != NULL) {
      tail = tail -> prev;
      tail -> next = NULL;
    } else {
      head = tail = NULL;
    }
    delete w;
  }
  void deleteNode(Node * ptr, int id) {
    if (head == NULL)
      return;
    if (head == ptr) {
      deleteFromBegining();
      return;
    }
    if (tail == ptr) {
      deleteFromEnd();
      return;
    }
    ptr -> next -> prev = ptr -> prev;
    ptr -> prev -> next = ptr -> next;
    delete ptr;
  }
  bool showReservation(int id) {
    if (head == NULL) {
      return false;
    }
    Node * ptr = head;
    while (ptr != NULL) {
      if (ptr -> id == id) {
        cout << "Hello, " << ptr -> name << endl;
        cout << "Your reservation is on " << days[ptr -> day] << " at " << times[ptr -> time] << endl;
        cout << "Do you want to cancel it? (Yes/No):";
        string answer = "";
        cin >> answer;
        if (answer == "Yes" || answer == "yes" ) {
          deleteNode(ptr, id);
          cout << "Your reservation is cancelled" << endl;
        }
        cout << "Thank you" << endl;
        return true;
      }
      ptr = ptr -> next;
    }
    return false;
  }
  int generateId() {
    int id = rand() % 10000;
    return id;
  }
  private:
    Node * head, * tail;
};
int main() {
  srand(43);
  doctor_clinic DLL;
  int operation;
  do {
    cout << endl << endl;
    cout << "\t\t***********************************************************************" << endl;
    cout << "\t\t*        Welcome to Palestine Clinic Program                          *" << endl;
    cout << "\t\t*        Made By Mai Hashlamoon  and  Nadeen Jubeh                    *" << endl;
    cout << "\t\t***********************************************************************" << endl;
    cout << "Hello, if you wish to make a reservation, please press 1.\nIf you wish to ask about your reservation, please press 2: ";
    cin >> operation;
    switch (operation) {
    case 1: {
      int day, time;
      string name;
      cout << "Please select a day (1-Sun, 2-Mon, 3-Tue, 4-Wed, 5-Thu): ";
      cin >> day;
      day--;
      cout << "On " << days[day] << " ";
      bool avalialbeTime[24] = {1,1,1,1,1,1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
      DLL.findAllowTime(day, avalialbeTime);
      int counter = 0;
      string message = "";
      int start = 10;
	  /*
	  *By default all days from 10 to 12 expect thu which is from 4pm to 8pm 
	  *Clock 24h so we add 12 hours in pm case.
	  */
      int end = 12;
      if (day == 4) {
        start = 16;
        end = 20;
      }
      for (int i = start; i <= end; i++) {
        if (avalialbeTime[i] == true) {
			//If counter not zero add 'or' word
          if (counter) {
            message += (" or " + times[i]);
          } else
            message += times[i];
          counter++;
        }
      }
      if (counter == 0) {
        cout << "No slots available" << endl;
        break;
      }
      cout << message << endl;
      cout << "Please enter the time: ";
      cin >> time;
      if (day == 4) {
        time += 12;
        if (time > 20 || time < 16 || !avalialbeTime[time]) {
          cout << "This slot is not available" << endl;
          break;
        }
      } else {
        if (time > 12 || time < 10 || !avalialbeTime[time]) {
          cout << "This slot is not available" << endl;
          break;
        }
      }
      cout << "Please enter your name: ";
      getline(cin, name);
      getline(cin, name);
      int id = DLL.AddAtEnd(day, time, name);
      cout << "Thank you for making the reservation. Your id is " << id << endl;
      break;
    }
    case 2: {
      cout << "Please enter your reservation number:" << endl;
      int id;
      cin >> id;
      bool ok = DLL.showReservation(id);
      if (!ok) {
        cout << "This number is wrong" << endl;
      }
      break;
    }
    default:
      cout << "Invalid input" << endl;
    }

  } while (operation != 3);

  system("pause");
  return 0;
}
