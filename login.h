#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "sign.h"
#include "game.h"
#include <QMessageBox>
#include <QtSql>
#include <QPainter>


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();


signals:
    void transmitdb(QSqlDatabase db);

private:
    Ui::login *ui;
    bool tableFlag;
    QSqlDatabase database;
    QSqlQuery sqt_query;

    int gm_id;
    QString gm_passwd;
    QString gm_user;
    QString gm_email;
    int gm_history;
    bool matchFlag;



    //���ݿ������Ϊgame.db   �������Ϊgameone     �û��� user  ����passwd   id chatid  �����ʼ� email
private:
    QString select_table;
    QString create_sql;
    QString insert_sql;
    QString select_sql;
    QString select_nameInfo;



private slots:
    void signButtonSlot();
    void loginButtonSlot();
    void getUserInfo(QString user);
    void exitButtonSlot();

};


#endif // LOGIN_H
