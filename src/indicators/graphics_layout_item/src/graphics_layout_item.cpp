//!
//! @file
//!
//! @brief
//!
//! @date
//!
//! @author     Clement Ailloud
//!



GraphicsLayoutItem::GraphicsLayoutItem(QGraphicsLayoutItem* parent, bool isLayout)
    : QGraphicsLayoutItem(parent, isLayout)
{
}


void GraphicsLayoutItem::setGeometry(const QRectF& geometry)
{
    prepareGeometryChange();

    QGraphicsLayoutItem::setGeometry(geom);

    setPos(geom.topLeft());
}


QSizeF GraphicsLayoutItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
	case Qt::MinimumSize:
	    break;

	case Qt::PreferredSize:
	    return graphicsItem()->boundingRect();

	case Qt::MaximumSize:
	    break;

	default:
	    break;
    }

    return constraint;
}
