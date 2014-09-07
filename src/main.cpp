#include <QApplication>
#include "qfractaltree.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFractalTree w;
    w.showMaximized();

    return a.exec();
}
