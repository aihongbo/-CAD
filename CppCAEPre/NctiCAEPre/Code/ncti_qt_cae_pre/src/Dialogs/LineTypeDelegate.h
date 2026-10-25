#pragma once

#include <QStyledItemDelegate>

class LineTypeDelegate : public QStyledItemDelegate
{
public:
    explicit LineTypeDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
