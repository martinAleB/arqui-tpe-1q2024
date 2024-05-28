GLOBAL syscall

SECTION .text

syscall:
    push rbx
    mov rax, rdi
    mov rbx, rsi
    int 80h
    pop rbx
    ret
    