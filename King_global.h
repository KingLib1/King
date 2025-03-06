#ifndef KING_GLOBAL_H
#define KING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KING_LIBRARY)
#  define KING_EXPORT Q_DECL_EXPORT
#else
#  define KING_EXPORT Q_DECL_IMPORT
#endif

#endif // KING_GLOBAL_H
