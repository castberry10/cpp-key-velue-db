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
//   int current;
//   Entry *entry;
// };

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value){
    Entry* entry = new Entry;
    entry->key = key;
    entry->type = type;
    entry->value = value;
    return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database){
    database.capacity = 16;
    database.size = 0;
    // Entry* entrylist = new Entry[database.size];
    database.entry = new Entry*[database.capacity];
    for (unsigned long long i = 0; i < database.capacity; ++i) {
        database.entry[i] = nullptr;
    }
}
// Entry 포인트 배열을 복사한다.
void dataCopy(Database &database, Entry **currentEntry, Entry **copyEntry){
    for (int i = 0; i < database.size; ++i) {
        // if(currentEntry[i]->type == Type::INT){
        // }else if(currentEntry[i]->type == Type::DOUBLE){
        // }else if(currentEntry[i]->type == Type::STRING){
        // }else if(currentEntry[i]->type == Type::ARRAY){
        // } 생각해보니 포인터를 가진 배열이니까 포인터를 까서 안넣어도 되네
        copyEntry[i] = currentEntry[i];
    }

}


// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry){
    // 넘칠라하면 늘리기
    if(database.capacity * (2 / 3) < database.size){
        database.capacity *= 2;
        Entry ** newEntry = new Entry *[database.capacity];
        dataCopy(database, database.entry, newEntry);
        for (unsigned long long i = 0; i < database.capacity; i++) {
            delete database.entry[i]; 
        }
        delete[] entry;  
        database.entry = newEntry;
    }

    database.entry[database.size] = entry;
    database.size++;
    
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key){
    Entry* returnEntry; 
    for(int i = 0; i<database.size; i++){
        if(database.entry[i]->key == key){
            returnEntry = database.entry[i];
        }
    }
    return returnEntry;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key){
    for(int i = 0; i<database.size; i++){
        if(database.entry[i]->key == key){
            // database.entry[i]->value;
            delEntryValue(database.entry[i]);
            delete database.entry[i];
            for(int index = i; index < database.size; index++){
                database.entry[i] = database.entry[i + 1];
            }
            database.size--;
            database.entry[i]->key = "";    
            break;
        }
    }
}
void delEntryValue(Entry * entry){
    if(entry != nullptr){
        if(entry->type == Type::INT){
            delete static_cast<int*>(entry->value);
        }else if(entry->type == Type::DOUBLE){
            delete static_cast<std::string*>(entry->value);
        }else if(entry->type == Type::STRING){
            delete static_cast<double*>(entry->value);
        }else if(entry->type == Type::ARRAY){
            
        }
    }
}

// 데이터베이스를 해제한다.
void destroy(Database &database){
    for(int i = 0; i<database.size; i++){
        delEntryValue(database.entry[i]);
    }
    delete[] database.entry;
    
}
