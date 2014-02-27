// $Id: intl.h 4 2012-07-27 12:29:39Z twu $
/*
 * Copyright (C) 2011 China Science & Intelligence Information Technology Co.,Ltd.
 * All rights reserved.
 *
 * Contact: Development Department <devel@cnsiit.com>
 * Author: Joseph Wu <twu@cnsiit.com>
 */

#ifndef FEI_INTL_H
#define FEI_INTL_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include "intlglobal.h"

QT_BEGIN_NAMESPACE
class QLocale;
QT_END_NAMESPACE

namespace Fei {

class IntlPrivate;

class FEI_INTL_DECL Intl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString translationsPath READ translationsPath WRITE setTranslationsPath)

public:
    explicit Intl(QObject* parent = 0);
    virtual ~Intl();

    QString translationsPath() const;
    void setTranslationsPath(const QString& translationsPath);

    bool installSystemLanguage();
    bool installLanguage(const QLocale& locale);
    bool installLanguage(const QString& language);

    bool installTranslators();
    void removeTranslators();

private:
    IntlPrivate* const d_ptr;

    Q_DECLARE_PRIVATE(Intl)
    Q_DISABLE_COPY(Intl)
};

} // namespace Fei

#endif // FEI_INTL_H
