#include "userquseorans.h"

extern User concernedUser;
extern QVector<User> allUsers;
extern QVector<answer> answers;
extern QVector<Question> questions;
extern Question presentQuest;
//被关注用户的回答和问题
UserQuseOrAns::UserQuseOrAns(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowTitle("My waffle");
    QIcon icon("resource/windows.ico");
    this->setWindowIcon(icon);
    this->setStyleSheet("background-image:url(resource/background.png)");
    this->resize(310,470);
    table1 = new QTableWidget;
    table2 = new QTableWidget;
    tabwidget = new QTabWidget;
    tabwidget->resize(310,400);

    lastPage = new QPushButton;
    nextPage = new QPushButton;
    buttonLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    mainLabel = new QLabel;
    currentPage1 = 0;
    currentPage2 = 0;
    numsPerPage = 10;
    QVector<QString> data1=concernedUser.getQuesList();
    QVector<QString> data2=concernedUser.getAnsList();
    int size1 = data1.size();
    int size2 = data2.size();
    totalPage1 = (size1/numsPerPage) + (size1 % numsPerPage!=0)-(size1!=0);
    totalPage2 = (size2/numsPerPage) + (size2 % numsPerPage!=0)-(size2!=0);

    lastPage->setText("上一页");
    lastPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");
    nextPage->setText("下一页");
    nextPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:16px");
    table1->setRowCount(numsPerPage);
    table1->setColumnCount(2);
    table1->resize(300,350);
    QStringList header;
    header<<"Ta的问题"<<"回答数";
    table1->setHorizontalHeaderLabels(header);
    table1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *headerview = table1->verticalHeader();
    headerview->setHidden(true);
    table1->setColumnWidth(0,190);
    table1->setColumnWidth(1,83);

    table2->setRowCount(numsPerPage);
    table2->setColumnCount(2);
    table2->resize(300,350);
    QStringList header1;
    header1<<"Ta的回答"<<"鲜花数";
    table2->setHorizontalHeaderLabels(header1);
    table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *headerview1 = table2->verticalHeader();
    headerview1->setHidden(true);
    table2->setColumnWidth(0,190);
    table2->setColumnWidth(1,83);


    initPage();
    renewPage();


    tabwidget->addTab(table1,QString("Ta的问题"));                 //布局
    tabwidget->addTab(table2,QString("Ta的回答"));
    mainLabel->setText(concernedUser.getName());
    buttonLayout->addWidget(lastPage,0,Qt::AlignCenter);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(nextPage,0,Qt::AlignCenter);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    mainLayout->addWidget(tabwidget);
    mainLayout->addItem(buttonLayout);
    setLayout(mainLayout);
    connect(lastPage,SIGNAL(clicked()),this,SLOT(turnLastPage()));
    connect(nextPage,SIGNAL(clicked()),this,SLOT(turnNextPage()));
    connect(tabwidget,SIGNAL(currentChanged(int)),this,SLOT(renewPage()));
    connect(table1,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showDetails(int,int)));
}

//初始化界面
void UserQuseOrAns::initPage()
{
    for(int i=0;i<numsPerPage;i++)
    {

        table1->setItem(i,0,new QTableWidgetItem(""));
        table1->setItem(i,1,new QTableWidgetItem(""));
        table2->setItem(i,0,new QTableWidgetItem(""));
        table2->setItem(i,1,new QTableWidgetItem(""));
    }
}

//更新界面
void UserQuseOrAns::renewPage()
{
    QVector<QString> data1 = concernedUser.getQuesList();                      //更新数据
    QVector<QString> data2 = concernedUser.getAnsList();
    int size1 = data1.size();
    int size2 = data2.size();
    totalPage1 = (size1/numsPerPage) + (size1 % numsPerPage!=0)-(size1!=0);
    totalPage2 = (size2/numsPerPage) + (size2 % numsPerPage!=0)-(size2!=0);
    if(currentPage1>totalPage1)
        currentPage1=0;
    if(currentPage2>totalPage2)
        currentPage2=0;
    int tab=tabwidget->currentIndex();
    Q_UNUSED(tab);                                                             //分界面更新
    {
        int i = numsPerPage*currentPage1;
        int j = std::min(data1.size(),numsPerPage*(currentPage1+1));           //获取index
        int k=0;
        for(;i<j;i++,k++)
        {
            QTableWidgetItem * item1 = table1->item(k,0);
            QTableWidgetItem * item2 = table1->item(k,1);
            QVector<Question>::iterator it = NULL;
            it = std::find(questions.begin(),questions.end(),data1[i]);
            if(item1)
            {
                if(it)
                    item1->setText(it->getTitle());
                else
                    item1->setText(QString(""));
            }
            else
            {
                if(it)
                    table1->setItem(k,0,new QTableWidgetItem(it->getTitle()));
                else
                    table1->setItem(k,0,new QTableWidgetItem(QString("")));
            }
            if(item2)
            {
                if(it)
                    item2->setText(QString::number(it->getAnsLisSize(),10));
                else
                    item2->setText(QString(""));

            }
            else
            {
                if(it)
                    table1->setItem(k,0,new QTableWidgetItem(QString::number(it->getAnsLisSize(),10)));
                else
                    table1->setItem(k,0,new QTableWidgetItem(QString("")));
            }
        }
        for(;k<numsPerPage;k++)                                              //覆盖掉剩余的
        {
            table1->setItem(k,0,new QTableWidgetItem(""));
            table1->setItem(k,1,new QTableWidgetItem(""));
        }
    }
    {                                                                         //同上
        int i = numsPerPage*currentPage1;
        int j = std::min(data2.size(),numsPerPage*(currentPage1+1));
        int k=0;
        for(;i<j;i++,k++)
        {
            QTableWidgetItem * item1 = table2->item(k,0);
            QTableWidgetItem * item2 = table2->item(k,1);
            QVector<answer>::iterator it = NULL;
            it = std::find(answers.begin(),answers.end(),data2[i]);
            if(item1)
            {
                if(it)
                    item1->setText(it->getContent());
                else
                    item1->setText(QString(""));
            }
            else
            {
                if(it)
                    table1->setItem(k,0,new QTableWidgetItem(it->getContent()));
                else
                    table1->setItem(k,0,new QTableWidgetItem(QString("")));
            }
            if(item2)
            {
                if(it)
                    item2->setText(QString::number(it->getPraiseTime(),10));
                else
                    item2->setText(QString(""));

            }
            else
            {
                if(it)
                    table1->setItem(k,0,new QTableWidgetItem(QString::number(it->getPraiseTime(),10)));
                else
                    table1->setItem(k,0,new QTableWidgetItem(QString("")));
            }
        }
        for(;k<numsPerPage;k++)
        {
            table1->setItem(k,0,new QTableWidgetItem(""));
            table1->setItem(k,1,new QTableWidgetItem(""));
        }
    }
}

//翻到上页
void UserQuseOrAns::turnLastPage()
{
    int tab=tabwidget->currentIndex();
    if(tab==-1)
        return;
    else if(tab==0)
        currentPage1 = std::max(currentPage1-1,0);
    else
        currentPage2 = std::max(currentPage2-1,0);
    renewPage();
}

//翻到下页
void UserQuseOrAns::turnNextPage()
{
    int tab=tabwidget->currentIndex();
    if(tab==-1)
        return;
    else if(tab==0)
        currentPage1 = std::min(currentPage1+1,totalPage1);
    else
        currentPage2 = std::max(currentPage2+1,totalPage2);
    renewPage();
}

//更新tab
void UserQuseOrAns::renew(int tab)
{
    Q_UNUSED(tab);
    renewPage();
}

void UserQuseOrAns::showDetails(int row,int column)
{
    QVector<QString> data = concernedUser.getQuesList();
    Q_UNUSED(column);
    int i= currentPage1*numsPerPage + row;
    QString a = data.at(i);
    Question a1;
    QVector<Question>::iterator it = NULL;
    it=std::find(questions.begin(),questions.end(),a);
    a1=*it;

    Question b;
    presentQuest = a1;
    answerOfQues dialog;
    dialog.show();
    dialog.exec();
    renewPage();
    presentQuest = b;
}
