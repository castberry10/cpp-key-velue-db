#include <iostream>
#include <string>
#include "database.h"
// list - DB에 존재하는 모든 엔트리를 출력한다.
// add - Key, Type, Value를 받아 DB에 추가한다.
// get - Key를 입력 받아 “KEY: VALUE” 형태로 출력한다.
// del - Key를 입력 받아 엔트리를 제거한다.
// exit - 프로그램을 종료한다.
namespace state{

}

Database db;

void add(){
    std::string key = "";
    std::string type = "";
    std::string value = "";
    std::cout << "key: ";
    std::cin >> key;
    std::cout << "type (int, double, string, array): ";
    std::cin >> type;
    if(type == "int"){

    }else if(type == "doble"){

    }else if(type == "string"){

    }else if(type == "array"){

    }
}
void list(){

}
void get(){
    std::string key = "";
    std::cin >> key;
    Entry getEntryData = get(db, key);
    if(getEntryData.type == Type::ARRAY){

    }else{

    }
}
void del(){
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
    while(1){
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> inputString;
        if(inputString == "add"){
            add();
        }else if(inputString == "list"){
            list();
        }else if(inputString == "get"){
            get();
        }else if(inputString == "del"){
            del();
        }else if(inputString == "exit"){
            exit();
        }else{
            std::cout << "command Error" << std::endl << std::endl;
        }
    }
}