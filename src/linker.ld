MEMORY {
  ewram (w!x) : ORIGIN = 0x02000000, LENGTH = 256K
  iwram (w!x) : ORIGIN = 0x03000000, LENGTH = 32K
  rom (rx)    : ORIGIN = 0x08000000, LENGTH = 32M
}

SECTIONS {
  .text : {
    _text_begin = .;
    KEEP(*(.entry.jmp))
    KEEP(*(.entry.header))
    *(.entry.start)
    *(.text)
    *(.text.*)
    _text_end = .;
  } > rom

  .rodata : {
    *(.rodata)
    *(.rodata.*)
  } > rom

  .data : {
    *(.data)
  } > iwram AT > rom

  .stack : {
    _stack_bottom = .;
    . = . + 1024;
    _stack = .;
  } > iwram

  /DISCARD/ : {
    *(.ARM.exidx)
  }
}
