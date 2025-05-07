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
    this-> next = NULL;
}
OneLinkedList::OneLinkedList(){
    this->head = this->tail = NULL;
}
OneLinkedList::~OneLinkedList(){
    while(head != NULL) pop_front();

}

OneLinkedList::OneLinkedList(OneLinkedList& other) : head(NULL), tail(NULL){
    Node* current = other.head;
    while(current != NULL){
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
void OneLinkedList::pop_front(){
    if(head == NULL) return;
    if(head == tail){
        delete tail;
        head = tail = NULL;
        return;
    }
    Node* node;
    node = head;
    head = node-> next;
    delete node;
}
void OneLinkedList::pop_back(){
    if(tail == NULL) return;
    if(head == tail){
        delete tail;
        head = tail = NULL;
        return;
    }
    Node* node;
    node = head;
    for(;node->next != tail; node = node->next);
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
void OneLinkedList::push_back(Student data){
    Node* node = new Node(data);
    if(head == NULL) head = node;
    if(tail != NULL) tail->next = node;
    tail = node;
}


OneLinkedList OneLinkedList::searchStudentsDate(string date) {
    OneLinkedList result;
    Node* current = head;
    
    while (current != NULL) {
        Student filteredStudent = current->data; // Копируем данные студента
        filteredStudent.visits.clear(); // Очищаем посещения
        
        // Проверяем все посещения студента
        for (const Visits& visit : current->data.visits) {
            if (visit.date_visit == date) 
                filteredStudent.visits.push_back(visit); // Добавляем только подходящие   
        }
        
        // Если нашли хотя бы одно посещение в диапазоне - добавляем студента в результат
        if (!filteredStudent.visits.empty()) {
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
        Student filteredStudent = current->data; // Копируем данные студента
        filteredStudent.visits.clear(); // Очищаем посещения
        
        // Проверяем все посещения студента
        for (const Visits& visit : current->data.visits) {
            if (visit.date_visit > start_date && 
                visit.date_visit < end_date && visit.diagnos == diagnos_search) 
                filteredStudent.visits.push_back(visit); // Добавляем только подходящие   
            if(visit.date_visit == start_date || visit.date_visit == end_date){
                if(visit.time_visit > start_time && visit.time_visit < end_time && visit.diagnos == diagnos_search)
                    filteredStudent.visits.push_back(visit);
            }
        }
        
        // Если нашли хотя бы одно посещение в диапазоне - добавляем студента в результат
        if (!filteredStudent.visits.empty()) {
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
        filteredStudent.visits.clear();
        
        for (const Visits& visit : current->data.visits) {
            if (visit.date_visit > start_date && 
                visit.date_visit < end_date && visit.recomendations == recomend_free)
                filteredStudent.visits.push_back(visit);   
            if(visit.date_visit == start_date || visit.date_visit == end_date){
                if(visit.time_visit > start_time && visit.time_visit < end_time && visit.diagnos == recomend_free)
                    filteredStudent.visits.push_back(visit);
            }
        }
        if (!filteredStudent.visits.empty()) {
            count++;
        }
        
        current = current->next;
    }
    return count;
}

void OneLinkedList::load_file(string filename){
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Невозможно открыть файл" + filename);
    }
    string line;
    int count;
    Student student;
    Visits visits;
    for(int i = 1;getline(file, line);i++){
        if(i % 9 == 1){
            student.lastname = line;
        }
        if(i % 9 == 2){
            student.inicial = line;
        }
        if(i % 9 == 3){
            student.date_born = stoi(line);
        }
        if(i % 9 == 4){
            student.phone_number = line;
        }
        if(i % 9 == 5){
            student.join_date = stoi(line);
        }
        if(i % 9 == 6){
            student.group_name = line;
        }
        if(i % 9 == 7){
            student.university = line;
        }
        if(i % 9 == 8){
            student.cafedra  = line;
        }
        if(i % 9 == 0){
            vector<string> words = readLineAsStrings(line);
            for(int j = 1; j < words.size();j++){
                if(j % 6 == 1) visits.date_visit = words[j-1];
                if(j % 6 == 2) visits.time_visit = words[j-1];
                if(j % 6 == 3) visits.diagnos = words[j-1];
                if(j % 6 == 4) visits.recomendations = words[j-1];
                if(j % 6 == 5) visits.doctor_lastname = words[j-1];
                if(j % 6 == 0){
                    visits.doctor_inicial = words[j-1];
                    student.visits.push_back(visits);
                }
                if(j == words.size() - 1){
                    visits.doctor_inicial = words[j];
                    student.visits.push_back(visits);
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

        cout << "Введите фамилию студента: ";
        cin >> obj.lastname;
        cout << "Введите инициалы студента: ";
        cin >> obj.inicial;
        cout << "Введите дату рождения (число): ";
        cin >> obj.date_born;
        cout << "Введите номер телефона: ";
        cin >> obj.phone_number;
        cout << "Введите дату зачисления (число): ";
        cin >> obj.join_date;
        cout << "Введите название группы: ";
        cin >> obj.group_name;
        cout << "Введите университет: ";
        cin >> obj.university;
        cout << "Введите кафедру: ";
        cin >> obj.cafedra;

        cout << "Введите количество посещений, которые необходимо ввести: ";
        cin >> k;

        for (int j = 0; j < k; j++) {
            cout << "Введите дату посещения(формат YYYY.MM.DD): ";
            cin >> visit.date_visit;
            cout << "Введите время посещения(формат HH.MM): ";
            cin >> visit.time_visit;
            cout << "Введите диагноз: ";
            cin >> visit.diagnos;
            cout << "Введите рекомендации: ";
            cin >> visit.recomendations;
            cout << "Введите фамилию врача: ";
            cin >> visit.doctor_lastname;
            cout << "Введите инициалы врача: ";
            cin >> visit.doctor_inicial;

            obj.visits.push_back(visit);
        }

        push_back(obj);
    }
}

void OneLinkedList::SaveToFile(string filename) {
    ofstream file(filename);
    Node* current = head;

    while (current != NULL) {
        Student& student = current->data;

        // Запись основных данных студента
        file << student.lastname << "\n";
        file << student.inicial << "\n";
        file << student.date_born << "\n";
        file << student.phone_number << "\n";
        file << student.join_date << "\n";
        file << student.group_name << "\n";
        file << student.university << "\n";
        file << student.cafedra << "\n";

        // Запись данных о посещениях
        for (const Visits& visit : student.visits) {
            file << visit.date_visit << " ";
            file << visit.time_visit << " ";
            file << visit.diagnos << " ";
            file << visit.recomendations << " ";
            file << visit.doctor_lastname << " ";
            file << visit.doctor_inicial << " ";
        }
        file << endl;
        current = current->next;
    }
    file.close();
}
ostream& operator<<(ostream& os, OneLinkedList list) {
    setlocale(LC_ALL, "ru_RU.utf8");
    Node* current = list.head;
    
    if (current == NULL) {
        os << "Список пуст!" << endl;
        return os;
    }
    
    while (current != NULL) {
        const Student& student = current->data;
        
        os << "Фамилия: " << student.lastname << "\n"
           << "Инициалы: " << student.inicial << "\n"
           << "Дата рождения: " << student.date_born << "\n"
           << "Телефон: " << student.phone_number << "\n"
           << "Дата зачисления: " << student.join_date << "\n"
           << "Группа: " << student.group_name << "\n"
           << "Университет: " << student.university << "\n"
           << "Кафедра: " << student.cafedra << "\n"
           << "Посещения:\n";
        
        for (const Visits& visit : student.visits) {
            os << "Дата посещения: " << visit.date_visit << " "
               << "Время посещения: " << visit.time_visit << " "
               << "Диагноз: " << visit.diagnos << " "
               << "Рекомендации: " << visit.recomendations << " "
               << "Врач: " << visit.doctor_lastname << " " << visit.doctor_inicial << "\n";
        }
        os << "\n=====================\n";
        current = current->next;
    }
    
    return os;
}

bool OneLinkedList::updateStudentData(string student_id, Student new_data) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.phone_number == student_id) { 
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
        if (current->data.phone_number == student_id) {
            current->data.visits.push_back(new_visit);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool OneLinkedList::removeVisitFromStudent(string student_id, string visit_date, string visit_time) {
    Node* current = head;
    while (current != NULL) {
        if (current->data.phone_number == student_id) {
            auto& visits = current->data.visits;
            for (auto it = visits.begin(); it != visits.end(); ++it) {
                if (it->date_visit == visit_date && it->time_visit == visit_time) {
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
        if (current->data.phone_number == student_id) {
            for (auto& visit : current->data.visits) {
                if (visit.date_visit == visit_date && visit.time_visit == visit_time) {
                    visit.diagnos = new_diagnosis;
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
        if (current->data.phone_number == student_id) {
            for (auto& visit : current->data.visits) {
                if (visit.date_visit == visit_date && visit.time_visit == visit_time) {
                    visit.recomendations = new_recommendations;
                    return true;
                }
            }
            return false;
        }
        current = current->next;
    }
    return false;
}