#include "gamescene.h"

GameScene::GameScene(QObject* parent)
    : BaseScene {parent}
{
    //游戏基础设置
    this->setSceneRect(0, 0, 2400, 1800);
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
    map_cells_base.resize(rows);
    map_cells_top.resize(rows);
    // 初始化map_cells数组
    for(int i=0;i<rows;++i) {
        map_cells_base[i].resize(cols);
        map_cells_top[i].resize(cols);
        for(int j=0;j<cols;++j) {
            // 创建地面层MapCell
            map_cells_base[i][j] = new MapCell(j, i, Ground, nullptr);
            this->addItem(map_cells_base[i][j]->getGraphicsItem());

            // 创建上层MapCell
            map_cells_top[i][j] = new MapCell(j, i, Ground, nullptr);
            this->addItem(map_cells_top[i][j]->getGraphicsItem());
        }
    }
    // 渲染
    render();

    // 敌人出生点用6号图片覆盖
    int mid = cols / 2;
    QVector<QPoint> enemySpawns = {
        QPoint(1, mid - 5),        // 中上偏左
        QPoint(1, mid + 5),        // 中上偏右
        QPoint(8, 2),              // 左边缘下移3格
        QPoint(8, cols - 3)        // 右边缘下移3格
    };

    // 添加玩家到地图中央
    int player_x = cols / 2;
    int player_y = rows - 3;
    player_ = new Player(player_x * 60 + 10, player_y * 60 + 10, this);
    this->addItem(player_->getGraphicsItem());

    // 生成敌人
    spawner = new EnemySpawner(map, this);
    spawner->setSpawnPoints(enemySpawns);
    spawner->start();
}

// 进入界面
void GameScene::enter() {
    setFocus();
    if (map) {
        map->generateRandomMap();
        render();
    }
}

// 按钮的样式
void GameScene::buttonSetting(SceneButton* button) {
    button->setPosition(1600-60, 900-20);
    button->setSize(60, 20);
}

// 所以按钮的点击事件
void GameScene::totalConnect(SceneButton* button, int type) {
    connect(button, &SceneButton::clicked, this, [=](){
        qDebug() << "点击返回按钮";
        emit switchToScene(type);
    });
}

//更新游戏对象
void GameScene::update() {
    if (player_) player_->update();
    detectCollisions();
}

void GameScene::detectCollisions() {
    // 1. Player与障碍物
    for (int i = 0; i < map->getRows(); ++i) {
        for (int j = 0; j < map->getCols(); ++j) {
            MapCell* cell = map->getMapCell(i, j);
            if (cell->getType() == Brick || cell->getType() == Steel) {
                if (player_->isCollision(cell->getRect())) {
                    qDebug() << "Player与障碍物碰撞:" << i << j;
                    player_->rollbackPos();
                    return; // 新增：回退后直接return
                }
            }
        }
    }
    // 2. Player与Enemy
    for (Enemy* enemy : spawner->getEnemies()) {
        if (player_->isCollision(enemy->getRect())) {
            qDebug() << "Player与Enemy碰撞!";
            player_->rollbackPos();
            return; // 新增：回退后直接return
        }
    }
    // 3. Enemy与障碍物
    for (Enemy* enemy : spawner->getEnemies()) {
        for (int i = 0; i < map->getRows(); ++i) {
            for (int j = 0; j < map->getCols(); ++j) {
                MapCell* cell = map->getMapCell(i, j);
                if (cell->getType() == Brick || cell->getType() == Steel) {
                    if (enemy->isCollision(cell->getRect())) {
                        qDebug() << "Enemy与障碍物碰撞:" << i << j;
                        enemy->rollbackPos();
                        return; // 新增：回退后直接return
                    }
                }
            }
        }
    }
}

//渲染游戏对象
void GameScene::render() {
    int rows = map->getRows();
    int cols = map->getCols();

    // 先渲染所有地面
    for(int i=0;i<rows;++i) {
        for(int j=0;j<cols;++j) {
            map_cells_base[i][j]->setType(Ground);
        }
    }

    // 再渲染上层元素
    for(int i=0;i<rows;++i) {
        for(int j=0;j<cols;++j) {
            CellType cellType = map->getCell(i, j);
            if(cellType == Ground) {
                map_cells_top[i][j]->setVisible(false); // 隐藏上层，显示地面
            } else {
                map_cells_top[i][j]->setVisible(true);
                map_cells_top[i][j]->setType(cellType);
                // 森林图层高于坦克
                if (cellType == Forest) {
                    map_cells_top[i][j]->getGraphicsItem()->setZValue(2000);
                } else {
                    map_cells_top[i][j]->getGraphicsItem()->setZValue(500);
                }
            }
        }
    }

    for(const auto& p : enemySpawns) {
        map_cells_top[p.x()][p.y()]->setVisible(true);
        map_cells_top[p.x()][p.y()]->setType(EnemySpawn);
    }
    // 保证player在最上层
    if (player_) {
        player_->getGraphicsItem()->setZValue(1000);
        player_->getGraphicsItem()->setVisible(true);
    }
}

//游戏界面运行
void GameScene::run() {
    // qDebug() << "gamescene" << running;
    if (running) {
        // qDebug() << "loop";
        update();
        render();
    }
}

//控制游戏开始
void GameScene::gameStart() {
    running = true;
}

//游戏暂停
void GameScene::gameCease() {
    running = false;
}

//测试部分，判断running属性是否正常修改
void GameScene::debug() {
    qDebug() << running;
}

//处理按键按下事件
void GameScene::handlePlayerKeyPress(int key) {
    if (player_) player_->handleKeyPress(key);
}

//处理按键释放
void GameScene::handlePlayerKeyRelease(int key) {
    if (player_) player_->handleKeyRelease(key);
}
