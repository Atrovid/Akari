#include "Box.h"
#include "GridView.h"
#include <QComboBox>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QGraphicsRectItem>
#include "MainWindow.h"
#include "QMultiHash"
#include <iostream>

GridView::GridView(QWidget *parent, int size) : QWidget(parent)
{
    _gridSize = size;
    _parent = parent;

}

void GridView::setSize(int size) {
    _gridSize = size;
}

int GridView::coordToIndex(int row, int col){
    return row*_gridSize + col;
}

void GridView::generateGrid(int size) {
    _gridLayout = new QGridLayout(this);
    _gridLayout->setSpacing(1);
    _boxesList = new QMultiHash<int, Box*>();
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++) {
            Box *caseView = new Box(this, row, col);
            _boxesList->insert( coordToIndex(row, col), caseView );
            _gridLayout->addWidget( caseView, row, col );
        }
    }
}


void GridView::refreshGrid(QMultiHash<int,state> gridChanges) {
    Box* boxView;
    QList<state> states;
    int row;
    int col;
    foreach (const int& key, gridChanges.keys()) {
        states = gridChanges.values(key);
        foreach (const state& st, states) {
            row = key / _gridSize;
            col = key % _gridSize;
            boxView = getBox(row, col);
            boxView->setState(st);
            boxView->update();
        }
    }
}

void GridView::displayGrid() {
    QDebug deb = qDebug();
    for (int row = 0; row < _gridSize; row++) {
        for (int col = 0; col < _gridSize; col++) {
            if (_boxesList->value( coordToIndex(row, col) )->getState() < 10 ) {
                deb.space() << "" << _boxesList->value( coordToIndex(row, col) )->getState();
            } else {
                deb.space() << _boxesList->value( coordToIndex(row, col) )->getState();
            }
        }
        deb.nospace() << "\n";
    }
}

QMultiHash<int, Box *> *GridView::getBoxesList() const {
    return _boxesList;
}


void GridView::resizeEvent(QResizeEvent *event)
{
    int size = event->size().width() > event->size().height() ? event->size().height() : event->size().width();
    resize(size, size);
    int widgetWidth = width();
    int widgetHeight = height();
    int x = (parentWidget()->width() - widgetWidth) / 2;
    int y = (parentWidget()->height() - widgetHeight) / 3;
    move(x, y);

}

void GridView::handleBoxClicked(int row, int col)
{
    _lastRowClicked = row;

    _lastColumnClicked = col;
    emit boxClicked(_lastRowClicked, _lastColumnClicked);
}

Box* GridView::getBox(int row, int col) {
    int index = coordToIndex(row,col);
    return _boxesList->value(index);

}

