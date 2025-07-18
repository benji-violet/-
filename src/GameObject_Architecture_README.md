# GameObject 架构说明

## 概述

本项目采用了基于GameObject的架构设计，所有游戏对象都继承自GameObject基类。这种设计提供了统一的接口和功能，便于管理和扩展。

## 架构特点

### 1. GameObject 基类
- 继承自QObject，支持Qt的信号槽机制
- 提供统一的位置、大小、速度、碰撞检测等基础功能
- 包含纯虚函数update()，强制子类实现更新逻辑
- 成员变量设为protected，便于子类访问

### 2. 图形渲染分离
- GameObject不直接继承QGraphicsItem
- 每个GameObject包含一个QGraphicsPixmapItem作为成员变量
- 通过getGraphicsItem()方法获取图形项，添加到场景中
- 这种设计避免了多重继承的复杂性

## 类层次结构

```
GameObject (基类)
├── MapCell (地图单元格)
├── Tank (坦克)
│   ├── PlayerTank (玩家坦克)
│   └── EnemyTank (敌方坦克)
├── Bullet (子弹)
└── 其他游戏对象...
```

## 使用方法

### 1. 创建新的游戏对象类

```cpp
// 头文件
class MyGameObject : public GameObject
{
    Q_OBJECT
public:
    explicit MyGameObject(int x, int y, QObject *parent = nullptr);
    ~MyGameObject();
    
    // 实现纯虚函数
    void update() override;
    
    // 获取图形项
    QGraphicsPixmapItem* getGraphicsItem() const { return m_graphicsItem; }

private:
    QGraphicsPixmapItem* m_graphicsItem;
    // 其他特有属性...
};
```

### 2. 实现构造函数

```cpp
MyGameObject::MyGameObject(int x, int y, QObject *parent)
    : GameObject(x, y, width, height, ObjectType, parent),
      m_graphicsItem(nullptr)
{
    // 创建图形项
    m_graphicsItem = new QGraphicsPixmapItem();
    m_graphicsItem->setPos(this->x, this->y);
    
    // 初始化特有属性
    // ...
}
```

### 3. 添加到场景

```cpp
// 在GameScene中
MyGameObject* obj = new MyGameObject(x, y, this);
this->addItem(obj->getGraphicsItem());
```

### 4. 更新逻辑

```cpp
void MyGameObject::update()
{
    // 实现更新逻辑
    // 例如：移动、动画、AI等
    
    // 更新图形项位置
    if (m_graphicsItem) {
        m_graphicsItem->setPos(this->x, this->y);
    }
}
```

## 优势

1. **统一接口**：所有游戏对象都有相同的基础功能
2. **易于扩展**：新增游戏对象只需继承GameObject
3. **类型安全**：通过ObjectType枚举区分不同类型的对象
4. **碰撞检测**：统一的碰撞检测接口
5. **内存管理**：自动管理图形项的生命周期

## 注意事项

1. 记得在析构函数中删除m_graphicsItem
2. 移动对象时要同步更新图形项位置
3. 实现update()方法时要考虑性能
4. 使用protected成员变量时要遵循封装原则

## 示例类

- **MapCell**: 地图单元格，静态对象
- **Tank**: 坦克，可移动的战斗单位
- **Bullet**: 子弹，快速移动的投射物

这些示例展示了不同类型游戏对象的实现方式。 