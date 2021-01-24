#pragma once

#include <QPixmap>

#undef slots

#include <torch/script.h>

#define slots Q_SLOTS

class Model {
public:
    explicit Model(std::string path);

    std::string predict(QPixmap pixmap);

    std::string predict(std::vector<torch::jit::IValue> normalized_input);

private:
    float normalizationMean[3] = {0.63, 0.63, 0.63};
    float normalizationStd[3] = {0.28, 0.28, 0.28};
    torch::jit::script::Module module;
};

