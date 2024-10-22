#ifndef USERLIST_H
#define USERLIST_H

#include <vector>

#include "User.h"

using namespace std ;

class UserList {

    vector <User*> users ;
    vector <User*> deleted ;
    vector <User*> added ;

public:
    void loadRecords() ;
    void saveRecords() ;
    void addUser(User *user) ;
    void deleteUser(User *user) ;
    void addUser( string username , string password ) ;
    [[nodiscard]] bool login(const string &username , const string &password ) const ;
    void deleteUser( const string& username , const string &password  ) ;

};



#endif //USERLIST_H
