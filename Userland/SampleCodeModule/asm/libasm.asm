GLOBAL syscall
GLOBAL throw_invalid_opcode

SECTION .text

syscall:
    push rbx
    mov rax, rdi
    mov rbx, rsi
    int 80h
    pop rbx
    ret
    
throw_invalid_opcode:
    ud2
    ret
