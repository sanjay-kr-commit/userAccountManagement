//
// Created by sanjay on 22/10/24.
//

#include "UserList.h"
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <utility>

#include "StaticVariables.h"

using namespace std;

bool UserList::login(const string &username , const string &password ) const {
    for (const User *user : users ) {
        if ( user->name == username && user->password == password ) {
            return true;
        }
    }
    for (const User *user : added ) {
        if ( user->name == username && user->password == password ) {
            return true;
        }
    }
    return false ;
}

void UserList::addUser(User *user) {
    added.push_back(user);
}

void UserList::addUser(string username, string password) {
    addUser( deserialize( std::move(username) , std::move(password) ) ) ;
}

void UserList::deleteUser(User *user) {
    vector<User *> changes;
    for ( User *it : users ) {
        if ( it != user ) changes.push_back(it);
    }
    users.clear();
    for ( User *it : changes ) {
        users.push_back(it);
    }
    deleted.push_back(user);
}

void UserList::deleteUser( const string& username , const string &password ) {
    for ( User *user : users ) {
        if ( user->name == username && user->password == password ) {
            deleteUser( user ) ;
        }
    }
}

void UserList::loadRecords() {
    ifstream records ;
    records.open( RECORD_FILE );
    if ( !records.is_open() ) {
        cout << "Record Doesn't Exists" << endl ;
        ofstream emptyFile;
        emptyFile.open (RECORD_FILE, ios::out);
        emptyFile.close() ;
        records.close();
        return;
    }
    string username , password ;
    while ( getline( records , username ) ) {
        if ( getline( records , password ) )
            users.push_back( deserialize( username , password )  ) ;
    }
    records.close();
}

void UserList::saveRecords()  {
    ifstream records ;
    ofstream tempRecordFile ;
    records.open( RECORD_FILE ) ;
    tempRecordFile.open( TEMP_RECORD_FILE ) ;
    bool changes = false ;
    // commit delete changes
    if ( !deleted.empty() ) {
        changes = true ;
        unordered_set<string> set ;
        for ( User *user : deleted ) {
            set.insert( user->name ) ;
            free( user ) ;
        }
        deleted.clear() ;
        string username , password ;
        while ( getline( records , username ) ) {
            if ( getline( records , password ) && !set.contains( username ) ) {
                tempRecordFile << username << "\n" << password << endl ;
            }
        }
        set.clear() ;
    }
    // commit add changes
    if ( !added.empty() ) {
        if ( !changes ) {
            string username , password ;
            while ( getline( records , username ) ) {
                if ( getline( records , password )) {
                    tempRecordFile << username << "\n" << password << endl ;
                }
            }
        }
        changes = true ;
        for ( User *user : added ) {
            tempRecordFile << user->serialize() ;
            users.push_back(user) ;
        }
        added.clear() ;
    }
    records.close() ;
    tempRecordFile.close() ;
    if ( changes ) {
        remove( RECORD_FILE.c_str() ) ;
        rename( TEMP_RECORD_FILE.c_str() , RECORD_FILE.c_str() ) ;
    }
}