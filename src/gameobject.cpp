#include "gameobject.h"

GameObject::GameObject(int x, int y, int width, int height, ObjectType type, QObject *parent)
    : QObject{parent}, x(x), y(y), width(width), height(height), type(type), is_alive(true), speed(0)
{
    this->position.setX(x);
    this->position.setY(y);
    this->bounding_rect = new QRect(x, y, width, height);
}

GameObject::~GameObject() {
    if (bounding_rect) {
        delete bounding_rect;
        bounding_rect = nullptr;
    }
}

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

ObjectType GameObject::getType() {
    return this->type;
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

QRect* GameObject::getRect() {
    return bounding_rect;
}

bool GameObject::isCollision(QRect* rect) {
    if (this->bounding_rect->contains(*rect)) {
        return true;
    }
    return false;
}
