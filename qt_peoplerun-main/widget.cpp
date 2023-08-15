#pragma execution_character_set("utf-8")
#include "widget.h"
#include"game_wgt.h"
#include<QIcon>
#include<QSound>
#include<QPushButton>
#include<QMouseEvent>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initControl();
}

Widget::~Widget()
{
}

void Widget::initControl()
{
    setFixedSize(win_size_width,win_size_height);
    setWindowIcon(QIcon(win_icon));
    setWindowTitle("Run Fast To Win");
    QSound*startSound=new QSound(bg_sound,this);
    startSound->play();
    startSound->setLoops(QSound::Infinite);//无限循环
    gameWgt=new GameWgt(this,width(),height());

    //
    createBtn(startBtn,startBtnNormal,startBtnX,startBtnY);
    createBtn(operateBtn,operateBtnNormal,operateBtnX,operateBtnY);
    createBtn(methodBtn,methodBtnNormal,methodBtnX,methodBtnY);
    createBtn(recordBtn,recordBtnNormal,recordBtnX,recordBtnY);
}
//创建一个按钮，然后设置按钮背景，和位置。
void Widget::createBtn(QPushButton *&btn, const char *png, int x, int y)
{
    btn=new QPushButton(this);
    btn->setStyleSheet("QPushButton{border:0px;}");//消除外虚线框
    btn->move(x,y);//移动到指定位置

    QPixmap pix(png);
    btn->setFixedSize(pix.size());
    btn->setIcon(pix);
    btn->setIconSize(pix.size());

    btn->installEventFilter(this);//注册事件过滤器,以便鼠标悬停或离开时切换图片
    connect(btn,&QPushButton::clicked,this,&Widget::btnClickSlot);//点击操作
}
//
void Widget::changeBtnIcon(QPushButton *&btn, const char *pngNormal,
                           const char*pngEnter, QEvent *event)
{
    if(event->type()==QEvent::Enter)//鼠标进入
    {
        QPixmap pix(pngEnter);
        btn->setFixedSize(pix.size());
        btn->setIcon(pix);
        btn->setIconSize(pix.size());
        btn->move(btn->x()-btnOffset,btn->y()-btnOffset);//移动50
    }
    else if(event->type()==QEvent::Leave)//鼠标离开
    {
        QPixmap pix(pngNormal);
        btn->setFixedSize(pix.size());
        btn->setIcon(pix);
        btn->setIconSize(pix.size());
        btn->move(btn->x()+btnOffset,btn->y()+btnOffset);
    }
}

void Widget::btnClickSlot(){
    QPushButton*btn=qobject_cast<QPushButton*>(sender());
    if(btn==startBtn){ //这里是开始游戏的按钮
        gameWgt->setRun(true);//开始运行这个窗口
        gameWgt->startBtn=startBtn;
        gameWgt->operateBtn=operateBtn;
        gameWgt->recordBtn=recordBtn;
        gameWgt->methodBtn=methodBtn;
        gameWgt->startGame();

        startBtn->hide();
        operateBtn->hide();
        recordBtn->hide();
        methodBtn->hide();
    }
    else if(btn==operateBtn){//操作
        QMessageBox::about(this,"游戏按键操作","按 键 操 作 :\n"
                                        "1.K键控制跳跃，在空中可进行二次跳跃。\n"
                                        "2.S键控制快速下降。\n"
                                        "3.A键向左移动。\n"
                                        "4.D键向右移动。\n"
                                        "5.Q键闪现。\n"
                                        "6.J键攻击。\n"
                                        "7.Esc暂停游戏。\n"
                                        "8.R键重新开始\n"
                                        "9.B键返回主页面");
    }
    else if(btn==methodBtn)
    {
        QMessageBox::about(this,"玩法说明","游 戏 玩 法 :躲避所有kunkun和他的蓝球，并吃到尽可能多的金币！吃到星星能获得短暂攻击能力哦~\n");
    }
    else if(btn==recordBtn)//历史记录
    {
        QMessageBox::about(this,"历史记录",QString("历史最高分:%1").arg(gameWgt->getMaxScore()));
    }
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==startBtn) //这里事件过滤器实现了按钮变大的效果
    {
        changeBtnIcon(startBtn,startBtnNormal,startBtnEnter,event);
    }
    else if(watched==operateBtn)
    {
        changeBtnIcon(operateBtn,operateBtnNormal,operateBtnEnter,event);
    }
    else if(watched==methodBtn)
    {
        changeBtnIcon(methodBtn,methodBtnNormal,methodBtnEnter,event);
    }
    else if(watched==recordBtn)
    {
        changeBtnIcon(recordBtn,recordBtnNormal,recordBtnEnter,event);
    }

    return QWidget::eventFilter(watched,event);
}

