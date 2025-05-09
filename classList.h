#ifndef CLASS_LIST_H
#define CLASS_LIST_H
#include <iostream>
#include <string>
#include <vector>
#include "struct.h"
#include <fstream>
#include <iterator>
#include <sstream>
using namespace std;

class Node{
    public:
        Student data;
        Node* next;
        Node(Student data);
    
    };
    class OneLinkedList{
        Node* head, *tail;
    public:
        Node* getHead() const { return head; }
        Node* getTail() const { return tail; }
        OneLinkedList();
        ~OneLinkedList();
        OneLinkedList(OneLinkedList& other);
        void pop_front();
        void pop_back();
        void push_back(Student data);
        void push_backNnodes(int N);
        void push_front(Student data);
        void load_file(string filename);
        OneLinkedList searchStudentsDate(string date);
        OneLinkedList searchStudentsBetweenDate(string start_date, string end_date, string start_time, string end_time, string diagnos_search);
        int countStudentsFree(string start_date, string end_date, string start_time, string end_time, string recomend_free);
        friend ostream& operator<<(ostream& os, OneLinkedList list);
        OneLinkedList operator=(OneLinkedList list);
        void SaveToFile(string filename);
        int FirstNameLetter(string letter);
        bool updateStudentData(string student_id, Student new_data);
        bool addVisitToStudent(string student_id, Visits new_visit);
        bool removeVisitFromStudent(string student_id, string visit_date, string visit_time);
        bool updateDiagnosis(string student_id, string visit_date, string visit_time, string new_diagnosis);
        bool updateRecommendations(string student_id, string visit_date, string visit_time, string new_recommendations);
    };
#endif