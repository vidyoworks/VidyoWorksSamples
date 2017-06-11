#ifndef MYGLCANVAS_H
#define MYGLCANVAS_H

#include <QtOpenGL/QGLWidget>

namespace Ui {
class MyGlCanvas;
}

class MyGlCanvas : public QGLWidget
{
    Q_OBJECT

public:
    explicit MyGlCanvas(QWidget *parent = 0);
    void setImage(const QImage& image);
    ~MyGlCanvas();
protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::MyGlCanvas *ui;
    QImage img;
};

#endif // MYGLCANVAS_H
