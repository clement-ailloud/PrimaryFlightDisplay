
#include "aircraft_symbol.h"

#include "QStyleOptionGraphicsItem"
#include "qpainter.h"
#include "qwidget.h"


AircraftSymbol::AircraftSymbol()
{
}


AircraftSymbol::AircraftSymbol(const AircraftSymbol& symbol)
{
}


AircraftSymbol::~AircraftSymbol()
{
}


void AircraftSymbol::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


}
