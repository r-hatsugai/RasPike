
#ifdef __cplusplus
extern "C" {
#endif

// #ifndef APP_H
// #define APP_H

#include "ev3api.h"

#define MAIN_PRIORITY    (TMIN_APP_TPRI + 1)
#define TRACER_PRIORITY  (TMIN_APP_TPRI + 2)
#define DEBRIS_PRIORITY  (TMIN_APP_TPRI + 3)
#define SMARTCARRY_PRIORITY  (TMIN_APP_TPRI + 4)

#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void tracer_task(intptr_t exinf);
extern void debris_task(intptr_t exinf);
extern void smartcarry_task(intptr_t exinf);
extern void tracer_cyc(intptr_t exinf);
extern void debris_cyc(intptr_t exinf);
extern void smartcarry_cyc(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
