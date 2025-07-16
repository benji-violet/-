/*
 * 此基类将被所有游戏对象所继承
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QPoint>
#include <QRect>

//枚举类型：
//玩家，敌人，中立， 子弹， 障碍物， 道具
enum ObjectType {
    PlayerType, EnemyType, NeutralType, BulletType, ObstacleType, PropType
};

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = nullptr); //需要初始化部分必须的属性
    ~GameObject();  //析构

//游戏对象方法
protected:
    void move(int dx, int dy);    //游戏对象移动方法
    virtual void update() = 0;  //用于更新状态

    int getX();    //获取x坐标
    int getY();    //获取y坐标
    QPoint getPos();   //获取位置

    virtual void setPos(const QPoint &pos); //设置位置
    virtual void setPos(int x, int y);

    ObjectType type();  //获取对象类型
    bool isAlive(); //获取存活状态

    int getSpeed();    //获取速度
    int getHeight();   //获取高度
    int getWidth();    //获取宽度
    QRectF getRect();   //获取碰撞箱

//游戏对象属性
private:
    int x;  //x横坐标
    int y;  //y纵坐标
    QPoint position;    //位置

    int width;  //宽度
    int height; //高度

    QRect bounding_rect;    //碰撞箱

    int speed; //速度

    ObjectType m_type;    //对象类型
    bool is_alive;   //存活状态

signals:
};

#endif // GAMEOBJECT_H
