#include "GridModel.h"
#include "Box.h"
#include <QDebug>


GridModel::GridModel( int size )
{
    _gridSize = size;
    _onBoxesNumber= 0;
    _checkedBlackBoxesNumber = 0;
    _emptyBoxesNumber = 0;
    _blackBoxesWithValueNumber = 0;
    _grid = new QMultiHash<int, state>();
    for (int row = 0; row < _gridSize; row++) {
        for (int col = 0; col < _gridSize; col++) {
            _grid->insert(coordToIndex(row, col), Off);
        }
    }
}

int GridModel::coordToIndex(int row, int col) {
    return row * _gridSize + col;
}

void GridModel::displayGrid() {
    QDebug deb = qDebug();
    for (int row = 0; row < _gridSize; row++) {
        for (int col = 0; col < _gridSize; col++) {
            if (getValueBox(row, col) < 10 ) {
                deb.space() << "" << getValueBox(row, col);
            } else {
                deb.space() << getValueBox(row, col);
            }
        }
        deb.nospace() << "\n";
    }
}

void GridModel::loadMap( QString map ) {
    _onBoxesNumber = 0;
    _checkedBlackBoxesNumber = 0;
    _emptyBoxesNumber = 0;
    _blackBoxesWithValueNumber = 0;
    for (int i = 0; i < map.length(); i++) {
        if (map.at(i) == "X") {
            _grid->replace(i, Black);
        } else if (map.at(i) == "0") {
            _grid->replace(i, Black_0);
            _blackBoxesWithValueNumber = QVariant::fromValue( _blackBoxesWithValueNumber.toInt() + 1 );
        } else if (map.at(i) == "1") {
            _grid->replace(i, Black_1);
            _blackBoxesWithValueNumber = QVariant::fromValue( _blackBoxesWithValueNumber.toInt() + 1 );
        } else if (map.at(i) == "2") {
            _grid->replace(i, Black_2);
            _blackBoxesWithValueNumber = QVariant::fromValue( _blackBoxesWithValueNumber.toInt() + 1 );
        } else if (map.at(i) == "3") {
            _grid->replace(i, Black_3);
            _blackBoxesWithValueNumber = QVariant::fromValue( _blackBoxesWithValueNumber.toInt() + 1 );
        } else if (map.at(i) == "4") {
            _grid->replace(i, Black_4);
            _blackBoxesWithValueNumber = QVariant::fromValue( _blackBoxesWithValueNumber.toInt() + 1 );
        } else {
            _grid->replace(i, Off);
            _emptyBoxesNumber = QVariant::fromValue( _emptyBoxesNumber.toInt() + 1 );
        }
    }
    refreshGrid();
    displayGrid();
}

bool GridModel::isABlackBox(int row, int col) {
    if ( isABlackBoxWithValue(row, col) ) {
        return true;
    } else {
        return getValueBox(row, col) == Black;
    }
}

bool GridModel::isThereALightInTheColumnUntilWall(int row, int col) {
    int goUp = row - 1;
    int goDown = row + 1;
    while ( goUp >= 0 && !isABlackBox(goUp, col) ) {
        if ( getValueBox(goUp, col) == Light || getValueBox(goUp, col) == Red_light ) {
            return true;
        }
        goUp--;
    }
    while ( goDown < _gridSize && !isABlackBox(goDown, col) ) {
        if ( getValueBox(goDown, col) == Light || getValueBox(goDown, col) == Red_light ) {
            return true;
        }
        goDown++;
    }
    return false;
}

bool GridModel::isThereALightInTheRowUntilWall(int row, int col) {
    int goLeft = col - 1;
    int goRight = col + 1;
    while ( goLeft >= 0 && !isABlackBox(row, goLeft) ) {
        if ( getValueBox(row, goLeft) == Light || getValueBox(row, goLeft) == Red_light ) {
            return true;
        }
        goLeft--;
    }
    while ( goRight < _gridSize && !isABlackBox(row, goRight) ) {
        if ( getValueBox(row, goRight) == Light || getValueBox(row, goRight) == Red_light ) {
            return true;
        }
        goRight++;
    }
    return false;
}

void GridModel::clickOnBox(int row, int col) {
    if ( !isABlackBox(row, col) ) {
        if ( !isALight(row, col) ) {
            _grid->replace(coordToIndex(row, col), Light);
        } else {
            _grid->replace(coordToIndex(row, col), Off);
        }
    }
    refreshGrid();
}

void GridModel::refreshBox(int row, int col) {
    if ( isThereALightInTheColumnUntilWall(row, col) || isThereALightInTheRowUntilWall(row, col) ) {
        _grid->replace(coordToIndex(row, col), On);
    } else {
        _grid->replace(coordToIndex(row, col), Off);
    }
}

void GridModel::refreshLight(int row, int col) {
    if ( isThereALightInTheColumnUntilWall(row, col) || isThereALightInTheRowUntilWall(row, col) ) {
        _grid->replace(coordToIndex(row, col), Red_light);
    } else {
        _grid->replace(coordToIndex(row, col), Light);
    }
}

void GridModel::refreshBlackBoxWithValue(int row, int col) {
    if ( checkBlackBoxWithValueCondition(row, col) ) {
        switch ( _grid->value(coordToIndex(row, col)) ) {
            case( Black_0 ):
                _grid->replace( coordToIndex(row, col), Black_0_checked );
            break;
            case( Black_1 ):
                _grid->replace( coordToIndex(row, col), Black_1_checked );
            break;
            case( Black_2 ):
                _grid->replace( coordToIndex(row, col), Black_2_checked );
            break;
            case( Black_3 ):
                _grid->replace( coordToIndex(row, col), Black_3_checked );
            break;
            case( Black_4 ):
                _grid->replace( coordToIndex(row, col), Black_4_checked );
            break;
            default:
            break;
        }
    } else {
        switch ( getValueBox(row, col) ) {
            case( Black_0_checked ):
                _grid->replace( coordToIndex(row, col), Black_0 );
            break;
            case( Black_1_checked ):
                _grid->replace( coordToIndex(row, col), Black_1 );
            break;
            case( Black_2_checked ):
                _grid->replace( coordToIndex(row, col), Black_2 );
            break;
            case( Black_3_checked ):
                _grid->replace( coordToIndex(row, col), Black_3 );
            break;
            case( Black_4_checked ):
                _grid->replace( coordToIndex(row, col), Black_4 );
            break;
            default:
            break;
        }
    }
}

void GridModel::refreshGrid() {
    _onBoxesNumber = 0;
    _checkedBlackBoxesNumber = 0;
    for (int row = 0; row < _gridSize; row++) {
        for (int col = 0; col < _gridSize; col++) {
            if ( isALight(row, col) ) {
                refreshLight(row, col);
                _onBoxesNumber = QVariant::fromValue(_onBoxesNumber.toInt() + 1);
            } else if ( isABlackBoxWithValue(row, col) ) {
                refreshBlackBoxWithValue(row, col);
                if ( checkBlackBoxWithValueCondition(row, col) ) {
                    _checkedBlackBoxesNumber = QVariant::fromValue(_checkedBlackBoxesNumber.toInt() + 1);
                }
            } else if ( !isABlackBox(row, col) ) {
                refreshBox(row, col);
                if ( getValueBox(row, col) == On ) {
                    _onBoxesNumber = QVariant::fromValue(_onBoxesNumber.toInt() + 1);
                }
            }
        }
    }
    displayGrid();
}

bool GridModel::checkGrid() {
    displayGrid();
    for (int row = 0; row < _gridSize; row++) {
        for (int col = 0; col < _gridSize; col++) {
            if ( getValueBox(row, col) == Off ) {
                return false;
            } else if (isABlackBoxWithValue(row, col)) {
                if (!checkBlackBoxWithValueCondition(row, col)) {
                    return false;
                }
            } else if ( getValueBox(row, col) == Red_light ) {
                return false;
            }
        }
    }
    return true;
}

bool GridModel::isABlackBoxWithValue(int row, int col) {
    switch (_grid->value(coordToIndex(row, col))) {
        case Black_0:
        case Black_1:
        case Black_2:
        case Black_3:
        case Black_4:
        case Black_0_checked:
        case Black_1_checked:
        case Black_2_checked:
        case Black_3_checked:
        case Black_4_checked:
            return true;
        break;
        default:
            return false;
        break;
    }
}

bool GridModel::checkBlackBoxWithValueCondition(int row, int col) {
    int checksum = 0;
    if ( row != 0 && isALight(row - 1, col) ) {
        checksum++;
    }
    if ( row != (_gridSize - 1) && isALight(row + 1, col) ) {
        checksum++;
    }
    if ( col != 0 && isALight(row, col - 1) ) {
        checksum++;
    }
    if ( col != (_gridSize - 1) && isALight(row, col + 1) ) {
        checksum++;
    }
    return ( checksum == ( _grid->value(coordToIndex(row, col)) - Black_0 ) || checksum == ( _grid->value(coordToIndex(row, col)) - (Black_0 + 5) ) );
}

bool GridModel::isALight(int row, int col) {
    return ( _grid->value(coordToIndex(row, col)) == Light || _grid->value(coordToIndex(row, col)) == Red_light );
}

void GridModel::manualChange(int row, int col, state new_state) {
    _grid->replace(coordToIndex(row, col), new_state);
}

QVariant GridModel::getOnBoxesNumber() {
    return _onBoxesNumber;
}

QVariant GridModel::getCheckedBlackBoxesNumber() {
    return _checkedBlackBoxesNumber;
}

QVariant GridModel::getEmptyBoxesNumber() {
    return _emptyBoxesNumber;
}

QVariant GridModel::getBlackBoxesWithValueNumber() {
    return _blackBoxesWithValueNumber;
}

QMultiHash<int, state> GridModel::getGrid() {
    return *_grid;
}

QMultiHash<int, state> GridModel::getGridChanges(int row, int col) {
    int goLeft = col - 1;
    int goRight = col + 1;
    int goUp = row - 1;
    int goDown = row + 1;
    QMultiHash<int, state> gridChanges = QMultiHash<int, state>();
    gridChanges.insert(coordToIndex(row, col), getValueBox(row, col));

    while ( goLeft >= 0 ) {
        gridChanges.insert(coordToIndex(row, goLeft), getValueBox(row, goLeft));
        goLeft--;
    }
    while ( goRight < _gridSize ) {
        gridChanges.insert(coordToIndex(row, goRight), getValueBox(row, goRight));
        goRight++;
    }
    while ( goUp >= 0 ) {
        gridChanges.insert(coordToIndex(goUp, col), getValueBox(goUp, col));
        goUp--;
    }
    while ( goDown < _gridSize ) {
        gridChanges.insert(coordToIndex(goDown, col), getValueBox(goDown, col));
        goDown++;
    }
    return gridChanges;
}

state GridModel::getValueBox(int row, int col) {
    return _grid->value( coordToIndex(row, col) );
}


















