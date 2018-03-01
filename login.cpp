#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //��������
    QObject::connect(ui->signButton,SIGNAL(clicked()),this,SLOT(signButtonSlot()));
    QObject::connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(loginButtonSlot()));
    QObject::connect(ui->passWordLineEdit,SIGNAL(returnPressed()),this,SLOT(loginButtonSlot()));
    QObject::connect(ui->exitButton,SIGNAL(clicked()),this,SLOT(exitButtonSlot()));
    QObject::connect(ui->comboBox,SIGNAL(editTextChanged(QString)),this,SLOT(getUserInfo(QString)));

    ui->passWordLineEdit->setEchoMode(QLineEdit::Password);         //���õ����ı��������뷽ʽ��ʾ


    database = QSqlDatabase::addDatabase("QSQLITE");    //ʹ�����ݿ�SQLITE
    database.setDatabaseName("gameone.db");       //�������ݿ�����Ϊgame.db

    //���ұ�game����Ŀ"gm_user"
    QString select_sql = "select game from gameone";
    QString create_sql= "create table game (chatid int primary key,user varchar(30),passwd varchar(30),email varchar(30),history int )";
    //�����ݿ�
        if(!database.open())
        {
            qDebug() << database.lastError();
            qFatal("failed to connect .");
        }
        else
        {
            qDebug() << "open seccess";
            QSqlQuery sql_query;
            sql_query.prepare(select_table);        //ִ�в������ݿ�Ĳ���
            if(!sql_query.exec())                   //�ж��Ƿ��ܹ�ִ��
            {
                qDebug() <<sql_query.lastError();       //����ִ��������󾯸�

            }
            else
            {
                QString tableName;                  //����һ������
                while(sql_query.next())             //ѭ����һ�����ݿ�
                {
                    tableName = sql_query.value(0).toString();      //�����ݿ�������Ϊ0������ת��Ϊstring����
                                                                    //����ֵ��tableName
                    qDebug() << tableName;                          //�ڵ��������tableName������
                    if(tableName.compare("game"))                   //�ж�talbeName�Ƿ���"game"
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
            if(tableFlag == false)                  //�ж�Ϊ��
            {
                sql_query.prepare(create_sql);          //ִ�д������ݿ�
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


void login::signButtonSlot()        //ע��
{
    Sign r(this);
    this->hide();
    r.show();
    transmitdb(database);
    r.exec();
    this->show();

}
void login::loginButtonSlot()       //��¼���˶��ʺ�����
{

    if(matchFlag == false)
    {
        qDebug() <<"errorone";
        QMessageBox::information(this,"info","Error");
        ui->comboBox->clear();      //����û��������
        ui->comboBox->setFocus();   //�뽫���ת���û��������
    }
    else
    {
       if(gm_passwd!=ui->passWordLineEdit->text())
       {
            QMessageBox::information(this,"info","Error");
            ui->passWordLineEdit->clear();  //������������
            ui->comboBox->setFocus();   //�뽫���ת���û��������
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
   /* //1.�ж������ַ��뱣����ļ������Ƿ�һ�£��񾯸棬���������
    if (ui->userNameLineEdit->text().operator == ("user")&& ui->passWordLineEdit->text().operator ==("1234567890"))
    {
        //QMessageBox::information(this,"��¼��ʾ","��¼�ɹ�");
        Game *dialog=new Game;            //2.������ת����Ϸ����
        dialog->show();
        close();
    }
    else
    {
        QMessageBox::information(this,"��¼��ʾ","��¼ʧ��");

    }
*/


void login::getUserInfo(QString user)
{
    QSqlQuery sql_query;

    QString tempstring = "select * from game where user='"+user+"'";
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
        if(gm_user==user)
            matchFlag=true;
        else
            matchFlag=false;
    }



void login::exitButtonSlot()
{
    close();
}
