#include "tank.h"
#include <QDebug>
#include <QtMath>

Tank::Tank(int x, int y, TankType type, QObject *parent)
    : GameObject(x, y, 40, 40, (type == PlayerTank) ? PlayerType : EnemyType, parent),
      tank_type_(type), direction_angle_(0.0), graphics_item_(nullptr)
{
    // 设置坦克速度
    speed = 3;
    // 创建图形项
    graphics_item_ = new QGraphicsPixmapItem();
    graphics_item_->setPos(this->x, this->y);
    updateImage();
}

Tank::~Tank() {
    if (graphics_item_) {
        delete graphics_item_;
        graphics_item_ = nullptr;
    }
}

void Tank::savePrevPos() {
    prev_x_ = x;
    prev_y_ = y;
}

void Tank::rollbackPos() {
    syncAllPos(prev_x_, prev_y_);
    if (graphics_item_) {
        graphics_item_->setPos(prev_x_, prev_y_);
        graphics_item_->setRotation(direction_angle_);
    }
}

void Tank::moveForward()
{
    savePrevPos();
    double rad = qDegreesToRadians(direction_angle_);
    int dx = static_cast<int>(speed * std::sin(rad));
    int dy = static_cast<int>(-speed * std::cos(rad));
    int next_x = x + dx;
    int next_y = y + dy;
    // 边界判断
    if (next_x < 0 || next_x > 2400 - 40 || next_y < 0 || next_y > 1800 - 40) {
        return; // 超出边界不移动
    }
    move(dx, dy);
    syncAllPos(x, y); // 新增：同步所有变量
    if (graphics_item_) {
        graphics_item_->setPos(this->x, this->y);
        graphics_item_->setRotation(direction_angle_);
    }
}

void Tank::moveBackward()
{
    savePrevPos();
    double rad = qDegreesToRadians(direction_angle_);
    int dx = static_cast<int>(-speed * std::sin(rad));
    int dy = static_cast<int>(speed * std::cos(rad));
    int next_x = x + dx;
    int next_y = y + dy;
    // 边界判断，假设地图宽1600，高900，坦克宽高40
    if (next_x < 0 || next_x > 1600 - 40 || next_y < 0 || next_y > 900 - 40) {
        return; // 超出边界不移动
    }
    move(dx, dy);
    syncAllPos(x, y); // 新增：同步所有变量
    if (graphics_item_) {
        graphics_item_->setPos(this->x, this->y);
        graphics_item_->setRotation(direction_angle_);
    }
}

void Tank::rotateLeft()
{
    direction_angle_ -= 3.0;
    if (direction_angle_ < 0) direction_angle_ += 360.0;
    if (graphics_item_) graphics_item_->setRotation(direction_angle_);
}

void Tank::rotateRight()
{
    direction_angle_ += 3.0;
    if (direction_angle_ >= 360.0) direction_angle_ -= 360.0;
    if (graphics_item_) graphics_item_->setRotation(direction_angle_);
}

void Tank::shoot()
{
    qDebug() << "Tank fired!";
}

void Tank::update() {}

void Tank::updateImage()
{
    if (!graphics_item_) return;
    QString filepath = ":/images/hero/hero1.gif";
    QPixmap pix(filepath);
    if (pix.isNull()) {
        qDebug() << "坦克图片加载失败:" << filepath;
        return;
    }
    graphics_item_->setPixmap(pix.scaled(40, 40));
    graphics_item_->setRotation(direction_angle_);
}
