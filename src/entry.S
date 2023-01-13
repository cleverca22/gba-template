.global _start

.section .entry.jmp
_jumppad:
  b _start

.section .entry.start
_start:
  ldr sp, =_stack
  bl main
  b .

.section .text
.global __aeabi_unwind_cpp_pr0
__aeabi_unwind_cpp_pr0:
  b .

.global putchar
putchar:
  ldr r1, =0x1234
  bx lr

