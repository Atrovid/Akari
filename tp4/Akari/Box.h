#ifndef BOX_H
#define BOX_H

#include "State.h"

#include <QPaintEvent>
#include <QWidget>

class Box : public QWidget
{
    Q_OBJECT
public:
    Box( QWidget* parent, int row, int col );
    Box( QWidget* parent, state initial_state, int value);
    state getState();
    void setState( state );
    void drawBlackSquare(QPainter &painter, int size, QString number, QColor color);
    void drawWhiteSquare(QPainter &painter, int size);
    void drawYellowSquareWithPicture(QPainter& painter, int size, QString path);
    void drawYellowSquare(QPainter &painter, int size);
    virtual ~Box();

private:
    state _state = Light;
    int _value;
    QWidget* _parent;
    int _row = 10;
    int _column = 10;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void clickedWithPosition(int row, int column);
};

#endif // CASE_H
