#include <QApplication>
#include <QPushButton>
#include "scanner.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Scanner scanner;
    scanner.show();

    return QApplication::exec();
}
