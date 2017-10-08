#include "myconcern.h"

extern User presentUser;
extern QVector<User> allUsers;
extern User concernedUser;


//我的关注，框体
MyConcern::MyConcern(QWidget *parent) : QWidget(parent)
{
    currentPage = 0;
    numsPerPage = 12;
    pageLabel =new QLabel;
    pagelayout = new QHBoxLayout;
    tableLayout = new QHBoxLayout;
    mainLabelLayout = new QHBoxLayout;
    lastPage = new QPushButton;
    nextPage = new QPushButton;
    table = new QTableWidget;
    mainLabel = new QLabel;
    mainLayout = new QVBoxLayout;
    disconcern = new QPushButton;

    data = presentUser.getList();
    int size = data.size();
    totalPage = (size/numsPerPage) + (size % numsPerPage!=0)-(size!=0);

    this->resize(251,450);
    disconcern->resize(90,32);
    table->resize(300,400);
    mainLabel->resize(120,15);
    mainLabel->setText(QString("有趣的Ta"));                        //设置界面
    mainLabel->setStyleSheet("color:white;font-weight:bold;font-size:20px;font-family:‘cursive’");
    disconcern->setText("取消关注");
    disconcern->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    lastPage->setText("上一页");
    lastPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    nextPage->setText("下一页");
    nextPage->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");

    table->setRowCount(numsPerPage);
    table->setColumnCount(2);
    QStringList header;
    header<<"姓名"<<"ID";
    table->setHorizontalHeaderLabels(header);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *headerview = table->verticalHeader();
    headerview->setHidden(true);
    table->setColumnWidth(0,135);
    table->setColumnWidth(1,135);
    initPage();
    renewPage();
    renewPageLabel();

    pagelayout->addWidget(lastPage);                            //更新框体
    pagelayout->addWidget(pageLabel,0,Qt::AlignCenter);
    pagelayout->addWidget(nextPage);
    tableLayout->addWidget(table);
    mainLabelLayout->addWidget(mainLabel,0,Qt::AlignCenter);
    mainLayout->addItem(mainLabelLayout);
    mainLayout->addItem(tableLayout);
    mainLayout->addItem(pagelayout);
    mainLayout->addWidget(disconcern);
    setLayout(mainLayout);
    connect(disconcern,SIGNAL(clicked()),this,SLOT(disConcern()));
    connect(lastPage,SIGNAL(clicked()),this,SLOT(turnLastPage()));
    connect(nextPage,SIGNAL(clicked()),this,SLOT(turnNextPage()));
    connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showDetails(int,int)));
}

//析构函数
MyConcern::~MyConcern()
{
    delete table;
    delete mainLabel;
    delete mainLayout;
    delete disconcern;
    delete lastPage;
    delete nextPage;
    delete tableLayout;
    delete mainLabelLayout;
    delete pageLabel;
    delete pagelayout;
}

//取消关注
void MyConcern::disConcern()
{
    int row = table->currentRow();
    int k = currentPage*numsPerPage +row;                  //获取目前的index
    QTableWidgetItem * item = table->item(k,1);

    QString id = item->text();
    data.removeAll(id);
    presentUser.setFocus(data);
    QVector<User>::iterator it = NULL;
    it=std::find(allUsers.begin(),allUsers.end(),presentUser);
    allUsers.replace(it-allUsers.begin(),presentUser);
    int size=data.size();
    totalPage = (size/numsPerPage) + (size % numsPerPage!=0)-(size!=0);

    if(currentPage> totalPage)
    {
        currentPage -=1;
    }
    renewPage();
    save();
}
//翻上一页
void MyConcern::turnLastPage()
{
    if(currentPage==0)                                 //错误处理
        return;
    currentPage -=1;
    renewPage();
}
//翻下一页
void MyConcern::turnNextPage()
{
    if(currentPage==totalPage)
        return;
    currentPage +=1;
    renewPage();
}

//初始化页面
void MyConcern::initPage()
{
    for(int i=0;i<numsPerPage;i++)
    {                                                 //初始化信息为空

        table->setItem(i,0,new QTableWidgetItem(""));
        table->setItem(i,1,new QTableWidgetItem(""));
    }
}
//更新页面
void MyConcern::renewPage()
{
    renewPageLabel();                                   //更新页面页数标题
    data=presentUser.getList();
    int i = numsPerPage*currentPage;
    int j = std::min(data.size(),numsPerPage*(currentPage+1));
    int k=0;
    for(;i<j;i++,k++)                                   //更新数据
    {
        QTableWidgetItem * item1 = table->item(k,0);
        QTableWidgetItem * item2 = table->item(k,1);
        QString name=findUser(data[i]).getName();
        if(item1)
        {
            item1->setText(name);
            //item1->setTextAlignment(0x0004);
        }
        else
            table->setItem(k,0,new QTableWidgetItem(name));
        if(item2)
            item2->setText(data[i]);
        else
            table->setItem(k,0,new QTableWidgetItem(data[i]));
    }
    for(;k<numsPerPage;k++)                            //覆盖剩余部分
    {
        table->setItem(k,0,new QTableWidgetItem(""));
        table->setItem(k,1,new QTableWidgetItem(""));
    }

}

//更新页面标签
void MyConcern::renewPageLabel()
{
    QString text = QString::number(currentPage+1,10) + QString("/")
            +QString::number(totalPage+1,10);
    pageLabel->setText(text);
}

//显示每个被关注用户的具体信息
void MyConcern::showDetails(int row,int column)
{
    Q_UNUSED(column);
    int index = currentPage*numsPerPage+row;
    QString userId=presentUser.getList().at(index);

    QVector<User>::iterator it=NULL;
    it=std::find(allUsers.begin(),allUsers.end(),userId);
    User temp;
    concernedUser = *it;
    UserQuseOrAns a;
    a.show();
    a.exec();
    concernedUser = temp;
}
