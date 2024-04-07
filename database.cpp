#include "database.h"
#include <iostream>
#include <string>


// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value){
    Entry* entry = new Entry;
    entry->key = key;
    entry->type = type;
    entry->value = value;
    if(entry->type == Type::INT){
        int* copiedValue = new int(*static_cast<int*>(value));
        entry->value = copiedValue;
    }else if(entry->type == Type::DOUBLE){
        double* copiedValue = new double(*static_cast<double*>(value));
        entry->value = copiedValue;
    }else if(entry->type == Type::STRING){
        std::string* copiedValue = new std::string(*static_cast<std::string*>(value));
        entry->value = copiedValue;
    }else if(entry->type == Type::ARRAY){
        Array* copiedValue = new Array(*static_cast<Array*>(value));
        entry->value = copiedValue;
    }
    
    return entry;
}

// 데이터베이스를 초기화한다.
void init(Database &database){
    database.capacity = 65536 * 2;
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
        *copyEntry[i] = *currentEntry[i];
    }
}


// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry){
    // 넘칠라하면 늘리기
    if(database.capacity <= database.size){
        database.capacity *= 2;
        Entry ** newEntry = new Entry *[database.capacity];
        
        dataCopy(database, database.entry, newEntry);
        
        for (unsigned long long i = 0; i < database.size; i++) {
            std::cout<<database.entry[i]<<std::endl;
            delete database.entry[i]; 
        }
        // std::cout<<"4"<<std::endl;
        
        delete[] database.entry;
        // std::cout<<"4.5"<<std::endl;  
        database.entry = newEntry;
        // std::cout<<"5"<<std::endl;
        
    }

    database.entry[database.size] = entry;
    database.size++;
    // std::cout<<"6"<<std::endl;
        
    
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
            delEntryValue(database.entry[i]);
            delete database.entry[i];
            for(int index = i; index < database.size; index++){
                database.entry[i] = database.entry[i + 1];
            }
            database.size--;
            break;
        }
    }
}
void delArray(Array & array){
    if(&array != nullptr){
        if(array.type == Type::ARRAY){
            delArray(*(static_cast<Array*>(array.items)));
        }else{
            if(array.type == Type::INT){
                delete static_cast<int*>(array.items);
            }else if(array.type == Type::DOUBLE){
                delete static_cast<std::string*>(array.items);
            }else if(array.type == Type::STRING){
                delete static_cast<double*>(array.items);
            }
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
            delArray(*(static_cast<Array*>(entry->value)));
            delete static_cast<Array*>(entry->value);
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
