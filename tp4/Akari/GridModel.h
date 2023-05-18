#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include "State.h"

#include <QMultiHash>
#include <QVariant>

class GridModel
{
private:
     int _gridSize;
     QMultiHash<int, state>* _grid;
     QVariant _onBoxesNumber;
     QVariant _checkedBlackBoxesNumber;
     QVariant _emptyBoxesNumber;
     QVariant _blackBoxesWithValueNumber;
     int coordToIndex(int row, int col);
     void displayGrid();
     bool checkBlackBoxWithValueCondition(int row, int col);
     bool isABlackBox(int row, int col);
     bool isABlackBoxWithValue(int row, int col);
     bool isALight(int row, int col);
     bool isThereALightInTheColumnUntilWall(int row, int col);
     bool isThereALightInTheRowUntilWall(int row, int col);
     void refreshBlackBoxWithValue(int row, int col);
     void refreshBox(int row, int col);
     void refreshGrid();
     void refreshLight(int row, int col);
     void switchColumnUntilWall(int row, int col);
     void switchRowUntilWall(int row, int col);

public:
     GridModel(int size = 7);
     bool checkGrid();
     void loadMap( QString map );
     void clickOnBox(int row, int col);
     void manualChange(int row, int col, state new_state);
     QVariant getOnBoxesNumber();
     QVariant getCheckedBlackBoxesNumber();
     QVariant getEmptyBoxesNumber();
     QVariant getBlackBoxesWithValueNumber();
     QMultiHash<int, state> getGrid();
     QMultiHash<int, state> getGridChanges(int row, int col);
     state getValueBox(int row, int col);
};

#endif // GRIDMODEL_H
