#include "model.h"
#include "kanji.h"

Model::Model(std::string path) {
    module = torch::jit::load(path);
}

std::string Model::predict(QPixmap pixmap) {
    int w = 32;
    int h = w;
    float input[1][3][w][h];
    auto image = pixmap.scaled(w, h).toImage();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            input[0][0][x][y] = image.pixelColor(x, y).redF();
            input[0][1][x][y] = image.pixelColor(x, y).greenF();
            input[0][2][x][y] = image.pixelColor(x, y).blueF();
        }
    }

    return predict({torch::from_blob(input, {1, 3, w, h}, {torch::kFloat32})});
}

std::string Model::predict(std::vector<torch::jit::IValue> inputs) {
    auto output = module.forward(inputs).toTensor();
    auto index = output.argmax(1).item<int>();
    return kanji[index];
}
