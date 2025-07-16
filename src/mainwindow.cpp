#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口大小
    resize(950, 750);
    // 初始化定时器，每50ms检查一次按键组合
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkKeyCombinations);
    timer->start(50);
    //创建按钮
    QPushButton* startBtn = new QPushButton("game start", this);
    startBtn->move(this->width()/2-75, this->height()/2-32.5);
    startBtn->resize(150, 65);
    //监听按钮点击
    Map* map = new Map;
    connect(map, &Map::switchToMainwindow, this, [=](){
        map->hide();
        this->show();
    });
    connect(startBtn, &QPushButton::clicked, this, [=](){
        qDebug() << "click the button startBtn";
        switchToGameScence(map);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToGameScence(Map* map) {
    this->hide();
    map->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 添加按键到集合，但忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressedKeys.insert(event->key());
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    // 从集合中移除按键，忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressedKeys.remove(event->key());
    }
    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::checkKeyCombinations(){
    // capslock+escape键 退出
    if (pressedKeys.contains(Qt::Key_CapsLock) &&
        pressedKeys.contains(Qt::Key_Escape)) {
        qDebug() << "press capslock and escape";
        close();
    }
}
