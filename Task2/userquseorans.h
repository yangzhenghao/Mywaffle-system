#ifndef USERQUSEORANS_H
#define USERQUSEORANS_H

#include <QTabWidget>
#include <QWidget>
#include <question.h>
#include <user.h>
#include <answer.h>
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
#include <QDialog>

//某个用户的问题
class UserQuseOrAns : public QDialog
{
    Q_OBJECT
public:
    explicit UserQuseOrAns(QWidget *parent = 0);
    void initPage();


signals:
public slots:
    void renew(int tab);                    //更新页面
    void turnLastPage();
    void turnNextPage();
    void renewPage();
    void showDetails(int row,int column);
private:
    QTableWidget *table1;
    QTableWidget *table2;
    QTabWidget *tabwidget;
    QPushButton *lastPage;
    QPushButton *nextPage;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QLabel *mainLabel;
    int currentPage1;
    int currentPage2;
    int totalPage1;
    int totalPage2;
    int numsPerPage;

};

#endif // USERQUSEORANS_H
