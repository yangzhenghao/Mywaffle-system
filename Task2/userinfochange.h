#ifndef USERINFOCHANGE_H
#define USERINFOCHANGE_H

#include <QWidget>
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
class userInfoChange : public QDialog
{
    Q_OBJECT
public:
    userInfoChange(QDialog *parent=0);
    QLabel userNameLabel;
    QLabel passwordLabel;
    QLabel mainLabel;
    QLabel ageLabel;
    QPushButton ok;
    QPushButton cancel;
    QLineEdit userNameEdit;
    QLineEdit passwordEdit;
    QLineEdit ageEdit;
    QRadioButton male;
    QRadioButton female;
    QButtonGroup gender;
    QHBoxLayout userNameLayout;
    QHBoxLayout userIdLayout;
    QHBoxLayout passwordLayout;
    QHBoxLayout buttonLayout;
    QHBoxLayout genderLayout;
    QHBoxLayout ageLayout;
    QVBoxLayout vlayout;

public slots:
    void checked();
    void goLogin();

signals:
    void newUser(User user);
};

#endif // USERINFOCHANGE_H
