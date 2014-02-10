/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef PREFERENCELISTITEMDELEAGTE_H
#define PREFERENCELISTITEMDELEAGTE_H

#include <QStyledItemDelegate>
#include <QPainter>


class PreferenceListItemDelegate : public QStyledItemDelegate  {
	public:
	PreferenceListItemDelegate(QObject *parent=0) : QStyledItemDelegate (parent){}

	void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const{
		painter->save();
		
		QRect		r;
		if(option.state & QStyle::State_Selected){
			painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));
		}

		QString title = index.data(Qt::DisplayRole).toString();
		QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
		
		QFont    font = painter->font();
		font.setBold(true);
		painter->setFont(font);
		
		r = option.rect.adjusted((200 - painter->fontMetrics().width(title)) / 2, 0, 0, -10);
		painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, title, &r);
		
		QSize 		iconsize = icon.actualSize(option.decorationSize);
		r = option.rect.adjusted((200 - iconsize.width()) / 2, (37 - iconsize.height()) / 2, 0, 0);
		painter->drawPixmap(QPoint(r.left(),r.top()),icon.pixmap(iconsize.width(),iconsize.height()));
		
		painter->restore();
	}
		
	QSize sizeHint ( const QStyleOptionViewItem &, const QModelIndex &) const{
		return QSize(200, 75);
	}
};

#endif // PREFERENCELISTITEMDELEAGTE_H
