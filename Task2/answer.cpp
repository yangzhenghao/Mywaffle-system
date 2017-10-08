#include "answer.h"

//默认构造函数，未使用
answer::answer()
{

}

//析构函数
answer::~answer()
{

}

answer::answer(QString id,QString fid,QString content,int nums,QVector<QString> users):BasicInfo(id,fid,content),praiseNum(nums),
    praiseUser(users)
{

}

//点赞或取消
 void answer::praiseOrCancel(QString uid)
 {
     if(uid==this->getfounderId())
         return;
     QVector<QString>::iterator it = NULL;
     QVector<QString>::iterator it1 = NULL;
     it = std::find(praiseUser.begin(),praiseUser.end(),uid);
     it1 = std::find(dislikeUser.begin(),dislikeUser.end(),uid);
     if(it==praiseUser.end())
     {
         it = std::lower_bound(praiseUser.begin(),praiseUser.end(),uid);
         praiseUser.insert(it,uid);
         praiseNum +=1;
         if(it1!=dislikeUser.end())
         {
             dislikeNum-=1;
             dislikeUser.erase(it1);
         }
     }
     else
     {
         praiseUser.erase(it);                       //重复点赞取消
         praiseNum -=1;
         if(it1!=dislikeUser.end())
         {
             dislikeNum-=1;
             dislikeUser.erase(it1);
         }
     }
 }

 //讨厌此回答或者取消
 void answer::dislikeOrCancel(QString uid)
 {
     if(uid==this->getfounderId())
         return;
     QVector<QString>::iterator it = NULL;
     QVector<QString>::iterator it1 = NULL;
     it = std::find(dislikeUser.begin(),dislikeUser.end(),uid);
     it1= std::find(praiseUser.begin(),praiseUser.end(),uid);
     if(it==dislikeUser.end())
     {
         it = std::lower_bound(dislikeUser.begin(),dislikeUser.end(),uid);
         dislikeUser.insert(it,uid);
         dislikeNum+=1;
         if(it1!=praiseUser.end())
         {
             praiseUser.erase(it1);                  //点赞后再diss，取消
             praiseNum -=1;
         }
     }
     else
     {
         dislikeUser.erase(it);                       //重复点赞取消
         dislikeNum-=1;
         if(it1!=praiseUser.end())
         {
             praiseUser.erase(it1);                  //点赞后再diss，取消
             praiseNum -=1;
         }
     }
 }

 //虚函数，增加回答
void answer::add(QString contents)
{
    QVector<QString>::iterator it = NULL;
    it = std::lower_bound(praiseUser.begin(),praiseUser.end(),contents);
    praiseUser.insert(it,contents);                  //找到插入的地方
    praiseNum +=1;
}
//输出，按下面格式
void answer::output(QTextStream & a)const
{
    QDate a1=this->getDate();
    QTime b1=this->getTime();
    QString a11=a1.toString("yyyyMMdd");
    QString b11=b1.toString("hhmmss");

    a<<getId()<<" "<<getfounderId()<<" "<<getContent()<<" "<<a11<<" "
    <<b11<<" "<<QString::number(praiseNum,10);
    for(int i=0;i<praiseUser.size();i++)
        a<<" "<<praiseUser[i];

    a<<" "<<QString::number(dislikeNum,10);
    for(int i=0;i<dislikeNum;i++)
        a<<" "<<dislikeUser[i];
}
//重载左移运算符，输出
QTextStream& operator<<(QTextStream & a, answer & b)
{
    QDate a1=b.getDate();
    QTime b1=b.getTime();
    QString a11=a1.toString("yyyyMMdd");
    QString b11=b1.toString("hhmmss");
    a<<b.getId()<<" "<<b.getfounderId()<<" "<<b.getContent()<<" "<<a11<<" "
    <<b11<<" "<<QString::number(b.praiseNum,10);
    for(int i=0;i<b.praiseUser.size();i++)
        a<<" "<<b.praiseUser[i];

    a<<" "<<QString::number(b.dislikeNum,10);
    for(int i=0;i<b.dislikeNum;i++)
        a<<" "<<b.dislikeUser[i];
    a<<endl;
    return a;
}

//输入，重载右移运算符
QTextStream& operator>>(QTextStream & a, answer & b)
{
    QString temp;
    a>>temp;
    b.setId(temp);
    a>>temp;
    b.setFounder(temp);
    a>>temp;
    b.setContent(temp);

    a>>temp;
    int year=temp.mid(0,4).toInt();                  //设置日期
    int month = temp.mid(4,2).toInt();
    int day = temp.mid(6,2).toInt();
    QDate date(year,month,day);

    a>>temp;
    int hour = temp.mid(0,2).toInt();               //设置时间
    int minute = temp.mid(2,2).toInt();
    int sec = temp.mid(4,2).toInt();
    QTime time(hour,minute,sec);
    b.setFoundDate(date);
    b.setFoundTime(time);

    a>>temp;
    int num=temp.toInt();
    b.praiseNum=num;
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.praiseUser.append(temp);
    }

    a>>temp;
    num=temp.toInt();
    b.dislikeNum=num;
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.dislikeUser.append(temp);
    }
    return a;
}
