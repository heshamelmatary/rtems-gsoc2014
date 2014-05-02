.file "start.S"

.globl  _start

.extern main

_start:
l.addi    r0,r0,5
l.jal	main
