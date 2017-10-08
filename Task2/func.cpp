#include<func.h>

extern QVector<User> allUsers;
extern QVector<answer> answers;
extern QVector<Question> questions;
extern User presentUser;
extern Question presentQuest;

//给密码md5加密
QString md5(QString string)
{
    QString Md5;
    QByteArray bb;
    bb = QCryptographicHash::hash(string.toLatin1(), QCryptographicHash::Md5);
    Md5.append(bb.toHex());
    return Md5;
}

//判断是否是合法的id
bool numJutify(QString id)
{
    if(id.length()<10)
        return false;
    for(auto i:id)
        if(i>'9'||i<'0')
            return false;
    return true;
}
//判断是否是合法的日期
bool dateStrJutify(QString date)
{
    for(auto i:date)
    {
        if(i>'9'||i<'0')
            return false;
    }
    return true;
}
//按照用户id寻找用户
User findUser(QString id)
{
    QVector<User>::iterator it = nullptr;
    it = std::find(allUsers.begin(),allUsers.end(),id);
    if(it!=allUsers.end())
        return *it;
    else
    {
        return User();
    }
}
//比较
bool comp(const Question &a,const Question &b)
{
    return !(a.getId()<b.getId());
}
//比较
bool comp1(const QString &a,const QString &b)
{
    return !(a<b);
}
//数据初始化
void dataInit()
{
    QFile file("records/user.txt");                  //关联文件
    try                                              //错误处理
    {
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
            throw(QString("Open error"));
    }
    catch(QString a)
    {
        qDebug()<<a;
    }

    QTextStream in(&file);
    User a;
    QString str;

    while(!in.atEnd())                              //按照格式读取信息
    {
        QVector<QString> slist,slist1,slist2;
        in>>str;
        if(str=="")
            break;
        a.setId(str);
        in>>str;
        a.setName(str);
        in>>str;
        a.setMd5PassWord(str);
        in>>str;
        a.setGender(str);
        in>>str;
        a.setAge(str.toInt());
        in>>str;
        int nums = str.toInt();
        for(int i=0;i<nums;i++)
        {
            in>>str;
            slist.append(str);
        }
        in>>str;
        nums=str.toInt();
        for(int i=0;i<nums;i++)
        {
            in>>str;
            slist1.append(str);
        }

        in>>str;
        nums=str.toInt();
        for(int i=0;i<nums;i++)
        {
            in>>str;
            slist2.append(str);
        }

        std::sort(slist.begin(),slist.end());     //对信息排序
        std::sort(slist1.begin(),slist1.end(),comp1);
        std::sort(slist2.begin(),slist2.end(),comp1);
        a.setFocus(slist);
        a.setQuesList(slist1);
        a.setAnsList(slist2);
        allUsers.append(a);
    }
    file.close();

    QFile file1("records/answers.txt");          //同上，初始化所有的回答
    try
    {
        if(!file1.open(QIODevice::ReadOnly|QIODevice::Text))
            throw(QString("Open error"));
    }
    catch(QString a)
    {
        qDebug()<<a;
    }
    QTextStream in1(&file1);

    answer a1;
    while(!in1.atEnd())
    {
        QVector<QString> slist;
        QVector<QString> slist1;
        in1>>str;
        if(str=="")
            break;
        a1.setId(str);
        in1>>str;
        a1.setFounder(str);
        in1>>str;
        a1.setContent(str);

        in1>>str;
        int year = (str.mid(0,4)).toInt();
        int month = (str.mid(4,2)).toInt();
        int day = (str.mid(6,2)).toInt();

        in1>>str;
        int hour = str.mid(0,2).toInt();
        int minute = str.mid(2,2).toInt();
        int sec = str.mid(4,2).toInt();

        QTime foundTime = QTime(hour,minute,sec);
        QDate foundDate = QDate(year,month,day);
        a1.setFoundDate(foundDate);
        a1.setFoundTime(foundTime);

        in1>>str;
        int nums = str.toInt();
        a1.setPraiseNum(nums);
        for(int i=0;i<nums;i++)
        {
            in1>>str;
            slist.append(str);
        }

        in1>>str;
        nums = str.toInt();
        a1.setDislikeNum(nums);
        for(int i=0;i<nums;i++)
        {
            in1>>str;
            slist1.append(str);
        }
        std::sort(slist.begin(),slist.end());
        std::sort(slist1.begin(),slist1.end());
        a1.setPraiseUserList(slist);
        a1.setDislikeUserList(slist1);
        answers.append(a1);
    }
    file1.close();


    QFile file2("records/question.txt");                   //问题
    try
    {
        if(!file2.open(QIODevice::ReadOnly|QIODevice::Text))
            throw(QString("Open error"));
    }
    catch(QString a)
    {
        qDebug()<<a;
    }
    QTextStream in2(&file2);

    Question a2;
    while(!in2.atEnd())
    {
        QVector<QString> slist;
        in2>>str;
        if(str=="")
            break;
        a2.setTitle(str);
        in2>>str;
        a2.setIDx(str);
        in2>>str;
        a2.setContent(str);
        in2>>str;
        int nums = str.toInt();
        for(int i=0;i<nums;i++)
        {
            in2>>str;
            slist.append(str);
        }
        std::sort(slist.begin(),slist.end());  //这句话有点问题
        a2.setAnsList(slist);
        questions.append(a2);
    }
    file2.close();
    std::sort(questions.begin(),questions.end(),comp);
}

void save()
{
    try
    {QFile file("records/user.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in(&file);
    for(int i=0;i<allUsers.size();i++)
    {
        if(i!=allUsers.size()-1)
            in<<allUsers[i];
        else                             //最后一个数据特殊处理
            allUsers[i].save(in);
    }
    file.close();
    QFile file1("records/question.txt"); //打开文件
    if(!file1.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in1(&file1);
    for(int i=0;i<questions.size();i++)
    {
        if(i!=questions.size()-1)
            in1<<questions[i];
        else
            questions[i].output(in1);
    }
    file1.close();
    QFile file2("records/answers.txt");
    if(!file2.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in2(&file2);
    for(int i=0;i<answers.size();i++)
    {
        if(i!=answers.size()-1)
            in2<<answers[i];
        else
            answers[i].output(in2);
    }
    file2.close();
    }
    catch(...)
    {
        qDebug()<<"Wrong with the file";
    }
}
