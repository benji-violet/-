#ifndef BASESCENE_H
#define BASESCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "scenebutton.h"

enum SceneType {
    Start, Game, GameOver, Close, Help
};

class BaseScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BaseScene(QObject *parent = nullptr);
    ~BaseScene() = default;

//方法
protected:
    virtual void enter() = 0;   //进入界面

//场景切换信号
signals:
    void switchToScene(int sceneType);
};

#endif // BASESCENE_H
