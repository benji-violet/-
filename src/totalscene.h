#ifndef TOTALSCENE_H
#define TOTALSCENE_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class TotalScene;
}
QT_END_NAMESPACE

class TotalScene : public QWidget
{
    Q_OBJECT

//初始
public:
    TotalScene(QWidget *parent = nullptr);  //构造
    ~TotalScene();  //析构

//方法
protected:
    void keyPressEvent(QKeyEvent * event) override; //按下检测
    void keyReleaseEvent(QKeyEvent * event) override;   //释放检测

//私有槽函数
public slots:
    void checkKeyCombinations();    //组合按键检测

//属性
protected:
    Ui::TotalScene *ui;
    //检测组合按键部分
    QSet<int> pressed_keys;
    QTimer *timer;
    //当前显示界面
    bool start_scene;
    bool game_scene;
};

#endif // TOTALSCENE_H
