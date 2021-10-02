/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "text_item/text_item.h"

#include "indicator/indicator_functions.h"

#include "qdebug.h"
#include "qpainter.h"

void drawTextItem(QPainter& painter, TextItem& item)
{
    painter.drawText(item.boundingRect(), item.alignment(), item.text());
}

void drawTextItem(QPainter& painter, int x, int y, TextItem& item)
{
    painter.drawText(x, y, item.width(), item.height(), item.alignment(), item.text());
}

TextItem::TextItem() = default;

TextItem::TextItem(QString text, QFont font)
    : _text(std::move(text)), _font(std::move(font))
{
    adjusted(_fontRect, _text, _font);

    qDebug() << _fontRect;
}

Qt::Alignment TextItem::alignment() const
{
    return _alignment;
}

void TextItem::setAlignment(Qt::Alignment alignment)
{
    _alignment = alignment;
}

const QString& TextItem::text() const
{
    return _text;
}

void TextItem::setText(const QString& text)
{
    if (text == _text)
    {
        return;
    }

    _text = text;
    _fontRect = adjusted(_fontRect, _text, _font);
}

const QFont& TextItem::font() const
{
    return _font;
}

void TextItem::setFont(QFont font)
{
    if (font == _font)
    {
        return;
    }

    _font = std::move(font);
    adjusted(_fontRect, _text, _font);
}

QPoint TextItem::position() const
{
    return _fontRect.topLeft();
}

void TextItem::setPosition(const QPoint& position)
{
    _fontRect.setTopLeft(position);
}

int TextItem::width() const
{
    return _fontRect.width();
}

int TextItem::height() const
{
    return _fontRect.height();
}

const QRect& TextItem::boundingRect() const
{
    return _fontRect;
}

QSize TextItem::size() const
{
    return _fontRect.size();
}
