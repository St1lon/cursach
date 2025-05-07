#include <iostream>
#include <string>
#include <vector>
#include "classList.h"
#include "des_utils.h"
#include "func.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include <limits>
using namespace std; 

vector<std::string> readLineAsStrings(string line) {  
    istringstream iss(line);  
    vector<string> words;
    string word;
    
    while (iss >> word) {          
        words.push_back(word);
    }
    return words;
}
void clear_key(DES_cblock& key) {
    memset(key, 0, sizeof(DES_cblock));
}
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void writeFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось создать файл: " + filename);
    }
    file << content;
    file.close();
}
void ShowFile(const string& filename){
   ifstream file(filename);
   if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Could not open the file." << endl;
    }
}
void des_menu() {
    DES_cblock key;
    bool key_initialized = false;
    int choice;
    
    while (true) {
        cout << "\nМеню DES:\n";
        cout << "1. Шифровать файл\n";
        cout << "2. Дешифровать файл\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            while(true) {
                string input_file, output_file;
                int t;
                cout << "\nОперации шифрования:\n";
                cout << "1. Ввести ключ\n";
                cout << "2. Сгенерировать ключ\n";
                cout << "3. Выполнить шифрование\n";
                cout << "0. Назад\n";
                cout << "Выбор: ";
                cin >> t;
                
                if(t == 0) break;
                
                switch(t) {
                    case 1: {
                        cout << "Введите 8-байтный ключ (16 шестнадцатеричных символов): ";
                        string key_str;
                        cin >> key_str;
                        
                        if(key_str.length() != 16) {
                            cout << "Ошибка: ключ должен быть 16 символов (8 байт)!\n";
                            break;
                        }
                        
                        bool valid = true;
                        for(char c : key_str) {
                            if(!isxdigit(c)) {
                                valid = false;
                                break;
                            }
                        }
                        
                        if(!valid) {
                            cout << "Ошибка: ключ должен содержать только шестнадцатеричные символы (0-9, a-f)!\n";
                            break;
                        }
                        
                        for(int i = 0; i < 8; i++) {
                            string byte_str = key_str.substr(i*2, 2);
                            key[i] = static_cast<unsigned char>(stoul(byte_str, nullptr, 16));
                        }
                        
                        key_initialized = true;
                        cout << "Ключ успешно установлен: ";
                        for(int i = 0; i < 8; i++) {
                            printf("%02x ", key[i]);
                        }
                        cout << endl;
                        break;
                    }
                    case 2:
                        DESUtils::generate_random_key(&key);
                        key_initialized = true;
                        cout << "Новый ключ сгенерирован: ";
                        for(int i = 0; i < 8; i++) {
                            printf("%02x ", key[i]);
                        }
                        cout << "\nСохраните этот ключ для последующего дешифрования!\n";
                        break;
                    case 3:
                        if(!key_initialized) {
                            cout << "Ошибка: ключ не установлен!\n";
                            break;
                        }
                        
                        cout << "Используемый ключ: ";
                        for(int i = 0; i < 8; i++) {
                            printf("%02x", key[i]);
                        }
                        cout << endl;
                        
                        cout << "Введите входной файл: ";
                        cin >> input_file;
                        cout << "Содержимое входного файла: \n";
                        ShowFile(input_file);
                        cout << "Введите выходной файл: ";
                        cin >> output_file;
                        
                        if (DESUtils::encrypt_file(input_file, output_file, key)) {
                            cout << "Файл успешно зашифрован!\n";
                            cout << "Содержимое выходного файла: \n";
                            ShowFile(output_file);
                            clear_key(key);
                            key_initialized = false;
                        } else {
                            cout << "Ошибка при шифровании!\n";

                        }
                        break;
                    default:
                        cout << "Неверный выбор!\n";
                }
            }
        } else if (choice == 2) {
            if(!key_initialized) {
                cout << "Введите 8-байтный ключ (16 шестнадцатеричных символов): ";
                string key_str;
                cin >> key_str;
                
                if(key_str.length() != 16) {
                    cout << "Ошибка: ключ должен быть 16 символов (8 байт)!\n";
                    continue;
                }
                
                bool valid = true;
                for(char c : key_str) {
                    if(!isxdigit(c)) {
                        valid = false;
                        break;
                    }
                }
                
                if(!valid) {
                    cout << "Ошибка: ключ должен содержать только шестнадцатеричные символы (0-9, a-f)!\n";
                    continue;
                }
                
                for(int i = 0; i < 8; i++) {
                    string byte_str = key_str.substr(i*2, 2);
                    key[i] = static_cast<unsigned char>(stoul(byte_str, nullptr, 16));
                }
                
                key_initialized = true;
            }
            
            cout << "Используемый ключ: ";
            for(int i = 0; i < 8; i++) {
                printf("%02x", key[i]);
            }
            cout << endl;
            
            string input_file, output_file;
            cout << "Введите зашифрованный файл: ";
            cin >> input_file;
            cout << "Содержимое зашифрованного файла: \n";
            ShowFile(input_file);
            cout << "Введите файл для сохранения результата: ";
            cin >> output_file;
            
            if (DESUtils::decrypt_file(input_file, output_file, key)) {
                cout << "Файл успешно дешифрован!\n";
                cout << "Содержимое выходного файла: \n";
                ShowFile(output_file);
                clear_key(key);
                key_initialized = false;
            } else {
                cout << "Ошибка при дешифровании!\n";

            }
        }
    }
}
