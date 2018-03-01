#include "sign.h"
#include "ui_sign.h"

Sign::Sign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign)
{
    ui->setupUi(this);
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(finishButtonSlot()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(exitButtonSlot()));

}

Sign::~Sign()
{
    delete ui;
}

  QString create_sql= "create table game (chatid int primary key,user varchar(30),passwd varchar(30),email varchar(30),history int )";
QString select_table = "select game from sqlite master where type = 'user'";
QString select_max_sql = "select max(chatid) from game";
QString insert_sql = "insert into game values (?,?,?,?,?)";     //插入向表game插入数据
QString select_sql = "select game from gameone";       //查找数据库表game的user的
/*
QString select_table = "select gameone from sqlite_master where type = 'user'";
QString create_sql = "create table gameone (chatid int primary key, user varchar(30),passwd varchar(30), email varchar(30), history int)";
QString select_max_sql = "select max(chatid) from gameone";
QString insert_sql = "insert into gameone values (?, ?, ?, ?,?)";
QString select_sql = "select user from gameone";
*/





void Sign::finishButtonSlot()           //完成键，写入数据库
{

    //1.将注册内容写入到数据库中
    bool userFlag =false;
    bool passwdFlag = false;
    int newchatid=max_id+1;
    QString newpasswd=NULL;
    QString newuser=NULL;
    QString newemail=ui->emailLineEdit->text();

    if(ui->passwordLineEdit->text()==""||ui->repasswordLineEdit->text()=="")
    {
        passwdFlag = false;
    }
    else if(ui->passwordLineEdit->text()==ui->repasswordLineEdit->text())
    {
        passwdFlag = true;
    }
    else
    {
        qDebug() <<"passwd error";
        passwdFlag = false;
    }

    //数据库操作
    QSqlQuery sql_query;

    sql_query.prepare(create_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"table created";
    }


    max_id = 0;
    sql_query.prepare(select_max_sql);

    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max chatid:%1").arg(max_id);
        }
    }

    //查询部分数据
    if(!sql_query.exec(select_sql))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(1)
        {
            if(sql_query.next())
            {
                QString user = sql_query.value("user").toString();
                qDebug()<<QString("user=%1").arg(user);

                if(ui->userLineEdit->text()==user)
                {
                    qDebug()<<"user exited";
                    userFlag =false;

                }
                else
                {
                    userFlag=true;
                    break;
                }
            }
            else
            {
                userFlag=true;          //列表为空
                break;
            }
        }
    }
    newchatid=max_id+1;
    if(userFlag==true)
        newuser=ui->userLineEdit->text();
    else
        return;
    if(passwdFlag==true)
    {
        newpasswd=ui->passwordLineEdit->text();
    }
    else
    {
        return;
    }


    //插入数据
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(newchatid);
    sql_query.addBindValue(newuser);
    sql_query.addBindValue(newpasswd);
    sql_query.addBindValue(newemail);
    sql_query.addBindValue(0);
    if(!sql_query.exec())
    {
        qDebug() <<sql_query.lastError();
    }
    else
    {
        qDebug() << "insterted";
    }

    this->close();
}


void Sign::receivedb(QSqlDatabase db)
{
    qDebug() <<"received db";
    database=db;
    if(!database.isOpen())
    {
        qDebug() <<database.lastError();
        qFatal("failde to connect.");
        return;
    }
    else
    {
    }
}
    //2.用户确认后关闭，否则返回注册

void Sign::exitButtonSlot()
{
    close();
}
