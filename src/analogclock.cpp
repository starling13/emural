#include "analogclock.h"

#include <cmath>

#include <QPaintEvent>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QStaticText>
#include <QPixmap>
#include <QRadialGradient>

class AnalogClock::AnalogClockData
{
public:

    AnalogClockData() :
    minutes {QStaticText("5"), QStaticText("10"),
            QStaticText("15"), QStaticText("20"), QStaticText("25"), QStaticText("30"),
            QStaticText("35"), QStaticText("40"), QStaticText("45"), QStaticText("50"),
            QStaticText("55"), QStaticText("0")},
    hours {QStaticText("1"), QStaticText("2"),
            QStaticText("3"), QStaticText("4"), QStaticText("5"), QStaticText("6"),
            QStaticText("7"), QStaticText("8"), QStaticText("9"), QStaticText("10"),
            QStaticText("11"), QStaticText("12")},
    _timeState(IDLE),
    _time(0,0,0)
    {
    }

    enum TimerState {IDLE, STARTED, STOPPED};

    QTimer  _timer;
    QPixmap _background;
    QPainter _painter;
    int     _side;
    QTime   _time;
    TimerState _timeState;

    const QStaticText minutes[12];
    const QStaticText hours[12];
};

AnalogClock::AnalogClock(QWidget *parent) :
QWidget(parent),
_data(*(new AnalogClockData))
{
    resize(200, 200);
    _data._timer.start(1000);
    QObject::connect(&_data._timer, SIGNAL(timeout()), this,
        SLOT(onTimerSignaled()));
    this->setMouseTracking(true);
}

AnalogClock::~AnalogClock()
{
    delete &_data;
}

void AnalogClock::onTimerSignaled()
{
    if (_data._timeState == AnalogClockData::STARTED)
       _data._time = _data._time.addSecs(1);
    this->update();
}

void AnalogClock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[5] = {
        QPoint(-2, 3),
        QPoint(2, 3),
        QPoint(4, -23),
        QPoint(0, -46),
        QPoint(-4, -23)
    };
    static const QPoint minuteHand[5] = {
        QPoint(-2, 4),
        QPoint(2, 4),
        QPoint(4, -35),
        QPoint(0, -70),
        QPoint(-4, -35)
    };
    static const QPoint secondHand[5] = {
        QPoint(1, 8),
        QPoint(-1, 8),
        QPoint(-1, -70),
        QPoint(0, -86),
        QPoint(1, -70),
    };

    static QColor hourColor(Qt::white);
    static QColor minuteColor(Qt::white);
    static QColor secondColor(Qt::white);
    static QPen   slender(Qt::white, 1.0);
    static QPen   broad(Qt::white, 2.0);

    int side = _data._side;
    QTime time = QTime::currentTime();

    QPainter     &painter = _data._painter;

    painter.begin(this);

    painter.drawPixmap(rect().center()-QPoint(side/2,side/2), _data._background);

    painter.setRenderHint(QPainter::Antialiasing);

    // маленький циферблат
    painter.resetMatrix();
    painter.translate(width() / 2,
        (height() + side*0.45) / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(slender);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6*_data._time.second());
    painter.drawLine(0,2,0,-30);
    painter.restore();

    painter.setPen(broad);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0*_data._time.minute());
    painter.drawLine(0,1,0,-20);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkGreen);
    painter.drawEllipse(-3,-3,6,6);

    // большой циферблат
    painter.resetMatrix();
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 5);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 5);
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondHand, 5);
    painter.restore();

    painter.setBrush(Qt::darkGreen);
    painter.drawEllipse(-7,-7,14,14);

    painter.setPen(slender);
    painter.setBrush(Qt::red);
    painter.drawEllipse(-90,40,24,24);
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(62,40,24,24);

    painter.end();
}

void AnalogClock::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    QPainter     &painter = _data._painter;
    static QPen   slender(Qt::white, 1.0);
    static QColor backgroundColor(Qt::black);
    static QPen   broad(Qt::white, 2.0);

    _data._side = qMin(width(), height());
    _data._background = QPixmap(_data._side, _data._side);
    _data._background.fill(Qt::transparent);
    QPoint  center = _data._background.rect().center();
    int side = _data._side;
    QFont    largeFont("Sans", side/16.0, QFont::DemiBold);

    painter.begin(&_data._background);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(_data._background.width() / 2,
                      _data._background.height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    // приливы для кнопок
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(50,50,50));
    painter.drawEllipse(-98,0,80,80);
    painter.drawEllipse(20,0,80,80);

    // корпус
    QRadialGradient   gradient;
    gradient.setCenter(-62,-62);
    gradient.setFocalPoint(-62,-62);
    gradient.setRadius(210);
    gradient.setColorAt(0, Qt::lightGray);
    gradient.setColorAt(0.6, Qt::black);
    gradient.setColorAt(1, Qt::darkGray);
    painter.setBrush(gradient);
    painter.drawEllipse(-97,-97, 194, 194);

    // большой циферблат
    painter.setPen(slender);
    painter.setBrush(backgroundColor);
    painter.drawEllipse(-87,-87, 174, 174);
    painter.drawEllipse(-84,-84, 168, 168);

    painter.save();
    painter.setPen(broad);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(80, 0, 83, 0);
        painter.rotate(30.0);
    }
    painter.restore();
    painter.save();
    painter.setPen(slender);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(80, 0, 83, 0);
        painter.rotate(6.0);
    }
    painter.restore();

    painter.setPen(slender);
    painter.setBrush(backgroundColor);
    painter.resetMatrix();

    // Draw semicircle with texts on every 30".
    painter.setFont(largeFont);
    for (int i = 1; i <= 12; ++i) {
        double c = cos(i * M_PI / 6.0), s = sin(i * M_PI / 6.0);
        QPoint p(center.x() + 0.35*side * s - side/36.0,
                 center.y() - 0.35*side * c - side/34.0);
        painter.drawStaticText(p, _data.hours[i-1]);
    }

    painter.translate(_data._background.width() / 2,
        (_data._background.height() + side*0.45) / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.drawEllipse(-36,-36, 72, 72);
    painter.setPen(slender);
    painter.save();
    for (int j = 0; j < 60; ++j)
        painter.drawLine(33, 0, 36, 0), painter.rotate(6.0);
    painter.restore();

    QRect   small(-36,-36, 72,72);
    center = small.center();
    painter.setFont(QFont("Sans", 7));
    // Draw semicircle with texts on every 30".
    for (int i = 1; i <= 12; ++i) {
        double c = cos(i * M_PI / 6.0), s = sin(i * M_PI / 6.0);
            QPoint p(center.x() + 27.0 * s - 5,
                     center.y() - 27.0 * c - 5);
            painter.drawStaticText(p, _data.minutes[i-1]);
    }

    painter.end();
}

void AnalogClock::mouseMoveEvent(QMouseEvent *event)
{
    int quantum = qMin(width(), height()) / 10;

    if ((event->y() > rect().center().y() + 2*quantum) &&
        (event->y() < rect().center().y() + 3*quantum)) {
        if ((event->x() > rect().center().x() - 4*quantum) &&
            (event->x() < rect().center().x() - 3*quantum))
            this->setCursor(QCursor(Qt::PointingHandCursor));
        else if ((event->x() > rect().center().x() + 3*quantum) &&
                 (event->x() < rect().center().x() + 4*quantum))
            this->setCursor(QCursor(Qt::PointingHandCursor));
        else
            this->setCursor(QCursor(Qt::ArrowCursor));
    } else
        this->setCursor(QCursor(Qt::ArrowCursor));
}

void AnalogClock::mousePressEvent(QMouseEvent *event)
{
    int quantum = qMin(width(), height()) / 10;

    if ((event->y() > rect().center().y() + 2*quantum) &&
        (event->y() < rect().center().y() + 3*quantum)) {
        if ((event->x() > rect().center().x() - 4*quantum) &&
            (event->x() < rect().center().x() - 3*quantum))
            _data._time.second();
        else if ((event->x() > rect().center().x() + 3*quantum) &&
                 (event->x() < rect().center().x() + 4*quantum))
            if (_data._timeState == AnalogClockData::IDLE) {
                _data._timeState = AnalogClockData::STARTED;
            } else if (_data._timeState == AnalogClockData::STARTED) {
                _data._timeState = AnalogClockData::STOPPED;
            } else
                _data._timeState = AnalogClockData::IDLE,
                _data._time = QTime(0,0,0);
        else
            this->setCursor(QCursor(Qt::ArrowCursor));
    } else
        this->setCursor(QCursor(Qt::ArrowCursor));
}
