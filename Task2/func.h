#include<QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <algorithm>
#include <user.h>
#include <answer.h>
#include <question.h>
#include <QTextStream>
#include <QFile>
#include <QTime>
#include <QDate>
#include<QDebug>

// 一些全局需要使用的函数
class User;
QString md5(QString string);                      //md5加密
bool numJutify(QString id);                       //判断是否是合法Id
bool dateStrJutify(QString date);                 //判断是否为合法的日期
User findUser(QString id);                        //寻找用户
void dataInit();                                  //初始化数据
bool comp(const Question &a,const Question &b);   //比较函数
bool comp1(const QString &a,const QString &b);
void save();
