#ifndef REGIST_H
#define REGIST_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLayout>
#include <QVBoxLayout>
#include <QValidator>
#include <QRegExpValidator>
#include <QButtonGroup>
#include <QRadioButton>
#include <user.h>
#include <QMessageBox>
#include <func.h>

//注册类
class Regist : public QDialog
{
    Q_OBJECT
public:
    Regist(QDialog *parent=0);
    QLabel userIdLabel;                 //一些主要的标签，用户id，用户名，密码，性别，年龄
    QLabel userNameLabel;
    QLabel passwordLabel;
    QLabel mainLabel;
    QLabel ageLabel;
    QPushButton ok;                     //功能按钮
    QPushButton cancel;
    QLineEdit userNameEdit;             //输入框
    QLineEdit passwordEdit;
    QLineEdit userIdEdit;
    QLineEdit ageEdit;
    QRadioButton male;
    QRadioButton female;
    QButtonGroup gender;
    QHBoxLayout userNameLayout;         //布局
    QHBoxLayout userIdLayout;
    QHBoxLayout passwordLayout;
    QHBoxLayout buttonLayout;
    QHBoxLayout genderLayout;
    QHBoxLayout ageLayout;
    QVBoxLayout vlayout;

public slots:
    void checked();                     //ok
    void goLogin();                     //取消

signals:
    void newUser(User user);
};

#endif // REGIST_H
