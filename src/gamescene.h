#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QDebug>
#include <QGraphicsPixmapItem>

#include "basescene.h"
#include "scenebutton.h"
#include "gameobject.h"
#include "map.h"
#include "mapcell.h"
#include "player.h"

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

    Player* player_ = nullptr;

protected:
    void totalConnect(SceneButton* button, int type);
    void buttonSetting(SceneButton* button);

    void handleInput();
    void update();
    void render();

private:
    SceneButton* back_btn;
    Map* map = nullptr;
    bool running = false;
    QVector<QVector<MapCell*>> map_cells_base;  // 地面层
    QVector<QVector<MapCell*>> map_cells_top;   // 上层元素
};

#endif // GAMESCENE_H
