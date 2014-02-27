// $Id: intlglobal.h 4 2012-07-27 12:29:39Z twu $
/*
 * Copyright (C) 2011 China Science & Intelligence Information Technology Co.,Ltd.
 * All rights reserved.
 *
 * Contact: Development Department <devel@cnsiit.com>
 * Author: Joseph Wu <twu@cnsiit.com>
 */

#ifndef FEI_INTLGLOBAL_H
#define FEI_INTLGLOBAL_H

#include <QtCore/QtGlobal>

#ifdef FEI_SHARED_LIBS
#  ifdef FEI_INTL_SOURCE
#    define FEI_INTL_DECL Q_DECL_EXPORT
#  else
#    define FEI_INTL_DECL Q_DECL_IMPORT
#  endif // FEI_INTL_SOURCE
#endif // FEI_SHARED_LIBS

#ifndef FEI_INTL_DECL
#  define FEI_INTL_DECL
#endif

#endif // FEI_INTLGLOBAL_H
