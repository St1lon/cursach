#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
protected:
    string lastname;
    string inicial;
    int date_born; 
    string phone_number;
private:
    virtual Person* clone() const = 0;
public:
    const string& getLastname() const { return lastname; }
    void setLastname(const string& value) { lastname = value; }
    const string& getInicial() const { return inicial; }
    void setInicial(const string& value) { inicial = value; }
    int getDateBorn() const { return date_born; }
    void setDateBorn(int value) { date_born = value; }
    const string& getPhoneNumber() const { return phone_number; }
    void setPhoneNumber(const string& value) { phone_number = value; }
    void validatePersonData() const {
        if (lastname.empty()) throw invalid_argument("Фамилия не может быть пустой");
        if (inicial.empty()) throw invalid_argument("Инициалы не могут быть пустыми");
        if (date_born <= 0) throw invalid_argument("Дата рождения должна быть положительным числом");
        if (phone_number.empty()) throw invalid_argument("Номер телефона не может быть пустым");
    }
};

class Visits {
    string date_visit;
    string time_visit;
    string diagnos;
    string recomendations;
    string doctor_lastname;
    string doctor_inicial;
public:
    const string& getDateVisit() const { return date_visit; }
    void setDateVisit(const string& value) { date_visit = value; }
    const string& getTimeVisit() const { return time_visit; }
    void setTimeVisit(const string& value) { time_visit = value; }
    const string& getDiagnos() const { return diagnos; }
    void setDiagnos(const string& value) { diagnos = value; }
    const string& getRecomendations() const { return recomendations; }
    void setRecomendations(const string& value) { recomendations = value; }
    const string& getDoctorLastname() const { return doctor_lastname; }
    void setDoctorLastname(const string& value) { doctor_lastname = value; }
    const string& getDoctorInicial() const { return doctor_inicial; }
    void setDoctorInicial(const string& value) { doctor_inicial = value; }
    void validateVisitData() const {
        if (date_visit.empty()) throw invalid_argument("Дата посещения не может быть пустой");
        if (date_visit.length() != 10 || date_visit[4] != '.' || date_visit[7] != '.')
            throw invalid_argument("Неверный формат даты. Используйте ГГГГ.ММ.ДД");
        if (time_visit.empty()) throw invalid_argument("Время посещения не может быть пустым");
        if (time_visit.length() != 5 || time_visit[2] != '.')
            throw invalid_argument("Неверный формат времени. Используйте ЧЧ.ММ");
        if (diagnos.empty()) throw invalid_argument("Диагноз не может быть пустым");
        if (doctor_lastname.empty()) throw invalid_argument("Фамилия врача не может быть пустой");
        if (doctor_inicial.empty()) throw invalid_argument("Инициалы врача не могут быть пустыми");
    }
};

class Student : public Person {
    int join_date;
    string group_name;
    string university;
    string cafedra;
    vector<Visits> visits;
public:
    int getJoinDate() const { return join_date; }
    void setJoinDate(int value) { join_date = value; }
    const string& getGroupName() const { return group_name; }
    void setGroupName(const string& value) { group_name = value; }
    const string& getUniversity() const { return university; }
    void setUniversity(const string& value) { university = value; }
    const string& getCafedra() const { return cafedra; }
    void setCafedra(const string& value) { cafedra = value; }
    const vector<Visits>& getVisits() const { return visits; }
    vector<Visits>& getVisits() { return visits; }
    void addVisit(const Visits& visit) { visits.push_back(visit); }
    void clearVisits() { visits.clear(); }
    Person* clone() const override {
        return new Student(*this);
    }
    void validateStudentData() const {
        validatePersonData();
        if (join_date <= 0) throw invalid_argument("Дата зачисления должна быть положительным числом");
        if (group_name.empty()) throw invalid_argument("Название группы не может быть пустым");
        if (university.empty()) throw invalid_argument("Название университета не может быть пустым");
        if (cafedra.empty()) throw invalid_argument("Название кафедры не может быть пустым");
        for (auto& visit : visits) {
            visit.validateVisitData();
        }
    }
};
#endif