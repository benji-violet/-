#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QDebug>
#include <QGraphicsPixmapItem>

#include "basescene.h"
#include "scenebutton.h"
#include "map.h"

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
    QVector<QVector<QGraphicsPixmapItem*>> map_items_base;
    QVector<QVector<QGraphicsPixmapItem*>> map_items_top;
};

#endif // GAMESCENE_H
