#include "enemy.h"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QtMath>

Enemy::Enemy(int x, int y, EnemyType enemy_type, QObject *parent)
    : Tank(x, y, EnemyTank, parent), enemy_type_(enemy_type), health_(1), fire_rate_(100), fire_counter_(0)
{
    switch(enemy_type) {
    case Normal:
        health_ = 1;
        speed = 2;
        break;
    case Fast:
        health_ = 1;
        speed = 4;
        break;
    case Heavy:
        health_ = 3;
        speed = 1;
        break;
    case Boss:
        health_ = 10;
        speed = 1;
        fire_rate_ = 50;
        break;
    }
    updateImage();
}

Enemy::~Enemy() {}

void Enemy::update()
{
    moveAI();
    shoot();
}

void Enemy::moveAI()
{
    // 随机旋转或前进
    int action = QRandomGenerator::global()->bounded(10);
    if (action < 2) {
        // 20%概率旋转
        if (QRandomGenerator::global()->bounded(2) == 0)
            rotateLeft();
        else
            rotateRight();
    } else {
        // 80%概率前进
        moveForward();
    }
}

void Enemy::shoot()
{
    if (fire_counter_ < fire_rate_) {
        fire_counter_++;
        return;
    }
    fire_counter_ = 0;
    qDebug() << "Enemy shoot!";
}

void Enemy::takeDamage(int damage)
{
    health_ -= damage;
    if (health_ <= 0) {
        emit destroyed(this);
    }
}

void Enemy::updateImage()
{
    QString filepath = ":/images/enemy/enemy1.gif";
    if (enemy_type_ == Heavy || enemy_type_ == Boss)
        filepath = ":/images/enemy/enemy2.gif";
    QPixmap pix(filepath);
    if (pix.isNull()) {
        qDebug() << "敌人图片加载失败:" << filepath;
        return;
    }
    if (graphics_item_)
        graphics_item_->setPixmap(pix.scaled(width, height));
    if (graphics_item_)
        graphics_item_->setRotation(direction_angle_);
}
