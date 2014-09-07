#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QKeyEvent>
#include <QPaintEvent>

class QFractalTree : public QWidget {
    Q_OBJECT
private:
    QImage image;
    QPainter painter;

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);

    void generateTree(int x, int y, float a, int l);
    void drawTree();

    int randomInInterval(int begin, int end) { return begin + qrand() % (end-begin); }
    float randomFloat() { return (float) qrand()/RAND_MAX; }

    int sValue;
    int lValue;
    const static int DEFAULT_S_L_VALUE = 100;

public:
    QFractalTree(QWidget *parent = 0);
    ~QFractalTree();
};

#endif // WIDGET_H
