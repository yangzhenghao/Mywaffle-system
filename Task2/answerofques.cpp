#include "answerofques.h"

extern QVector<answer> answers;
extern Question presentQuest;
extern User presentUser;
extern QVector<User> allUsers;
extern QVector<Question> questions;

//构造函数，设置界面
answerOfQues::answerOfQues(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("My waffle");
    QIcon icon("resource/windows.ico");
    this->setWindowIcon(icon);
    this->setStyleSheet("background-image:url(resource/background.png)");
    setWindowFlags(Qt::WindowCloseButtonHint);
    this->resize(550,540);
    currentPage = 0;
    numsPerPage = 15;
    int size=presentQuest.getAnsList().size();
    totalPage = size/numsPerPage + (size % numsPerPage!=0)-(size!=0);

    title = new QLabel;                                            //从堆中分配内存
    content = new QLabel;
    userLabel = new QLabel;
    foundDTLabel = new QLabel;
    currentPageLabel  = new QLabel;
    pageEdit = new QLineEdit;
    answerEdit = new QLineEdit;
    answerEdit->setPlaceholderText("随便答答");
    pageEdit->setPlaceholderText("你想去哪儿？");

    answerslist = new QTableWidget;
    answerslist->resize(530,350);
    answerslist->setColumnCount(4);
    answerslist->setRowCount(numsPerPage);
    QStringList header;
    header<<"内容"<<"用户"<<"鲜花"<<"便便";
    answerslist->setHorizontalHeaderLabels(header);
    answerslist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    answerslist->setSelectionBehavior(QAbstractItemView::SelectRows);
    QHeaderView *headerview = answerslist->verticalHeader();
    headerview->setHidden(true);
    answerslist->setColumnWidth(0,250);
    answerslist->setColumnWidth(1,86);
    answerslist->setColumnWidth(2,86);
    answerslist->setColumnWidth(3,86);
    initPage();
    renewAnsList();

    go = new QPushButton;                                         //button
    concern = new QPushButton;
    praise = new QPushButton;
    answeQues = new QPushButton;
    concernAuthorButton = new QPushButton;
    dislike = new QPushButton;

    mainLayout = new QVBoxLayout;
    pageLayout = new QHBoxLayout;
    buttonsLayout = new QHBoxLayout;
    answerLayout = new QHBoxLayout;


    go->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    concern->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    praise->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    answeQues->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    concernAuthorButton->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");
    dislike->setStyleSheet("background-color:rgba(52,73,104,50);color:white;font-size:14px");


    title->setText(QString("标题:")+presentQuest.getTitle());      //设置信息
    content->setText(QString("内容:")+presentQuest.getContent());
    User a = findUser(presentQuest.getfounderId());
    userLabel->setText(QString("姓名：")+a.getName()+QString(" ")+QString("Id:")+a.getId());
    QString id1 = presentQuest.getId();
    QString text = id1.mid(0,4)+QString("-")+id1.mid(4,2)+QString("-")+id1.mid(6,2);
    foundDTLabel->setText(QString("创建时间：")+text+QString(" ")+presentQuest.getTime().toString(Qt::TextDate));
    setCurrentPageLabel();

    go->setText("俺去也");
    praise->setText("送朵小花");
    answeQues->setText("我要回答");
    concern->setText("关注Ta呗");
    concernAuthorButton->setText("关注作者");
    dislike->setText("踩踩");

    pageEdit->resize(200,20);                                    //更改大小，设置布局，下同
    pageLayout->addWidget(currentPageLabel,0,Qt::AlignCenter);
    pageLayout->addWidget(pageEdit,0,Qt::AlignCenter);
    pageLayout->addSpacing(8);
    pageLayout->addWidget(go);

    buttonsLayout->addWidget(praise);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(dislike);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(concern);
    buttonsLayout->addSpacing(5);
    buttonsLayout->addWidget(concernAuthorButton);

    answerLayout->addWidget(answerEdit);
    answerLayout->addSpacing(5);
    answerLayout->addWidget(answeQues);

    mainLayout->addWidget(title);                                //设置主要的布局
    mainLayout->addWidget(content);
    mainLayout->addWidget(userLabel);
    mainLayout->addWidget(foundDTLabel);
    mainLayout->addItem(answerLayout);
    mainLayout->addWidget(answerslist);
    mainLayout->addItem(pageLayout);
    mainLayout->addItem(buttonsLayout);
    setLayout(mainLayout);
    connect(praise,SIGNAL(clicked()),this,SLOT(praiseUser())); //连接信号
    connect(concern,SIGNAL(clicked()),this,SLOT(concernUser()));
    connect(answeQues,SIGNAL(clicked()),this,SLOT(answerQuestion()));
    connect(go,SIGNAL(clicked()),this,SLOT(goPage()));
    connect(concernAuthorButton,SIGNAL(clicked()),this,SLOT(concernAuthor()));
    connect(dislike,SIGNAL(clicked()),this,SLOT(dislikeAnswer()));
}

answerOfQues::~answerOfQues()
{
    /*delete title;
    delete content;
    delete userLabel;
    delete foundDTLabel;
    delete currentPageLabel;
    delete pageEdit;
    delete answerslist;
    delete buttonsLayout;
    //delete pageLayout;
    //delete go;
    //delete concern;
    //delete praise;
    //delete answeQues;
*/

    //delete mainLayout;
}

//更新目前页数以及总页数
void answerOfQues::setCurrentPageLabel()
{
    QString text = QString::number(currentPage+1,10) + QString("/")
            +QString::number(totalPage+1,10);
    currentPageLabel->setText(text);
}

//更新问题的回答列表
void answerOfQues::renewAnsList()
{

    QVector<QString> data=presentQuest.getAnsList();
    int i = numsPerPage*currentPage;                         //判断目前的页面的起始index
    int j = std::min(data.size(),numsPerPage*(currentPage+1));
    int k=0;
    QVector<answer>::iterator it =nullptr;
    for(;i<j;i++,k++)                                         //遍历，直接设置相应的内容
    {
        QTableWidgetItem * item1 = answerslist->item(k,0);
        QTableWidgetItem * item2 = answerslist->item(k,1);
        QTableWidgetItem * item3 = answerslist->item(k,2);
        QTableWidgetItem * item4 = answerslist->item(k,3);

        it=std::find(answers.begin(),answers.end(),data[i]);
        if(item1)                                            //判空
            item1->setText(it->getContent());
        else
            answerslist->setItem(k,0,new QTableWidgetItem(it->getContent()));
        QString name=findUser(it->getfounderId()).getName();

        if(item2)
            item2->setText(name);
        else
            answerslist->setItem(k,1,new QTableWidgetItem(name));
        if(item3)
        {
            item3->setText(QString::number(it->getPraiseTime(),10));
        }
        else
            answerslist->setItem(k,2,new QTableWidgetItem(QString::number(it->getPraiseTime(),10)));
        if(item4)
        {
            item4->setText(QString::number(it->getDislikeTime(),10));
        }
        else
            answerslist->setItem(k,3,new QTableWidgetItem(QString::number(it->getDislikeTime(),10)));
    }
    for(;k<numsPerPage;k++)                                  //覆盖掉每一页剩下的条目
    {
        answerslist->setItem(k,0,new QTableWidgetItem(""));
        answerslist->setItem(k,1,new QTableWidgetItem(""));
        answerslist->setItem(k,2,new QTableWidgetItem(""));
        answerslist->setItem(k,3,new QTableWidgetItem(""));
    }
}
void answerOfQues::initPage()
{
    for(int i=0;i<numsPerPage;i++)
        {

            answerslist->setItem(i,0,new QTableWidgetItem(""));
            answerslist->setItem(i,1,new QTableWidgetItem(""));
            answerslist->setItem(i,2,new QTableWidgetItem(""));
            answerslist->setItem(i,3,new QTableWidgetItem(""));
        }
}

//为用户点赞
void answerOfQues::praiseUser()
{
    int row =answerslist->currentRow();
    int index = numsPerPage*currentPage + row;
    if(index>=presentQuest.getAnsLisSize())
        return;
    QString answerId = presentQuest.at(index);
    QVector<answer>::iterator it=NULL;
    it = std::find(answers.begin(),answers.end(),answerId);       //在容器中寻找
    it->praiseOrCancel(presentUser.getId());
    int praiseTimes = it->getPraiseTime();
    int dislikeTimes = it->getDislikeTime();
    QTableWidgetItem * item1 = answerslist->item(row,2);
    item1->setText(QString::number(praiseTimes,10));

    QTableWidgetItem * item2 = answerslist->item(row,3);
    item2->setText(QString::number(dislikeTimes,10));
    save();
}

//dis一个用户
void answerOfQues::dislikeAnswer()
{
    int row =answerslist->currentRow();
    int index = numsPerPage*currentPage + row;
    if(index>=presentQuest.getAnsLisSize())
        return;
    QString answerId = presentQuest.at(index);
    QVector<answer>::iterator it=NULL;
    it = std::find(answers.begin(),answers.end(),answerId);       //在容器中寻找
    it->dislikeOrCancel(presentUser.getId());
    int dislikeTimes = it->getDislikeTime();
    int praiseTimes = it->getPraiseTime();
    QTableWidgetItem * item1 = answerslist->item(row,3);
    item1->setText(QString::number(dislikeTimes,10));

    QTableWidgetItem * item2 = answerslist->item(row,2);
    item2->setText(QString::number(praiseTimes,10));
    save();
}

//关注问题回答者
void answerOfQues::concernUser()
{
    int row =answerslist->currentRow();
    int index = numsPerPage*currentPage + row;
    if(index>=presentQuest.getAnsLisSize())
        return;
    QString ansId = presentQuest.getAnsList().at(index);
    QVector<answer>::iterator it =std::find(answers.begin(),answers.end(),ansId);
    presentUser.concernUser(it->getfounderId());

    QVector<User>::iterator it1 =NULL;
    it1 = std::find(allUsers.begin(),allUsers.end(),presentUser);
    allUsers.replace(it1-allUsers.begin(),presentUser);
    save();
}
//回答问题
void answerOfQues::answerQuestion()
{
    QString content = answerEdit->text().trimmed();             //获取信息
    if(content==""||content.contains(" "))                      //判断特殊情况
        return;
    QString qid = presentQuest.getId() +
            QString::number(presentQuest.getAnsLisSize(),10);
    QString founderId = presentUser.getId();
    QDate date=QDate::currentDate();
    QTime time =QTime::currentTime();
    QVector<QString> temp;
    answer a(qid,founderId,content,0,temp);
    a.setFoundTime(time);
    a.setFoundDate(date);
    QVector<answer>::iterator it = nullptr;
    it = std::lower_bound(answers.begin(),answers.end(),qid);  //替换掉容器里的数据
    answers.insert(it,a);
    presentQuest.append(qid);

    QVector<Question>::iterator it1=NULL;
    it1=std::find(questions.begin(),questions.end(),presentQuest);
    questions.replace(it1-questions.begin(),presentQuest);

    QVector<User>::iterator it2=NULL;
    it2=std::find(allUsers.begin(),allUsers.end(),presentUser.getId());
    presentUser.ansAppend(qid);
    allUsers.replace(it2-allUsers.begin(),presentUser);
    renewAnsList();
    answerEdit->clear();
    save();
}
//跳转到某一页
void answerOfQues::goPage()
{
    int page = (pageEdit->text()).trimmed().toInt();
    if(page<=0)                                    //特殊处理
    {
        pageEdit->clear();
        return;
    }
    if(page<=totalPage+1)
    {
        currentPage=page-1;
        pageEdit->clear();
        renewAnsList();
    }

}

//关注作者
void answerOfQues::concernAuthor()
{
   QString authID = presentQuest.getfounderId();
   presentUser.concernUser(authID);                  //调用user里的属性
   QVector<User>::iterator it =NULL;
   it = std::find(allUsers.begin(),allUsers.end(),presentUser);
   allUsers.replace(it-allUsers.begin(),presentUser);
   save();
}

