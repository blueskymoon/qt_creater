#include "game.h"
#include "ui_game.h"

#include <QMessageBox>
//声明它是一个外部变量
extern int gScore;


game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game),
    m_iTime(60)
{
    ui->setupUi(this);
    initWallList();
    checkCrash();
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startButtonSlot()));
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeButtonSlot()));

}

game::~game()
{
    delete ui;
}

void game::startButtonSlot()             //开始按键
{
    initpicture();          //初始化图片路径
    initPosList();          //初始化图片位置
    checkCrash();           //检查字母是否撞倒地
    //1.定义控制字母下移的定时器
    QTimer *DownTimer = new QTimer;
    connect(DownTimer,SIGNAL(timeout()),this,SLOT(updateMap()));
    DownTimer->start(1000);

    //2.定义一个产生字母的定时器
    QTimer *CharTimer = new QTimer;
    connect(CharTimer,SIGNAL(timeout()),this,SLOT(createChar()));
    CharTimer->start(3000);


    //3.定义一个刷新分数的定时器
    QTimer *ScoreTimer = new QTimer;
    connect(ScoreTimer,SIGNAL(timeout()),this,SLOT(updateScore()));
    ScoreTimer->start(500);
    //4.定义一个刷新计时的定时器
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);

}

void game::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    //1.绘制背景
    p.drawPixmap(0,0,800,640,QPixmap(":image/back.jpg"));
    //2.绘制砖头
    for(int i = 0; i< m_WallList.size(); ++i)
    {
        int x = m_WallList.at(i).x();
        int y = m_WallList.at(i).y();
        p.drawPixmap(x,y,40,40,QPixmap(":image/wall.jpg"));
    }
    //3.绘制随机产生的字母
    for(int i = 0;i<m_CharList.size();++i)
    {
        int x = m_CharList.at(i).x;
        int y = m_CharList.at(i).y;
        int iIndex = m_CharList.at(i).iIndex;
        p.drawPixmap(x,y,40,40,QPixmap(m_PictureList.at(iIndex)));

    }
}

//按键事件
void game::keyPressEvent(QKeyEvent *event)
{
    m_key = event->key();
    m_key += 32;
    for(int i = 0; i< m_CharList.size();++i)
        if(m_key == m_CharList.at(i).value)
        {
            m_CharList.removeAt(i);
            gScore += 10;
            break;
        }
    update();
    return;

}

//更新地图
void game::updateMap()
{
    //1.改变字母的位置
    for(int i =0;i<m_CharList.size();++i)
        m_CharList[i].y +=40;
    //2.检查字母是否触底
    checkCrash();
    //3.重绘地图
    update();
    return;

}

//产生字母
void game::createChar()
{
    if(m_CharList.size() > 4)
        return;

    STCHAR stChar;
    stChar.iIndex = rand()%m_PictureList.size();
    stChar.x = m_PosList.at(stChar.iIndex%20).x();
    stChar.y = m_PosList.at(stChar.iIndex%20).y();
    stChar.value = stChar.iIndex + 'a';

    m_CharList.append(stChar);
    return;
}

//初始化图片路径
void game::initpicture()
{
    for(char i = 'a'; i <= 'z'; ++i)
    {
        QString szPath = QString(":image/%1.jpg").arg(i);
        m_PictureList.append(szPath);
    }
    return;
}
void game::initPosList()
{
    for(int iCol = 0; iCol < 20; ++iCol)
        m_PosList.append(QPoint(iCol*40,0));
    return ;
}
//初始化砖头列表
void game::initWallList()
{
    for(int iRow = 13;iRow < 16; ++ iRow)
        for(int iCol = 0;iCol <20;++iCol)
            m_WallList.append(QPoint(iCol*40,iRow*40));
    return;
}

//检查字母是否触底
void game::checkCrash()
{
    for(int i = 0; i< m_CharList.size(); ++i)
        for(int j =0; j < m_WallList.size(); ++j)
        {
            int x1 = m_CharList.at(i).x;
            int y1 = m_CharList.at(i).y;
            int x2 = m_WallList.at(j).x();
            int y2 = m_WallList.at(j).y();
            if( x1 == x2 && y1 ==y2)
            {
                m_CharList.removeAt(i);
                m_WallList.removeAt(j);
                gScore -=5;
                return;
            }
        }
}


void game::updateTime()                 //更新时间
{
   ui->timeLcd->display(m_iTime--);
   if(m_iTime<0)
    close();
   return;
}


void game::updateScore()            //刷新显示分数
{
    ui->scoreLcd->display(gScore);
    return;
}

void game::closeButtonSlot()            //关闭按钮
{
    close();
}
