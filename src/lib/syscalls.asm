global _write
global _exit
_write:
    mov rax, 1
    syscall
    ret

_exit:
    mov rax, 60
    syscall

section .note.GNU-stack

