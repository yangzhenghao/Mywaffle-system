#include "mainwidget.h"

extern User presentUser;
extern QVector<User> allUsers;
extern QVector<answer> answers;
extern QVector<Question> questions;

//主界面
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("My waffle");
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    QIcon icon("resource/windows.ico");
    this->setWindowIcon(icon);
    this->resize(330,536);
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("resource/background.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    exitButton = new QPushButton;
    exitButton->resize(25,25);
    //exitButton->setText("注销");
    exitButton->setIcon(QIcon("resource/shutdown.png"));
    exitButton->setIconSize(QSize(25,25));
    exitButton->setStyleSheet("border-image:url(resource/shutdown.png)");


    //exitButton->setStyleSheet("background-color:rgba(255,255,255,50);color:white;font-size:14px;border-width: 2px;border-color:rgb(52,73,104)");
    bottomLayout = new QHBoxLayout;

    tabWidget = new QTabWidget(this);
    tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
    userLable = new QLabel;
    userLable->setText(QString("很高兴,我们又见面了,")+presentUser.getName());
    userLable->resize(100,20);
    userLable->setStyleSheet("color:rgb(223,223,223)");
    userInfo = new UserInformation;
    puttingquestion = new PuttingQuestion;
    myconcern = new MyConcern;
    mysquare = new MySqure;
    tabWidget->addTab(userInfo,QString("读者信息"));
    tabWidget->addTab(mysquare,QString("时光广场"));
    tabWidget->addTab(puttingquestion,QString("提问专区"));
    tabWidget->addTab(myconcern,QString("我的关注"));

    bottomLayout->addWidget(userLable,0,Qt::AlignLeft);
    bottomLayout->addWidget(exitButton,0,Qt::AlignRight);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(userLable,0,Qt::AlignLeft|Qt::AlignBottom);
    mainLayout->addItem(bottomLayout);
    setLayout(mainLayout);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exitWind()));
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(renew1(int)));
    connect(userInfo,SIGNAL(userNameChange(QString)),this,SLOT(renewUserLabel(QString)));
    connect(puttingquestion,SIGNAL(addNewQuestionSiagnal()),mysquare,SLOT(QuestionAdded()));
}

//析构函数
MainWidget::~MainWidget()
{
    delete tabWidget;
    delete userLable;
    delete userInfo;
    delete mainLayout;
    delete mysquare;
}


//关闭事件
void MainWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    save();
}

//储存信息
void MainWidget::save()
{
    try
    {QFile file("records/user.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in(&file);
    for(int i=0;i<allUsers.size();i++)
    {
        if(i!=allUsers.size()-1)
            in<<allUsers[i];
        else                             //最后一个数据特殊处理
            allUsers[i].save(in);
    }
    file.close();
    QFile file1("records/question.txt"); //打开文件
    if(!file1.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in1(&file1);
    for(int i=0;i<questions.size();i++)
    {
        if(i!=questions.size()-1)
            in1<<questions[i];
        else
            questions[i].output(in1);
    }
    file1.close();
    QFile file2("records/answers.txt");
    if(!file2.open(QIODevice::WriteOnly|QIODevice::Text))
        qDebug()<<"Open error";
    QTextStream in2(&file2);
    for(int i=0;i<answers.size();i++)
    {
        if(i!=answers.size()-1)
            in2<<answers[i];
        else
            answers[i].output(in2);
    }
    file2.close();
    }
    catch(...)
    {
        qDebug()<<"Wrong with the output.";
    }
}
//推出
void  MainWidget::exitWind()
{
    this->close();
    Login a;
    int ac;bool flag = true;
    a.show();
    while(flag)
    {
        ac=a.exec();
        switch(ac)
        {
          case QDialog::Accepted :              //返回正确
            this->show();
            userInfo->renew();
            userLable->setText(QString("很高兴,我们又见面了,")+presentUser.getName());
            flag = false;
            break;
          case 100:
            break;
          default:
            return;
            break;
        }
    }
}

//按照点击回复信息
void MainWidget::renew1(int page)
{
    switch(page)
    {
        case 1:
            mysquare->renewPage();
        break;
        case 3:
            myconcern->renewPage();
        break;
        default:
            break;
    }
}

//更新标签
void MainWidget::renewUserLabel(QString Name)
{
    userLable->setText(QString("很高兴,我们又见面了,"+Name));
}
