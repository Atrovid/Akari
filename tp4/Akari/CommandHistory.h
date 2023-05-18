#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QList>

class CommandHistory
{
private:
    QList< QPair<int, int> >* _commandsUndoList;
    QList< QPair<int, int> >* _commandsRedoList;

public:
    CommandHistory();
    void pushUndo(int x, int y);
    QPair<int, int> popRedo();
    QPair<int, int> popUndo();
    bool isUndoListEmpty();
    bool isRedoListEmpty();
};

#endif // COMMANDHISTORY_H
