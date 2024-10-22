#include "gui.h"

#include <iostream>

#include "ui_gui.h"

gui::gui(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::gui)
{
    m_ui->setupUi(this);

}

gui::~gui() = default;

// void gui::on_login_clicked() {
//     m_ui->login->setText( "Hello World" ) ;
// }


#include "moc_gui.cpp"
