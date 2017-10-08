#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QString>
#include <QWidget>
#include <QLabel>
#include <user.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <regist.h>
#include <QPushButton>
#include <QVector>
#include <func.h>
#include <user.h>

//用户基本信息
class UserInformation:public QWidget
{
    Q_OBJECT
public:
    UserInformation(QWidget *parent=0);
    void renew();
private:
    QLabel mainLable;                            //界面主标签
    QLabel userName;                             //用户名标签
    QLabel userId;                               //性别标签
    QLabel userGender;                           //性别标签
    QLabel userAge;                              //年纪标签
    QHBoxLayout mainLabelLayout;                 //布局标签
    QHBoxLayout userNameLayut;
    QHBoxLayout userIdLayout;
    QHBoxLayout userGenderLayout;
    QHBoxLayout userAgeLayout;
    QHBoxLayout buttonLayout;
    QPushButton changeButton;
    QVBoxLayout labelLayout;
signals:
    void userNameChange(QString);
public slots:
    void change();
    void changePresentUser(User user);           //目前用户改变了
};

#endif // USERINFORMATION_H
