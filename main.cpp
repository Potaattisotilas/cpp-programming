#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int id;

// create custom type todo which has two fields, id and mission
struct todo {
int id;
string task;
};

// this method will add a new mission to the list
void addtodo() {
    system("cls");
    cout<< "Mission manager \n";
    todo todo;
    cout << "Add a new mission: \n";
    cin.get();
    getline(cin, todo.task); // getting the input
    id++; // adding id

    // write new mission to todo.txt file
    ofstream write;
    write.open("todo.txt", ios::app);
    write << "\n" << id;
    write<< "\n" << todo.task;
    write.close();

    // write id to new file so the id can be used to add new mission
    write.open("id.txt");
    write << id;
    write.close();

    char ch;
    cout << "Want to add a another new mission? (y/n) \n";
    cin >> ch;

    if (ch == 'y') {
        addtodo();
    }
    else {
        cout << "A new mission has been added \n";
        return;
    }
}

void print(todo s) {
    cout << "Id is : \n" << s.id;
    cout << "Mission is: \n" << s.task; 
}

// reading data
void readData() {
    system("cls");
    cout << "Mission manager \n";
    todo todo;
    ifstream read;
    read.open("todo.txt");
    cout << " List of missions \n";
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }
    read.close();

}

// searching a specific mission
int searchData() {
    system("cls");
    cout << "Mission manager \n";
    int id;
    cout << "Enter missions id \n";
    cin >> id;
    todo todo;
    ifstream read;
    read.open ("todo.txt");
    while (!read.eof()) {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id) {
            print (todo);
            return id;
        }
    }
}

// deleting mission from todo.txt file
void deleteData () {
    system("cls");
    cout << "Mission Manager \n";
    int od = searchData();
    cout << "Deleting mission? (y/n) \n";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id ) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename ("temp.txt", "todo.txt");
        cout << "\n Mission deleted \n";
    }
    else {
        cout << "Mission not deleted \n";
    }
}

//this method is used to update the task
//here we create a new temp.txt file and add all the updated data to this file
//once updated we then delete the original todo.txt and th
void updateData() {
    system("cls");
    cout << "Mission manager \n";
    int id = searchData();
    cout << "Do you want to update this mission? (y/n) \n";
    char choice;
    cin >> choice;
    if (choice == 'Y') {
        todo newData;
        cout  << "Enter mission to do: \n";
        cin.get();
        getline(cin, newData.task);
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
            else {
                tempFile << "\n"<< todo.id;
                tempFile << "\n"<< newData.task;
            }
        }
         read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n Mission updated \n";
    }
    else {
        cout << "\n Mission not deleted \n";
    }
}
int main() {
    system("cls");
	system("Color E0"); // "Color XY", X - backgroung color, Y - text color
    system("title todoapp @copyassignment");
    cout <<  "Mission manager \n";
    ifstream read;
    read.open("id.txt");
    if (!read.fail()) {
        read >> id;
    }
    else {
        id = 0;
    }
    read.close();

    while (true) {
        cout<<endl<<endl;
        cout << "\n\t1.Add data";
        cout << "\n\t2.See data";
        cout << "\n\t3.Search data";
        cout << "\n\t4.Delete data";
        cout << "\n\t5.Update data";

        int choice;
        cout << "\n\tEnter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addtodo();
            break;
        case 2:
            readData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            updateData();
            break;
        }
    }
}