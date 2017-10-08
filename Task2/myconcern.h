#ifndef MYCONCERN_H
#define MYCONCERN_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <user.h>
#include <QString>
#include <answerofques.h>
#include <QStringList>
#include <QHeaderView>
#include <userquseorans.h>

//我的关注界面
class MyConcern : public QWidget
{
    Q_OBJECT
public:
    explicit MyConcern(QWidget *parent = 0);
    ~MyConcern();
    void setData(const QVector<QString>& a);          //更改关注列表的数据
    void setNumsPerPage(int n){numsPerPage = n;}      //设置每一页的显示的关注数

    QVector<QString> getData()const{return data;}     //返回数据
    int getNumsPerPage()const{return numsPerPage;}    //返回基本信息
    void initPage();
    void renewPage();                                 //更新页面一些信息
    void renewPageLabel();
signals:

public slots:
    void turnLastPage();                              //翻上一页
    void turnNextPage();                              //翻下一页
    void disConcern();                                //取消关注
    void showDetails(int row,int column);             //显示某个用户的具体信息
private:
    int currentPage;                                  //目前的页数
    int totalPage;                                    //总页数
    int numsPerPage;                                  //每页的数目
    QTableWidget *table;                              //显示关注信息的表格
    QLabel *mainLabel;
    QVBoxLayout *mainLayout;                          //界面布局
    QHBoxLayout *pagelayout;
    QHBoxLayout *tableLayout;
    QHBoxLayout *mainLabelLayout;
    QPushButton * disconcern;                         //一些功能性按钮
    QPushButton *lastPage;
    QPushButton *nextPage;
    QVector<QString> data;
    QLabel *pageLabel;

};

#endif // MYCONCERN_H
