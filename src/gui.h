#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

#include <memory>

namespace Ui {
class gui;
}

class gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui(QWidget *parent = nullptr);
    ~gui() override;

    const std::unique_ptr<Ui::gui> m_ui;

    // private slots:
    // void on_login_clicked();

};

#endif // GUI_H
