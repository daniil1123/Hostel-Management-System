#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Resident {
    int id;
    string name;
    string room;
    double fee;
    double paid;
    bool active;
};

class HostelManager {
private:
    vector<Resident> residents;
    int nextId;

    int findResidentIndex(int id) const {
        for (size_t i = 0; i < residents.size(); ++i) {
            if (residents[i].id == id && residents[i].active) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    int countOccupantsInRoom(const string& room) const {
        int count = 0;
        for (const auto& r : residents) {
            if (r.active && r.room == room) {
                ++count;
            }
        }
        return count;
    }

public:
    HostelManager() : nextId(1) {}
    void addResident(const string& name, const string& room, double fee, int maxCapacity = 3) {
        if (name.empty() || room.empty() || fee <= 0.0) {
            cout << "[ПОМИЛКА] Некоректні дані для поселення.\n";
            return;
        }
        if (countOccupantsInRoom(room) >= maxCapacity) {
            cout << "[ПОМИЛКА] У кімнаті " << room << " немає вільних місць.\n";
            return;
        }
        residents.push_back({nextId++, name, room, fee, 0.0, true});
        cout << "[УСПІХ] Студента " << name << " поселено у кімнату " << room << ".\n";
    }

    void recordPayment(int id, double amount) {
        int idx = findResidentIndex(id);
        if (idx == -1) {
            cout << "[ПОМИЛКА] Мешканця з ID " << id << " не знайдено.\n";
            return;
        }
        if (amount <= 0.0) {
            cout << "[ПОМИЛКА] Сума оплати має бути більшою за 0.\n";
            return;
        }
        residents[idx].paid += amount;
        cout << "[ОПЛАТА] Зараховано " << fixed << setprecision(2) << amount
             << " для " << residents[idx].name << ".\n";
    }

    void transferRoom(int id, const string& newRoom, int maxCapacity = 3) {
        int idx = findResidentIndex(id);
        if (idx == -1) {
            cout << "[ПОМИЛКА] Мешканця з ID " << id << " не знайдено.\n";
            return;
        }
        if (countOccupantsInRoom(newRoom) >= maxCapacity) {
            cout << "[ПОМИЛКА] Цільова кімната " << newRoom << " вже заповнена.\n";
            return;
        }
        string oldRoom = residents[idx].room;
        residents[idx].room = newRoom;
        cout << "[ПЕРЕСЕЛЕННЯ] " << residents[idx].name
             << " переведено з " << oldRoom << " у " << newRoom << ".\n";
    }

    void checkOut(int id) {
        int idx = findResidentIndex(id);
        if (idx == -1) {
            cout << "[ПОМИЛКА] Мешканця з ID " << id << " не знайдено.\n";
            return;
        }
        residents[idx].active = false;
        cout << "[ВИСЕЛЕННЯ] Мешканця " << residents[idx].name << " виселено.\n";
    }

    void showResidents() const {
        cout << "\n================ СПИСОК МЕШКАНЦІВ ГУРТОЖИТКУ ================\n";
        cout << left << setw(5) << "ID" << setw(24) << "ПІБ" << setw(10) << "Кімната" << right << setw(10) << "Оплата" << setw(10) << "Внесено" << "  " << left << setw(10) << "Статус" << "\n";
        cout << "------------------------------------------------------------\n";
        for (const auto& r : residents) {
            if (!r.active) continue;
            string status = (r.paid >= r.fee) ? "ОПЛАЧЕНО" : (r.paid > 0.0 ? "ЧАСТКОВО" : "БОРГ");
            cout << left << setw(5) << r.id << setw(24) << r.name << setw(10) << r.room << right << setw(10) << fixed << setprecision(2) << r.fee << setw(10) << fixed << setprecision(2) << r.paid << "  " << left << setw(10) << status << "\n";
        }
        cout << "============================================================\n\n";
    }

    void showDebtors() const {
        cout << "--- СПИСОК БОРЖНИКІВ ---\n";
        bool found = false;
        for (const auto& r : residents) {
            if (r.active && r.paid < r.fee) {
                cout << r.name << " (кімната " << r.room << ") — борг: " << fixed << setprecision(2) << (r.fee - r.paid) << "\n";
                found = true;
            }
        }
        if (!found) cout << "Боржників немає.\n";
        cout << "-----------------------\n\n";
    }

    void showStats() const {
        int activeCount = 0;
        double sumFee = 0.0, sumPaid = 0.0;
        for (const auto& r : residents) {
            if (!r.active) continue;
            ++activeCount;
            sumFee += r.fee;
            sumPaid += r.paid;
        }
        double debt = (sumFee > sumPaid) ? (sumFee - sumPaid) : 0.0;
        cout << "Активних мешканців: " << activeCount << "\n";
        cout << "Нараховано всього : " << fixed << setprecision(2) << sumFee << "\n";
        cout << "Отримано оплат   : " << fixed << setprecision(2) << sumPaid << "\n";
        cout << "Загальний борг   : " << fixed << setprecision(2) << debt << "\n\n";
    }
};

int main() {
    HostelManager hostel;
    hostel.addResident("Луговик Данііл", "412", 1400.0, 2);
    hostel.addResident("Іваненко Олександр", "412", 1400.0, 2);
    hostel.addResident("Коваленко Максим", "412", 1400.0, 2);
    hostel.addResident("Коваленко Максим", "305", 1400.0, 3);
    hostel.recordPayment(1, 1400.0);
    hostel.recordPayment(2, 700.0);
    hostel.transferRoom(3, "412", 2);
    hostel.transferRoom(3, "310", 3);
    hostel.showResidents();
    hostel.showDebtors();
    hostel.showStats();
    hostel.checkOut(2);
    hostel.showResidents();
    return 0;
}
