#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "classList.h"
#include "func.h"
#include <iomanip>
using namespace std;

Node::Node(Student data) {
    this->data = data;
    this->next = NULL;
}

OneLinkedList::OneLinkedList() {
    this->head = this->tail = NULL;
}

OneLinkedList::~OneLinkedList() {
    while(head != NULL) pop_front();
}

OneLinkedList::OneLinkedList(OneLinkedList& other) : head(NULL), tail(NULL) {
    Node* current = other.head;
    while(current != NULL) {
        push_back(current->data);
        current = current->next;  
    }
}

OneLinkedList OneLinkedList::operator=(OneLinkedList list) {
    if (this != &list) {
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = NULL;
        current = list.head;
        while (current != nullptr) {
            push_front(current->data);
            current = current->next;
        }
    }
    return *this;
}

void OneLinkedList::pop_front() {
    if(head == NULL) return;
    if(head == tail) {
        delete tail;
        head = tail = NULL;
        return;
    }
    Node* node = head;
    head = node->next;
    delete node;
}

void OneLinkedList::pop_back() {
    if(tail == NULL) return;
    if(head == tail) {
        delete tail;
        head = tail = NULL;
        return;
    }
    Node* node = head;
    for(; node->next != tail; node = node->next);
    node->next = NULL;
    delete tail;
    tail = node;
}

void OneLinkedList::push_front(Student data) {
    try{
    data.validateStudentData();
    Node* newNode = new Node(data);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
} catch(invalid_argument& e){
    cerr << "Ошибка добавления студента: " << e.what() << endl;
    throw;
}

}

void OneLinkedList::push_back(Student data) {
    try {
        data.validateStudentData();
        Node* node = new Node(data);
        if(head == NULL) head = node;
        if(tail != NULL) tail->next = node;
        tail = node;
    } catch (invalid_argument& e) {
        cerr << "Ошибка добавления студента: " << e.what() << endl;
        throw;
    }
}

OneLinkedList OneLinkedList::searchStudentsDate(string date) {
    OneLinkedList result;
    Node* current = head;
    
    while (current != NULL) {
        Student filteredStudent = current->data;
        filteredStudent.clearVisits();
        
        for (const Visits& visit : current->data.getVisits()) {
            if (visit.getDateVisit() == date) {
                filteredStudent.addVisit(visit);
            }
        }
        
        if (!filteredStudent.getVisits().empty()) {
            result.push_back(filteredStudent);
        }
        
        current = current->next;
    }
    
    return result;
}

OneLinkedList OneLinkedList::searchStudentsBetweenDate(string start_date, string end_date, string start_time, string end_time, string diagnos_search) {
    OneLinkedList result;
    Node* current = head;
    
    while (current != NULL) {
        Student filteredStudent = current->data;
        filteredStudent.clearVisits();
        
        for (const Visits& visit : current->data.getVisits()) {
            if (visit.getDateVisit() > start_date && 
                visit.getDateVisit() < end_date && visit.getDiagnos() == diagnos_search) {
                filteredStudent.addVisit(visit);
            }
            if(visit.getDateVisit() == start_date || visit.getDateVisit() == end_date) {
                if(visit.getTimeVisit() > start_time && visit.getTimeVisit() < end_time && 
                   visit.getDiagnos() == diagnos_search) {
                    filteredStudent.addVisit(visit);
                }
            }
        }
        
        if (!filteredStudent.getVisits().empty()) {
            result.push_back(filteredStudent);
        }
        
        current = current->next;
    }
    
    return result;
}

int OneLinkedList::countStudentsFree(string start_date, string end_date, string start_time, string end_time, string recomend_free) {
    int count = 0;
    Node* current = head;
    
    while (current != NULL) {
        Student filteredStudent = current->data;
        filteredStudent.clearVisits();
        
        for (const Visits& visit : current->data.getVisits()) {
            if (visit.getDateVisit() > start_date && 
                visit.getDateVisit() < end_date && visit.getRecomendations() == recomend_free) {
                filteredStudent.addVisit(visit);
            }
            if(visit.getDateVisit() == start_date || visit.getDateVisit() == end_date) {
                if(visit.getTimeVisit() > start_time && visit.getTimeVisit() < end_time && 
                   visit.getDiagnos() == recomend_free) {
                    filteredStudent.addVisit(visit);
                }
            }
        }
        if (!filteredStudent.getVisits().empty()) {
            count++;
        }
        
        current = current->next;
    }
    return count;
}

void OneLinkedList::load_file(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Невозможно открыть файл" + filename);
    }
    string line;
    Student student;
    Visits visits;
    for(int i = 1; getline(file, line); i++) {
        if(i % 9 == 1) {
            student.setLastname(line);
        }
        if(i % 9 == 2) {
            student.setInicial(line);
        }
        if(i % 9 == 3) {
            student.setDateBorn(stoi(line));
        }
        if(i % 9 == 4) {
            student.setPhoneNumber(line);
        }
        if(i % 9 == 5) {
            student.setJoinDate(stoi(line));
        }
        if(i % 9 == 6) {
            student.setGroupName(line);
        }
        if(i % 9 == 7) {
            student.setUniversity(line);
        }
        if(i % 9 == 8) {
            student.setCafedra(line);
        }
        if(i % 9 == 0) {
            vector<string> words = readLineAsStrings(line);
            for(int j = 1; j < words.size(); j++) {
                if(j % 6 == 1) visits.setDateVisit(words[j-1]);
                if(j % 6 == 2) visits.setTimeVisit(words[j-1]);
                if(j % 6 == 3) visits.setDiagnos(words[j-1]);
                if(j % 6 == 4) visits.setRecomendations(words[j-1]);
                if(j % 6 == 5) visits.setDoctorLastname(words[j-1]);
                if(j % 6 == 0) {
                    visits.setDoctorInicial(words[j-1]);
                    student.addVisit(visits);
                }
                if(j == words.size() - 1) {
                    visits.setDoctorInicial(words[j]);
                    student.addVisit(visits);
                }
            }
            push_back(student);
            student = Student();
            visits = Visits();
        }
    }
}

void OneLinkedList::push_backNnodes(int N) {
    if (N <= 0) {
        cerr << "Ошибка: количество студентов должно быть положительным числом." << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < N; i++) {
        cout << "\n=== Ввод данных студента " << i + 1 << " из " << N << " ===" << endl;
        
        Student newStudent;
        Visits newVisit;
        string input;
        int intValue;
        int visitCount = 0;

        try {
            cout << "Фамилия: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Фамилия не может быть пустой");
            newStudent.setLastname(input);

            cout << "Инициалы: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Инициалы не могут быть пустыми");
            newStudent.setInicial(input);

            cout << "Дата рождения (число): ";
            if (!(cin >> intValue)) throw invalid_argument("Неверный формат даты рождения");
            if (intValue <= 0) throw invalid_argument("Дата рождения должна быть положительным числом");
            newStudent.setDateBorn(intValue);
            cin.ignore();

            cout << "Номер телефона: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Номер телефона не может быть пустым");
            if (input.find_first_not_of("0123456789+()- ") != string::npos) {
                throw invalid_argument("Номер телефона содержит недопустимые символы");
            }
            newStudent.setPhoneNumber(input);

            cout << "Дата зачисления (число): ";
            if (!(cin >> intValue)) throw invalid_argument("Неверный формат даты зачисления");
            if (intValue <= 0) throw invalid_argument("Дата зачисления должна быть положительным числом");
            newStudent.setJoinDate(intValue);
            cin.ignore();
            cout << "Группа: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Название группы не может быть пустым");
            newStudent.setGroupName(input);
            cout << "Университет: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Название университета не может быть пустым");
            newStudent.setUniversity(input);
            cout << "Кафедра: ";
            getline(cin, input);
            if (input.empty()) throw invalid_argument("Название кафедры не может быть пустым");
            newStudent.setCafedra(input);
            cout << "Количество посещений: ";
            if (!(cin >> visitCount)) throw invalid_argument("Неверный формат количества посещений");
            if (visitCount < 0) throw invalid_argument("Количество посещений не может быть отрицательным");
            cin.ignore();

            for (int j = 0; j < visitCount; j++) {
                cout << "\n  Ввод посещения " << j + 1 << " из " << visitCount << endl;
                
                cout << "Дата посещения (ГГГГ.ММ.ДД): ";
                getline(cin, input);
                if (input.length() != 10 || input[4] != '.' || input[7] != '.') {
                    throw invalid_argument("Неверный формат даты. Используйте ГГГГ.ММ.ДД");
                }
                newVisit.setDateVisit(input);

                cout << "Время посещения (ЧЧ.ММ): ";
                getline(cin, input);
                if (input.length() != 5 || input[2] != '.') {
                    throw invalid_argument("Неверный формат времени. Используйте ЧЧ.ММ");
                }
                newVisit.setTimeVisit(input);

                cout << " Диагноз: ";
                getline(cin, input);
                if (input.empty()) throw invalid_argument("Диагноз не может быть пустым");
                newVisit.setDiagnos(input);

                cout << " Рекомендации: ";
                getline(cin, input);
                if (input.empty()) throw invalid_argument("Рекомендации не могут быть пустыми");
                newVisit.setRecomendations(input);

                cout << " Фамилия врача: ";
                getline(cin, input);
                if (input.empty()) throw invalid_argument("Фамилия врача не может быть пустой");
                newVisit.setDoctorLastname(input);

                cout << " Инициалы врача: ";
                getline(cin, input);
                if (input.empty()) throw invalid_argument("Инициалы врача не могут быть пустыми");
                newVisit.setDoctorInicial(input);

                newStudent.addVisit(newVisit);
            }

            push_back(newStudent);
            cout << "Студент успешно добавлен!" << endl;

        } catch (invalid_argument& e) {
            cerr << "Ошибка ввода данных: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        } catch (exception& e) {
            cerr << "Неожиданная ошибка: " << e.what() << endl;
            return;
        }
    }
}

void OneLinkedList::SaveToFile(string filename) {
    ofstream file(filename);
    Node* current = head;

    while (current != NULL) {
        Student& student = current->data;

        file << student.getLastname() << "\n";
        file << student.getInicial() << "\n";
        file << student.getDateBorn() << "\n";
        file << student.getPhoneNumber() << "\n";
        file << student.getJoinDate() << "\n";
        file << student.getGroupName() << "\n";
        file << student.getUniversity() << "\n";
        file << student.getCafedra() << "\n";

        for (const Visits& visit : student.getVisits()) {
            file << visit.getDateVisit() << " ";
            file << visit.getTimeVisit() << " ";
            file << visit.getDiagnos() << " ";
            file << visit.getRecomendations() << " ";
            file << visit.getDoctorLastname() << " ";
            file << visit.getDoctorInicial() << " ";
        }
        file << endl;
        current = current->next;
    }
    file.close();
}

ostream& operator<<(ostream& os, OneLinkedList list) {
    setlocale(LC_ALL, "ru_RU.utf8");
    
    // Фиксированные ширины столбцов
    const int lastname_width = 12;
    const int initials_width = 10;
    const int birth_width = 12;
    const int phone_width = 15;
    const int enroll_width = 12;
    const int group_width = 10;
    const int uni_width = 15;
    const int dept_width = 10;
    const int visits_width = 25;

    // Функция вывода разделительной линии
    auto print_line = [&]() {
        os << "+" << string(lastname_width+2, '-')
           << "+" << string(initials_width+2, '-')
           << "+" << string(birth_width+2, '-')
           << "+" << string(phone_width+2, '-')
           << "+" << string(enroll_width+2, '-')
           << "+" << string(group_width+2, '-')
           << "+" << string(uni_width+2, '-')
           << "+" << string(dept_width+2, '-')
           << "+" << string(visits_width+2, '-')
           << "+" << endl;
    };

    Node* current = list.getHead();
    if (!current) {
        os << "Список пуст!" << endl;
        return os;
    }

    // Шапка таблицы
    print_line();
    os << "| " << left << setw(lastname_width) << "Фамилия"
       << " | " << setw(initials_width) << "Инициалы"
       << " | " << setw(birth_width) << "Дата рожд."
       << " | " << setw(phone_width) << "Телефон"
       << " | " << setw(enroll_width) << "Дата зач."
       << " | " << setw(group_width) << "Группа"
       << " | " << setw(uni_width) << "Университет"
       << " | " << setw(dept_width) << "Кафедра"
       << " | " << setw(visits_width) << "Посещения"
       << " |" << endl;
    print_line();

    while (current) {
        const Student& student = current->data;
        const auto& visits = student.getVisits();

        // Основная строка с данными студента
        os << "| " << left << setw(lastname_width) << student.getLastname().substr(0, lastname_width)
           << " | " << setw(initials_width) << student.getInicial().substr(0, initials_width)
           << " | " << setw(birth_width) << student.getDateBorn()
           << " | " << setw(phone_width) << student.getPhoneNumber().substr(0, phone_width)
           << " | " << setw(enroll_width) << student.getJoinDate()
           << " | " << setw(group_width) << student.getGroupName().substr(0, group_width)
           << " | " << setw(uni_width) << student.getUniversity().substr(0, uni_width)
           << " | " << setw(dept_width) << student.getCafedra().substr(0, dept_width)
           << " | ";

        // Первое посещение (если есть)
        if (!visits.empty()) {
            os << setw(visits_width) << (visits[0].getDateVisit() + " " + visits[0].getTimeVisit()).substr(0, visits_width);
        } else {
            os << setw(visits_width) << "Нет";
        }
        os << " |" << endl;

        // Дополнительные строки с посещениями
        for (size_t i = 1; i < visits.size(); i++) {
            os << "| " << string(lastname_width, ' ')
               << " | " << string(initials_width, ' ')
               << " | " << string(birth_width, ' ')
               << " | " << string(phone_width, ' ')
               << " | " << string(enroll_width, ' ')
               << " | " << string(group_width, ' ')
               << " | " << string(uni_width, ' ')
               << " | " << string(dept_width, ' ')
               << " | " << setw(visits_width) << (visits[i].getDateVisit() + " " + visits[i].getTimeVisit()).substr(0, visits_width)
               << " |" << endl;
        }

        // Строки с диагнозами
        for (size_t i = 0; i < visits.size(); i++) {
            os << "| " << string(lastname_width, ' ')
               << " | " << string(initials_width, ' ')
               << " | " << string(birth_width, ' ')
               << " | " << string(phone_width, ' ')
               << " | " << string(enroll_width, ' ')
               << " | " << string(group_width, ' ')
               << " | " << string(uni_width, ' ')
               << " | " << string(dept_width, ' ')
               << " | " << setw(visits_width) << ("Диагноз: " + visits[i].getDiagnos()).substr(0, visits_width)
               << " |" << endl;
        }

        print_line();
        current = current->next;
    }

    return os;
}

bool OneLinkedList::updateStudentData(string student_id, Student new_data) {
    try {
        new_data.validateStudentData();
        Node* current = head;
        while (current != NULL) {
            if (current->data.getPhoneNumber() == student_id) { 
                current->data = new_data;
                return true;
            }
            current = current->next;
        }
        return false;
    } catch (invalid_argument& e) {
        cerr << "Ошибка обновления данных студента: " << e.what() << endl;
        return false;
    }
}

bool OneLinkedList::addVisitToStudent(string student_id, Visits new_visit) {
    try {
        new_visit.validateVisitData();
        Node* current = head;
        while (current != NULL) {
            if (current->data.getPhoneNumber() == student_id) {
                current->data.addVisit(new_visit);
                return true;
            }
            current = current->next;
        }
        return false;
    } catch (invalid_argument& e) {
        cerr << "Ошибка добавления посещения: " << e.what() << endl;
        return false;
    }
}

bool OneLinkedList::removeVisitFromStudent(string student_id, string visit_date, string visit_time) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getPhoneNumber() == student_id) {
            auto& visits = current->data.getVisits();
            for (auto it = visits.begin(); it != visits.end(); ++it) {
                if (it->getDateVisit() == visit_date && it->getTimeVisit() == visit_time) {
                    visits.erase(it);
                    return true;
                }
            }
            return false;
        }
        current = current->next;
    }
    return false;
}

bool OneLinkedList::updateDiagnosis(string student_id, string visit_date, string visit_time, string new_diagnosis) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getPhoneNumber() == student_id) {
            for (auto& visit : current->data.getVisits()) {
                if (visit.getDateVisit() == visit_date && visit.getTimeVisit() == visit_time) {
                    visit.setDiagnos(new_diagnosis);
                    return true;
                }
            }
            return false;
        }
        current = current->next;
    }
    return false;
}

bool OneLinkedList::updateRecommendations(string student_id, string visit_date, string visit_time, string new_recommendations) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getPhoneNumber() == student_id) {
            for (auto& visit : current->data.getVisits()) {
                if (visit.getDateVisit() == visit_date && visit.getTimeVisit() == visit_time) {
                    visit.setRecomendations(new_recommendations);
                    return true;
                }
            }
            return false;
        }
        current = current->next;
    }
    return false;
}