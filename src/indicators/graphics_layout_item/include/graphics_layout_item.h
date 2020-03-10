//!
//! @file
//!
//! @brief
//!
//! @date
//!
//! @author     Clement Ailloud
//!


#include "qgraphicslayoutitem.h"


class GraphicsLayoutItem : public QGraphicsLayoutItem
{
    public:

	GraphicsLayoutItem(QGraphicsLayoutItem * parent = 0, bool isLayout = false);

	virtual ~GraphicsLayoutItem() = default;

	void setGeometry(const QRectF& geometry);

	QSizeF sizeHint(Qt::SizeHint which, const QSizeF & constraint = QSizeF()) const override;
};
