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

    QTimer  _timer;
    QPixmap _background;
    QPainter _painter;
    int     _side;
    QTime   _time;
};

AnalogClock::AnalogClock(QWidget *parent) :
QWidget(parent),
_data(*(new AnalogClockData))
{
    resize(200, 200);

    _data._timer.start(1000);
    QObject::connect(&_data._timer, SIGNAL(timeout()), this,
        SLOT(onTimerSignaled()));
}

AnalogClock::~AnalogClock()
{
    delete &_data;
}

void AnalogClock::onTimerSignaled()
{
    _data._time.addSecs(1);
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

    int side = _data._side;
    QTime time = QTime::currentTime();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.drawPixmap(-100,-100, 200, 200, _data._background);

    painter.resetTransform();
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
    painter.drawEllipse(-90,50,28,28);
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(62,50,28,28);

    painter.resetMatrix();
    painter.setBrush(Qt::darkGreen);
    painter.translate(width() / 2,
        (height() + side/2) / 2);
    painter.scale(side / 200.0, side / 200.0);
    painter.drawEllipse(-3,-3,6,6);
}

void AnalogClock::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    QPainter     &painter = _data._painter;
    static QPen   slender(Qt::white, 1.0);
    static QColor backgroundColor(Qt::black);
    static QPen   broad(Qt::white, 2.0);
    static QStaticText hours[12] = {QStaticText("1"), QStaticText("2"),
        QStaticText("3"), QStaticText("4"), QStaticText("5"), QStaticText("6"),
        QStaticText("7"), QStaticText("8"), QStaticText("9"), QStaticText("10"),
        QStaticText("11"), QStaticText("12")};
    static QStaticText minutes[12] = {QStaticText("5"), QStaticText("10"),
        QStaticText("15"), QStaticText("20"), QStaticText("25"), QStaticText("30"),
        QStaticText("35"), QStaticText("40"), QStaticText("45"), QStaticText("50"),
        QStaticText("55"), QStaticText("0")};

    _data._side = qMin(width(), height());
    _data._background = QPixmap(_data._side, _data._side);
    _data._background.fill(Qt::transparent);
    QPoint  center = _data._background.rect().center();
    int side = _data._side;

    painter.begin(&_data._background);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(_data._background.width() / 2,
                      _data._background.height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkGray);
    painter.drawEllipse(-100,10,80,80);
    painter.drawEllipse(20,10,80,80);

    QRadialGradient   gradient;
    gradient.setCenter(-60,-60);
    gradient.setFocalPoint(-60,-60);
    gradient.setRadius(210);

    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(0.7, Qt::darkGray);
    gradient.setColorAt(1, Qt::lightGray);

    painter.setBrush(gradient);
    painter.drawEllipse(-97,-97, 194, 194);

    painter.setPen(slender);
    painter.setBrush(backgroundColor);
    painter.drawEllipse(-89,-89, 178, 178);
    painter.drawEllipse(-86,-86, 172, 172);

    painter.save();
    painter.setPen(broad);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(80, 0, 84, 0);
        painter.rotate(30.0);
    }
    painter.restore();

    painter.save();
    painter.setPen(slender);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(80, 0, 84, 0);
        painter.rotate(6.0);
    }
    painter.restore();

    painter.setPen(slender);
    painter.setBrush(backgroundColor);
    painter.resetMatrix();

    // Draw semicircle with texts on every 30".
    painter.setFont(QFont("Sans", side/18.0));
    for (int i = 1; i <= 12; ++i) {
        double c = cos(i * M_PI / 6.0), s = sin(i * M_PI / 6.0);
        QPoint p(center.x() + 0.35*side * s - side/36.0,
                 center.y() - 0.35*side * c - side/36.0);
        painter.drawStaticText(p, hours[i-1]);
    }

    painter.translate(_data._background.width() / 2,
        (_data._background.height() + side/2) / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.drawEllipse(-35,-35, 70, 70);
    painter.setPen(slender);
    painter.save();
    for (int j = 0; j < 60; ++j)
        painter.drawLine(33, 0, 35, 0), painter.rotate(6.0);
    painter.restore();

    QRect   small(-36,-36, 72,72);
    center = small.center();
    painter.setFont(QFont("Sans", 6));
    // Draw semicircle with texts on every 30".
    for (int i = 1; i <= 12; ++i) {
        double c = cos(i * M_PI / 6.0), s = sin(i * M_PI / 6.0);
            QPoint p(center.x() + 26.0 * s - 5,
                     center.y() - 26.0 * c - 4);
            painter.drawStaticText(p, minutes[i-1]);
    }

    painter.end();
}
