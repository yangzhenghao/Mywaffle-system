#include "question.h"


//默认构造函数
Question::Question():title("")
{

}

//构造函数
Question::Question(QString id,QString fid,QString content,QString Title,const QVector<QString>& alist):BasicInfo(id,fid,content),title(Title)
  ,answerlist(alist)
{
    setDateAndTime();
    autoSetFounderId();
}

//重载输出运算符
QTextStream& operator<<(QTextStream & a, Question & b)
{
    a<<b.title<<" "<<b.getId()<<" "<<b.getContent()<<" "<<
       QString::number(b.answerlist.size(),10);
    for(int i=0;i<b.answerlist.size();i++)
        a<<" "<<b.answerlist[i];
    a<<endl;
    return a;
}
QTextStream& operator>>(QTextStream & a, Question & b)
{
    QString temp;
    a>>b.title;
    a>>temp;
    b.setId(temp);
    a>>temp;
    b.setContent(temp);
    int num;
    a>>temp;
    num = temp.toInt();
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.answerlist.append(temp);
    }
    return a;
}
//输出
void Question::output(QTextStream &a)const
{
    a<<title<<" "<<getId()<<" "<<getContent()<<" "<<
       QString::number(answerlist.size(),10);
    for(int i=0;i<answerlist.size();i++)
        a<<" "<<answerlist[i];
}
