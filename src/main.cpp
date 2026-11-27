#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int id;
    string name;
    string room;
    bool isPaid;
};

struct HostelApp {
    vector<Student> students;

    void addStudent(int id, string name, string room) {
        students.push_back({id, name, room, false});
        cout << "[SUCCESS] Student " << name << " added to room " << room << "\n";
    }

    void markPaid(int id) {
        for (auto& s : students) {
            if (s.id == id) {
                s.isPaid = true;
                cout << "[PAYMENT] Payment confirmed for student ID " << id << "\n";
                return;
            }
        }
        cout << "[ERROR] Student not found.\n";
    }

    void showAll() {
        cout << "\n---------------- HOSTEL RESIDENTS ----------------\n";
        cout << left << setw(8) << "ID" << setw(20) << "Name" << setw(10) << "Room" << "Status\n";
        cout << "--------------------------------------------------\n";
        for (const auto& s : students) {
            cout << left << setw(8) << s.id << setw(20) << s.name << setw(10) << s.room 
                 << (s.isPaid ? "PAID" : "NOT PAID") << "\n";
        }
        cout << "--------------------------------------------------\n\n";
    }
};

int main() {
    HostelApp app;
    app.addStudent(1, "Daniil Luhovyk", "Dorm-6");
    app.addStudent(2, "Olexander Ivanenko", "Dorm-6");
    app.markPaid(1);
    app.showAll();

    return 0;
}
