#include "totalscene.h"
#include "ui_totalscene.h"

TotalScene::TotalScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TotalScene)
{
    ui->setupUi(this);
    //设置窗口大小
    resize(950, 750);
    // 初始化定时器，每50ms检查一次按键组合
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TotalScene::checkKeyCombinations);
    timer->start(50);
}

TotalScene::~TotalScene()
{
    delete ui;
}

//按下按键
void TotalScene::keyPressEvent(QKeyEvent *event)
{
    // 添加按键到集合，但忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressed_keys.insert(event->key());
    }
    QWidget::keyPressEvent(event);
}

//释放按键
void TotalScene::keyReleaseEvent(QKeyEvent *event)
{
    // 从集合中移除按键，忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressed_keys.remove(event->key());
    }
    QWidget::keyReleaseEvent(event);
}

//检测组合按键
void TotalScene::checkKeyCombinations(){
    // capslock+escape键 退出
    if (pressed_keys.contains(Qt::Key_CapsLock) &&
        pressed_keys.contains(Qt::Key_Escape)) {
        qDebug() << "press capslock and escape";
        close();
    }
}
