#include "puttingquestion.h"

extern QVector<Question> questions;
extern QVector<User> allUsers;
extern User presentUser;

//提问，设置界面
PuttingQuestion::PuttingQuestion(QWidget *parent) : QWidget(parent)
{
    mainLabel = new QLabel;
    titleLabel = new QLabel;
    contentLabel = new QLabel;
    titleEdit = new QLineEdit;
    contentEdit = new QLineEdit;
    submit = new QPushButton;
    titleLayout = new QHBoxLayout;
    contentLayout= new QHBoxLayout ;
    mainLayout = new QVBoxLayout ;


    mainLabel->setText("  提问小专区");
    mainLabel->resize(111,31);
    mainLabel->setStyleSheet("color:white;font-weight:bold;font-size:20px;font-family:‘cursive’");
    titleLabel->setText("  问题名称:");
    titleLabel->resize(54,12);
    titleEdit->resize(151,20);
    contentLabel->setText("  问题描述:");
    contentLabel->resize(54,12);
    contentEdit->resize(151,20);
    submit->resize(75,23);
    submit->setText("Submit");
    submit->setStyleSheet("background-color:rgba(52,73,104,0);color:rgb(52,73,104);font-size:14px;font-weight:bold;border-color:rgb(52,73,104);border-width: 2px");

    titleLayout->setMargin(8);
    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch(6);
    titleLayout->addWidget(titleEdit);
    titleLayout->addStretch(6);
    contentLayout->setMargin(8);
    contentLayout->addWidget(contentLabel);
    contentLayout->addStretch(6);
    contentLayout->addWidget(contentEdit);
    contentLayout->addStretch(6);

    mainLayout->addWidget(mainLabel,0,Qt::AlignCenter);        //设置布局
    mainLayout->setSpacing(60);
    mainLayout->addItem(titleLayout);
    mainLayout->setSpacing(30);
    mainLayout->addItem(contentLayout);
    mainLayout->setSpacing(70);
    mainLayout->addWidget(submit,0,Qt::AlignCenter);
    mainLayout->setSpacing(70);

    setLayout(mainLayout);

    connect(submit,SIGNAL(clicked()),this,SLOT(addNewQuestion())); //连接信号
}

//析构函数
PuttingQuestion::~PuttingQuestion()
{
    delete mainLabel;
    delete titleLabel;
    delete contentLabel;
    delete titleEdit;
    delete contentEdit;
    delete submit;
    delete titleLayout;
    delete contentLayout;
    delete mainLayout;
}

//新建问题
void PuttingQuestion::addNewQuestion()
{   //特殊情况处理
    if(titleEdit->text().trimmed()==""||contentEdit->text().trimmed()=="")
    {
        this->titleEdit->clear();
        this->titleEdit->setFocus();
        this->contentEdit->clear();
        return;
    }
    Question a;
    QDate date(QDate::currentDate());
    QTime time(QTime::currentTime());
    QString userId = presentUser.getId();
    QString date1 = date.toString(QString("yyyyMMdd"));
    QString time1 = time.toString(QString("hhmmss"));

    a.setTitle(this->titleEdit->text().trimmed());                //设置新建问题信息
    a.setContent(this->contentEdit->text().trimmed());
    a.setFounder(userId);
    a.setFoundDate(date);
    a.setFoundTime(time);
    a.setId(date1+time1+userId);
    presentUser.quesAppend(a.getId());
    QVector<User>::iterator it =NULL;
    it=std::find(allUsers.begin(),allUsers.end(),presentUser.getId());
    allUsers.replace(it-allUsers.begin(),presentUser);

    questions.insert(questions.begin(),a);                        //插入到容器中
    QMessageBox::about(NULL, "About", "<font color='red'>Submit successfully!</font>");
    this->titleEdit->clear();
    this->titleEdit->setFocus();
    this->contentEdit->clear();
    emit addNewQuestionSiagnal();
    save();
}
