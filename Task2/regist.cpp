#include "regist.h"

class Login;
extern QVector<User> allUsers;
extern Login *login;


//注册页面的布局
Regist::Regist(QDialog *parent):QDialog(parent)
{
    this->setWindowTitle("My waffle");
    //QIcon icon("resource/windows.ico");
    //this->setWindowIcon(icon);
    this->setStyleSheet("background-image:url(resource/background.png)");
    this->resize(300,255);
    this->setWindowFlags(Qt::FramelessWindowHint);
    userIdLabel.setText(QString("ID:"));
    userIdLabel.setGeometry(this->x()+30,this->y()+43,54,12);
    userIdLabel.setParent(this);
    userIdEdit.setGeometry(this->x()+120,this->y()+38,141,20);
    userIdEdit.setParent(this);


    userNameLabel.setText(QString("name:"));
    userNameLabel.setGeometry(this->x()+30,this->y()+72,54,12);
    userNameLabel.setParent(this);
    userNameEdit.setGeometry(this->x()+120,this->y()+67,141,20);
    userNameEdit.setParent(this);

    passwordLabel.setText(QString("password:"));
    passwordLabel.setGeometry(this->x()+30,this->y()+107,54,12);
    passwordLabel.setParent(this);
    passwordEdit.setGeometry(this->x()+120,this->y()+102,141,20);
    passwordEdit.setParent(this);

    ageLabel.setText("Age:");
    ageLabel.setGeometry(this->x()+30,this->y()+175,54,12);
    ageLabel.setParent(this);
    ageEdit.setGeometry(this->x()+120,this->y()+170,141,20);
    ageEdit.setParent(this);

    mainLabel.setText(QString("Register:"));
    ok.setText(QString("OK"));
    ok.setGeometry(this->x()+50,this->y()+210,81,21);
    ok.setParent(this);
    ok.setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");
    cancel.setText(QString("Cancel"));
    cancel.setGeometry(this->x()+155,this->y()+210,81,21);
    cancel.setParent(this);
    cancel.setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");

    QRegExp rs("[0-9]{10}");
    QValidator *validator = new QRegExpValidator(rs,this);
    userIdEdit.setValidator(validator);
    userIdLayout.addWidget(&userIdLabel);
    userIdLayout.addWidget(&userIdEdit);

    QRegExp rs1("[1-9][0-9]{0,1}");
    QValidator *validator1 = new QRegExpValidator(rs1,this);
    ageEdit.setValidator(validator1);
    ageLayout.addWidget(&ageLabel);
    ageLayout.addWidget(&ageEdit);

    userNameLayout.addWidget(&userNameLabel);
    userNameLayout.addWidget(&userNameEdit);

    passwordEdit.setEchoMode(QLineEdit::Password);
    passwordLayout.addWidget(&passwordLabel);
    passwordLayout.addWidget(&passwordEdit);

    male.setText("Male");
    male.setGeometry(this->x()+32,this->y()+136,91,20);
    male.setParent(this);
    female.setText("Female");
    female.setGeometry(this->x()+158,this->y()+136,91,20);
    female.setParent(this);
    gender.addButton(&male);
    gender.addButton(&female);
    gender.setExclusive(true);
    gender.setParent(this);

    connect(&cancel,SIGNAL(clicked()),this, SLOT(goLogin()));
    connect(&ok,SIGNAL(clicked()),this, SLOT(checked()));
}

//点击按钮，新建用户
void Regist::checked()
{
    bool flag = numJutify(userIdEdit.text().trimmed());
    QVector<User>::iterator it = nullptr;
    it = std::find(allUsers.begin(),allUsers.end(),userIdEdit.text().trimmed());
    flag = flag&(it == allUsers.end());               //判断是否存在
    if(flag)
    {
        QString name = userNameEdit.text().trimmed();
        QString id = userIdEdit.text().trimmed();
        QString password = passwordEdit.text().trimmed();
        QString sex = (male.isChecked())?QString("Male"):QString("Female");
        int age = ageEdit.text().toInt();
        User a(name, id, password, sex, age);
        it = std::lower_bound(allUsers.begin(),allUsers.end(),id);
        allUsers.insert(it,a);
        save();
        emit(newUser(a));
        accept();
    }
    else                                                //警告
    {
        QMessageBox message(QMessageBox::Warning,"Warning","Registed Before Or Wrong Id！",QMessageBox::Yes,NULL);
        message.setButtonText(QMessageBox::Yes,"Fine");
        message.exec();
    }
}

//返回
void Regist::goLogin()
{
    this->close();
}
