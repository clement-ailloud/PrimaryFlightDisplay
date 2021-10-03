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
    : m_text(std::move(text))
    , m_font(std::move(font))
{
    adjusted(m_fontRect, m_text, m_font);
}

Qt::Alignment TextItem::alignment() const
{
    return m_alignment;
}

void TextItem::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
}

const QString& TextItem::text() const
{
    return m_text;
}

void TextItem::setText(const QString& text)
{
    if (text == m_text)
    {
        return;
    }

    m_text = text;
    m_fontRect = adjusted(m_fontRect, m_text, m_font);
}

const QFont& TextItem::font() const
{
    return m_font;
}

void TextItem::setFont(QFont font)
{
    if (font == m_font)
    {
        return;
    }

    m_font = std::move(font);
    adjusted(m_fontRect, m_text, m_font);
}

QPoint TextItem::position() const
{
    return m_fontRect.topLeft();
}

void TextItem::setPosition(const QPoint& position)
{
    m_fontRect.moveTopLeft(position);
}

int TextItem::width() const
{
    return m_fontRect.width();
}

int TextItem::height() const
{
    return m_fontRect.height();
}

const QRect& TextItem::boundingRect() const
{
    return m_fontRect;
}

QSize TextItem::size() const
{
    return m_fontRect.size();
}
