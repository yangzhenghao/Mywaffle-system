#include "user.h"

User::User():name("NULL"),password("NULL"),Id("NULL"),gender("Male"),age(0)
{

}
//用户信息
User::User(QString Name,QString id, QString Password, QString Gender, int Age)
    :name(Name),Id(id),password(md5(Password)),gender(Gender),age(Age)
{

}

//验证密码
bool User::passwordVerify(QString password1)const
{
    return password1 == password;
}
//设置密码
void User::setPassWord(QString password1)
{
    this->password=md5(password1);
}

//关注用户
void User::concernUser(QString userId)
{
    QVector<QString>::iterator find=NULL;
    find = std::lower_bound(foculist.begin(),foculist.end(),userId);
    if(userId==Id)
        return;
    //if(find!=foculist.end()&&*find==userId)
      //  disConcern(userId);
    if(find==foculist.end()||*find!=userId)
        foculist.insert(find,userId);
}

//取消关注
void User::disConcern(QString uid)
{
    QVector<QString>::iterator it = NULL;
    it = std::lower_bound(foculist.begin(),foculist.end(),uid);
    if(it==foculist.end())                          //判断是否含有
        return;
    if(*it == uid)
    {
        foculist.erase(it);
    }

}


//保存信息
void User::save(QTextStream & a)
{
    a<<Id<<" "<<name<<" "<<password<<" "<<gender<<" "<<QString::number(age,10)<<" ";
    a<<QString::number(foculist.size(),10);
    for(int i=0;i<foculist.size();i++)
        a<<" "<<foculist[i];
    a<<" "<<QString::number(quesList.size(),10);
    for(int i=0;i<quesList.size();i++)
        a<<" "<<quesList[i];
    a<<" "<<QString::number(ansList.size(),10);
    for(int i=0;i<ansList.size();i++)
        a<<" "<<ansList[i];

}

//重载左移右移运算符，输出
QTextStream & operator<<(QTextStream & a,const User &b)
{
    a<<b.Id<<" "<<b.name<<" "<<b.password<<" "<<b.gender<<" "<<QString::number(b.age,10)<<" ";
    a<<QString::number(b.foculist.size(),10);
    for(int i=0;i<b.foculist.size();i++)
        a<<" "<<b.foculist[i];
    a<<" "<<QString::number(b.quesList.size(),10);
    for(int i=0;i<b.quesList.size();i++)
        a<<" "<<b.quesList[i];
    a<<" "<<QString::number(b.ansList.size(),10);
    for(int i=0;i<b.ansList.size();i++)
        a<<" "<<b.ansList[i];
    a<<endl;
    return a;
}
//同上，功能相反
QTextStream &operator>>(QTextStream & a,User &b)
{
    a>>b.Id>>b.name>>b.password>>b.gender;
    QString temp;
    a>>temp;
    b.age=temp.toInt();
    int num;
    a>>temp;
    num=temp.toInt();
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.foculist.append(temp);
    }
    a>>temp;
    num=temp.toInt();
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.quesList.append(temp);
    }
    a>>temp;
    num=temp.toInt();
    for(int i=0;i<num;i++)
    {
        a>>temp;
        b.ansList.append(temp);
    }
    return a;
}
