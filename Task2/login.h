#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QPushButton>
#include <regist.h>
#include<user.h>
#include <QIcon>
#include <algorithm>
#include <QMessageBox>
#include <QCloseEvent>
#include <func.h>

//登录框体
class Login : public QDialog
{
    Q_OBJECT
public:
    Login(QWidget * parent = 0);
    ~Login();
    void closeEvent(QCloseEvent * e){Q_UNUSED(e);this->close();}
    bool checkInfo(QString name, QString password);
    QLabel *userNameLabel;                     //全是框体有关的窗格，用户名标题，密码标题，界面主标题
    QLabel *passwordLabel;
    QLabel *mainLabel;
    QPushButton *login;                        //一些功能性按钮
    QPushButton *regist;
    QPushButton *Exit;
    QLineEdit *userNameEdit;                   //输入框
    QLineEdit *passwordEdit;
    QHBoxLayout *mainLabellayout;              //布局
    QHBoxLayout *userLayout;
    QHBoxLayout *passwordLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *vlayout;

public slots:
    void checkPushed();
    void Register();
};

#endif // LOGIN_H
