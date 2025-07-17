#include "gamescene.h"

GameScene::GameScene(QObject* parent)
    : BaseScene {parent}
{
    //游戏基础设置
    this->setSceneRect(0, 0, 1920, 1080);
    setBackgroundBrush(QBrush(Qt::black));
    //新建按钮
    back_btn = new SceneButton("Back");
    //按钮设置
    buttonSetting(back_btn);
    //添加按钮
    this->addItem(back_btn);
    //按钮信号
    totalConnect(back_btn, Start);
    // 初始化地图
    map = new Map(this);
    running = false;
    // 初始化地图显示
    int rows = map->getRows();
    int cols = map->getCols();
    map_items_base.resize(rows);
    map_items_top.resize(rows);
    for(int i=0;i<rows;++i) {
        map_items_base[i].resize(cols);
        map_items_top[i].resize(cols);
        for(int j=0;j<cols;++j) {
            QGraphicsPixmapItem* base = new QGraphicsPixmapItem();
            QGraphicsPixmapItem* top = new QGraphicsPixmapItem();
            base->setPos(j*60, i*60);
            top->setPos(j*60, i*60);
            this->addItem(base);
            this->addItem(top);
            map_items_base[i][j] = base;
            map_items_top[i][j] = top;
        }
    }
    render();
}

void GameScene::enter() {
    setFocus();
    if (map) {
        map->generateRandomMap();
        render();
    }
}

void GameScene::buttonSetting(SceneButton* button) {
    button->setPosition(this->width()-60, this->height()-20);
    button->setSize(60, 20);
}

void GameScene::totalConnect(SceneButton* button, int type) {
    connect(button, &SceneButton::clicked, this, [=](){
        qDebug() << "点击返回按钮";
        emit switchToScene(type);
    });
}

void GameScene::handleInput() {

}

void GameScene::update() {

}

void GameScene::render() {
    int rows = map->getRows();
    int cols = map->getCols();
    // 先用0号图片铺满地面
    for(int i=0;i<rows;++i) {
        for(int j=0;j<cols;++j) {
            QString filepath = QString(":/images/walls/0.png");
            QPixmap pix(filepath);
            map_items_base[i][j]->setPixmap(pix.scaled(60, 60));
        }
    }
    // 上层元素
    int mid = cols / 2;
    QVector<QPoint> enemySpawns = {
        QPoint(1, mid - 5),        // 中上偏左
        QPoint(1, mid + 5),        // 中上偏右
        QPoint(5, 2),              // 左边缘下移3格
        QPoint(5, cols - 3)        // 右边缘下移3格
    };
    for(int i=0;i<rows;++i) {
        for(int j=0;j<cols;++j) {
            int tag = map->getCell(i, j);
            bool isEnemy = false;
            for(const auto& p : enemySpawns) {
                if(i == p.x() && j == p.y()) isEnemy = true;
            }
            if(isEnemy) {
                QString filepath = QString(":/images/walls/6.png");
                QPixmap pix(filepath);
                map_items_top[i][j]->setPixmap(pix.scaled(60, 60));
            } else if(tag == 5) {
                QString filepath = QString(":/images/walls/5.png");
                QPixmap pix(filepath);
                map_items_top[i][j]->setPixmap(pix.scaled(60, 60));
            } else if(tag == 1 || tag == 2 || tag == 3 || tag == 4) {
                QString filepath = QString(":/images/walls/%1.png").arg(tag);
                QPixmap pix(filepath);
                map_items_top[i][j]->setPixmap(pix.scaled(60, 60));
            } else {
                map_items_top[i][j]->setPixmap(QPixmap()); // 透明
            }
        }
    }
}

void GameScene::run() {
    qDebug() << "gamescene" << running;
    if (running) {
        qDebug() << "loop";
        handleInput();
        update();
        render();
    }
}

void GameScene::gameStart() {
    running = true;
}

void GameScene::gameCease() {
    running = false;
}

void GameScene::debug() {
    qDebug() << running;
}
