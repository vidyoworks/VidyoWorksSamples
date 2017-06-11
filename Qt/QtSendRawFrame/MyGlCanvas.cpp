#include "MyGlCanvas.h"
#include "ui_MyGlCanvas.h"

MyGlCanvas::MyGlCanvas(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::MyGlCanvas)
{
    ui->setupUi(this);
}

MyGlCanvas::~MyGlCanvas()
{
    delete ui;
}

void MyGlCanvas::setImage(const QImage& image)
{
    img = image;
}

void MyGlCanvas::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    //Set the painter to use a smooth scaling algorithm.

    p.setRenderHint(QPainter::SmoothPixmapTransform);

    p.drawImage(this->rect(), img);
}
