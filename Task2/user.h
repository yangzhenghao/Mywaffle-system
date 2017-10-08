#ifndef USER_H
#define USER_H
#include <QString>
#include <QVector>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <func.h>

//用户
class User
{

public:
    User(QString Name,QString id, QString Password, QString Gender, int Age);
    User();
    virtual ~User(){;}

    void setName(QString Name){name = Name;}
    void setId(QString id){Id = id;}
    void setAge(int Age){age = Age;}
    void setPassWord(QString password1);
    void setMd5PassWord(QString md5password){password = md5password;}
    void setGender(QString gen){gender = gen;}
    void setFocus(const QVector<QString>&a){foculist=a;}
    void setAnsList(const QVector<QString>&a){ansList=a;}
    void setQuesList(const QVector<QString>&a){quesList=a;}
    void ansAppend(QString id){ansList.append(id);std::sort(ansList.begin(),ansList.end());}
    void quesAppend(QString id){quesList.append(id);std::sort(quesList.begin(),quesList.end());}
    QString getName()const{return name;}
    QString getId()const{return Id;}
    QString getGender()const{return gender;}
    const QVector<QString>& getList()const{return foculist;}   //返回关注列表用户的ID
    const QVector<QString>& getAnsList()const{return ansList;}
    const QVector<QString>& getQuesList()const{return quesList;}
    int getAge(){return age;}

    bool operator <(const User &a)const {return Id < a.getId();}
    bool operator <(const QString aId)const {return Id < aId;}
    bool operator ==(const User &a)const {return Id == a.getId();}
    bool operator ==(const QString aId)const {return Id == aId;}
    bool passwordVerify(QString password1)const;

    void concernUser(QString userId);
    void disConcern(QString id);
    void save(QTextStream & a);
    friend QString md5(QString string);
    friend QTextStream & operator<<(QTextStream & a,const User &b);
    friend QTextStream &operator>>(QTextStream & a,User &b);
private:
    QString name;                                             //关注列表
    QString password;                                         //密码
    QString Id;                                               //id
    QString gender;                                           //性别
    int age;
    QVector<QString> foculist;                                //关注列表
    QVector<QString> ansList;                                 //回答列表
    QVector<QString> quesList;                                //问题列表
};
#endif // USER_H

