#include <QApplication>
#include<user.h>
#include<question.h>
#include<QFile>
#include<QTextStream>
#include<answer.h>
#include<QVector>
#include<mainwidget.h>
#include<login.h>
#include<userinformation.h>
#include<QDebug>
#include<exception>
#include<QFont>

QVector<User> allUsers;
QVector<answer> answers;
QVector<Question> questions;
MainWidget* w = NULL;
Login *login = NULL;
User presentUser;
User concernedUser;
Question presentQuest;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    try{
        dataInit();                   //初始化信息
        login = new Login;
        login->show();
        int ac;bool flag = true;
        while(flag)
        {
            ac=login->exec();
            switch(ac)
            {
              case QDialog::Accepted : //按信息处理
                delete login;
                login=NULL;
                w = new MainWidget;
                w->show();
                flag = false;
                break;
              case 100:
                break;
              default:
                return 0;
                break;
            }
        }
        return a.exec();
 }
    catch(...)
    {
        qDebug()<<QString("Something bad happen!")<<endl;
        exit(1);
    }
}
