#include "map.h"

Map::Map(QWidget *parent)
    : QWidget{parent}
{
    resize(950, 750);
    //检测组合按键
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Map::checkKeyCombinations);
    timer->start(50);
    //创建按钮
    QPushButton* backBtn = new QPushButton("back to main", this);
    backBtn->move(this->width()-80, this->height()-32);
    backBtn->resize(80, 32);
    //监听按钮点击
    connect(backBtn, &QPushButton::clicked, this, [=](){
        emit switchToMainwindow();
        qDebug() << "back to mainwindow";
    });
}

Map::~Map() {}

void Map::renderMap() {

}

QVector<QVector<int>> Map::generateRandomMap() {
        QVector<QVector<int>> map(ROWS, QVector<int>(COLS, 0));  // 初始化全为空地
        QRandomGenerator* rand = QRandomGenerator::global();

        // 1. 设置边界为不可破坏墙体（1）
        for (int i = 0; i < ROWS; ++i) {
            map[i][0] = 1;                  // 左边界
            map[i][COLS-1] = 1;             // 右边界
        }
        for (int j = 0; j < COLS; ++j) {
            map[0][j] = 1;                  // 上边界
            map[ROWS-1][j] = 1;             // 下边界
        }

        // 2. 设置出生点（例如：玩家在(2,2)，敌人在(ROWS-3, COLS-3)）
        QVector<QPoint> spawnPoints = {
            QPoint(2, 2),                  // 玩家1出生点
            QPoint(ROWS-3, COLS-3)         // 敌人出生点
        };
        for (auto& p : spawnPoints) {
            map[p.x()][p.y()] = 5;         // 标记出生点
            // 出生点周围3×3范围设为空地（安全区）
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int x = p.x() + dx;
                    int y = p.y() + dy;
                    if (x > 0 && x < ROWS-1 && y > 0 && y < COLS-1) {
                        map[x][y] = 0;
                    }
                }
            }
        }

        // 3. 随机生成障碍物（1和2）
        int totalCells = (ROWS-2) * (COLS-2);  // 除去边界的总单元格数
        int obstacleCount = totalCells * OBSTACLE_DENSITY / 100;  // 障碍物总数

        for (int k = 0; k < obstacleCount; ++k) {
            // 随机生成一个非边界、非出生点的位置
            int x, y;
            do {
                x = rand->bounded(1, ROWS-1);  // 避开边界（0和ROWS-1）
                y = rand->bounded(1, COLS-1);  // 避开边界（0和COLS-1）
            } while (map[x][y] != 0);  // 确保是空地（排除已占用的单元格）

            // 随机决定是不可破坏墙体（1）还是可破坏墙体（2）
            if (rand->bounded(100) < BREAKABLE_RATIO) {
                map[x][y] = 2;  // 可破坏墙体
            } else {
                map[x][y] = 1;  // 不可破坏墙体
            }
        }

        // 4. 随机添加道具点（3）
        int propCount = 5;  // 道具数量
        for (int k = 0; k < propCount; ++k) {
            int x, y;
            do {
                x = rand->bounded(1, ROWS-1);
                y = rand->bounded(1, COLS-1);
            } while (map[x][y] != 0);  // 只在空地上放道具
            map[x][y] = 3;
        }

        // 5. 随机添加水域（4）（可选）
        int waterCount = 10;
        for (int k = 0; k < waterCount; ++k) {
            int x, y;
            do {
                x = rand->bounded(1, ROWS-1);
                y = rand->bounded(1, COLS-1);
            } while (map[x][y] != 0);  // 只在空地上放水域
            map[x][y] = 4;
        }

        return map;
}


void Map::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap image;
    image.load(":/wall/images/walls/2.png");
    painter.drawPixmap(0, 0, image);
    painter.drawPixmap(0, 50, image);
}

void Map::keyPressEvent(QKeyEvent * event){
    if (!event->isAutoRepeat()) {
        pressed_keys.insert(event->key());
    }
    QWidget::keyPressEvent(event);
}

void Map::keyRealeaseEent(QKeyEvent * event){
    if (!event->isAutoRepeat()) {
        pressed_keys.insert(event->key());
    }
    QWidget::keyReleaseEvent(event);
}

void Map::checkKeyCombinations(){
    if (pressed_keys.contains(Qt::Key_CapsLock) &&
        pressed_keys.contains(Qt::Key_Escape)) {
        close();
    }
}
