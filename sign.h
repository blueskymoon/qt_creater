#ifndef SIGN_H
#define SIGN_H

#include <QDialog>
#include "game.h"
#include "login.h"
#include <QtSql>



namespace Ui {
class Sign;
}

class Sign : public QDialog
{
    Q_OBJECT

public:
    explicit Sign(QWidget *parent = 0);
    ~Sign();

private:
    Ui::Sign *ui;

private slots:
    void finishButtonSlot();
    void exitButtonSlot();
    void receivedb(QSqlDatabase db);
private:
    QSqlDatabase database;
    bool tableFlag;
    int max_id;


};

#endif // SIGN_H
