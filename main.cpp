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

void mainTui() {
    UserList userList;
    cout << "Reading Records From Disk : " ;
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
            } break;
            case 'l' : {
                string username , password ;
                cout << "Enter User Name : " ;
                cin >> username ;
                cout << "Enter Password : " ;
                cin >> password ;
                if ( userList.login( username , password ) ) {
                    cout << "Logged In Successfully!" << endl ;
                } else cout << "Logged In Failed!" << endl ;
            } break;
            case 'd' : {
                string username , password ;
                cout << "Enter User Name : " ;
                cin >> username ;
                cout << "Enter Password : " ;
                cin >> password ;
                userList.deleteUser( username , password ) ;
            } break;
            case 'q' : break;
            default: cout << "Invalid Choice!" << endl ;
        }
        cout << "Writing Changes To Disk : " ;
        userList.saveRecords() ;
        cout << "Transaction Complete" << endl << endl ;
    } while ( op != 'q' ) ;
}

void mainGui() {

}