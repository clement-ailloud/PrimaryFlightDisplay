/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#ifndef TEXT_ITEM_H
#define TEXT_ITEM_H

#include "qfont.h"
#include "qrect.h"
#include "qstring.h"

#include "Qt"

class TextItem;

void drawTextItem(QPainter& painter, TextItem& item);
void drawTextItem(QPainter& painter, int x, int y, TextItem& item);

/**
 * @brief   Encapsulates a text and its properties like font and alignment within an item
 */

class TextItem
{
  public:
    TextItem();
    explicit TextItem(QString text, QFont font = QFont());

    Qt::Alignment alignment() const;
    void setAlignment(Qt::Alignment alignment);

    const QRect& boundingRect() const;
    QSize size() const;
    int height() const;
    int width() const;

    const QFont& font() const;
    void setFont(QFont font);

    QPoint position() const;
    void setPosition(const QPoint& position);

    const QString& text() const;
    void setText(const QString& text);

    TextItem& operator=(const QString& text)
    {
        if (text == m_text)
            return *this;

        m_text = text;
        return *this;
    }

  private:
    QString m_text;
    QFont m_font;
    QRect m_fontRect;
    Qt::Alignment m_alignment;
};

#endif
