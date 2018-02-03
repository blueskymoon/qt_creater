#include "game.h"
#include "ui_game.h"

#include <QMessageBox>
//��������һ���ⲿ����
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

void game::startButtonSlot()             //��ʼ����
{
    initpicture();          //��ʼ��ͼƬ·��
    initPosList();          //��ʼ��ͼƬλ��
    checkCrash();           //�����ĸ�Ƿ�ײ����
    //1.���������ĸ���ƵĶ�ʱ��
    QTimer *DownTimer = new QTimer;
    connect(DownTimer,SIGNAL(timeout()),this,SLOT(updateMap()));
    DownTimer->start(1000);

    //2.����һ��������ĸ�Ķ�ʱ��
    QTimer *CharTimer = new QTimer;
    connect(CharTimer,SIGNAL(timeout()),this,SLOT(createChar()));
    CharTimer->start(3000);


    //3.����һ��ˢ�·����Ķ�ʱ��
    QTimer *ScoreTimer = new QTimer;
    connect(ScoreTimer,SIGNAL(timeout()),this,SLOT(updateScore()));
    ScoreTimer->start(500);
    //4.����һ��ˢ�¼�ʱ�Ķ�ʱ��
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(1000);

}

void game::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    //1.���Ʊ���
    p.drawPixmap(0,0,800,640,QPixmap(":image/back.jpg"));
    //2.����שͷ
    for(int i = 0; i< m_WallList.size(); ++i)
    {
        int x = m_WallList.at(i).x();
        int y = m_WallList.at(i).y();
        p.drawPixmap(x,y,40,40,QPixmap(":image/wall.jpg"));
    }
    //3.���������������ĸ
    for(int i = 0;i<m_CharList.size();++i)
    {
        int x = m_CharList.at(i).x;
        int y = m_CharList.at(i).y;
        int iIndex = m_CharList.at(i).iIndex;
        p.drawPixmap(x,y,40,40,QPixmap(m_PictureList.at(iIndex)));

    }
}

//�����¼�
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

//���µ�ͼ
void game::updateMap()
{
    //1.�ı���ĸ��λ��
    for(int i =0;i<m_CharList.size();++i)
        m_CharList[i].y +=40;
    //2.�����ĸ�Ƿ񴥵�
    checkCrash();
    //3.�ػ��ͼ
    update();
    return;

}

//������ĸ
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

//��ʼ��ͼƬ·��
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
//��ʼ��שͷ�б�
void game::initWallList()
{
    for(int iRow = 13;iRow < 16; ++ iRow)
        for(int iCol = 0;iCol <20;++iCol)
            m_WallList.append(QPoint(iCol*40,iRow*40));
    return;
}

//�����ĸ�Ƿ񴥵�
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


void game::updateTime()                 //����ʱ��
{
   ui->timeLcd->display(m_iTime--);
   if(m_iTime<0)
    close();
   return;
}


void game::updateScore()            //ˢ����ʾ����
{
    ui->scoreLcd->display(gScore);
    return;
}

void game::closeButtonSlot()            //�رհ�ť
{
    close();
}
