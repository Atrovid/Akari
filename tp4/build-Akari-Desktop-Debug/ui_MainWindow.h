/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GridView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *_aboutAction;
    QAction *_quitAction;
    QAction *_rulesAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *_title;
    GridView *_grid;
    QGridLayout *_informationField;
    QLabel *_onBoxesStatusText;
    QLabel *_onBoxesStatus;
    QLabel *_checkedBlackBoxesStatus;
    QLabel *_checkedBlackBoxesStatusText;
    QLabel *_undoStatusText;
    QLabel *_gridStatus;
    QLabel *_gridStatusText;
    QLabel *_undoStatus;
    QPushButton *_checkButton;
    QHBoxLayout *_menuArea;
    QLabel *_sizeLabel;
    QLabel *_difficultyLabel;
    QPushButton *_startButton;
    QPushButton *_resetButton;
    QPushButton *_quitButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 691);
        _aboutAction = new QAction(MainWindow);
        _aboutAction->setObjectName(QString::fromUtf8("_aboutAction"));
        _quitAction = new QAction(MainWindow);
        _quitAction->setObjectName(QString::fromUtf8("_quitAction"));
        _rulesAction = new QAction(MainWindow);
        _rulesAction->setObjectName(QString::fromUtf8("_rulesAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(50, 20, 50, 20);
        _title = new QLabel(centralwidget);
        _title->setObjectName(QString::fromUtf8("_title"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        _title->setFont(font);
        _title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(_title);

        _grid = new GridView(centralwidget);
        _grid->setObjectName(QString::fromUtf8("_grid"));
        _grid->setMinimumSize(QSize(295, 10));

        verticalLayout->addWidget(_grid);

        _informationField = new QGridLayout();
        _informationField->setObjectName(QString::fromUtf8("_informationField"));
        _onBoxesStatusText = new QLabel(centralwidget);
        _onBoxesStatusText->setObjectName(QString::fromUtf8("_onBoxesStatusText"));
        _onBoxesStatusText->setMinimumSize(QSize(60, 0));
        _onBoxesStatusText->setWordWrap(false);
        _onBoxesStatusText->setMargin(0);

        _informationField->addWidget(_onBoxesStatusText, 0, 1, 1, 1);

        _onBoxesStatus = new QLabel(centralwidget);
        _onBoxesStatus->setObjectName(QString::fromUtf8("_onBoxesStatus"));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        _onBoxesStatus->setFont(font1);
        _onBoxesStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _informationField->addWidget(_onBoxesStatus, 0, 0, 1, 1);

        _checkedBlackBoxesStatus = new QLabel(centralwidget);
        _checkedBlackBoxesStatus->setObjectName(QString::fromUtf8("_checkedBlackBoxesStatus"));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        _checkedBlackBoxesStatus->setFont(font2);
        _checkedBlackBoxesStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _informationField->addWidget(_checkedBlackBoxesStatus, 0, 2, 1, 1);

        _checkedBlackBoxesStatusText = new QLabel(centralwidget);
        _checkedBlackBoxesStatusText->setObjectName(QString::fromUtf8("_checkedBlackBoxesStatusText"));

        _informationField->addWidget(_checkedBlackBoxesStatusText, 0, 3, 1, 1);

        _undoStatusText = new QLabel(centralwidget);
        _undoStatusText->setObjectName(QString::fromUtf8("_undoStatusText"));

        _informationField->addWidget(_undoStatusText, 1, 1, 1, 1);

        _gridStatus = new QLabel(centralwidget);
        _gridStatus->setObjectName(QString::fromUtf8("_gridStatus"));
        QFont font3;
        font3.setBold(true);
        font3.setUnderline(true);
        font3.setWeight(75);
        _gridStatus->setFont(font3);
        _gridStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _informationField->addWidget(_gridStatus, 1, 2, 1, 1);

        _gridStatusText = new QLabel(centralwidget);
        _gridStatusText->setObjectName(QString::fromUtf8("_gridStatusText"));

        _informationField->addWidget(_gridStatusText, 1, 3, 1, 1);

        _undoStatus = new QLabel(centralwidget);
        _undoStatus->setObjectName(QString::fromUtf8("_undoStatus"));
        _undoStatus->setFont(font2);
        _undoStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _informationField->addWidget(_undoStatus, 1, 0, 1, 1);

        _informationField->setColumnStretch(3, 1);

        verticalLayout->addLayout(_informationField);

        _checkButton = new QPushButton(centralwidget);
        _checkButton->setObjectName(QString::fromUtf8("_checkButton"));
        _checkButton->setEnabled(false);

        verticalLayout->addWidget(_checkButton);

        _menuArea = new QHBoxLayout();
        _menuArea->setSpacing(6);
        _menuArea->setObjectName(QString::fromUtf8("_menuArea"));
        _menuArea->setContentsMargins(0, -1, 0, -1);
        _sizeLabel = new QLabel(centralwidget);
        _sizeLabel->setObjectName(QString::fromUtf8("_sizeLabel"));
        _sizeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _menuArea->addWidget(_sizeLabel);

        _difficultyLabel = new QLabel(centralwidget);
        _difficultyLabel->setObjectName(QString::fromUtf8("_difficultyLabel"));
        _difficultyLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        _menuArea->addWidget(_difficultyLabel);

        _startButton = new QPushButton(centralwidget);
        _startButton->setObjectName(QString::fromUtf8("_startButton"));

        _menuArea->addWidget(_startButton);

        _resetButton = new QPushButton(centralwidget);
        _resetButton->setObjectName(QString::fromUtf8("_resetButton"));
        _resetButton->setEnabled(false);

        _menuArea->addWidget(_resetButton);


        verticalLayout->addLayout(_menuArea);

        _quitButton = new QPushButton(centralwidget);
        _quitButton->setObjectName(QString::fromUtf8("_quitButton"));

        verticalLayout->addWidget(_quitButton);

        verticalLayout->setStretch(1, 6);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(_quitAction);
        menuHelp->addAction(_rulesAction);
        menuHelp->addAction(_aboutAction);

        retranslateUi(MainWindow);

        _quitButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        _aboutAction->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
        _quitAction->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
        _rulesAction->setText(QCoreApplication::translate("MainWindow", "&Rules", nullptr));
        _title->setText(QCoreApplication::translate("MainWindow", "Akari Game", nullptr));
        _onBoxesStatusText->setText(QString());
        _onBoxesStatus->setText(QCoreApplication::translate("MainWindow", "On boxes: ", nullptr));
        _checkedBlackBoxesStatus->setText(QCoreApplication::translate("MainWindow", "Checked black boxes: ", nullptr));
        _checkedBlackBoxesStatusText->setText(QString());
        _undoStatusText->setText(QString());
        _gridStatus->setText(QCoreApplication::translate("MainWindow", "Status: ", nullptr));
        _gridStatusText->setText(QString());
        _undoStatus->setText(QCoreApplication::translate("MainWindow", "Number of undo: ", nullptr));
        _checkButton->setText(QCoreApplication::translate("MainWindow", "Check it!", nullptr));
        _sizeLabel->setText(QCoreApplication::translate("MainWindow", "Size:", nullptr));
        _difficultyLabel->setText(QCoreApplication::translate("MainWindow", "Difficulty:", nullptr));
        _startButton->setText(QCoreApplication::translate("MainWindow", "Start!", nullptr));
        _resetButton->setText(QCoreApplication::translate("MainWindow", "Reset!", nullptr));
        _quitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
