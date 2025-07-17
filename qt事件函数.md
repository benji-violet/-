# 以下是Qt中常见的事件处理函数分类总结：

## ​​1. 鼠标事件​​
mousePressEvent (QMouseEvent*)：鼠标按下时触发

mouseReleaseEvent (QMouseEvent*)：鼠标释放时触发

mouseDoubleClickEvent (QMouseEvent*)：鼠标双击时触发

mouseMoveEvent (QMouseEvent*)：鼠标移动时触发

wheelEvent (QWheelEvent*)：滚轮滚动时触发

## 2. 键盘事件​​
keyPressEvent (QKeyEvent*)：键盘按键按下时触发

keyReleaseEvent (QKeyEvent*)：键盘按键释放时触发

## ​​3. 窗口事件​​
resizeEvent (QResizeEvent*)：窗口大小调整时触发


paintEvent (QPaintEvent*)：窗口重绘时触发（必须实现）

showEvent(QShowEvent*)：窗口显示时触发

hideEvent(QHideEvent*)：窗口隐藏时触发

## ​​4. 焦点事件​​
focusInEvent(QFocusEvent*)：控件获得焦点时触发

focusOutEvent(QFocusEvent*)：控件失去焦点时触发
​​
## 5. 拖放事件​​
dragEnterEvent(QDragEnterEvent*)：拖拽进入控件时触发

dragLeaveEvent(QDragLeaveEvent*)：拖拽离开控件时触发

dragMoveEvent(QDragMoveEvent*)：拖拽在控件内移动时触发

dropEvent(QDropEvent*)：拖拽释放时触发
​
## ​6. 定时器事件​​
timerEvent(QTimerEvent*)：定时器超时时触发（需配合startTimer()使用）

## ​​7. 其他事件​​
enterEvent(QEvent*)：鼠标进入控件区域时触发

leaveEvent(QEvent*)：鼠标离开控件区域时触发

contextMenuEvent(QContextMenuEvent*)：右键菜单触发
​
## ​8. 通用事件处理​​
event(QEvent*)：所有事件的统一入口，可在此函数中分发事件

eventFilter(QObject*, QEvent*)：事件过滤器，用于拦截其他对象的事件