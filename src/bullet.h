#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
#include <QGraphicsPixmapItem>

enum BulletDirection {
    BulletUp,
    BulletDown,
    BulletLeft,
    BulletRight
};

class Bullet : public GameObject
{
    Q_OBJECT
public:
    explicit Bullet(int x, int y, BulletDirection direction, ObjectType ownerType = NeutralType, QObject *parent = nullptr);
    ~Bullet();

    // Bullet特有方法
    void move();
    bool isOutOfBounds() const;
    
    // 获取和设置属性
    BulletDirection getDirection() const { return m_direction; }
    ObjectType getOwnerType() const { return m_ownerType; }
    
    // 获取图形项（用于添加到场景）
    QGraphicsPixmapItem* getGraphicsItem() const { return m_graphicsItem; }
    
    // 实现GameObject的纯虚函数
    void update() override;

private:
    BulletDirection m_direction;
    ObjectType m_ownerType;
    QGraphicsPixmapItem* m_graphicsItem;
    
    void updateImage();
    QString getImagePath() const;
};

#endif // BULLET_H 