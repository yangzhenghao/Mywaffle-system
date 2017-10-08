#include "login.h"

//extern QWidget w;
extern QVector<User> allUsers;
extern User presentUser;

//登录
Login::Login(QWidget * parent):QDialog(parent)
{
    //setWindowIcon(QIcon("/option/titlebarImages/library->png"));
    this->setStyleSheet("background-image:url(resource/background.png)");
    QIcon icon("resource/windows.ico");
    this->setWindowIcon(icon);                        //设置页面
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(350, 260);

    userNameLabel = new QLabel;
    userNameLabel->setGeometry(this->x()+30,this->y()+65,64,12);
    userNameLabel->setParent(this);                   //布局

    passwordLabel = new QLabel;
    passwordLabel->setGeometry(this->x()+30,this->y()+135,64,12);
    passwordLabel->setParent(this);

    mainLabel = new QLabel;
    mainLabel->setGeometry(this->x()+120,this->y()+20,110,30);
    mainLabel->setParent(this);
    login = new QPushButton;
    login->setGeometry(this->x()+46,this->y()+180,101,21);
    login->setParent(this);

    regist = new QPushButton;
    regist->setGeometry(this->x()+233,this->y()+180,111,21);
    regist->setParent(this);

    Exit = new QPushButton;
    Exit->setGeometry(this->x()+138,this->y()+230,111,21);
    Exit->setParent(this);

    userNameEdit = new QLineEdit;
    userNameEdit->setGeometry(this->x()+130,this->y()+60,131,20);
    userNameEdit->setParent(this);

    passwordEdit = new QLineEdit;
    passwordEdit->setGeometry(this->x()+130,this->y()+130,131,20);
    passwordEdit->setParent(this);

    userLayout = new QHBoxLayout;                    //布局
    mainLabellayout = new QHBoxLayout;
    passwordLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    vlayout  = new QVBoxLayout;

    mainLabel->setText("  SIGN IN");
    mainLabel->setStyleSheet("color:rgb(42,73,104);font-weight:bold;font-size:20px;font-family:segoe");
    userNameLabel->setText("    用户: ");
    userNameLabel->setStyleSheet("color:rgb(42,73,104);font-weight:bold;font-size:13px");
    userLayout->addWidget(userNameLabel);
    userLayout->addWidget(userNameEdit);

    passwordLabel->setText("    密码: ");
    passwordLabel->setStyleSheet("color:white;font-weight:bold;font-size:13px");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    login->setText("Login");
    login->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");

    regist->setText("Register");
    regist->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");
    Exit->setText("Exit");
    Exit->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");
    mainLabellayout->addWidget(mainLabel,0,Qt::AlignCenter);
    buttonLayout->addWidget(login);
    buttonLayout->addWidget(regist);
    /*vlayout->addSpacing(10);
    vlayout->addWidget(mainLabel);
    vlayout->addLayout(userLayout);
    vlayout->addLayout(passwordLayout);
    vlayout->addLayout(buttonLayout);
    vlayout->addWidget(Exit);
    setLayout(vlayout);
*/
    QWidget::setTabOrder(userNameEdit,passwordEdit);

    connect(login,SIGNAL(clicked()),this,SLOT(checkPushed()));
    connect(regist,SIGNAL(clicked()),this,SLOT(Register()));
    connect(Exit,SIGNAL(clicked()),this, SLOT(close()));
}

//析构函数
Login::~Login()
{
    delete userNameLabel;
    delete passwordLabel;
    delete mainLabel;
    delete login;
    delete regist;
    delete Exit;
    delete userNameEdit;
    delete passwordEdit;
    delete userLayout;
    delete passwordLayout;
    delete buttonLayout;
    delete vlayout;
}

//判断用户信息是否合法
bool Login::checkInfo(QString nameID, QString password)
{
    if(nameID.length()!=10||!numJutify(nameID))
        return false;
    QVector<User>::iterator it = NULL;
    it = std::find(allUsers.begin(),allUsers.end(),nameID);
    if(it == allUsers.end())
        return false;

    bool isTrue = it->passwordVerify(md5(password));
    if(!isTrue)
        return false;
    return true;
}


void Login::checkPushed()
{
    QString text1=userNameEdit->text().trimmed();
    QString text2=passwordEdit->text().trimmed();
   bool checked = checkInfo(text1,text2);
   if(!checked)
   {
       passwordEdit->clear();
       userNameEdit->clear();
       QMessageBox message(QMessageBox::Warning,"Warning","Wrong user or Wrong password！",QMessageBox::Yes,NULL);
       message.setButtonText(QMessageBox::Yes,"Fine");
       message.exec();
   }
   else
   {
       presentUser = *(std::find(allUsers.begin(),allUsers.end(),userNameEdit->text()));
       accept();
   }
}

void Login::Register()
{
    Regist *a = new Regist;
    this->close();
    a->show();
    if(a->exec() == QDialog::Accepted)
    {
        this->show();
        this->exec();
        this->done(100);
    }
    else
    {
        this->show();
        this->exec();
        this->done(100);
        //delete a;
    }
}

