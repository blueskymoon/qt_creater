#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

//�ַ���Ϣ�ṹ��
typedef struct _STCHAR
{
    int iIndex;     //��ĸ����ֵ
    int x;          //��ĸX����
    int y;          //��ĸY����
    int value;      //��ĸֵ
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
    void initpicture();     //��ʼ��ͼƬ·��
    void initPosList();     //��ʼ����ĸͼƬλ��
    void initWallList();    //��ʼ��שͷ
    void checkCrash();      //�����ĸ�Ƿ񴥵�
    void initRocket();      //��ʼ�����ͼƬ��С
    void RocketMove();      //����ƶ�

protected:
    void paintEvent(QPaintEvent *);   //��ͼ�¼�
    void keyPressEvent(QKeyEvent * event);  //�����¼�
public slots:
    void updateMap();       //���µ�ͼ
    void createChar();      //�����ַ�
    void updateTime();      //����ʱ��
    void updateScore();     //���·���


private slots:
    void startButtonSlot();
    void closeButtonSlot();

private:
    Ui::game *ui;
    QList<QString> m_PictureList;   //��ĸͼƬ·��
    QList<QPoint> m_PosList;        //��ĸ��ʼλ��
    QList<STCHAR> m_CharList;       //��ĸ����
    QList<QPoint> m_WallList;       //שͷ�б�
    QLabel *RocketLabel;            //�����ǩ
    int m_key;          //�û�����key
    int m_iTime;        //��ʱʱ��
    int gScore = 0;

};

#endif // GAME_H
