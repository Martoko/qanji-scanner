#include <QVBoxLayout>
#include <QGuiApplication>
#include <QWindow>
#include <QScreen>
#include "scanner.h"

Scanner::Scanner() : screenshotLabel(new QLabel(this)), timer(new QTimer(this)) {
    setWindowTitle(tr("Qanji"));

    auto *mainLayout = new QVBoxLayout(this);

    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    const QRect screenGeometry = screen()->geometry();
    screenshotLabel->setMinimumSize(5, 5);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(screenshotLabel);

    shootScreen();
    connect(timer, SIGNAL(timeout()), this, SLOT(shootScreen()));
    timer->start(100);
}

void Scanner::resizeEvent(QResizeEvent *event) {
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (scaledSize != screenshotLabel->pixmap(Qt::ReturnByValue).size())
        updateScreenshotLabel();
}

void Scanner::updateScreenshotLabel() {
    screenshotLabel->setPixmap(originalPixmap.scaled(screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));
}

void Scanner::shootScreen() {
    QPoint cursorPosition = QCursor::pos();
    QScreen *screen = qApp->screenAt(cursorPosition);
    if (screen == nullptr) return;

    originalPixmap = screen->grabWindow(0);
    updateScreenshotLabel();
}
