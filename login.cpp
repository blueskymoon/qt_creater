#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QObject::connect(ui->signButton,SIGNAL(clicked()),this,SLOT(signButtonSlot()));
    QObject::connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(loginButtonSlot()));
    QObject::connect(ui->passWordLineEdit,SIGNAL(returnPressed()),this,SLOT(loginButtonSlot()));
    QObject::connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exitButtonSlot()));
    QObject::connect(ui->comboBox,SIGNAL(editTextChanged(QString)),this,SLOT(getUserInfo(QString)));

    ui->passWordLineEdit->setEchoMode(QLineEdit::Password);         //设置单行文本框以密码方式显示


    database = QSqlDatabase::addDatabase("QSQLITE");    //使用数据库SQLITE
    database.setDatabaseName("game.db");       //设置数据库名称为game.db


    //打开数据库
        if(!database.open())
        {
            qDebug() << database.lastError();
            qFatal("failed to connect .");
        }
        else
        {
            qDebug() << "open seccess";
            QSqlQuery sql_query;
            sql_query.prepare(select_table);
            if(!sql_query.exec())
            {
                qDebug() <<sql_query.lastError();

            }
            else
            {
                QString tableName;
                while(sql_query.next())
                {
                    tableName = sql_query.value(0).toString();
                    qDebug() << tableName;
                    if(tableName.compare("gameone"))
                    {
                        tableFlag =false;
                        qDebug() << "table is not exist";
                    }
                    else
                    {
                        tableFlag = true;
                        qDebug() << "table is exist";
                    }

                }
            }
            if(tableFlag == false)
            {
                sql_query.prepare(create_sql);
                if(!sql_query.exec())
                {
                    qDebug() << sql_query.lastError();
                }
                else
                {
                    qDebug() << "table created";
                }
            }

        }

}

login::~login()
{
    delete ui;
}


void login::signButtonSlot()        //注册
{
    Sign r(this);
    this->hide();
    r.show();
    transmitdb(database);
    r.exec();
    this->show();

}
void login::loginButtonSlot()       //登录，核对帐号密码
{

    if(matchFlag == false)
    {
        qDebug() <<"errorone";
        QMessageBox::information(this,"info","Error");
        ui->comboBox->clear();      //清空用户名输入框
        ui->comboBox->setFocus();   //请将光标转到用户名输入框
    }
    else
    {
       if(gm_passwd!=ui->passWordLineEdit->text())
       {
            QMessageBox::information(this,"info","Error");
            ui->passWordLineEdit->clear();  //清空密码输入框
            ui->comboBox->setFocus();   //请将光标转到用户名输入框
       }
    else
    {
        game gm;
        this->hide();
        gm.show();
        gm.exec();
        this->close();
    }
    }
}
   /* //1.判断输入字符与保存的文件内容是否一致，否警告，清空密码栏
    if (ui->userNameLineEdit->text().operator == ("user")&& ui->passWordLineEdit->text().operator ==("1234567890"))
    {
        //QMessageBox::information(this,"登录提示","登录成功");
        Game *dialog=new Game;            //2.是则跳转到游戏界面
        dialog->show();
        close();
    }
    else
    {
        QMessageBox::information(this,"登录提示","登录失败");

    }
*/


void login::getUserInfo(QString user)
{
    QSqlQuery sql_query;

    QString tempstring = "select * from gameone where user='"+user+"'";
    //QString tempstring = sql_query.value(1).toString();
    qDebug() <<tempstring;
    qDebug() <<"error one...........";
    if(!sql_query.exec(tempstring))
    {
        qDebug() <<sql_query.lastError();
        matchFlag = false;
    }
    else
    {
        while(sql_query.next())
        {
            gm_id = sql_query.value(0).toInt();
            gm_user = sql_query.value(1).toString();
            gm_passwd = sql_query.value(2).toString();
            gm_email = sql_query.value(3).toString();
            gm_history = sql_query.value(4).toInt();

            qDebug() << QString("chatid =%1  user=%2  passwd =%3  email =%5  history =%4").arg(gm_id).arg(gm_user).arg(gm_passwd).arg(gm_email).arg(gm_history);
        }
    }
        if(gm_user==user)   matchFlag=true;
        else                matchFlag=false;
    }



void login::exitButtonSlot()
{
    close();
}
