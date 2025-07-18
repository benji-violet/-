#include "mapcell.h"
#include <QDebug>

// 构造
MapCell::MapCell(int x, int y, CellType cell_type, QObject *parent)
    : GameObject(x * cell_size_, y * cell_size_, cell_size_, cell_size_, ObstacleType, parent),
      cell_type_(cell_type), graphics_item_(nullptr)
{
    graphics_item_ = new QGraphicsPixmapItem();
    graphics_item_->setPos(this->x, this->y);
    updateImage();
}

// 析构
MapCell::~MapCell() {
    if (graphics_item_) {
        delete graphics_item_;
        graphics_item_ = nullptr;
    }
}

// 设置地图元素类型
void MapCell::setType(CellType cell_type)
{
    if (cell_type_ != cell_type) {
        cell_type_ = cell_type;
        updateImage();
    }
}

// 更新载入图片
void MapCell::updateImage()
{
    if (!graphics_item_) return;
    QString filepath = QString(":/images/walls/%1.png").arg(static_cast<int>(cell_type_));
    QPixmap pix(filepath);
    if (pix.isNull()) {
        qDebug() << "图片加载失败:" << filepath;
        return;
    }
    graphics_item_->setPixmap(pix.scaled(cell_size_, cell_size_));
}

// 将地图元素设为可见
void MapCell::setVisible(bool visible)
{
    if (graphics_item_) {
        graphics_item_->setVisible(visible);
    }
}

void MapCell::update()
{
    // 未来可扩展动画或其他逻辑
}
