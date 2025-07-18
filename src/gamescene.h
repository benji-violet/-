#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QVector>

#include "basescene.h"
#include "enemy.h"
#include "enemyspawner.h"
#include "map.h"
#include "mapcell.h"
#include "player.h"
#include "scenebutton.h"


class GameScene : public BaseScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject* parent = nullptr);
    ~GameScene() = default;
    void enter() override;

    void gameStart();
    void gameCease();

    void run();
    void debug();

    void handlePlayerKeyPress(int key);
    void handlePlayerKeyRelease(int key);

    //有关tank的对象生成
    Player* player_ = nullptr;
    Enemy* enemy_ = nullptr;
    EnemySpawner* spawner = nullptr;

protected:
    void totalConnect(SceneButton* button, int type);
    void buttonSetting(SceneButton* button);

    void update();
    void render();

private:
    void detectCollisions();
    SceneButton* back_btn;
    Map* map = nullptr;
    bool running = false;
    QVector<QVector<MapCell*>> map_cells_base;  // 地面层
    QVector<QVector<MapCell*>> map_cells_top;   // 上层元素
    QVector<QPoint> enemySpawns;    // 敌人生成点数组
};

#endif // GAMESCENE_H
