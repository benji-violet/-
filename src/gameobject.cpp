#include "gameobject.h"

GameObject::GameObject(QObject *parent)
    : QObject{parent}
{
    this->position.setX(x);
    this->position.setY(y);
}

GameObject::~GameObject() {}

void GameObject::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
    position += QPoint(dx, dy);
}

int GameObject::getX() {
    return x;
}

int GameObject::getY() {
    return y;
}

QPoint GameObject::getPos() {
    return position;
}

void GameObject::setPos(const QPoint &pos) {
    this->position = pos;
}

void GameObject::setPos(int nx, int ny) {
    this->position.setX(nx);
    this->position.setY(ny);
}

ObjectType GameObject::type() {
    return this->m_type;
}

bool GameObject::isAlive() {
    return this->is_alive;
}

int GameObject::getWidth() {
    return this->width;
}

int GameObject::getHeight() {
    return this->height;
}

int GameObject::getSpeed() {
    return this->speed;
}

QRectF GameObject::getRect() {
    return bounding_rect;
}
