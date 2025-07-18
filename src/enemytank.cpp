#include "enemytank.h"
#include "main.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include "bullet.h"
EnemyTank::EnemyTank(int iIndex, int jIndex, Dir dir, int style)
    : Tank(iIndex, jIndex, dir, style, 1), // 组别1表示敌人
    m_targetPosition(QPoint())
{
    // 初始时开始移动
    startmove();
}

EnemyTank::~EnemyTank()
{
    // 无需处理定时器，因为已经移除
}

void EnemyTank::Display(QPainter& paint)
{
    m_explosionState=NotExploding;
    if (m_bDisappear){
        QImage explosimg("images\boom\blast1.glf");
        paint.drawImage(m_rectSphere, explosimg);
        return;} ;

    // 先绘制子弹
    for (int i = 0; i < bullets.size(); i++) {
        if (!bullets[i]->IsDisappear()) {
            bullets[i]->Display(paint);
        }
        else {
            delete bullets[i];
            auto it = bullets.begin() + i;
            bullets.erase(it);
            i--;
        }
    }

    QString imagePath;

    // 根据坦克等级和方向选择不同图片
    switch (this->getstyle()) {
    case 0: // 普通坦克
        switch (m_dir) {
        case UP:    imagePath = "images/enemy/enemy1U.gif"; break;
        case DOWN:  imagePath = "images/enemy/enemy1D.gif"; break;
        case LEFT:  imagePath = "images/enemy/enemy1L.gif"; break;
        case RIGHT: imagePath = "images/enemy/enemy1R.gif"; break;
        }
        break;
    case 1: // 中型坦克
        switch (m_dir) {
        case UP:    imagePath = "images/enemy/enemy2U.gif"; break;
        case DOWN:  imagePath = "images/enemy/enemy2D.gif"; break;
        case LEFT:  imagePath = "images/enemy/enemy2L.gif"; break;
        case RIGHT: imagePath = "images/enemy/enemy2R.gif"; break;
        }
        break;
    case 2: // 重型坦克
        switch (m_dir) {
        case UP:    imagePath = "images/enemy/enemy2U.gif"; break;
        case DOWN:  imagePath = "images/enemy/enemy2D.gif"; break;
        case LEFT:  imagePath = "images/enemy/enemy2L.gif"; break;
        case RIGHT: imagePath = "images/enemy/enemy2R.gif"; break;
        }
        break;
    default: // 默认图片
        imagePath = "images/enemy/enemy1U.gif";
    }

    QImage img(imagePath);
    if (!img.isNull()) {
        paint.drawImage(m_rectSphere, img);
    }
}

void EnemyTank::Move()
{
    // 先调用基类的移动方法
    Tank::Move();

    // 如果坦克消失，停止移动
    if (m_bDisappear) {
        stopmove();
        return;
    }

    // 进行AI决策
    decideNextAction();

    // 如果能看到玩家，尝试开火
    if (canSeePlayer()) {
        fireAtPlayer();
    }
}

void EnemyTank::setTargetPosition(const QPoint& target)
{
    m_targetPosition = target;
}

void EnemyTank::decideNextAction()
{
    if (canSeePlayer()) {
        // 朝向玩家移动
        Dir targetDir = static_cast<Dir>((m_targetPosition.x() > m_pos.x()) ? RIGHT : ((m_targetPosition.x() < m_pos.x()) ? LEFT : m_dir));
        if (m_targetPosition.y() > m_pos.y()) targetDir = DOWN;
        if (m_targetPosition.y() < m_pos.y()) targetDir = UP;

        if (isPathClear(targetDir)) {
            setdir(targetDir);
        }
    }
    else {
        // 随机移动
        Dir newDir = static_cast<Dir>(QRandomGenerator::global()->bounded(4));
        if (isPathClear(newDir)) {
            setdir(newDir);
        }
    }
}

bool EnemyTank::canSeePlayer() const
{
    if (m_targetPosition.isNull()) return false;

    // 计算距离
    double distance = qSqrt(qPow(m_targetPosition.x() - m_pos.x(), 2) +
                            qPow(m_targetPosition.y() - m_pos.y(), 2));

    // 视野距离限制
    if (distance > 500) return false;

    // 检查方向是否大致一致
    Dir targetDir = static_cast<Dir>((m_targetPosition.x() > m_pos.x()) ? RIGHT : ((m_targetPosition.x() < m_pos.x()) ? LEFT : m_dir));
    if (m_targetPosition.y() > m_pos.y()) targetDir = DOWN;
    if (m_targetPosition.y() < m_pos.y()) targetDir = UP;

    return targetDir == m_dir;
}

bool EnemyTank::isPathClear(Dir dir) const
{
    // 创建临时坦克用于预测碰撞
    Tank tmpTank = *this;
    tmpTank.setdir(dir);

    // 尝试移动一步
    tmpTank.Move1();

    // 检查边界
    if (tmpTank.getrect().left() < 0 ||
        tmpTank.getrect().right() > 950 ||
        tmpTank.getrect().bottom() > 750 ||
        tmpTank.getrect().top() < 0) {
        return false;
    }

    // 检查地图碰撞
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (glo.gamemap->getcell(i, j) &&
                !glo.gamemap->getcell(i, j)->ischuantou() &&
                tmpTank.IsBoom(*glo.gamemap->getcell(i, j))) {
                return false;
            }
        }
    }

    return true;
}

void EnemyTank::fireAtPlayer()
{
    // 调用基类开火方法
    if (this->getisfire()) {
        Bullet* newbullet = new Bullet(*this);
        bullets.push_back(newbullet);
    }
}
