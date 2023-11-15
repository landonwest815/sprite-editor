#include "FrameLabel.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Frame Label class is used to create a FrameLabel.
 */

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
