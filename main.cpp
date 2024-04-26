#include "mode_selection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mode_selection w;
    w.show();
    return a.exec();
}

//code by beluga684
