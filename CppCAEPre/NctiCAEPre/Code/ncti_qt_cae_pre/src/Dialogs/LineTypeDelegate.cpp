#include "LineTypeDelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>

LineTypeDelegate::LineTypeDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void LineTypeDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    painter->save();

    QString text = index.data(Qt::DisplayRole).toString();
    int lineTypeWidth = 60;
    int lineTypeHeight = 2;
    int padding = 5;

    int lineX = opt.rect.x() + padding;
    int lineY = opt.rect.y() + (opt.rect.height() - lineTypeHeight) / 2;

    if (text == "实线") {
        painter->drawLine(lineX, lineY, lineX + lineTypeWidth, lineY);
    }
    else if (text == "点线") {
        for (int i = 0; i <= lineTypeWidth; i += 4) {
            painter->drawPoint(lineX + i, lineY);
        }
    }
    else if (text == "点划线") {
        for (int i = 0; i <= lineTypeWidth; i += 12) {
            painter->drawLine(lineX + i, lineY, lineX + i + 4, lineY);
            painter->drawPoint(lineX + i + 8, lineY);
        }
    }
    else if (text == "中心线") {
        for (int i = 0; i <= lineTypeWidth; i += 16) {
            painter->drawLine(lineX + i, lineY, lineX + i + 6, lineY);
            painter->drawLine(lineX + i + 10, lineY, lineX + i + 12, lineY);
        }
    }
    else if (text == "虚线") {
        for (int i = 0; i <= lineTypeWidth; i += 8) {
            painter->drawLine(lineX + i, lineY, lineX + i + 4, lineY);
        }
    }
    else if (text == "双点线") {
        for (int i = 0; i <= lineTypeWidth; i += 16) {
            painter->drawLine(lineX + i, lineY, lineX + i + 4, lineY);
            painter->drawPoint(lineX + i + 8, lineY);
            painter->drawPoint(lineX + i + 12, lineY);
        }
    }
    else if (text == "三点线") {
        for (int i = 0; i < lineTypeWidth; i += 20) {
            painter->drawLine(lineX + i, lineY, lineX + i + 4, lineY);
            painter->drawPoint(lineX + i + 8, lineY);
            painter->drawPoint(lineX + i + 12, lineY);
            painter->drawPoint(lineX + i + 16, lineY);
        }
    }

    int textX = lineX + lineTypeWidth + padding;
    painter->drawText(textX, opt.rect.y() + (opt.rect.height() + painter->fontMetrics().ascent()) / 2, text);

    painter->restore();
}
