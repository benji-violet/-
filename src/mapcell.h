#ifndef MAP_CELL_H
#define MAP_CELL_H

#include "gameobject.h"
#include <QGraphicsPixmapItem>
#include <QPoint>

enum CellType {
    Ground = 0,
    Brick = 1,
    Steel = 2,
    Forest = 3,
    Water = 4,
    HQ = 5,
    EnemySpawn = 6,
    Prop = 7
};

class MapCell : public GameObject
{
public:
    explicit MapCell(int x, int y, CellType cell_type = Ground, QObject *parent = nullptr);
    ~MapCell();

    CellType getType() const { return cell_type_; }
    void setType(CellType cell_type);
    void updateImage();
    void setVisible(bool visible);
    QGraphicsPixmapItem* getGraphicsItem() const { return graphics_item_; }
    void update() override;

private:
    CellType cell_type_;
    QGraphicsPixmapItem* graphics_item_;
    static const int cell_size_ = 60;
};

#endif // MAP_CELL_H
