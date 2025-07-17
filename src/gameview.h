#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

#include "startscene.h"
#include "gamescene.h"
#include "gameoverscene.h"

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GameView(QWidget *parent = nullptr);
    ~GameView();

private slots:
    void switchScene(int sceneType);
    void checkKeyCombinations();
    void run();

private:
    StartScene *start_scene = nullptr;
    GameScene *game_scene = nullptr;
    GameOverScene *game_over_scene = nullptr;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

protected:
    //检测组合按键部分
    QTimer* timer;
    QSet<int> pressed_keys;
    //游戏循环部分
    QTimer* game_timer;
};

#endif // GAMEVIEW_H

