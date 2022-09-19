#ifndef HOOKS_GLOBAL_H
#define HOOKS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HOOKS_LIBRARY)
#  define HOOKS_EXPORT Q_DECL_EXPORT
#else
#  define HOOKS_EXPORT Q_DECL_IMPORT
#endif

#endif // HOOKS_GLOBAL_H
