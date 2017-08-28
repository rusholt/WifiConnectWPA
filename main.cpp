#include "scannerwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QFont font = QFont("Ubuntu", 10, 1);


    MainWindow w;
    w.show();

    return a.exec();
}
