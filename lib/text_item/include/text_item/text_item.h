/**
* @file
*
* @brief
*
* @date
*
* @author     Clement Ailloud
*/

#include "qstring.h"
#include "qrect.h"
#include "qfont.h"

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

    // TODO: remove from class
    QPoint position() const;
    void setPosition(const QPoint& position);

    const QString& text() const;
    void setText(const QString& text);

    TextItem& operator=(const QString& text)
    {
        if (text == _text)
            return *this;

        _text = text;
        return *this;
    }

private:
    QString _text;
    QFont _font;
    QRect _fontRect;
    Qt::Alignment _alignment;
};
