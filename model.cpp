#include "model.h"
#include "kanji.h"

Model::Model(std::string path) {
    module = torch::jit::load(path);
}

std::string Model::predict(QPixmap pixmap) {
    constexpr int w = 32;
    constexpr int h = w;
    float input[1][3][w][h];
    auto image = pixmap.scaled(w, h).toImage();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            input[0][0][y][x] = (image.pixelColor(x, y).redF() - normalizationMean[0]) / normalizationStd[0];
            input[0][1][y][x] = (image.pixelColor(x, y).greenF() - normalizationMean[1]) / normalizationStd[1];
            input[0][2][y][x] = (image.pixelColor(x, y).blueF() - normalizationMean[2]) / normalizationStd[2];
        }
    }

    return predict({torch::from_blob(input, {1, 3, w, h}, {torch::kFloat32})});
}

std::string Model::predict(std::vector<torch::jit::IValue> normalized_input) {
    auto output = module.forward(normalized_input).toTensor();
    auto index = output.argmax(1).item<int>();
    return kanji[index];
}
