#ifndef PUTTINGQUESTION_H
#define PUTTINGQUESTION_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <question.h>
#include <user.h>
#include <QDate>
#include <QTime>
#include <func.h>
#include <QMessageBox>

//提问的框体，提问用
class PuttingQuestion : public QWidget
{
    Q_OBJECT
public:
    explicit PuttingQuestion(QWidget *parent = 0);
    ~PuttingQuestion();
signals:
    void addNewQuestionSiagnal();
public slots:
    void addNewQuestion();
private:
    QLabel *mainLabel;                  //主标签，问题标签，内容标签
    QLabel *titleLabel;
    QLabel *contentLabel;
    QLineEdit * titleEdit;              //输入框
    QLineEdit * contentEdit;
    QPushButton *submit;
    QHBoxLayout *titleLayout;           //布局
    QHBoxLayout *contentLayout;
    QVBoxLayout *mainLayout;
};

#endif // PUTTINGQUESTION_H
