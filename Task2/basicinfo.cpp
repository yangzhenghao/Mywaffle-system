#include "basicinfo.h"

BasicInfo::BasicInfo()
{

}

//构造函数，question的id=日期+时间+用户id
BasicInfo::BasicInfo(QString Id,QString fid,QString Cont):id(Id),founderId(fid),content(Cont)
{
    QString fdate = id.mid(0,8);
    QString ftime = id.mid(8,6);
    int year = (fdate.mid(0,4)).toInt();
    int month = (fdate.mid(4,2)).toInt();
    int day = (fdate.mid(6,2)).toInt();

    int hour = ftime.mid(0,2).toInt();
    int minute = ftime.mid(2,2).toInt();
    int sec = ftime.mid(4,2).toInt();

    foundTime = QTime(hour,minute,sec);
    foundDate = QDate(year,month,day);
}

//设置创建日期和时间
void BasicInfo::setDateAndTime()
{
    QString fdate = id.mid(0,8);
    QString ftime = id.mid(8,6);
    int year = (fdate.mid(0,4)).toInt();
    int month = (fdate.mid(4,2)).toInt();
    int day = (fdate.mid(6,2)).toInt();

    int hour = ftime.mid(0,2).toInt();
    int minute = ftime.mid(2,2).toInt();
    int sec = ftime.mid(4,2).toInt();

    foundTime = QTime(hour,minute,sec);
    foundDate = QDate(year,month,day);
}
//重载小于运算符，便于判断
bool BasicInfo::operator <(const BasicInfo &a)const
{
    return this->id < a.getId();
}
bool BasicInfo::operator <(const QString &a)const
{
    return this->id < a;
}
