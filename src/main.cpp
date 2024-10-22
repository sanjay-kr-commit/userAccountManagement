#include <iostream>
#include <ui_gui.h>
#include "UserList.h"
#include "gui.h"

using namespace std;

void mainTui( UserList userList ) ;
int mainGui( int argc, char *argv[] , UserList *userList ) ;

int main(int argc, char* argv[])
{
    UserList userList;
    cout << "Reading Records From Disk " << endl ;
    userList.loadRecords() ;
    cout << "Transaction Complete" << endl << endl ;
    //return mainGui( argc, argv , &userList ) ;
    if ( argc > 1 ) {
        string isGui = argv[1] ;
        if ( isGui == "--gui" ) return mainGui( argc, argv , &userList ) ;
    }
    mainTui( userList ) ;
    return 0 ;

}

void updateChanges( UserList userList ) {
    cout << endl << "Writing Changes To Disk " << endl ;
    userList.saveRecords() ;
    cout << "Transaction Complete" << endl << endl ;
}

void mainTui( UserList userList ) {
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

int mainGui( int argc, char *argv[], UserList *userList ) {
    QApplication app(argc,argv );
    auto guiWindow = new gui;
    QObject::connect(guiWindow->m_ui->register_2, &QPushButton::clicked, [guiWindow,&userList]() {
        QString username = guiWindow->m_ui->username->toPlainText() ,
               password = guiWindow->m_ui->passowrd->toPlainText() ;
        if ( username.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Username Cannot Be Empty" ) ;
        else if ( password.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Password Cannot Be Empty" ) ;
        else {
            userList->addUser( username.toStdString() , password.toStdString() ) ;
            updateChanges( *userList ) ;
            guiWindow->m_ui->logMessage->setText( "Registered Successfully!" ) ;
        }
    });
    QObject::connect(guiWindow->m_ui->login, &QPushButton::clicked, [guiWindow,&userList] {
        QString username = guiWindow->m_ui->username->toPlainText() ,
               password = guiWindow->m_ui->passowrd->toPlainText() ;
        if ( username.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Username Cannot Be Empty" ) ;
        else if ( password.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Password Cannot Be Empty" ) ;
        else {
            if ( userList->login( username.toStdString() , password.toStdString() ) ) {
                guiWindow->m_ui->logMessage->setText( "Logged In Successfully!" ) ;
            } else {
                guiWindow->m_ui->logMessage->setText( "Login Failed!" ) ;
            }
        }
    });
    QObject::connect(guiWindow->m_ui->delete_2, &QPushButton::clicked, [guiWindow,&userList] {
        QString username = guiWindow->m_ui->username->toPlainText() ,
               password = guiWindow->m_ui->passowrd->toPlainText() ;
        if ( username.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Username Cannot Be Empty" ) ;
        else if ( password.isEmpty() ) guiWindow->m_ui->logMessage->setText( "Password Cannot Be Empty" ) ;
        else {
            userList->deleteUser( username.toStdString() , password.toStdString() ) ;
            updateChanges( *userList ) ;
            guiWindow->m_ui->logMessage->setText( "Deleted User Successfully!" ) ;
        }
    });

    guiWindow->setFixedSize( 1000 , 480 ) ;
    guiWindow->show();

    return app.exec();
}

