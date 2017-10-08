#ifndef ANSWEROFQUES_H
#define ANSWEROFQUES_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <question.h>
#include <func.h>
#include <user.h>
#include <answer.h>
#include <QDialog>
#include <QStringList>
#include <QHeaderView>

//问题的回答界面
class answerOfQues : public QDialog
{
    Q_OBJECT
public:
    explicit answerOfQues(QWidget *parent = 0);
    ~answerOfQues();
    void setCurrentPage(int page);
    void setCurrentPageLabel();
    void initPage();
signals:

public slots:
    void praiseUser();                   //给用户点赞
    void concernUser();                  //关注用户
    void goPage();                       //跳转到某个页面
    void answerQuestion();               //回答问题
    void renewAnsList();                 //更新关注列表
    void concernAuthor();                //关注作者
    void dislikeAnswer();
private:
    int currentPage;                     //目前页数
    int numsPerPage;                     //每页的栏目
    int totalPage;                       //总页数
    QLabel *title;                       //以下为界面中的一些标题
    QLabel *content;
    QLabel *userLabel;
    QLabel *foundDTLabel;
    QLabel *currentPageLabel;
    QLineEdit *pageEdit;
    QLineEdit *answerEdit;
    QTableWidget *answerslist;
    QPushButton *go;                      //一些按钮
    QPushButton *concern;
    QPushButton *praise;
    QPushButton *answeQues;
    QPushButton *concernAuthorButton;
    QPushButton *dislike;
    QHBoxLayout *pageLayout;              //布局
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *answerLayout;
    QVBoxLayout *mainLayout;
};

#endif // ANSWEROFQUES_H
