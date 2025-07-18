
#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h"

class EnemyTank : public Tank
{
public:
    EnemyTank(int iIndex, int jIndex, Dir dir = DOWN, int style = 0);
    ~EnemyTank();

    // 重写显示函数，使用专门的图片
    void Display(QPainter& paint) override;

    // 设置目标位置，通常是玩家位置
    void setTargetPosition(const QPoint& target);

    // 重写移动函数，包含AI逻辑
    void Move() override;

private:
    // AI决策逻辑
    void decideNextAction();
    // 向玩家开火
    void fireAtPlayer();
    // 判断是否能看到玩家
    bool canSeePlayer() const;
    // 判断路径是否畅通
    bool isPathClear(Dir dir) const;

    QPoint m_targetPosition;

public:
    enum ExplosionState { NotExploding, Exploding, Exploded };


private:
    ExplosionState m_explosionState;

    // 目标位置，通常是玩家位置
};

#endif // ENEMYTANK_H
