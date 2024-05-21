section .text
global call_80h

call_80h:
    mov rax, 4
    mov rbx, 1
    mov rcx, stdout
    mov rdx, stdoutsize
    int 80h

    mov rax, 4
    mov rbx, 2
    mov rcx, stderr
    mov rdx, stderrsize
    int 80h

    ret

section .rodata
stdout db "STDOUT", 0
stdoutsize equ $-stdout
stderr db "STDERR", 0
stderrsize equ $-stderr