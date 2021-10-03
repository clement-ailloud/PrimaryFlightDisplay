/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "qobject.h"

class LinearGauge;

class QRect;
class QSize;

class LinearGaugePrivate : public QObject
{
    Q_OBJECT

  public:
    LinearGaugePrivate(LinearGauge const* view = nullptr);

  protected:
    // Draw methods
    QRect& getTickPosition(QRect& rect, int thickness, int padding);

  public slots:
    virtual void onSizeChanged(const QSize& size);

  private:
    LinearGauge const* m_view;
};
