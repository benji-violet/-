#include "startscene.h"

StartScene::StartScene() {
    //设置窗口大小
    resize(950, 750);
    // 初始化定时器，每50ms检查一次按键组合
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartScene::checkKeyCombinations);
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

StartScene::~StartScene() {}

void StartScene::switchToGameScence(Map* map) {
    this->hide();
    map->show();
}

