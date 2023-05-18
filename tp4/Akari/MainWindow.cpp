#include "GridView.h"
#include "MainWindow.h"
#include "Stopwatch.h"
#include "ui_MainWindow.h"

#include <QComboBox>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QKeySequence>
#include <QMessageBox>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSettings>
#include <QShortcut>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings;
    setWindowTitle( tr("David & Thomas' Akari Game"));
    QSize size = settings.value("size", QSize(800, 600)).toSize();
    resize(size);

    _commandHistory = new CommandHistory();
    _gridModel = new GridModel();
    _isRunning = false;
    _randomSeed = new QRandomGenerator(QDateTime::currentMSecsSinceEpoch() / 1000);
    _stopwatchIsRunning = false;
    _stopwatch = Stopwatch::getInstance();
    _stopwatch->setMinimumWidth(200);
    ui->verticalLayout->insertWidget(1, _stopwatch);
    ui->verticalLayout->itemAt(1)->setAlignment(Qt::AlignHCenter);
    ui->verticalLayout->setStretch(1, 1);
    _undoNumber = 0;

    _gridView = ui->_grid;

    _sizeComboBox = new QComboBox();
    _difficultyComboBox = new QComboBox();

    _sizeComboBox->addItem( tr("7 x 7"), 7);
    _sizeComboBox->addItem( tr("10 x 10"), 10);
    _sizeComboBox->addItem( tr("14 x 14"), 14);

    _difficultyComboBox->addItem( tr("Easy"), 0);
    _difficultyComboBox->addItem( tr("Normal"), 1);
    _difficultyComboBox->addItem( tr("Hard"), 2);

    ui->_menuArea->insertWidget(1, _sizeComboBox);
    ui->_menuArea->insertWidget(3, _difficultyComboBox);
    ui->_menuArea->setStretch(1, 1);
    ui->_menuArea->setStretch(3, 1);
    ui->_menuArea->setStretch(4, 1);
    ui->_menuArea->setStretch(5, 1);


    connect(ui->_resetButton, &QPushButton::clicked, this, &MainWindow::onResetClick);
    connect(ui->_quitButton, &QPushButton::clicked, this, &MainWindow::onQuitClick);
    connect(ui->_startButton, &QPushButton::clicked, this, &MainWindow::onStartClick);
    connect(ui->_checkButton, &QPushButton::clicked, this, &MainWindow::onCheckClick);

    ui->_checkButton->setToolTip( tr("You think it's okay? Click here!") );
    _sizeComboBox->setToolTip( tr("Choose the grid size!") );
    _difficultyComboBox->setToolTip( tr("Choose the grid difficulty!") );
    ui->_startButton->setToolTip( tr("Let's go!") );
    ui->_resetButton->setToolTip( tr("Remove all the lights!") );
    ui->_quitButton->setToolTip( tr("It's enough for this time?") );

    QShortcut* undoShortcut = new QShortcut( QKeySequence("Ctrl+Z"), this);
    QShortcut* redoShortcut = new QShortcut( QKeySequence("Ctrl+Y"), this);
    QShortcut* quitShortcut = new QShortcut( QKeySequence("Ctrl+Q"), this);
    QShortcut* startShortcut = new QShortcut( QKeySequence("Ctrl+S"), this);
    QShortcut* resetShortcut = new QShortcut( QKeySequence("Ctrl+R"), this);
    QShortcut* checkShortcut = new QShortcut( QKeySequence("Ctrl+C"), this);

    connect( undoShortcut, &QShortcut::activated, this, &MainWindow::undo );
    connect( redoShortcut, &QShortcut::activated, this, &MainWindow::redo );
    connect( quitShortcut, &QShortcut::activated, this, &MainWindow::onQuitClick );
    connect( startShortcut, &QShortcut::activated, this, &MainWindow::onStartClick );
    connect( resetShortcut, &QShortcut::activated, this, &MainWindow::onResetClick );
    connect( checkShortcut, &QShortcut::activated, this, &MainWindow::onCheckClick ); connect( ui->_quitAction, &QAction::triggered, this, &MainWindow::onQuitClick ); connect( ui->_aboutAction, &QAction::triggered, this, &MainWindow::onAbout );
    connect( ui->_rulesAction, &QAction::triggered, this, &MainWindow::onRules );


    _gridView->generateGrid( getSize().toInt() );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRules() {
  QMessageBox* rulesMessageBox = new QMessageBox();
  rulesMessageBox->setFixedWidth( width() * 0.3 );
  rulesMessageBox->setTextFormat(Qt::RichText);
  rulesMessageBox->about(nullptr,
                         tr("Rules of Akari Game"),
                         tr("<center>Switch on all the boxes putting lights!<br><br>"
                           "Be careful to respect the number of lights needed around the black boxes with a value!</center>"));
  delete rulesMessageBox;
}

void MainWindow::onAbout() {
  QMessageBox* aboutMessageBox = new QMessageBox();
  aboutMessageBox->about(nullptr,
                    tr("About David & Thomas' Akari Game"),
                    tr("Akari Game provided by David GUO and Thomas SENG.")
                    );
  aboutMessageBox->setFixedWidth( width() * 0.3 );
  delete aboutMessageBox;
}

void MainWindow::onQuitClick() {
  int button = QMessageBox::question(this,
                                     tr("You want to quit..."),
                                     tr("Are you sure that you want to quit"
                                     " this great application?"),
                                     QMessageBox::Yes, QMessageBox::No | QMessageBox::Default);
  if (button == QMessageBox::Yes) {
    close();
  }
}

void MainWindow::onStartClick() {
    ui->_resetButton->setEnabled( true);
    ui->_checkedBlackBoxesStatusText->setText("0 / " + _gridModel->getBlackBoxesWithValueNumber().toString() );
    ui->_checkButton->setEnabled( true);
    ui->_gridStatusText->setText( tr("You start a new grid!") );
    ui->_onBoxesStatusText->setText("0 / " + _gridModel->getEmptyBoxesNumber().toString());
    ui->_undoStatusText->setText( _undoNumber.toString() );

    qDeleteAll(_gridView->findChildren<Box*>());
    qDeleteAll(_gridView->findChildren<QGridLayout *>());
    _gridView->setSize(getSize().toInt());
    _gridView->generateGrid( getSize().toInt() );

    for (int row = 0; row < getSize().toInt(); row++) {
        for (int col = 0; col < getSize().toInt(); col++) {
            connect(_gridView->getBoxesList()->value(row * getSize().toInt() + col), &Box::clickedWithPosition, this, &MainWindow::handleClickOnBox);
        }
    }

    _commandHistory = new CommandHistory();
    _stopwatch->start();
    _isRunning = true;
    _undoNumber = 0;
    _map = readerFile();
    _gridModel = new GridModel( getSize().toInt() );
    _gridModel->loadMap( _map );
    _gridView->refreshGrid( _gridModel->getGrid() );
}

void MainWindow::handleClickOnBox(int row, int col)
{
    if (_isRunning) {
        ui->_gridStatusText->setText( tr("You have clicked at position (") + QVariant(row + 1).toString() + ", " + QVariant(col + 1).toString() + ")" );
        _gridModel->clickOnBox(row, col);
        _commandHistory->pushUndo(row, col);
        _gridView->refreshGrid( _gridModel->getGridChanges(row, col) );
        refreshStatus();
    }
}

void MainWindow::onTestClick() {
    ui->_gridStatusText->setText("");
    _gridModel->clickOnBox(0, 2);
    _commandHistory->pushUndo(0, 2);
    _gridModel->clickOnBox(0, 6);
    _commandHistory->pushUndo(0, 6);
    _gridModel->clickOnBox(1, 3);
    _commandHistory->pushUndo(1, 3);
    _gridModel->clickOnBox(1, 5);
    _commandHistory->pushUndo(1, 5);
    _gridModel->clickOnBox(2, 0);
    _commandHistory->pushUndo(2, 0);
    _gridModel->clickOnBox(2, 5);
    _commandHistory->pushUndo(2, 5);
    _gridModel->clickOnBox(3, 1);
    _commandHistory->pushUndo(3, 1);
    _gridModel->clickOnBox(3, 3);
    _commandHistory->pushUndo(3, 3);
    _gridModel->clickOnBox(4, 0);
    _commandHistory->pushUndo(4, 0);
    _gridModel->clickOnBox(4, 4);
    _commandHistory->pushUndo(4, 4);
    _gridModel->clickOnBox(5, 3);
    _commandHistory->pushUndo(5, 3);
    _gridModel->clickOnBox(6, 2);
    _commandHistory->pushUndo(6, 2);
    _gridModel->clickOnBox(6, 6);
    _commandHistory->pushUndo(6, 6);
    _gridModel->clickOnBox(1, 5);
    _commandHistory->pushUndo(1, 5);
    ui->_onBoxesStatusText->setText(_gridModel->getOnBoxesNumber().toString() + " / " + _gridModel->getEmptyBoxesNumber().toString());
    ui->_checkedBlackBoxesStatusText->setText(_gridModel->getBlackBoxesWithValueNumber().toString() + " / " + _gridModel->getBlackBoxesWithValueNumber().toString() );
    _gridView->refreshGrid( _gridModel->getGrid() );
}

void MainWindow::onResetClick() {
    if ( _isRunning ) {
        _gridModel = new GridModel( getSize().toInt() );
        _gridModel->loadMap( _map );
        _commandHistory = new CommandHistory();

        ui->_checkButton->setEnabled( true);
        ui->_gridStatusText->setText( tr("You have reset the grid!"));
        ui->_onBoxesStatusText->setText("0 / " + _gridModel->getEmptyBoxesNumber().toString());
        ui->_checkedBlackBoxesStatusText->setText("0 / " + _gridModel->getBlackBoxesWithValueNumber().toString() );
        ui->_undoStatusText->setText( _undoNumber.toString() );
        _gridView->refreshGrid( _gridModel->getGrid() );
        refreshStatus();
    }
}

void MainWindow::undo() {
    if ( _isRunning ) {
        if ( ui->_checkButton->isEnabled() && !(_commandHistory->isUndoListEmpty()) ) {
            ui->_gridStatusText->setText( tr("You have undone an action!"));
            QPair<int, int> lastCommand = _commandHistory->popUndo();
            _gridModel->clickOnBox(lastCommand.first, lastCommand.second);
            _undoNumber = QVariant::fromValue( _undoNumber.toInt() + 1 );
            ui->_undoStatusText->setText( _undoNumber.toString() );
            _gridView->refreshGrid( _gridModel->getGridChanges(lastCommand.first, lastCommand.second) );
            refreshStatus();
        }
    }
}

void MainWindow::redo() {
    if ( _isRunning ) {
        if ( ui->_checkButton->isEnabled() && !(_commandHistory->isRedoListEmpty()) ) {
            ui->_gridStatusText->setText( tr("You have redone an action!"));
            QPair<int, int> lastCommand = _commandHistory->popRedo();
            _gridModel->clickOnBox( lastCommand.first, lastCommand.second );
            _undoNumber = QVariant::fromValue( _undoNumber.toInt() - 1 );
            ui->_undoStatusText->setText( _undoNumber.toString() );
            _gridView->refreshGrid( _gridModel->getGridChanges(lastCommand.first, lastCommand.second) );
            refreshStatus();
        }
    }
}

void MainWindow::onCheckClick() {
    if ( _isRunning ) {
        if ( _gridModel->checkGrid() ) {
            _stopwatch->stop();
            ui->_checkButton->setEnabled(false);
            ui->_resetButton->setEnabled(false);
            _isRunning = false;
            ui->_gridStatusText->setText( tr("<span style='color: green;'><span style='font-weight: bold;'>Congratulations!</span> You have successfully completed the grid!</span>") );
        } else {
            ui->_gridStatusText->setText( tr("<span style='color: red;'><span style='font-weight: bold;'>Sorry...</span> The grid has not been filled in correctly...</span>") );
        }
    }
}

QString MainWindow::readerFile() {
    QFileInfo file_path = ":/maps/" + getSize().toString() + "_" + getDifficultyString() + ".txt";
    QFile fichier(file_path.filePath());
    QString line;
    int linesNumber;
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error: the selected file could not be opened";

    QTextStream *stream = new QTextStream(&fichier);
    linesNumber = stream->readLine().toInt();
    int random = ( _randomSeed->generate64() + 1 ) % linesNumber;
    int lineNumber = 1;
    while(!stream->atEnd()) {
        line = stream->readLine();
        if ( lineNumber == random ) {
            qDebug() << "Random number: " << random;
            qDebug() << line;
            break;
        }
        lineNumber++;
    }
    fichier.close();
    return line;
}

QVariant MainWindow::getSize() {
    return _sizeComboBox->itemData( _sizeComboBox->currentIndex() ).toInt();
}

QVariant MainWindow::getDifficulty() {
    return _difficultyComboBox->itemData( _difficultyComboBox->currentIndex() ).toInt();
}

QString MainWindow::getDifficultyString() {
    switch( getDifficulty().toInt() ) {
        case(1):
            return "normal";
        break;
        case(2):
            return "hard";
        break;
        default:
            return "easy";
    }
}

void MainWindow::refreshStatus() {
    ui->_onBoxesStatusText->setText(_gridModel->getOnBoxesNumber().toString() + " / " + _gridModel->getEmptyBoxesNumber().toString());
    ui->_checkedBlackBoxesStatusText->setText(_gridModel->getCheckedBlackBoxesNumber().toString() + " / " + _gridModel->getBlackBoxesWithValueNumber().toString() );
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings;
    settings.setValue("size", size());
    QMainWindow::closeEvent(event);
}
