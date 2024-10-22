//
// Created by sanjay on 22/10/24.
//

#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std ;

class User {

public:
    string name , password ;

public:
    string serialize() const ;

};

User *deserialize(string username , string password) ;

#endif //USER_H
