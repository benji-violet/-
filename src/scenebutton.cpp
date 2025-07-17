#include "scenebutton.h"

SceneButton::SceneButton(const QString& text)
{
    // 创建实际的按钮控件
    m_button = new QPushButton(text);

    // 设置默认样式
    setButtonStyle(
        "QPushButton {"
        "background-color: #4CAF50;"
        "color: white;"
        "text-align: center;"
        "font-size: 14px;"
        "border: 1px solid #45a049;"  // 添加强制边框
        "border-radius: 2px;"         // 可选：轻微圆角让边框更和谐
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "border-color: #3d8b40;"      // 悬停时同步修改边框色
        "}"
        "QPushButton:pressed {"
        "background-color: #3d8b40;"
        "border-color: #367c39;"      // 点击时同步修改边框色
        "}"
        );

    // 设置默认大小
    setSize(120, 36);

    // 将按钮设置为代理控件
    setWidget(m_button);

    // 转发点击信号
    connect(m_button, &QPushButton::clicked, this, &SceneButton::clicked);

    // 允许按钮获取焦点以响应键盘事件
    setFocusPolicy(Qt::StrongFocus);
    m_button->setFocusPolicy(Qt::StrongFocus);
}

void SceneButton::setPosition(int x, int y) {
    setPos(x, y);
}

void SceneButton::setSize(int width, int height) {
    // 1. 设置按钮本身的固定大小
    m_button->setFixedSize(width, height);
    // 2. 设置代理控件的大小（与按钮一致）
    setMinimumSize(width, height);
    setMaximumSize(width, height);
}

void SceneButton::setButtonStyle(const QString& style) {
    m_button->setStyleSheet(style);
}

void SceneButton::setButtonEnabled(bool enabled) {
    m_button->setEnabled(enabled);
}
