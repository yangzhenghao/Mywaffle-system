#ifndef BASICINFO_H
#define BASICINFO_H
#include<QString>
#include<Qtime>
#include<Qdate>
#include<iostream>
#include<QTextStream>

//基本信息类
class BasicInfo
{
public:
    BasicInfo();
    BasicInfo(QString id,QString fid,QString content);
    virtual ~BasicInfo(){;}
    QString getId()const{return id;}                           //以下函数为返回某个属性，如id，创建者id，内容，创建时间等
    QString getfounderId()const{return founderId;}
    QString getContent()const{return content;}
    QTime getTime()const{return foundTime;}
    QDate getDate()const{return foundDate;}

    void setId(QString Id){id = Id;}                           //以下函数为修改某些基本属性,如ID，创建者Id等
    void setFounder(QString Id){founderId = Id;setDateAndTime();}
    void setContent(QString cont){content = cont;}
    void setFoundTime(QTime time){foundTime = time;}
    void setFoundDate(QDate date){foundDate= date;}
    void setDateAndTime();
    virtual void output(QTextStream &a)const =0;               //格式化输出属性
    virtual void add(QString contents)=0;                      //新建问题或者答案

    bool operator <(const BasicInfo &a)const;                  //重载一些运算符，便于一些需要判断的地方
    bool operator <(const QString &a)const;
    bool operator==(const BasicInfo &a)const{return a.getId()==this->getId();}
    bool operator==(const QString &a)const{return a==this->getId();}
private:
    QString id;                                                //基本属性，顾名思义
    QString founderId;
    QString content;
    QTime foundTime;
    QDate foundDate;
};

#endif // BASICINFO_H
