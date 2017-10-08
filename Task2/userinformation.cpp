#include "userinformation.h"

extern User presentUser;
extern QVector<User> allUsers;

//用户的基本信息，构造函数，布局
UserInformation::UserInformation(QWidget* parent):QWidget(parent)
{
    this->resize(275,306);

    this->userAge.setText(QString("年龄:")+QString::number(presentUser.getAge(),10));      //设置基本信息
    userAge.setStyleSheet("color:rgb(52,73,104);font-weight:bold;font-size:13px;font-family:‘cursive’");
    this->userGender.setText(QString("性别:")+presentUser.getGender());
    userGender.setStyleSheet("color:rgb(52,73,104);font-weight:bold;font-size:13px;font-family:‘cursive’");
    this->userId.setText(QString("ID:")+presentUser.getId());
    userId.setStyleSheet("color:rgb(52,73,104);font-weight:bold;font-size:13px;font-family:‘cursive’");
    this->userName.setText(QString("名字：")+ presentUser.getName());
    userName.setStyleSheet("color:white;font-weight:bold;font-size:13px;font-family:‘cursive’");
    this->mainLable.setText("User Basic Information");
    mainLable.setStyleSheet("color:white;font-weight:bold;font-size:20px;font-family:‘cursive’");
    this->changeButton.setText("修改信息");
    changeButton.setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");;
    changeButton.resize(35,23);


    mainLabelLayout.addWidget(&mainLable,0,Qt::AlignCenter);                               //布局
    userNameLayut.addWidget(&userName,0,Qt::AlignCenter);
    userIdLayout.addWidget(&userId,0,Qt::AlignCenter);
    userGenderLayout.addWidget(&userGender,0,Qt::AlignCenter);
    userAgeLayout.addWidget(&userAge,0,Qt::AlignCenter);
    buttonLayout.addWidget(&changeButton,0,Qt::AlignCenter);

    labelLayout.addItem(&mainLabelLayout);                                                //中布局
    labelLayout.addItem(&userNameLayut);
    labelLayout.addItem(&userIdLayout);
    labelLayout.addItem(&userGenderLayout);
    labelLayout.addItem(&userAgeLayout);
    labelLayout.addItem(&buttonLayout);
    labelLayout.setSpacing(10);
    this->setLayout(&labelLayout);

    connect(&changeButton,SIGNAL(clicked()),this,SLOT(change()));
}

//更新界面
void UserInformation::renew()
{
    this->userAge.setText(QString("年龄:        ")+QString::number(presentUser.getAge(),10));
    this->userGender.setText(QString("性别:       ")+presentUser.getGender());
    this->userId.setText(QString("ID:       ")+presentUser.getId());
    this->userName.setText(QString("名字：     ")+ presentUser.getName());
}

//更改信息
void UserInformation::change()
{
    User temp = presentUser;
    QString id = presentUser.getId();
    QVector<User>::iterator it = nullptr;
    it = std::find(allUsers.begin(),allUsers.end(),id);
    temp =*it;
    allUsers.erase(it);                 //擦除原来的信息
    Regist a;
    a.show();
    connect(&a,SIGNAL(newUser(User)),this,SLOT(changePresentUser(User)));
    if(a.exec()==QDialog::Accepted)     //更改了
    {
        renew();
        emit userNameChange(presentUser.getName());
        save();
        a.close();
    }
    else                                //没更改
    {
        allUsers.insert(it,temp);
        a.close();
    }
}
void UserInformation::changePresentUser(User user)
{
    presentUser = user;
}
