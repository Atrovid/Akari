#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include "Box.h"

#include <QGridLayout>
#include <QPainter>
#include <QWidget>

class GridView : public QWidget
{
    Q_OBJECT

public:
    GridView(QWidget *parent= nullptr, int size = 7);
    int coordToIndex(int row, int col);
    void displayGrid();
    void generateGrid(int size);
    Box* getBox(int row, int col);
    QMultiHash<int, Box *>* getBoxesList() const;
    void paintCase(int row, int col);
    void refreshGrid(QMultiHash<int,state> _currentGrid);
    void refreshGrid();
    void setSize(int size);

private:
    QMultiHash<int,Box*>* _boxesList;
    QGridLayout* _grid;
    QGridLayout *_gridLayout;
    int _gridSize;
    int _lastColumnClicked;
    int _lastRowClicked;
    QWidget* _parent;


public slots:
    void handleBoxClicked(int row, int col);

signals:
    void boxClicked(int row, int col);

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // GRIDVIEW_H
