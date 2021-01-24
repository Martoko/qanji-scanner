#include <QApplication>
#include <QPushButton>
#include "scanner.h"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

void openCvTest() {
    cv::Mat output = cv::Mat::zeros(120, 350, CV_8UC3);
    cv::putText(output,
                "Hello World :)",
                cv::Point(15, 70),
                cv::FONT_HERSHEY_PLAIN,
                3,
                cv::Scalar(0, 255, 0),
                4);
}

int main(int argc, char *argv[]) {
    openCvTest();

    QApplication app(argc, argv);

    Scanner scanner;
    scanner.show();

    return QApplication::exec();
}
