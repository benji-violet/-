/*
 * 此基类将被所有游戏对象所继承
*/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

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
    explicit GameObject(int x = 0, int y = 0, int width = 60, int height = 60, 
                       ObjectType type = NeutralType, QObject *parent = nullptr);
    virtual ~GameObject();  //析构
    bool isCollision(QRect* rect); //判断是否碰撞
    QRect* getRect();   //获取碰撞箱

protected:
    void move(int dx, int dy);    //游戏对象移动方法
    virtual void update() = 0;  //用于更新状态

    int getX();    //获取x坐标
    int getY();    //获取y坐标
    QPoint getPos();   //获取位置

    virtual void setPos(const QPoint &pos); //设置位置
    virtual void setPos(int x, int y);

    ObjectType getType();  //获取对象类型
    bool isAlive(); //获取存活状态

    int getSpeed();    //获取速度
    int getHeight();   //获取高度
    int getWidth();    //获取宽度

    void syncAllPos(int nx, int ny); // 同步位置相关变量


//游戏对象属性
protected:
    int x;  //x横坐标
    int y;  //y纵坐标
    QPoint position;    //位置

    int width;  //宽度
    int height; //高度

    QRect* bounding_rect;    //碰撞箱

    ObjectType type;    //对象类型
    bool is_alive;   //存活状态
    int speed; //速度


signals:
};

#endif // GAME_OBJECT_H
