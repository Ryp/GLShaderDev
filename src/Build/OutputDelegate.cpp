/*
 * This file is part of GLShaderDev.
 *
 * GLShaderDev is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GLShaderDev is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GLShaderDev.  If not, see <http://www.gnu.org/licenses/>
 */

#include <QtGui/QPainter>

#include "OutputDelegate.h"
#include "OutputModel.h"

OutputDelegate::OutputDelegate(QObject* parent)
: QItemDelegate(parent) {}

OutputDelegate::~OutputDelegate() {}

void OutputDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem  opt = option;
    QVariant      status = index.data(OutputModel::OutputItemTypeRole);
    QBrush        brush;

    if (status.isValid())
    {
        OutputItem::OutputItemType type = static_cast<OutputItem::OutputItemType>(status.toInt());

        switch (type)
        {
            case OutputItem::ErrorItem:
            {
                brush.setColor(QColor("#BF0303"));
                opt.palette.setBrush(QPalette::Text, brush);
            } break;
            case OutputItem::WarningItem:
            {
                brush.setColor(QColor("#B08000"));
                opt.palette.setBrush(QPalette::Text, brush);
            } break;
            case OutputItem::InformationItem: {
                brush.setColor(QColor("#006E28"));
                opt.palette.setBrush(QPalette::Text, brush);
            } break;
            default:
                break;
        }
    }
    QItemDelegate::paint(painter, opt, index);
}
