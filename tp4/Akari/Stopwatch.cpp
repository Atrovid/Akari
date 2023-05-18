#include "Stopwatch.h"
#include <QTime>

Stopwatch* Stopwatch::_instance = nullptr;

Stopwatch::Stopwatch(QWidget *parent) : QWidget(parent), _elapsedTime(0)
{
    setFixedSize(200,20);
    _elapsedTimer = new QElapsedTimer();
    _timeLabel = new QLabel("00:00:00", this);
    _timeLabel->setAlignment(Qt::AlignHCenter);
    _timeLabel->setMinimumWidth(200);
    _timeLabel->setMinimumHeight(20);
    _timerChrono = new QTimer(this);

    connect(_timerChrono, &QTimer::timeout, this, &Stopwatch::updateDisplay);
}

Stopwatch* Stopwatch::getInstance(QWidget* parent)
{
    if ( !_instance )
        _instance = new Stopwatch(parent);
    return _instance;
}


void Stopwatch::onStart()
{
    _elapsedTimer->restart();
    _timerChrono->start();
}

void Stopwatch::onStop()
{
    _elapsedTime = _elapsedTimer->elapsed();
    _timerChrono->stop();
}

void Stopwatch::onReset()
{
    _elapsedTime = 0;
    _timeLabel->setText("00:00:00");
}

void Stopwatch::updateDisplay()
{
    _elapsedTime = _elapsedTimer->elapsed();
    QTime time = QTime::fromMSecsSinceStartOfDay(_elapsedTime);
    QString timeString = time.toString("HH:mm:ss");
    _timeLabel->setText(timeString);
}

void Stopwatch::start()
{
    _timeLabel->setText("00:00:00");
    _elapsedTime = 0;
    _elapsedTimer->restart();
    _timerChrono->start();
}

void Stopwatch::stop()
{
    _timerChrono->stop();
}

