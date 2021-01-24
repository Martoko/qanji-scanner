#include <torch/torch.h>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "scanner.h"

int main(int argc, char *argv[]) {
    torch::Tensor tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;

    QApplication app(argc, argv);

    Scanner scanner;
    scanner.show();

    return QApplication::exec();
}
