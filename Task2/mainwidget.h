#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <userinformation.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <puttingquestion.h>
#include <myconcern.h>
#include <mysqure.h>
#include <user.h>
#include <QLabel>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QCloseEvent>
#include <login.h>
#include <QFile>
#include <QTextStream>
#include <QSize>
#include <QDebug>
//程序的主界面
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);   //构造函数
    ~MainWidget();
signals:

public slots:
    void exitWind();                            //推出窗口
    void renew1(int page);
    void renewUserLabel(QString Name);          //更新欢迎的标题
    void save();                                //保存
protected:
    void closeEvent(QCloseEvent *event);
private:
    QTabWidget * tabWidget;                     //分页功能
    UserInformation * userInfo;                 //基本信息类
    PuttingQuestion * puttingquestion;          //提问专区界面
    MyConcern * myconcern;                      //我的关注界面
    MySqure *mysquare;                          //显示所有问题的界面
    QVBoxLayout * mainLayout;                   //一些布局
    QHBoxLayout *bottomLayout;
    QLabel *userLable;                          //欢迎用户的标签
    QPushButton * exitButton;
};

#endif // MAINWIDGET_H
