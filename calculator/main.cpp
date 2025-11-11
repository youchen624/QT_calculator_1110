#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("不嚴謹的抽象計算機");
    w.show();
    return a.exec();
}
