#include <iostream>
#include <string>
#include "database.h"
// list - DB에 존재하는 모든 엔트리를 출력한다.
// add - Key, Type, Value를 받아 DB에 추가한다.
// get - Key를 입력 받아 “KEY: VALUE” 형태로 출력한다.
// del - Key를 입력 받아 엔트리를 제거한다.
// exit - 프로그램을 종료한다.

// Database db;
Database *db = new Database;

void inputArray(Array* superArray){
    int size;
    std::cout << "size: ";
    std::cin >> size;

    Array * dataArray = new Array[size];
    for(int t=0; t<size; t++){
        std::cout << "item["<< t <<"]: ";
        std::cout << "type (int, double, string, array): ";
        std::string inputType = ""; 
        std::cin >> inputType;
        if(inputType == "int"){
            std::cout << "size: ";
            std::cin >> size;
            int * value = new int[size];
            for(int i = 0; i<size; i++){
                std::cout << "item["<< i <<"]: ";
                std::cin >> value[i];
            }
            dataArray->type = Type::INT;
            dataArray->size = size;
            dataArray->items = value;
        }else if(inputType == "double"){
            std::cout << "size: ";
            std::cin >> size;
            double * value = new double[size];
            for(int i = 0; i<size; i++){
                std::cout << "item["<< i <<"]: ";
                std::cin >> value[i];
            }
            dataArray->type = Type::DOUBLE;
            dataArray->size = size;
            dataArray->items = value;
        }else if(inputType == "string"){
            std::cout << "size: ";
            std::cin >> size;
            std::string * value = new std::string[size];
            for(int i = 0; i<size; i++){
                std::cout << "item["<< i <<"]: ";
                std::cin >> value[i];
            }
            dataArray->type = Type::STRING;
            dataArray->size = size;
            dataArray->items = value;
        }else if(inputType == "array"){
            inputArray(superArray);
        }
    }
    superArray->items = dataArray;
}

Array* input1Array(){
    Array * dataArray = new Array;
    std::cout << "value: ";
    std::cout << "type (int, double, string, array): ";
    std::string inputType = ""; 
    std::cin >> inputType;
    int size = 0;

    if(inputType == "int"){
        std::cout << "size: ";
        std::cin >> size;
        int * value = new int[size];
        for(int i = 0; i<size; i++){
            std::cout << "item["<< i <<"]: ";
            std::cin >> value[i];
        }
        dataArray->type = Type::INT;
        dataArray->size = size;
        dataArray->items = value;
    }else if(inputType == "double"){
        std::cout << "size: ";
        std::cin >> size;
        double * value = new double[size];
        for(int i = 0; i<size; i++){
            std::cout << "item["<< i <<"]: ";
            std::cin >> value[i];
        }
        dataArray->type = Type::DOUBLE;
        dataArray->size = size;
        dataArray->items = value;
    }else if(inputType == "string"){
        std::cout << "size: ";
        std::cin >> size;
        std::string * value = new std::string[size];
        for(int i = 0; i<size; i++){
            std::cout << "item["<< i <<"]: ";
            std::cin >> value[i];
        }
        dataArray->type = Type::STRING;
        dataArray->size = size;
        dataArray->items = value;
    }else if(inputType == "array"){
        inputArray(dataArray);
    }

    return dataArray;
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
        add(*db, inputEntry);
    }else if(type == "double"){
        double value;
        std::cout << "value: ";
        std::cin >> value;
        Entry * inputEntry = create(Type::DOUBLE, key, &value);
        add(*db, inputEntry);
    }else if(type == "string"){
        std::string value = "";
        std::cin.ignore();
        std::cout << "value: ";
        // std::cin >> value;
        getline(std::cin, value);

        Entry * inputEntry = create(Type::STRING, key, &value);
        add(*db, inputEntry);
    }else if(type == "array"){
        // 히히 나중에 해야지
        Array * array = input1Array();
        Entry * inputEntry = create(Type::ARRAY, key, array);
        add(*db, inputEntry);
    }

}


void getArray(Array* array){
    std::cout << "[" ;
    if(array->type == Type::ARRAY){       
        getArray(static_cast<Array*>(array->items));
    }else if(array->type == Type::INT){
        for(int i=0; i<array->size; i++){
            if(i != 0){
                std::cout <<", ";
            }
            std::cout << static_cast<int*>(array->items)[i];
        }
    }else if(array->type == Type::DOUBLE){
        for(int i=0; i<array->size; i++){
            if(i != 0){
                std::cout <<", ";
            }
            std::cout << (static_cast<double*>(array->items)[i]);
        }
    }else if(array->type == Type::STRING){
        for(int i=0; i<array->size; i++){
            if(i != 0){
                std::cout <<", ";
            }
            std::cout <<"\""<< (static_cast<std::string*>(array->items)[i]) <<"\"";
        }
    }

    std::cout << "]" << std::endl;
}
void _list(){
    for (unsigned long long i = 0; i < db->size; i++) {
        if(db->entry[i]->value != nullptr){
            std::cout<<db->entry[i]->key<<": ";
            if(db->entry[i]->type == Type::INT){
                std::cout << *(static_cast<int*>(db->entry[i]->value));
            }else if(db->entry[i]->type == Type::DOUBLE){
                std::cout << *(static_cast<double*>(db->entry[i]->value));
            }else if(db->entry[i]->type == Type::STRING){
                std::cout <<"\""<< *(static_cast<std::string*>(db->entry[i]->value)) <<"\"";
            }else if(db->entry[i]->type == Type::ARRAY){
                getArray(static_cast<Array*>(db->entry[i]->value));
            }
            std::cout<<std::endl;
        }
        
    }
}
void _get(){
    std::string key = "";
    std::cout << "key: ";
    std::cin >> key;
    Entry* getEntryData = get(*db, key);
    if(getEntryData == nullptr){ // 만약 값이 없다면 ~~ 
        std::cout << "not found" << std::endl;
        return;
    }
    //이제 무조건 값이 있는 경우
    std::cout<<getEntryData->key<<": ";

    if(getEntryData->type == Type::ARRAY){
        getArray(static_cast<Array*>(getEntryData->value));
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
    std::cout << "key: ";
    std::cin >> key;
    remove(*db, key);
}
void exit(){
    destroy(*db);
    exit(0);
}
int main(){
    std::string inputString = "";
    init(*db);
    while(1){

        ///debug
        // std::cout << "db size: " <<db->size << std::endl;
        // std::cout << "db capacity: " <<db->capacity << std::endl;
        
        ///debug
        
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> inputString;
        if(inputString == "add"){
            _add();
        }else if(inputString == "list"){
            _list();
        }else if(inputString == "get"){
            _get();
        }else if(inputString == "del"){
            // std::cout<<1;
            _del();
        }else if(inputString == "exit"){
            destroy(*db);
            exit();
        }else{
            std::cout << "command Error" << std::endl << std::endl;
        }
    }
}