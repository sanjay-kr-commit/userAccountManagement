#include <QApplication>
#include <QPushButton>
#include <iostream>

#include "UserList.h"

using namespace std;

void mainTui() ;
void mainGui() ;

int main(int argc, char* argv[])
{
    if ( argc > 1 ) {
        string isGui = argv[1] ;
        if ( isGui == "--gui" ) {
            mainGui() ;
            return 0 ;
        }
    }
    mainTui() ;
    return 0 ;
}

void updateChanges( UserList userList ) {
    cout << endl << "Writing Changes To Disk " << endl ;
    userList.saveRecords() ;
    cout << "Transaction Complete" << endl << endl ;
}

void mainTui() {
    UserList userList;
    cout << "Reading Records From Disk " << endl ;
    userList.loadRecords() ;
    cout << "Transaction Complete" << endl << endl ;
    cout << "Here are List of operation\nl - login user\nr - register user\nd - delete user\nq - quit" << endl << endl;
    char op ;
    do {
        cout << "Enter your choice l , r , d , q : " ;
        cin >> op ;
        switch ( op ) {
            case 'r' : {
                string username , password ;
                cout << "Enter User Name : " ;
                cin >> username ;
                cout << "Enter Password : " ;
                cin >> password ;
                userList.addUser( username , password ) ;
                updateChanges(userList) ;
            } break;
            case 'l' : {
                string username , password ;
                cout << "Enter User Name : " ;
                cin >> username ;
                cout << "Enter Password : " ;
                cin >> password ;
                if ( userList.login( username , password ) ) {
                    cout << "Logged In Successfully!" << endl << endl ;
                } else cout << "Logged In Failed!" << endl << endl ;
            } break;
            case 'd' : {
                string username , password ;
                cout << "Enter User Name : " ;
                cin >> username ;
                cout << "Enter Password : " ;
                cin >> password ;
                userList.deleteUser( username , password ) ;
                updateChanges(userList) ;
            } break;
            case 'q' : break;
            default: cout << "Invalid Choice!" << endl ;
        }

    } while ( op != 'q' ) ;
}

void mainGui() {

}