#ifndef FRAMELABEL_H
#define FRAMELABEL_H
#include <QLabel>
#include <QMouseEvent>

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a FrameLabel class which has been splitted into a header
 * file. It assists in declarations of the FrameLabel object, functions, etc.
 */

class FrameLabel : public QLabel {
    Q_OBJECT

public:
    explicit FrameLabel(int frameIndex, QWidget *parent = nullptr);
    int getFrameIndex() const;

signals:
    void clicked(int frameIndex);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_frameIndex;
};

#endif // FRAMELABEL_H
