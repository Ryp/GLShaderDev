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

#ifndef PREFERENCELISTITEMDELEAGTE_H
#define PREFERENCELISTITEMDELEAGTE_H

#include <QStyledItemDelegate>
#include <QPainter>


class PreferenceListItemDelegate : public QStyledItemDelegate  {
    public:
	PreferenceListItemDelegate(QObject *parent=0);

	void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	QSize sizeHint ( const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // PREFERENCELISTITEMDELEAGTE_H
