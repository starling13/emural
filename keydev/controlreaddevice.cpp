#include "controlreaddevice.hpp"
#include "ui_controlreaddevice.h"

#include <cstring>
#include <string>

#include <QDebug>
#include <QFileDialog>
#include <QContextMenuEvent>

PunchTape::PunchTape()
{
}

PunchTape::~PunchTape()
{
}

void PunchTape::loadData(const QByteArray &data)
{
    Number  buffer;
    int position;

    _data.clear();
    position = 0;
    while (data.size() >= position+11) {
        for (int i=0; i<11; ++i)
            buffer.data[i] = data[position+i];
        _data.push_back(buffer);
        position += 11;
    }
}

PunchTapeViewWidget::PunchTapeViewWidget(QWidget *parent) :
QWidget(parent),
_tape(NULL)
{
}

PunchTapeViewWidget::~PunchTapeViewWidget()
{
}

void PunchTapeViewWidget::setTape(PunchTape *newVal)
{
    _tape = newVal;
    _position = 0;
    this->update();
}

void PunchTapeViewWidget::paintEvent(QPaintEvent*)
{
    if (_tape == NULL)
        return;

    double ratio = double (height()) / double (width());
    double frameTop = 0;

    _painter.begin(this);

    _painter.scale(width() / 400.0, height() / (ratio * 400.0));
    _painter.setBrush(Qt::white);

    int frameCounter = 0;
    int scaledHeight = 400.0 * ratio;
    while (frameTop < scaledHeight) {
        if (_tape->tapeData().size() > _position+frameCounter)
            drawFrame(frameCounter++);
        else
            break;
        frameTop += 190.0;
    }

    _painter.end();
}

void PunchTapeViewWidget::drawFrame(int number)
{
    Q_CHECK_PTR(_tape);
    Q_ASSERT(_tape->tapeData().size() >= _position+number);

    qDebug() << __PRETTY_FUNCTION__;

    unsigned hShift = 50.0;
    unsigned shift = 190.0 * number;
    _painter.fillRect(0, shift, hShift, 190.0, Qt::white);
    _painter.setPen(Qt::black);
    _painter.drawLine(0,shift,hShift,shift);
    _painter.setFont(QFont("Sans", 17.0));
    _painter.drawText(0.0, shift+10.0, hShift, 50.0, 0, QString::number(_position+number));

    _painter.setPen(Qt::NoPen);
    _painter.fillRect(hShift, shift, 350.0, 190.0, Qt::black);

    for (int i=0; i<4; ++i) {
        _painter.drawRect(hShift+20.150, shift + 13.85 + 47.5*i, 28.0, 19.8);
        _painter.drawRect(hShift+301.85, shift + 13.85 + 47.5*i, 28.0, 19.8);

        for (int j=0; j<11; ++j) {
            char digit = _tape->tapeData().at(_position+number).data[j];
            if (digit & (1<<(3-i)))
                _painter.drawRect(hShift+52.0 + 23.0*j, shift + 9.75 + 47.5*i, 13.0, 28.0);
        }
    }
}

ControlReadDevice::ControlReadDevice(QWidget *parent) :
    QWidget(parent),
    ui(*(new Ui::ControlReadDevice))
{
    ui.setupUi(this);

    ui.stretchViewWidget->setTape(&_tape);

    _contextMenu.addAction(QString::fromUtf8(u8"Новая"), this, SLOT(newTape()));
    _contextMenu.addAction(QString::fromUtf8(u8"Загрузить"), this, SLOT(loadTape()));
    _contextMenu.addAction(QString::fromUtf8(u8"Сохранить"), this, SLOT(saveTape()));

    QObject::connect(this->ui.scrollBar, SIGNAL(valueChanged(int)),
        this->ui.stretchViewWidget, SLOT(setPosition(int)));
}

ControlReadDevice::~ControlReadDevice()
{
    delete &ui;
}

void ControlReadDevice::punchNumber(PunchTape::Number newVal)
{
    if (_tape.tapeData().size() < ui.scrollBar->value()+3)
        _tape.tapeData().resize(ui.scrollBar->value()+3);
    ui.scrollBar->setMaximum(_tape.tapeData().size()-1);
    ui.scrollBar->setValue(ui.scrollBar->value()+1);
    _tape.tapeData().operator [](ui.scrollBar->value()+1) = newVal;
}

void ControlReadDevice::newTape()
{
    _tape.tapeData().clear();
    ui.scrollBar->setMaximum(0);
}

void ControlReadDevice::contextMenuEvent(QContextMenuEvent *event)
{
    _contextMenu.popup(event->globalPos());
}

void ControlReadDevice::loadTape()
{
    QString fileName;

    fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8(
        u8"ыбор файла перфоленты для загрузки"), QDir::homePath(), "*.upt");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            QByteArray ba, line, bytes(11, Qt::Uninitialized);
            while (true) {
                line = file.readLine(file.size());
                bytes.clear();
                if (line.isEmpty())
                    break;
                if (line[0] == '#')
                    continue;
                if (line.size() < 11) {
                    qWarning() << QString::fromUtf8(u8"Слишком короткая строка");
                    continue;
                }
                for (int i=0; i<11; ++i) {
                    char c = line[i];
                    if (isdigit(c))
                        bytes[i] = std::atoi(std::string("").append(1, c).c_str());
                    else
                        qWarning() << QString::fromUtf8(u8"Не цифра") << int (c);
                }
                ba.append(bytes);
            };
            _tape.loadData(ba);
            if (_tape.tapeData().size() > 1)
                ui.scrollBar->setMaximum(_tape.tapeData().size()-1);
            else
                ui.stretchViewWidget->update();
        } else
            qWarning() << QString::fromUtf8(u8"евозможно открыть файл") << fileName;
    }
}

void ControlReadDevice::saveTape()
{
}
