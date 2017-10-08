#ifndef QUESTION_H
#define QUESTION_H
#include <basicinfo.h>
#include <QVector>
#include <QString>

//问题类，继承自基本信息类
class Question:public BasicInfo
{
public:
    Question();
    Question(QString id,QString fid,QString content,QString Title,const QVector<QString>& alist);

    void setTitle(QString Title){title = Title;}                           //修改自身属性
    void setAnsList(QVector<QString> alist){answerlist = alist;}
    void autoSetFounderId(){this->setFounder(this->getId().mid(14,10));}
    void setIDx(QString Id){this->setId(Id);autoSetFounderId();setDateAndTime();}
    void append(QString ansId){answerlist.append(ansId);}                  //添加回答列表
    QString at(int i){return answerlist.at(i);}                            //返回基本信息
    QString getTitle()const{return title;}
    const QVector<QString>& getAnsList()const{return answerlist;}
    int getAnsLisSize(){return answerlist.size();}
    virtual void output(QTextStream &a)const;
    virtual void add(QString contents){answerlist.insert(answerlist.begin(),contents);}

    friend QTextStream& operator<<(QTextStream & a, Question & b);         //重载左移右移运算符，便于输入输出
    friend QTextStream& operator>>(QTextStream & a, Question & b);
private:
    QString title;
    QVector<QString> answerlist;                                           //回答列表，储存的是回答的id
};

#endif // QUESTION_H
