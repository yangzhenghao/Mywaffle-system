#ifndef MYSQURE_H
#define MYSQURE_H

#include <QWidget>
#include <question.h>
#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QVBOxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QHeaderView>
#include <func.h>
#include <answerofques.h>
#include <QDate>
#include <QTime>
#include <QIcon>
#include <QSize>
#include <QMessageBox>

//时光广场类，显示问题列表
class MySqure : public QWidget
{
    Q_OBJECT
public:
    explicit MySqure(QWidget *parent = 0);
    ~MySqure();
    void renewPage();
    void initPage();

signals:
    void QuestionChoosen(Question ques);

public slots:
    void Search();                     //按内容搜索
    void Search(QString a,QString b);
    void turnLastPage();               //翻页
    void turnNextPage();
    void showQuestionDatails(int row,int column);
    void timeSearchF();                //按时间搜索
    void QuestionAdded();              //问题增加了
private:
    QTableWidget *table;               //显示问题的表格
    QVBoxLayout * mainLayout;
    QLineEdit *search;
    QPushButton *lastPage;             //功能性按钮
    QPushButton *nextPage;
    QPushButton *searchButton;
    QHBoxLayout * searchLayout;        //布局
    QHBoxLayout *buttonLayout;
    QHBoxLayout *timeLayout;
    QLineEdit *startDate;              //按时间搜索的输入框
    QLineEdit *endDate;
    QPushButton *timeSearch;
    int currentPage;                   //目前页数，中页数，每页数目
    int totalPage;
    int numsPerPage;
    QVector<Question> data;
};

#endif // MYSQURE_H
