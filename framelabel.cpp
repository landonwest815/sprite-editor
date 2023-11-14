#include "FrameLabel.h"

FrameLabel::FrameLabel(int frameIndex, QWidget *parent) :
    QLabel(parent), m_frameIndex(frameIndex) {
    // Your constructor's code (if any)
}

void FrameLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked(m_frameIndex);
    }
    // Make sure to call the base class implementation unless you want to prevent default behavior
    QLabel::mousePressEvent(event);
}

int FrameLabel::getFrameIndex() const {
    return m_frameIndex;
}
