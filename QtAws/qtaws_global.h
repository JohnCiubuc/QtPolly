#ifndef QTAWS_GLOBAL_H
#define QTAWS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTAWS_LIBRARY)
#  define QTAWSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTAWSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTAWS_GLOBAL_H
