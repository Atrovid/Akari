#include "Box.h"

#include <QPainter>
#include <QDebug>
#include <QGridLayout>


Box::Box( QWidget* parent, int row, int col ) : QWidget(parent), _row(row), _column(col) {
    _parent = parent;
    _state = Off;
    _value = 0;
}

Box::Box( QWidget *parent, state initial_state, int value) : QWidget(parent)
{
    _state = initial_state;
    _value = value;
}

void Box::setState( state new_state )
{
    _state = new_state;
}

state Box::getState()
{
    return _state;
}

Box::~Box() {
}

void Box::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    switch(_state){
        case (Black):
            drawBlackSquare(painter, width() - 2, " ", Qt::black);
            break;
        case (Black_0):
            drawBlackSquare(painter, width() - 2, "0", Qt::white);
            break;
        case (Black_1):
            drawBlackSquare(painter, width() - 2, "1", Qt::white);
            break;
        case (Black_2):
            drawBlackSquare(painter, width() - 2, "2", Qt::white);
            break;
        case (Black_3):
            drawBlackSquare(painter, width() - 2, "3", Qt::white);
            break;
        case(Black_4):
            drawBlackSquare(painter,width() - 2, "4", Qt::white);
            break;
        case (Black_0_checked):
            drawBlackSquare(painter, width() - 2, "0", Qt::green);
            break;
        case (Black_1_checked):
            drawBlackSquare(painter, width() - 2, "1", Qt::green);
            break;
        case (Black_2_checked):
            drawBlackSquare(painter, width() - 2, "2", Qt::green);
            break;
        case (Black_3_checked):
            drawBlackSquare(painter, width() - 2, "3", Qt::green);
            break;
        case(Black_4_checked):
            drawBlackSquare(painter, width() - 2, "4", Qt::green);
            break;
        case(On):
            drawYellowSquare(painter, width() - 2);
            break;
        case(Light):
            drawYellowSquareWithPicture(painter, width() - 2, ":/lights/light.png");
            break;
        case(Red_light):
            drawYellowSquareWithPicture(painter, width() - 2, ":/lights/red_light.png");
            break;
        default:
            drawWhiteSquare(painter, width() - 2);
            break;
    }

}

void Box::drawBlackSquare(QPainter& painter, int size, QString number, QColor color){
    QRectF square(0, 0, size, size);

    painter.fillRect(square, Qt::black);
    painter.setPen(color);
    int fontSize = size * 0.6; // ajuster la taille de la police en fonction de la taille du carré
    painter.setFont(QFont("Arial", fontSize));
    QRectF textRect(0, 0, size, size);
    painter.drawText(textRect, Qt::AlignCenter, number);
    painter.setPen(Qt::white);
    painter.drawRect(square);
}


void Box::drawWhiteSquare(QPainter& painter, int size) {
    QRectF square(0, 0, size, size);
    QPen(Qt::black,2);
    painter.fillRect(square, Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(square);
}

void Box::drawYellowSquareWithPicture(QPainter& painter, int size, QString path){
    QRectF square(0, 0, size, size);
    painter.fillRect(square, "#ffff99");
    painter.setPen(Qt::black);
    painter.drawRect(square);

    QPixmap pixmap(path);
    QPixmap resizedPixMap = pixmap.scaled(size, size);
    painter.drawPixmap(0, 0, resizedPixMap);
}

void Box::drawYellowSquare(QPainter& painter, int size){
    QRectF square(0, 0, size, size);
    painter.fillRect(square, "#ffff99");
    painter.setPen(Qt::black);
    painter.drawRect(square);
}

void Box::mousePressEvent(QMouseEvent *)
{
    emit clickedWithPosition(_row, _column);
}

