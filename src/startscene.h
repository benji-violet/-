#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include "totalscene.h"
#include "map.h"


class StartScene : public TotalScene
{
    Q_OBJECT

public:
    StartScene();
    ~StartScene();

protected:
    void switchToGameScence(Map* map);

private:
};
#endif // STARTSCENE_H
