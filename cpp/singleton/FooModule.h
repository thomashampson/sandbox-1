#ifndef FOO_MODULE_H
#define FOO_MODULE_H

#ifdef foo_EXPORTS
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#else
#define DLL_PUBLIC
#endif

#endif // FOO_MODULE_H
