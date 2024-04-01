#include <iostream>
#include <string>
#include "database.h"
// list - DB에 존재하는 모든 엔트리를 출력한다.
// add - Key, Type, Value를 받아 DB에 추가한다.
// get - Key를 입력 받아 “KEY: VALUE” 형태로 출력한다.
// del - Key를 입력 받아 엔트리를 제거한다.
// exit - 프로그램을 종료한다.

Database db;


void inputArray(){

}
void _add(){
    std::string key = "";
    std::string type = "";
    std::cout << "key: ";
    std::cin >> key;
    std::cout << "type (int, double, string, array): ";
    std::cin >> type;
    if(type == "int"){
        int value;
        std::cout << "value: ";
        std::cin >> value;
        Entry * inputEntry = create(Type::INT, key, &value);
        add(db, inputEntry);
    }else if(type == "double"){
        double value;
        std::cout << "value: ";
        std::cin >> value;
        Entry * inputEntry = create(Type::DOUBLE, key, &value);
        add(db, inputEntry);
    }else if(type == "string"){
        std::string value = "";
        std::cout << "value: ";
        std::cin >> value;
        Entry * inputEntry = create(Type::STRING, key, &value);
        add(db, inputEntry);
    }else if(type == "array"){
        // 히히 나중에 해야지
    }

}
void _list(){
    for (unsigned long long i = 0; i < db.size; i++) {
        std::cout<<db.entry[i]->key<<": ";
        if(db.entry[i]->type == Type::INT){
            std::cout << *(static_cast<int*>(db.entry[i]->value));
        }else if(db.entry[i]->type == Type::DOUBLE){
            std::cout << *(static_cast<double*>(db.entry[i]->value));
        }else if(db.entry[i]->type == Type::STRING){
            std::cout <<"\""<< *(static_cast<std::string*>(db.entry[i]->value)) <<"\"";
        }else if(db.entry[i]->type == Type::ARRAY){
            // 히히 나중에 해야지
        }
        std::cout<<std::endl;
    }
}
void _get(){
    std::string key = "";
    std::cout << "key: ";
    std::cin >> key;
    Entry* getEntryData = get(db, key);
    if(getEntryData == nullptr){ // 만약 값이 없다면 ~~ 
        std::cout << "not found" << std::endl;
        return;
    }
    //이제 무조건 값이 있는 경우
    std::cout<<getEntryData->key<<": ";

    if(getEntryData->type == Type::ARRAY){
        // 히히 나중에 해야지
    }else if(getEntryData->type == Type::INT){
        std::cout << *(static_cast<int*>(getEntryData->value));
    }else if(getEntryData->type == Type::DOUBLE){
        std::cout << *(static_cast<double*>(getEntryData->value));
    }else if(getEntryData->type == Type::STRING){
        std::cout <<"\""<< *(static_cast<std::string*>(getEntryData->value)) <<"\"";
    }
    std::cout<<std::endl;
}
void _del(){
    std::string key = "";
    std::cin >> key;
    remove(db, key);
}
void exit(){
    destroy(db);
    exit(0);
}
int main(){
    std::string inputString = "";
    init(db);
    while(1){
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> inputString;
        if(inputString == "add"){
            _add();
        }else if(inputString == "list"){
            _list();
        }else if(inputString == "get"){
            _get();
        }else if(inputString == "del"){
            _del();
        }else if(inputString == "exit"){
            destroy(db);
            exit();
        }else{
            std::cout << "command Error" << std::endl << std::endl;
        }
    }
}