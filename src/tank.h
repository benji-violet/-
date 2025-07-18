#ifndef TANK_H
#define TANK_H

#include "gameobject.h"
#include <QGraphicsPixmapItem>
#include <cmath>

enum TankType {
    PlayerTank,
    EnemyTank
};

class Tank : public GameObject
{
    Q_OBJECT
public:
    explicit Tank(int x, int y, TankType type = PlayerTank, QObject *parent = nullptr);
    ~Tank();

    // Tank特有方法
    void moveForward();
    void moveBackward();
    void rotateLeft();   // a键
    void rotateRight();  // d键
    virtual void shoot();
    
    // 获取和设置属性
    TankType getTankType() const { return tank_type_; }
    double getDirectionAngle() const { return direction_angle_; }
    
    // 获取图形项（用于添加到场景）
    QGraphicsPixmapItem* getGraphicsItem() const { return graphics_item_; }
    
    // 实现GameObject的纯虚函数
    void update() override;

protected:
    TankType tank_type_;
    double direction_angle_; // 角度，0为up
    QGraphicsPixmapItem* graphics_item_;
    
    // 新增：上一步位置
    int prev_x_;
    int prev_y_;
    
    void updateImage();
public:
    // 新增：保存当前位置为上一步
    void savePrevPos();
    // 新增：回退到上一步
    void rollbackPos();
};

#endif // TANK_H
