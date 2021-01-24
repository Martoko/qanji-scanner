#include <iostream>
#include <QApplication>
#include "scanner.h"
#include "model.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Scanner scanner;
    scanner.show();

    return QApplication::exec();
}
