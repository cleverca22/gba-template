#include "asm.h"


.section .entry.jmp
FUNCTION(_jumppad)
  b _start
END_FUNCTION(_jumppad)

.section .entry.start
LOCAL_FUNCTION(_start)
  ldr sp, =_stack
  bl irq_on
  bl main
  b .
END_FUNCTION(_start)

.section .text
FUNCTION(__aeabi_unwind_cpp_pr0)
  b .
END_FUNCTION(__aeabi_unwind_cpp_pr0)

FUNCTION(irq_on)
  mrs r0, cpsr
  bic r0, #1<<7
  msr cpsr, r0
  bx lr
END_FUNCTION(irq_on)
