#include "User.h"
#include <iostream>
#include <utility>

using namespace std;

string User::serialize() const {
    return name + "\n" + password ;
}

User *deserialize(string username , string password) {
    User *user = new User();
    user->name = move(username) ;
    user->password = move(password) ;
    return user ;
}
