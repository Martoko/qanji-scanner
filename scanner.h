#pragma once

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include "model.h"

class Scanner : public QWidget {
Q_OBJECT

public:
    Scanner();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void shootScreen();

private:
    Model model;
    QLabel *screenshotLabel;
    QLineEdit *text;
    QPixmap originalPixmap;

    void updateScreenshotLabel();
};

