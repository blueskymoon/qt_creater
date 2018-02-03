#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->welcomButton,SIGNAL(clicked()),SLOT(welcomeButtonSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::welcomeButtonSlot()
{
    login *dialog=new login;
    dialog->show();
    close();
}
