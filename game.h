#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

//字符信息结构体
typedef struct _STCHAR
{
    int iIndex;     //字母索引值
    int x;          //字母X坐标
    int y;          //字母Y坐标
    int value;      //字母值
}STCHAR;

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();
    void initpicture();     //初始化图片路径
    void initPosList();     //初始化字母图片位置
    void initWallList();    //初始化砖头
    void checkCrash();      //检查字母是否触底
    void initRocket();      //初始化火箭图片大小
    void RocketMove();      //火箭移动

protected:
    void paintEvent(QPaintEvent *);   //绘图事件
    void keyPressEvent(QKeyEvent * event);  //按键事件
public slots:
    void updateMap();       //更新地图
    void createChar();      //创建字符
    void updateTime();      //更新时间
    void updateScore();     //更新分数


private slots:
    void startButtonSlot();
    void closeButtonSlot();

private:
    Ui::game *ui;
    QList<QString> m_PictureList;   //字母图片路径
    QList<QPoint> m_PosList;        //字母初始位置
    QList<STCHAR> m_CharList;       //字母链表
    QList<QPoint> m_WallList;       //砖头列表
    QLabel *RocketLabel;            //火箭标签
    int m_key;          //用户输入key
    int m_iTime;        //计时时间
    int gScore = 0;

};

#endif // GAME_H
