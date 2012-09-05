/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartdatetimeaxisy_p.h"
#include "chartpresenter_p.h"
#include "qdatetimeaxis.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <QDateTime>
#include <qmath.h>


static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDateTimeAxisY::ChartDateTimeAxisY(QAbstractAxis *axis,ChartPresenter *presenter) : ChartAxis(axis,presenter),
m_tickCount(0)
{
}

ChartDateTimeAxisY::~ChartDateTimeAxisY()
{
}

void ChartDateTimeAxisY::createLabels(QStringList &labels,qreal min, qreal max, int ticks)
{
    Q_ASSERT(max>min);
    Q_ASSERT(ticks>1);

    QDateTimeAxis *axis = qobject_cast<QDateTimeAxis *>(m_chartAxis);

    int n = qMax(int(-floor(log10((max-min)/(ticks-1)))),0);
    n++;
    for (int i=0; i< ticks; i++) {
        qreal value = min + (i * (max - min)/ (ticks-1));
        labels << QDateTime::fromMSecsSinceEpoch(value).toString(axis->format());
    }
}

QVector<qreal> ChartDateTimeAxisY::calculateLayout() const
{
    Q_ASSERT(m_tickCount>=2);

    QVector<qreal> points;
    points.resize(m_tickCount);
    QRectF rect = presenter()->chartsGeometry();
    const qreal deltaY = rect.height()/(m_tickCount-1);
    for (int i = 0; i < m_tickCount; ++i) {
        int y = i * -deltaY + rect.bottom();
        points[i] = y;
    }

    return points;
}

void ChartDateTimeAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();

    if(layout.isEmpty()) return;

    QStringList ticksList;

    createLabels(ticksList,m_min,m_max,layout.size());

    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    Q_ASSERT(labels.size() == ticksList.size());
    Q_ASSERT(layout.size() == ticksList.size());

    QRectF chartRect = presenter()->chartsGeometry();

    qreal height =  chartRect.bottom();

    QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(axis.at(0));
    lineItem->setLine(chartRect.left() , chartRect.top(), chartRect.left(), chartRect.bottom());

    for (int i = 0; i < layout.size(); ++i) {
        QGraphicsLineItem *lineItem = static_cast<QGraphicsLineItem*>(lines.at(i));
        lineItem->setLine(chartRect.left() , layout[i], chartRect.right(), layout[i]);
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));

            labelItem->setText(ticksList.at(i));
            const QRectF& rect = labelItem->boundingRect();

            QPointF center = rect.center();
            labelItem->setTransformOriginPoint(center.x(), center.y());
            labelItem->setPos(chartRect.left() - rect.width() - label_padding , layout[i]-center.y());

            if(labelItem->pos().y()+rect.height()>height) {
                labelItem->setVisible(false);
                lineItem->setVisible(false);
            }
            else {
                labelItem->setVisible(true);
                lineItem->setVisible(true);
                height=labelItem->pos().y();
            }

        if ((i+1)%2 && i>1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem*>(shades.at(i/2-1));
            rectItem->setRect(chartRect.left(),layout[i],chartRect.width(),layout[i-1]-layout[i]);
        }
        lineItem = static_cast<QGraphicsLineItem*>(axis.at(i+1));
        lineItem->setLine(chartRect.left()-5,layout[i],chartRect.left(),layout[i]);
    }
}

void ChartDateTimeAxisY::handleAxisUpdated()
{
    //TODO:: fix this
    QDateTimeAxis* axis = qobject_cast<QDateTimeAxis*>(m_chartAxis);
    m_tickCount = axis->tickCount();
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(m_font);
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width(),fn.height());
            break;
        case Qt::PreferredSize:{

            const QVector<qreal>& layout = ChartAxis::layout();
            if(layout.isEmpty()) break;
            QStringList ticksList;


            qreal width=0;
            qreal height=0;

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                width+=rect.width();
                height+=qMax(rect.height()+label_padding,height);
            }
            sh = QSizeF(width,height);
            break;
        }
        default:
          break;
      }

      return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
