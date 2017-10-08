#ifndef ANSWER_H
#define ANSWER_H
#include<basicinfo.h>
#include<QVector>
#include<QString>
#include<algorithm>

//回答类，共有继承自基本信息类
class answer:public BasicInfo
{
public:
    answer();
    ~answer();
    answer(QString id,QString fid,QString content,int nums,QVector<QString> users);
    void praiseOrCancel(QString uid);                               //点赞或者取消
    void dislikeOrCancel(QString uid);
    void setPraiseUserList(const QVector<QString> &a){praiseUser=a;}//设置一些基本信息
    void setDislikeUserList(const QVector<QString> &a){dislikeUser=a;}
    void setPraiseNum(int x){praiseNum=x;}
    void setDislikeNum(int x){dislikeNum=x;}
    int getPraiseTime()const{return praiseNum;}                     //返回点赞数
    int getDislikeTime()const{return dislikeUser.size();}
    friend QTextStream& operator<<(QTextStream & a, answer & b);
    friend QTextStream& operator>>(QTextStream & a, answer & b);
    virtual void output(QTextStream & a)const;                      //输出
    virtual void add(QString contents);
    bool operator ==(const QString id){return this->getId()==id;}   //重载运算符，便于一些判断操作
    bool operator ==(answer &a){return this->getId()==a.getId();}
    bool operator <(answer&a){return this->getId()<a.getId();}
    bool operator <(const QString id){return this->getId()<id;}
private:
    int praiseNum;                                                  //点赞数
    int dislikeNum;
    QVector<QString> praiseUser;                                    //点赞的用户
    QVector<QString> dislikeUser;
};
#endif // ANSWER_H
