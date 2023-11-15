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

#ifndef FRAMELABEL_H
#define FRAMELABEL_H

#include <QLabel>
#include <QMouseEvent>

/**
 * @brief The FrameLabel class represents a custom QLabel used for frames in the sprite editor.
 * It extends QLabel to provide additional functionality for handling mouse events.
 */
class FrameLabel : public QLabel {
    Q_OBJECT

public:
    /// @brief Constructor for FrameLabel.
    /// @param frameIndex The index of the frame associated with this label.
    /// @param parent The parent widget (default is nullptr).
    explicit FrameLabel(int frameIndex, QWidget *parent = nullptr);

    /// @brief Getter for the frame index associated with this label.
    /// @return The index of the frame.
    int getFrameIndex() const;

signals:
    /// @brief Signal emitted when the label is clicked.
    /// @param frameIndex The index of the frame associated with the label.
    void clicked(int frameIndex);

protected:
    /// @brief Overridden function to handle mouse press events.
    /// @param event The mouse event.
    void mousePressEvent(QMouseEvent *event) override;

private:
    /// The index of the frame associated with this label.
    int m_frameIndex;
};

#endif // FRAMELABEL_H
