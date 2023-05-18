#include "MainWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QTranslator>
#include <QLibraryInfo>
#include <QtGui/QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList languages = QLocale().uiLanguages();
    if (languages.size()) {
        QString language = languages.front().split("-").front();
        QString qmFile = QString(":/translations/Akari_%1.qm").arg(language);
        if (QFileInfo(qmFile).exists()) {
            QTranslator* translator = new QTranslator(&a);
            if (translator->load(qmFile)) {
                a.installTranslator(translator);
            }
            else {
                translator->deleteLater();
            }
            translator = new QTranslator(&a);
            if (translator->load(QString("qt_%1").arg(language),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
                a.installTranslator(translator);
            }
            else {
                translator->deleteLater();
            }
        }
    }

    QDesktopWidget dw;
    MainWindow w;

    int width = QGuiApplication::primaryScreen()->geometry().width();
    int height = QGuiApplication::primaryScreen()->geometry().height();

    w.setMinimumSize(width * 0.4, height * 0.6);

    w.show();
    return a.exec();
}
