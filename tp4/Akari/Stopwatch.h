#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QElapsedTimer>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

class Stopwatch : public QWidget
{
    Q_OBJECT
public:
    static Stopwatch* getInstance(QWidget *parent = nullptr);
    void start();
    void stop();

public slots:
    void onReset();
    void onStart();
    void onStop();
    void updateDisplay();

private:
    Stopwatch(QWidget *parent = nullptr);

    qint64 _elapsedTime;
    QElapsedTimer *_elapsedTimer;
    static Stopwatch* _instance;
    QLabel *_timeLabel;
    QTimer *_timerChrono;
};

#endif // STOPWATCH_H
