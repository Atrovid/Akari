#include "CommandHistory.h"
#include <QDebug>

CommandHistory::CommandHistory()
{
    _commandsUndoList = new QList< QPair<int, int> >();
    _commandsRedoList = new QList< QPair<int, int> >();
}

void CommandHistory::pushUndo(int x, int y) {
    _commandsUndoList->append(QPair<int, int>(x, y));
}

QPair<int, int> CommandHistory::popUndo() {
    QPair<int, int> lastCommand = _commandsUndoList->back();
    _commandsUndoList->pop_back();
    _commandsRedoList->append(lastCommand);
    return lastCommand;
}

QPair<int, int> CommandHistory::popRedo() {
    QPair<int, int> lastCommand = _commandsRedoList->back();
    _commandsRedoList->pop_back();
    _commandsUndoList->append(lastCommand);
    return lastCommand;
}

bool CommandHistory::isUndoListEmpty() {
    return _commandsUndoList->isEmpty();
}

bool CommandHistory::isRedoListEmpty() {
    return _commandsRedoList->isEmpty();
}
