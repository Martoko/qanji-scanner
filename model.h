#pragma once
#include <QPixmap>
#undef slots
#include <torch/script.h>
#define slots Q_SLOTS

class Model {
public:
    explicit Model(std::string path);

    std::string predict(QPixmap pixmap);

    std::string predict(std::vector<torch::jit::IValue> inputs);

private:
    torch::jit::script::Module module;
};

