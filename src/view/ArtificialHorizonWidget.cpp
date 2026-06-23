#include "ArtificialHorizonWidget.h"

#include <QPainter>

ArtificialHorizonWidget::ArtificialHorizonWidget(QWidget* parent):
    QWidget(parent),
    m_pitch(0.0),
    m_roll(0.0)
{
}

void ArtificialHorizonWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::black);

    drawHorizon(painter);
    drawInstrumentFrame(painter);
    drawAircraftReference(painter);
    drawRollScale(painter);
    drawRollPointer(painter);

    painter.end();
}

void ArtificialHorizonWidget::setPitch(double pitch)
{
    m_pitch = pitch;

    update();
}

void ArtificialHorizonWidget::setRoll(double roll)
{
    m_roll = roll;

    update();
}

void ArtificialHorizonWidget::drawInstrumentFrame(QPainter& painter)
{
    int size = qMin(width(), height()) - 40;
    QRect instrumentRect(
        (width() - size) / 2,
        (height() - size) / 2,
        size,
        size
        );

    painter.setPen(QPen(Qt::white, 4));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(instrumentRect);
}

void ArtificialHorizonWidget::drawAircraftReference(QPainter& painter)
{
    painter.setPen(QPen(Qt::white, 3));

    int centerX = width() / 2;
    int centerY = height() / 2;

    painter.drawLine(centerX - 80, centerY, centerX - 20, centerY);
    painter.drawLine(centerX + 20, centerY, centerX + 80, centerY);

    painter.drawLine(centerX, centerY - 10, centerX, centerY + 10);
}

void ArtificialHorizonWidget::drawHorizon(QPainter& painter)
{
    painter.fillRect(rect(), Qt::black);

    painter.translate(width() / 2, height() / 2);

    painter.rotate(-m_roll);

    int horizonY = static_cast<int>(m_pitch * PIXELS_PER_DEGREE);

    painter.fillRect(
        QRect(-2000, -2000, 4000, 2000 + horizonY),
        QColor(70, 130, 180));

    painter.fillRect(
        QRect(-2000, horizonY, 4000, 2000),
        QColor(139, 69, 19));

    painter.setPen(QPen(Qt::white, 3));

    painter.drawLine(
        -2000,
        horizonY,
        2000,
        horizonY);

    drawPitchScale(painter, horizonY);

    painter.resetTransform();
}

void ArtificialHorizonWidget::drawRollScale(QPainter& painter)
{
    int centerX = width() / 2;
    int centerY = height() / 2;

    int radius = qMin(width(), height()) / 2 - 30;

    painter.setPen(QPen(Qt::white, 3));

    for (int angle : { -60, -45, -30, -20, -10, 10, 20, 30, 45, 60 })
    {
        double rad = qDegreesToRadians(static_cast<double>(angle));

        int x1 = centerX + std::sin(rad) * (radius - 20);
        int y1 = centerY - std::cos(rad) * (radius - 20);

        int x2 = centerX + std::sin(rad) * radius;
        int y2 = centerY - std::cos(rad) * radius;

        painter.drawLine(x1, y1, x2, y2);
    }
}

void ArtificialHorizonWidget::drawPitchScale(QPainter& painter, int horizonY)
{
    painter.setPen(QPen(Qt::white, 2));

    for (int pitch = -90; pitch <= 90; pitch += 10)
    {
        if (pitch == 0)
        {
            continue;
        }

        int y = horizonY - pitch * PIXELS_PER_DEGREE;

        int width = (pitch % 20 == 0) ? 80 : 40;

        painter.drawLine(
            -width / 2,
            y,
            width / 2,
            y);

        if (pitch % 20 == 0)
        {
            QString text = QString::number(std::abs(pitch));

            painter.drawText(-120, y + 5, text);
            painter.drawText(90, y + 5, text);
        }
    }
}

void ArtificialHorizonWidget::drawRollPointer(QPainter& painter)
{
    int centerX = width() / 2;
    int centerY = height() / 2;

    int radius = qMin(width(), height()) / 2 - 30;

    int TopY = centerY - radius;

    QPoint points[3] =
        {
            QPoint(centerX, TopY - 10),
            QPoint(centerX - 10, TopY + 10),
            QPoint(centerX + 10, TopY + 10)
        };

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    painter.drawPolygon(points, 3);
}