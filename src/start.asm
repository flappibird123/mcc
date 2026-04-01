section .text
global _start

extern main

_start:
    xor ebp, ebp         ; clear frame pointer

    pop rdi              ; rdi = argc
    mov rsi, rsp         ; rsi = argv pointer

    ; calculate envp = argv + argc + 1
    lea rdx, [rsi + rdi*8 + 8]

    and rsp, -16         ; align stack for ABI compliance

    call main            ; rdi=argc, rsi=argv, rdx=envp

    mov rdi, rax         ; move return value of main into rdi
    mov rax, 60          ; syscall: exit
    syscall
    
section .note.GNU-stack

