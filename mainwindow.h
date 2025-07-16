#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <QDebug>

#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void switchToGameScence(Map* map);

private slots:
    void checkKeyCombinations();

private:
    Ui::MainWindow *ui;
    //检测组合按键部分
    QSet<int> pressedKeys;
    QTimer *timer;
    //按钮部分
};
#endif // MAINWINDOW_H
