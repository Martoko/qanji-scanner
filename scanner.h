#pragma once

#include <QWidget>
#include <QLabel>
#include <QTimer>

class Scanner : public QWidget {
Q_OBJECT

public:
    Scanner();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void shootScreen();

private:
    QLabel *screenshotLabel;
    QTimer *timer;

    void updateScreenshotLabel();

    QPixmap originalPixmap;
};

