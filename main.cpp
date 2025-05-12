#include <iostream>
#include <string>
#include <vector>
#include "classList.h"
#include <fstream>
#include <iterator>
#include <sstream>
#include <clocale>
#include "func.h"
using namespace std;

int main() {
    system("chcp 65001");
    OneLinkedList list;
    cout << "Мусолин Дмитрий БАСО-02-24 вар 21\n";
    int choice;
    while (true) {
        cout << "\nГлавное меню:\n";
        cout << "1. Загрузить БД\n";
        cout << "2. Сохранить БД\n";
        cout << "3. Показать БД\n";
        cout << "4. Добавить студента\n";
        cout << "5. Найти посещения в определенную дату\n";
        cout << "6. Найти посещение по интервалу даты по определенному диагнозу\n";
        cout << "7. Найти количество студентов которые получили освобождение за некоторое время\n";
        cout << "8. Редактировать данные\n";
        cout << "9. Меню шифрования\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        string filename, date, start_date, end_date, start_time, end_time, diagnos_search;
        string student_id, visit_date, visit_time, new_value;
        OneLinkedList result;
        int count;
        bool check = false;
        Node* current;
        Student new_student;
        Visits new_visit;
        string temp_str;
        int temp_int;
        
        switch(choice) {
            case 1:
                cout << "Введите название файла: ";
                cin >> filename;
                list.load_file(filename);
                cout << "БД загружена\n";
                break;
            case 2:
                cout << "Введите название файла: ";
                cin >> filename;
                list.SaveToFile(filename);
                cout << "БД сохранена\n";
                break;
            case 3:
                cout << list;
                system("pause");
                break;
            case 4:
                cout << "Введите количество студентов: ";
                cin >> count;
                if(count == 0) break;
                list.push_backNnodes(count);
                cout << "Студенты добавлены\n";
                system("pause");
                break;
            case 5:
                cout << "Введите дату посещения (ГГГГ.ММ.ДД): ";
                cin >> date;
                result = list.searchStudentsDate(date);
                cout << result;
                system("pause");
                break;
            case 6:
                cout << "Введите начальную дату (ГГГГ.ММ.ДД): ";
                cin >> start_date;
                cout << "Введите начальное время (ЧЧ.ММ): ";
                cin >> start_time;
                cout << "Введите конечную дату (ГГГГ.ММ.ДД): ";
                cin >> end_date;
                cout << "Введите конечное время (ЧЧ.ММ): ";
                cin >> end_time;
                cout << "Введите диагноз: ";
                cin >> diagnos_search;
                result = list.searchStudentsBetweenDate(start_date, end_date, start_time, end_time, diagnos_search);
                cout << result;
                system("pause");
                break;
            case 7:
                cout << "Введите начальную дату (ГГГГ.ММ.ДД): ";
                cin >> start_date;
                cout << "Введите начальное время (ЧЧ.ММ): ";
                cin >> start_time;
                cout << "Введите конечную дату (ГГГГ.ММ.ДД): ";
                cin >> end_date;
                cout << "Введите конечное время (ЧЧ.ММ): ";
                cin >> end_time;
                cout << "Введите рекомендацию для поиска: ";
                cin >> diagnos_search;
                count = list.countStudentsFree(start_date, end_date, start_time, end_time, diagnos_search);
                cout << "Количество студентов: " << count << endl;
                system("pause");
                break;
            case 8:
                cout << "Введите номер телефона студента (ID): ";
                cin >> student_id;
                current = list.getHead();
                while(current != NULL){
                    Student new_student = current->data;
                    if(new_student.getPhoneNumber() == student_id){
                        check = true;
                        break;
                    }
                    current = current->next;
                }
                if(check == false){
                    cout << "Студента с таким номером не существует";
                    break;
                }
                cout << "\nМеню редактирования:\n";
                cout << "1. Изменить данные студента\n";
                cout << "2. Добавить посещение\n";
                cout << "3. Удалить посещение\n";
                cout << "4. Изменить диагноз\n";
                cout << "5. Изменить рекомендации\n";
                cout << "Выбор: ";
                cin >> choice;
                switch(choice) {
                    case 1: {
                        cout << "Введите новые данные студента:\n";
                        cout << "Фамилия: "; cin >> temp_str; new_student.setLastname(temp_str);
                        cout << "Инициалы: "; cin >> temp_str; new_student.setInicial(temp_str);
                        cout << "Дата рождения: "; cin >> temp_int; new_student.setDateBorn(temp_int);
                        cout << "Номер телефона: "; cin >> temp_str; new_student.setPhoneNumber(temp_str);
                        cout << "Дата зачисления: "; cin >> temp_int; new_student.setJoinDate(temp_int);
                        cout << "Группа: "; cin >> temp_str; new_student.setGroupName(temp_str);
                        cout << "Университет: "; cin >> temp_str; new_student.setUniversity(temp_str);
                        cout << "Кафедра: "; cin >> temp_str; new_student.setCafedra(temp_str);
                        
                        if(list.updateStudentData(student_id, new_student)) {
                            cout << "Данные студента обновлены!\n";
                        } else {
                            cout << "Студент не найден!\n";
                        }
                        break;
                    }   
                    case 2: {
                        cout << "Введите данные посещения:\n";
                        cout << "Дата посещения (ГГГГ.ММ.ДД): "; cin >> temp_str; new_visit.setDateVisit(temp_str);
                        cout << "Время посещения (ЧЧ.ММ): "; cin >> temp_str; new_visit.setTimeVisit(temp_str);
                        cout << "Диагноз: "; cin >> temp_str; new_visit.setDiagnos(temp_str);
                        cout << "Рекомендации: "; cin >> temp_str; new_visit.setRecomendations(temp_str);
                        cout << "Фамилия врача: "; cin >> temp_str; new_visit.setDoctorLastname(temp_str);
                        cout << "Инициалы врача: "; cin >> temp_str; new_visit.setDoctorInicial(temp_str);
                        
                        if(list.addVisitToStudent(student_id, new_visit)) {
                            cout << "Посещение добавлено!\n";
                        } else {
                            cout << "Студент не найден!\n";
                        }
                        break;
                    }
                        
                    case 3: {
                        cout << "Введите дату посещения для удаления (ГГГГ.ММ.ДД): ";
                        cin >> visit_date;
                        cout << "Введите время посещения для удаления (ЧЧ.ММ): ";
                        cin >> visit_time;
                        
                        if(list.removeVisitFromStudent(student_id, visit_date, visit_time)) {
                            cout << "Посещение удалено!\n";
                        } else {
                            cout << "Студент или посещение не найдены!\n";
                        }
                        break;
                    }  
                    case 4: {
                        cout << "Введите дату посещения (ГГГГ.ММ.ДД): ";
                        cin >> visit_date;
                        cout << "Введите время посещения (ЧЧ.ММ): ";
                        cin >> visit_time;
                        cout << "Введите новый диагноз: ";
                        cin >> new_value;
                        
                        if(list.updateDiagnosis(student_id, visit_date, visit_time, new_value)) {
                            cout << "Диагноз обновлен!\n";
                        } else {
                            cout << "Запись не найдена!\n";
                        }
                        break;
                    }  
                    case 5: {
                        cout << "Введите дату посещения (ГГГГ.ММ.ДД): ";
                        cin >> visit_date;
                        cout << "Введите время посещения (ЧЧ.ММ): ";
                        cin >> visit_time;
                        cout << "Введите новые рекомендации: ";
                        cin >> new_value;
                        
                        if(list.updateRecommendations(student_id, visit_date, visit_time, new_value)) {
                            cout << "Рекомендации обновлены!\n";
                        } else {
                            cout << "Запись не найдена!\n";
                        }
                        break;
                    }   
                    default:
                        cout << "Неверный выбор!\n";
                }
                system("pause");
                break;
            case 9:
                des_menu();
                break;  
            default:
                cout << "Неверный выбор!\n";
        }
    }
    return 0;
}