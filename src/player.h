#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"
#include <QSet>
#include <QKeyEvent>

class Player : public Tank
{
    Q_OBJECT
public:
    explicit Player(int x = 0, int y = 0, QObject *parent = nullptr);
    void handleKeyPress(int key);
    void handleKeyRelease(int key);
    void update() override;

private:
    QSet<int> pressed_keys_;
};

#endif // PLAYER_H
