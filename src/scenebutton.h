#ifndef SCENEBUTTON_H
#define SCENEBUTTON_H

#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QString>

/**
 * @brief 用于QGraphicsScene的按钮封装类
 * 可以直接添加到QGraphicsScene中，支持自定义样式和点击事件
 */
class SceneButton : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param text 按钮显示文本
     * @param parent 父对象
     */
    explicit SceneButton(const QString& text);

    /**
     * @brief 设置按钮位置（场景坐标）
     * @param x X坐标
     * @param y Y坐标
     */
    void setPosition(int x, int y);

    /**
     * @brief 设置按钮大小
     * @param width 宽度
     * @param height 高度
     */
    void setSize(int width, int height);

    /**
     * @brief 设置按钮样式表
     * @param style 样式表字符串（同QPushButton的setStyleSheet）
     */
    void setButtonStyle(const QString& style);

    /**
     * @brief 设置按钮是否可用
     * @param enabled 可用状态
     */
    void setButtonEnabled(bool enabled);

signals:
    /**
     * @brief 按钮被点击时发射的信号
     */
    void clicked();

private:
    QPushButton* m_button; // 实际的按钮控件
};

#endif // SCENEBUTTON_H
