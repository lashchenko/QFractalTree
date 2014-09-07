#include "qfractaltree.h"
#include <cmath>

QFractalTree::QFractalTree(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(640, 480);
    setMaximumSize(640, 480);
    setWindowTitle("[QFractalTree] Press space to generate new tree");
    sValue = DEFAULT_S_L_VALUE;
    lValue = DEFAULT_S_L_VALUE;
    srand(time(NULL));
    drawTree();
}

void QFractalTree::generateTree(int x, int y, float a, int l ) {
    if( l<8 ) { return; }

    int x1 = x+l*cos(a);
    int y1 = y+l*sin(a);

    int p = (l>100) ? 100 : l;

    if (p<40) {
        QPen leafPen = QPen(QColor::fromHsl(randomInInterval(70, 130), sValue, lValue));
        painter.setPen(leafPen);

        for(int i=0; i<3; ++i) {
            painter.drawLine(x+i, y, x1, y1);
        }
    }
    else {
        QPen trunkPen = QPen(QColor::fromHsl(randomInInterval(30, 40), sValue, lValue));
        painter.setPen(trunkPen);
        for(int i=0; i<(p/6); ++i) {
            painter.drawLine(x+i-(p/12), y, x1, y1);
        }
    }
    for (int i=0; i<9-randomInInterval(0,9); ++i) {
        int s = randomInInterval(0, l-l/6) + (l/6);
        float a1 = a + 1.6 * (0.5 - randomFloat()); // branches angle
        x1 = x+s*cos(a);
        y1 = y+s*sin(a);
        generateTree(x1, y1, a1, p-5-randomInInterval(0,30)); // splendor
    }
}

void QFractalTree::paintEvent(QPaintEvent *)
{
    painter.begin(this);
    painter.drawImage(0,0, image);
    painter.end();
}

void QFractalTree::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Space:
        drawTree();
        break;
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        ++sValue;
        ++lValue;
        drawTree();
        break;
    case Qt::Key_Minus:
        --sValue;
        --lValue;
        drawTree();
        break;
    case Qt::Key_0:
        sValue = DEFAULT_S_L_VALUE;
        lValue = DEFAULT_S_L_VALUE;
        drawTree();
        break;
    default:
        break;
    }
}

void QFractalTree::drawTree()
{
    image = QImage(size(), QImage::Format_ARGB32);
    int opacity = 100;// Set this between 0 and 255
    image.fill(QColor(0,0,0,opacity));
    painter.begin(&image);
    generateTree(320, 480, 3*M_PI/2, 200);
    painter.end();
    update();
}

QFractalTree::~QFractalTree()
{
}
