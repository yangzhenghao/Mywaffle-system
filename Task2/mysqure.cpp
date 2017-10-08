#include "mysqure.h"

extern QVector<Question> questions;
extern Question presentQuest;

//时光广场，显示问题列表
MySqure::MySqure(QWidget *parent) : QWidget(parent)
{
    data = questions;
    currentPage = 0;
    numsPerPage=10;
    int size=data.size();
    totalPage = (size/numsPerPage) + (size % numsPerPage!=0)-(size!=0);
    table = new QTableWidget;                                 //初始化一些信息
    mainLayout = new QVBoxLayout;
    search =new QLineEdit;
    lastPage = new QPushButton;
    nextPage = new QPushButton;
    searchButton = new QPushButton;
    searchLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    timeLayout=new QHBoxLayout;
    startDate = new QLineEdit;
    endDate = new QLineEdit;
    timeSearch = new QPushButton;


    search->setPlaceholderText("搜搜问题");
    startDate->setPlaceholderText("起始(yyyyMMdd)");           //设置默认填充
    endDate->setPlaceholderText("终止(yyyyMMdd)");
    timeSearch->setText("筛选");
    timeSearch->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");


    table->setRowCount(numsPerPage);
    table->setColumnCount(2);
    table->resize(256,321);
    QStringList header;
    header<<"瞎扯题目"<<"用户";
    table->setHorizontalHeaderLabels(header);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *headerview = table->verticalHeader();
    headerview->setHidden(true);
    table->setColumnWidth(0,200);
    table->setColumnWidth(1,85);
    initPage();
    renewPage();

    searchButton->resize(24,24);
    searchButton->setIcon(QIcon("resource/search.png"));               //设置界面
    searchButton->setIconSize(QSize(24,24));
    searchButton->setStyleSheet("background-color:rgba(52,73,104,70);color:white;font-size:14px");
    lastPage->setText("上一页");
    lastPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    nextPage->setText("下一页");
    nextPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");

    searchLayout->addWidget(search);                         //设置界面布局
    searchLayout->addSpacing(8);
    searchLayout->addWidget(searchButton);
    buttonLayout->addWidget(lastPage);
    buttonLayout->addSpacing(8);
    buttonLayout->addWidget(nextPage);
    timeLayout->addWidget(startDate,0,Qt::AlignCenter);
    timeLayout->addSpacing(10);
    timeLayout->addWidget(timeSearch,0,Qt::AlignCenter);
    timeLayout->addSpacing(10);
    timeLayout->addWidget(endDate,0,Qt::AlignCenter);
    mainLayout->addItem(searchLayout);
    mainLayout->addWidget(table);
    mainLayout->addItem(buttonLayout);
    mainLayout->addItem(timeLayout);

    setLayout(mainLayout);                                   //连接槽
    connect(searchButton,SIGNAL(clicked()),this,SLOT(Search()));
    connect(lastPage,SIGNAL(clicked()),this,SLOT(turnLastPage()));
    connect(nextPage,SIGNAL(clicked()),this,SLOT(turnNextPage()));
    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showQuestionDatails(int,int)));
    connect(timeSearch,SIGNAL(clicked()),this,SLOT(timeSearchF()));
}

//析构函数
MySqure::~MySqure()
{
    delete table;
    delete mainLayout;
    delete  search;
    delete lastPage;
    delete nextPage;
    delete searchButton;
    delete buttonLayout;
    delete searchLayout;
}

//搜索功能
void MySqure::Search()
{
    QString content = search->text().trimmed();

    if(content.contains(" ")||content=="")               //特殊情况处理
    {
        search->clear();
        data=questions;
        renewPage();
        currentPage=0;
        return;
    }
    else
    {
        QVector<Question> temp;
        for(Question i:questions)
        {
            if(i.getTitle().contains(content))
                temp.append(i);
        }
        data = temp;
        currentPage = 0;
        search->clear();
        renewPage();
    }

}
//翻上页并更新信息
void MySqure::turnLastPage()
{
    if(currentPage==0)
        return;
    currentPage-=1;
    renewPage();
}
//翻上页并更新信息
void MySqure::turnNextPage()
{
    if(currentPage==totalPage)
        return;
    currentPage+=1;
    renewPage();
}
//更新页面
void MySqure::renewPage()
{
    int size= data.size();
    totalPage = (size/numsPerPage) + (size % numsPerPage!=0)-(size!=0);
    if(currentPage>totalPage)
        currentPage = 0;
    int i = numsPerPage*currentPage;
    int j = std::min(data.size(),numsPerPage*(currentPage+1));
    int k=0;
    for(;i<j;i++,k++)
    {
        QTableWidgetItem * item1 = table->item(k,0);
        QTableWidgetItem * item2 = table->item(k,1);
        if(item1)
        {
            item1->setText(data[i].getTitle());
            //item1->setTextAlignment(0x0004);
        }
        else
            table->setItem(k,0,new QTableWidgetItem(data[i].getTitle()));
        QString name=findUser(data[i].getfounderId()).getName();
        if(item2)
            item2->setText(name);
        else
            table->setItem(k,0,new QTableWidgetItem(name));
    }
    for(;k<numsPerPage;k++)
    {
        table->setItem(k,0,new QTableWidgetItem(""));
        table->setItem(k,1,new QTableWidgetItem(""));
    }
}
//初始化界面
void MySqure::initPage()
{
    for(int i=0;i<numsPerPage;i++)
    {

        table->setItem(i,0,new QTableWidgetItem(""));
        table->setItem(i,1,new QTableWidgetItem(""));
    }
}

//显示问题的具体细节
void MySqure::showQuestionDatails(int row,int column)
{
    Q_UNUSED(column);
    int i= currentPage*numsPerPage + row;
    Question a = data.at(i);
    QVector<Question>::iterator it = NULL;
    it=std::find(questions.begin(),questions.end(),a);
    a=*it;
    data.replace(i,a);
    Question b;
    presentQuest = a;
    answerOfQues dialog;
    dialog.show();
    dialog.exec();
    renewPage();
    presentQuest = b;
}
void MySqure::Search(QString sbdate,QString sedate)
{
    if(sbdate.size()!=8&&sbdate.size()!=0)              //特殊情况处理
    {
        startDate->clear();
        endDate->clear();
        QMessageBox::about(NULL, "Warning", "<font color='red'>Wrong format,date should be like 20170914!</font>");
        return;
    }
    if(sedate.size()!=8&&sedate.size()!=0)
    {
        startDate->clear();
        endDate->clear();
        QMessageBox::about(NULL, "Warning", "<font color='red'>Wrong format,date should be like 20170914!</font>");
        return;
    }
    if(!dateStrJutify(sbdate))
    {
        startDate->clear();
        endDate->clear();
        QMessageBox::about(NULL, "Warning", "<font color='red'>Wrong format,date should be like 20170914!</font>");
        return;
    }
    if(!dateStrJutify(sedate))
    {
        startDate->clear();
        endDate->clear();
        QMessageBox::about(NULL, "Warning", "<font color='red'>Wrong format,date should be like 20170914!</font>");
        return;
    }
    if(sbdate>sedate)
    {
        startDate->clear();
        endDate->clear();
        QMessageBox::about(NULL, "Warning", "<font color='red'>起始日期不能超过终止日期!</font>");
        return;
    }
    int byear = sbdate.mid(0,4).toInt();
    int bmonth = sbdate.mid(4,2).toInt();
    int bday = sbdate.mid(6,2).toInt();

    int eyear = sedate.mid(0,4).toInt();
    int emonth = sedate.mid(4,2).toInt();
    int eday = sedate.mid(6,2).toInt();

    QDate bDate(byear,bmonth,bday);
    QDate eDate(eyear,emonth,eday);

    QVector<Question> tempData;
    for(int i=0;i<questions.size();i++)
    {
       QDate a = questions[i].getDate();
       if(sbdate!=""&&sedate!="")
        {
            if(a>=bDate&&a<=eDate)
                tempData.append(questions[i]);

        }
       else if(sbdate==""&&sedate!="")
       {
           if(a<=eDate)
               tempData.append(questions[i]);
       }
       else if(sbdate!=""&&sedate=="")
       {
           if(a>=bDate)
               tempData.append(questions[i]);
       }
       else
            tempData.append(questions[i]);
    }

    data = tempData;
    renewPage();
    startDate->clear();
    endDate->clear();
}

//按照时间搜索
void MySqure::timeSearchF()
{
    QString sbdate=startDate->text().trimmed();
    QString sedate=endDate->text().trimmed();
    Search(sbdate,sedate);
}
//有信号增加了
void MySqure::QuestionAdded()
{
    data = questions;
}
