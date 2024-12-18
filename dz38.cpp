#include <iostream>
#include <set>
#include <string>

using namespace std;


class Request {
public:
    static int counter;
    int id;
    string destination;
    string passenger;
    string date;

    Request(string dest, string pass, string dat)
        : destination(dest), passenger(pass), date(dat) {
        id = ++counter;
    }

    bool operator<(const Request& other) const {
        if (destination == other.destination) {
            return date < other.date;
        }
        return destination < other.destination;
    }
};

int Request::counter = 0;


multiset<Request> requests;


void addRequest() {
    string dest, pass, date;
    cout << "Введите пункт назначения: ";
    cin >> dest;
    cout << "Введите фамилию и инициалы пассажира: ";
    cin >> pass;
    cout << "Введите дату вылета (формат YYYY-MM-DD): ";
    cin >> date;
    requests.insert(Request(dest, pass, date));
    cout << "Заявка добавлена." << endl;
}


void deleteRequest() {
    int id;
    cout << "Введите номер заявки для удаления: ";
    cin >> id;
    for (auto it = requests.begin(); it != requests.end(); ++it) {
        if (it->id == id) {
            requests.erase(it);
            cout << "Заявка удалена." << endl;
            return;
        }
    }
    cout << "Заявка с таким номером не найдена." << endl;
}


void printRequestsByDestination() {
    string dest;
    cout << "Введите пункт назначения: ";
    cin >> dest;
    for (const auto& req : requests) {
        if (req.destination == dest) {
            cout << "Номер заявки: " << req.id
                << ", Пассажир: " << req.passenger
                << ", Дата вылета: " << req.date << endl;
        }
    }
}


void countRequestsByDateAndDestination() {
    string dest, startDate, endDate;
    cout << "Введите пункт назначения: ";
    cin >> dest;
    cout << "Введите начальную дату (формат YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Введите конечную дату (формат YYYY-MM-DD): ";
    cin >> endDate;
    int count = 0;
    for (const auto& req : requests) {
        if (req.destination == dest && req.date >= startDate && req.date <= endDate) {
            ++count;
        }
    }
    cout << "Количество заявок: " << count << endl;
}


void printAllRequests() {
    for (const auto& req : requests) {
        cout << "Номер заявки: " << req.id
            << ", Пункт назначения: " << req.destination
            << ", Пассажир: " << req.passenger
            << ", Дата вылета: " << req.date << endl;
    }
}


void menu() {
    setlocale(0, "");
    int choice;
    do {
        cout << "Меню:\n";
        cout << "1. Добавить заявку\n";
        cout << "2. Удалить заявку\n";
        cout << "3. Вывести заявки по пункту назначения\n";
        cout << "4. Определить количество заявок на заданный промежуток дат и направления\n";
        cout << "5. Вывести все заявки\n";
        cout << "6. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        switch (choice) {
        case 1: addRequest(); break;
        case 2: deleteRequest(); break;
        case 3: printRequestsByDestination(); break;
        case 4: countRequestsByDateAndDestination(); break;
        case 5: printAllRequests(); break;
        case 6: cout << "Выход." << endl; break;
        default: cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}
