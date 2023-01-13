#include "asm.h"


.section .entry.jmp
FUNCTION(_jumppad)
  b _start
END_FUNCTION(_jumppad)

.section .entry.start
LOCAL_FUNCTION(_start)
  ldr sp, =_stack
  bl main
  b .
END_FUNCTION(_start)

.section .text
FUNCTION(__aeabi_unwind_cpp_pr0)
  b .
END_FUNCTION(__aeabi_unwind_cpp_pr0)
