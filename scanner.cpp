#include <QVBoxLayout>
#include <QGuiApplication>
#include <QWindow>
#include <QScreen>
#include <QKeyEvent>
#include "scanner.h"

Scanner::Scanner() : screenshotLabel(new QLabel(this)), text(new QLineEdit(this)), model("model.pt") {
    setWindowTitle(tr("Qanji"));

    auto *mainLayout = new QVBoxLayout(this);

    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setMinimumSize(32, 32);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(screenshotLabel);

    text->setFont(QFont("sans serif", 32));
    text->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(text);

    shootScreen();
}

void Scanner::keyPressEvent(QKeyEvent *event) {
    if (event->type() == QEvent::KeyPress && event->key() == Qt::Key_Shift) {
        shootScreen();
    }
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
    QRect screenGeometry = screen->geometry();

    // Grab the 32x32 around the cursor
    auto clipGeometry = QRect(
            cursorPosition.x() - 32 / 2, cursorPosition.y() - 32 / 2,
            32, 32
    );

    // Ensure that we are within screen bounds
    if (clipGeometry.left() < screenGeometry.left()) {
        clipGeometry.moveLeft(screenGeometry.left());
    }

    if (clipGeometry.right() > screenGeometry.right()) {
        clipGeometry.moveRight(screenGeometry.right());
    }

    if (clipGeometry.top() < screenGeometry.top()) {
        clipGeometry.moveTop(screenGeometry.top());
    }

    if (clipGeometry.bottom() > screenGeometry.bottom()) {
        clipGeometry.moveBottom(screenGeometry.bottom());
    }

    // Bail out if screen is smaller than 32x32
    if (!screenGeometry.contains(clipGeometry)) {
        std::cerr << "Clip size is larger than screen size" << std::endl;
        return;
    }

    clipGeometry.moveTopLeft(clipGeometry.topLeft() - screen->geometry().topLeft());

    originalPixmap = screen->grabWindow(0,
                                        clipGeometry.x(), clipGeometry.y(),
                                        clipGeometry.width(), clipGeometry.height());
    updateScreenshotLabel();

    text->setText(QString::fromStdString(model.predict(originalPixmap)));
}
