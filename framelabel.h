#ifndef FRAMELABEL_H
#define FRAMELABEL_H

#include <QLabel>
#include <QMouseEvent>

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
