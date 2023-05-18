#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CommandHistory.h"
#include "GridModel.h"
#include "GridView.h"

#include <QComboBox>
#include <QMainWindow>
#include <QRandomGenerator>
#include <QPushButton>

class Stopwatch;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVariant getSize();
    QVariant getDifficulty();
    QString readerFile();
    QString getDifficultyString();
    void refreshStatus();

public slots:
    void onAbout();
    void onQuitClick();
    void onStartClick();
    void onTestClick();
    void onCheckClick();
    void undo();
    void redo();
    void onResetClick();
    void onRules();
    void handleClickOnBox(int row, int column);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Stopwatch* _stopwatch;
    bool _stopwatchIsRunning;
    QComboBox* _sizeComboBox;
    QComboBox* _difficultyComboBox;
    QRandomGenerator* _randomSeed;
    GridModel* _gridModel;
    CommandHistory* _commandHistory;
    QVariant _undoNumber;
    QString _map;
    GridView* _gridView;
    QPushButton* _resetButton;
    bool _isRunning;
};
#endif // MAINWINDOW_H
