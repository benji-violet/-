#include "tank.h"
#include <QDebug>
#include <QtMath>

Tank::Tank(int x, int y, TankType type, QObject *parent)
    : GameObject(x, y, 60, 60, (type == PlayerTank) ? PlayerType : EnemyType, parent),
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

void Tank::moveForward()
{
    double rad = qDegreesToRadians(direction_angle_);
    int dx = static_cast<int>(speed * std::sin(rad));
    int dy = static_cast<int>(-speed * std::cos(rad));
    move(dx, dy);
    if (graphics_item_) {
        graphics_item_->setPos(this->x, this->y);
        graphics_item_->setRotation(direction_angle_);
    }
}

void Tank::moveBackward()
{
    double rad = qDegreesToRadians(direction_angle_);
    int dx = static_cast<int>(-speed * std::sin(rad));
    int dy = static_cast<int>(speed * std::cos(rad));
    move(dx, dy);
    if (graphics_item_) {
        graphics_item_->setPos(this->x, this->y);
        graphics_item_->setRotation(direction_angle_);
    }
}

void Tank::rotateLeft()
{
    direction_angle_ -= 10.0;
    if (direction_angle_ < 0) direction_angle_ += 360.0;
    if (graphics_item_) graphics_item_->setRotation(direction_angle_);
}

void Tank::rotateRight()
{
    direction_angle_ += 10.0;
    if (direction_angle_ >= 360.0) direction_angle_ -= 360.0;
    if (graphics_item_) graphics_item_->setRotation(direction_angle_);
}

void Tank::shoot()
{
    qDebug() << "Tank fired!";
}

void Tank::update()
{
    // Tank的更新逻辑
}

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

QString Tank::getImagePath() const
{
    return ":/images/hero/hero1U.gif";
}
