#include "bullet.h"
#include <QDebug>

Bullet::Bullet(int x, int y, BulletDirection direction, ObjectType ownerType, QObject *parent)
    : GameObject(x, y, 20, 20, BulletType, parent),
      m_direction(direction), m_ownerType(ownerType), m_graphicsItem(nullptr)
{
    // 设置子弹速度
    speed = 10;
    
    // 创建图形项
    m_graphicsItem = new QGraphicsPixmapItem();
    m_graphicsItem->setPos(this->x, this->y);
    updateImage();
}

Bullet::~Bullet() {
    if (m_graphicsItem) {
        delete m_graphicsItem;
        m_graphicsItem = nullptr;
    }
}

void Bullet::move()
{
    int dx = 0, dy = 0;
    switch (m_direction) {
        case BulletUp:    dy = -speed; break;
        case BulletDown:  dy = speed;  break;
        case BulletLeft:  dx = -speed; break;
        case BulletRight: dx = speed;  break;
    }
    
    GameObject::move(dx, dy);
    
    // 更新图形项位置
    if (m_graphicsItem) {
        m_graphicsItem->setPos(this->x, this->y);
    }
}

bool Bullet::isOutOfBounds() const
{
    // 检查子弹是否超出边界
    return (x < 0 || y < 0 || x > 2400 || y > 1800);
}

void Bullet::update()
{
    // Bullet的更新逻辑
    move();
    
    // 检查是否超出边界
    if (isOutOfBounds()) {
        is_alive = false;
    }
}

void Bullet::updateImage()
{
    if (!m_graphicsItem) return;
    
    QString filepath = getImagePath();
    QPixmap pix(filepath);
    
    if (pix.isNull()) {
        qDebug() << "子弹图片加载失败:" << filepath;
        return;
    }
    
    m_graphicsItem->setPixmap(pix.scaled(width, height));
}

QString Bullet::getImagePath() const
{
    return ":/images/bullet/bullet.png";
} 