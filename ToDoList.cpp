#include <bits/stdc++.h>
using namespace std;

int ID = 0;

struct Todo {
    int id;
    string task;
};

void print(Todo s) {
    cout << "\tID: " << s.id << endl;
    cout << "\tTask: " << s.task << endl;
}

void addTodo() {
    system("cls");  // Clear the console screen (use "clear" for Linux/Unix)
    cout << "\t\t\t******************************" << endl;
    cout << "\t\t\t       WELCOME TO TODO LIST   " << endl;
    cout << "\t\t\t******************************" << endl;

    Todo todo;
    cout << "\n\tEnter New Task: ";
    cin.ignore();  // Ignore any leftover newline character from previous inputs
    getline(cin, todo.task);
    ID++;

    ofstream write;
    write.open("todo.txt", ios::app);
    write << ID << endl;
    write << todo.task << endl;
    write.close();

    ofstream idWrite;
    idWrite.open("id.txt");
    idWrite << ID;
    idWrite.close();

    char ch;
    cout << "\n\tDo you want to add more tasks? (Y/N): ";
    cin >> ch;
    if (tolower(ch) == 'y') {
        addTodo();
    } else {
        cout << "\n\tTask added successfully!\n";
    }
}

void readData() {
    system("cls");
    cout << "\t\t\t******************************" << endl;
    cout << "\t\t\t       WELCOME TO TODO LIST   " << endl;
    cout << "\t\t\t******************************" << endl;

    ifstream read;
    read.open("todo.txt");
    Todo todo;
    cout << "\n\t\t\t------------- Your Current Tasks -------------\n";
    while (read >> todo.id) {
        read.ignore();  // Ignore newline before reading the task
        getline(read, todo.task);
        print(todo);
    }
    read.close();
}

int searchData() {
    system("cls");
    cout << "\t\t\t******************************" << endl;
    cout << "\t\t\t       WELCOME TO TODO LIST   " << endl;
    cout << "\t\t\t******************************" << endl;

    int id;
    cout << "\n\tEnter task ID: ";
    cin >> id;

    ifstream read;
    read.open("todo.txt");
    Todo todo;
    while (read >> todo.id) {
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id) {
            print(todo);
            return id;
        }
    }
    read.close();
    cout << "\n\tTask not found!" << endl;
    return -1;
}

void deleteData() {
    system("cls");
    cout << "\t\t\t******************************" << endl;
    cout << "\t\t\t       WELCOME TO TODO LIST   " << endl;
    cout << "\t\t\t******************************" << endl;

    int id = searchData();
    if (id == -1) return;

    cout << "\n\tDo you want to delete this task? (Y/N): ";
    char choice;
    cin >> choice;

    if (tolower(choice) == 'y') {
        Todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");

        while (read >> todo.id) {
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << todo.id << endl;
                tempFile << todo.task << endl;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");

        cout << "\n\tTask deleted successfully!";
    } else {
        cout << "\n\tTask not deleted!";
    }
}

int main() {
    system("cls");
    system("Color E0");  // Set console colors (works on Windows)
    system("title TodoApp @copyassignment");

    ifstream read("id.txt");
    if (!read.fail()) {
        read >> ID;
    } else {
        ID = 0;
    }
    read.close();

    while (true) {
        cout << "\n\t1. Add Task";
        cout << "\n\t2. View All Tasks";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Exit";

        int choice;
        cout << "\n\tEnter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTodo();
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
                exit(0);
            default:
                cout << "\n\tInvalid choice, please choose between 1-5.";
        }
    }

    return 0;
}  