#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include "classList.h"
#include "func.h"
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
    Node* newNode = new Node(data);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

void OneLinkedList::push_back(Student data) {
    Node* node = new Node(data);
    if(head == NULL) head = node;
    if(tail != NULL) tail->next = node;
    tail = node;
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

OneLinkedList OneLinkedList::searchStudentsBetweenDate(string start_date, string end_date, 
                                                     string start_time, string end_time, 
                                                     string diagnos_search) {
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

int OneLinkedList::countStudentsFree(string start_date, string end_date, 
                                   string start_time, string end_time, 
                                   string recomend_free) {
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
    cin.ignore();
    if (N == 0) return;

    for (int i = 0; i < N; i++) {
        Student obj;
        Visits visit;
        int k;
        string temp_str;
        int temp_int;

        cout << "Введите фамилию студента: ";
        cin >> temp_str; obj.setLastname(temp_str);
        cout << "Введите инициалы студента: ";
        cin >> temp_str; obj.setInicial(temp_str);
        cout << "Введите дату рождения (число): ";
        cin >> temp_int; obj.setDateBorn(temp_int);
        cout << "Введите номер телефона: ";
        cin >> temp_str; obj.setPhoneNumber(temp_str);
        cout << "Введите дату зачисления (число): ";
        cin >> temp_int; obj.setJoinDate(temp_int);
        cout << "Введите название группы: ";
        cin >> temp_str; obj.setGroupName(temp_str);
        cout << "Введите университет: ";
        cin >> temp_str; obj.setUniversity(temp_str);
        cout << "Введите кафедру: ";
        cin >> temp_str; obj.setCafedra(temp_str);

        cout << "Введите количество посещений, которые необходимо ввести: ";
        cin >> k;

        for (int j = 0; j < k; j++) {
            cout << "Введите дату посещения(формат YYYY.MM.DD): ";
            cin >> temp_str; visit.setDateVisit(temp_str);
            cout << "Введите время посещения(формат HH.MM): ";
            cin >> temp_str; visit.setTimeVisit(temp_str);
            cout << "Введите диагноз: ";
            cin >> temp_str; visit.setDiagnos(temp_str);
            cout << "Введите рекомендации: ";
            cin >> temp_str; visit.setRecomendations(temp_str);
            cout << "Введите фамилию врача: ";
            cin >> temp_str; visit.setDoctorLastname(temp_str);
            cout << "Введите инициалы врача: ";
            cin >> temp_str; visit.setDoctorInicial(temp_str);

            obj.addVisit(visit);
        }

        push_back(obj);
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
    Node* current = list.getHead();
    
    if (current == NULL) {
        os << "Список пуст!" << endl;
        return os;
    }
    
    while (current != NULL) {
        const Student& student = current->data;
        
        os << "Фамилия: " << student.getLastname() << "\n"
           << "Инициалы: " << student.getInicial() << "\n"
           << "Дата рождения: " << student.getDateBorn() << "\n"
           << "Телефон: " << student.getPhoneNumber() << "\n"
           << "Дата зачисления: " << student.getJoinDate() << "\n"
           << "Группа: " << student.getGroupName() << "\n"
           << "Университет: " << student.getUniversity() << "\n"
           << "Кафедра: " << student.getCafedra() << "\n"
           << "Посещения:\n";
        
        for (const Visits& visit : student.getVisits()) {
            os << "Дата посещения: " << visit.getDateVisit() << " "
               << "Время посещения: " << visit.getTimeVisit() << " "
               << "Диагноз: " << visit.getDiagnos() << " "
               << "Рекомендации: " << visit.getRecomendations() << " "
               << "Врач: " << visit.getDoctorLastname() << " " << visit.getDoctorInicial() << "\n";
        }
        os << "\n=====================\n";
        current = current->next;
    }
    
    return os;
}

bool OneLinkedList::updateStudentData(string student_id, Student new_data) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getPhoneNumber() == student_id) { 
            current->data = new_data;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool OneLinkedList::addVisitToStudent(string student_id, Visits new_visit) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.getPhoneNumber() == student_id) {
            current->data.addVisit(new_visit);
            return true;
        }
        current = current->next;
    }
    return false;
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