#include "database.h"
#include <iostream>
#include <string>

// database
// ㄴ entry
// ㄴ entry
//    ㄴ array

// enum Type { INT, DOUBLE, STRING, ARRAY };

// struct Array {
//   int size;
//   Type type;
//   void *items;
// };

// struct Entry {
//   Type type;
//   std::string key;
//   void *value;
// };

// struct Database {
//   int size;
//   Entry *entry;
// };

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value){
    Entry* entry = new Entry;
    entry->key = key;
    entry->type = type;
    entry->value = value;
}

// 데이터베이스를 초기화한다.
void init(Database &database){
    database.size = 128;
    database.current = 0;
    Entry* entrylist = new Entry[database.size];
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry){

}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key){
    Entry* returnEntry; 
    for(int i = 0; i<database.size; i++){
        if(database.entry[i].key == key){
            returnEntry = &database.entry[i];
        }
    }
    return returnEntry;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key){
    for(int i = 0; i<database.size; i++){
        if(database.entry[i].key == key){
            delete database.entry[i].value;
            database.size--;
            database.entry[i].key = "";
        }
    }
}

// 데이터베이스를 해제한다.
void destroy(Database &database){
    for(int i = 0; i<database.size; i++){
        delete database.entry[i].value;
    }
    delete[] database.entry;
    
}