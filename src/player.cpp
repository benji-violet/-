#include "player.h"

Player::Player(int x, int y, QObject *parent)
    : Tank(x, y, PlayerTank, parent)
{
    if (graphics_item_) {
        graphics_item_->setTransformOriginPoint(width / 2, height / 2);
    }
}

void Player::handleKeyPress(int key)
{
    pressed_keys_.insert(key);
}

void Player::handleKeyRelease(int key)
{
    pressed_keys_.remove(key);
}

void Player::update()
{
    // 按键优先级：旋转 > 移动
    if (pressed_keys_.contains(Qt::Key_A)) {
        direction_angle_ -= 3.0; // 旋转速度
        if (direction_angle_ < 0) direction_angle_ += 360.0;
        if (graphics_item_) graphics_item_->setRotation(direction_angle_);
    }
    if (pressed_keys_.contains(Qt::Key_D)) {
        direction_angle_ += 3.0; // 旋转速度
        if (direction_angle_ >= 360.0) direction_angle_ -= 360.0;
        if (graphics_item_) graphics_item_->setRotation(direction_angle_);
    }
    if (pressed_keys_.contains(Qt::Key_W)) {
        moveForward();
    }
    if (pressed_keys_.contains(Qt::Key_S)) {
        moveBackward();
    }
}
