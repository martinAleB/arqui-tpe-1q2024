GLOBAL cpuVendor
GLOBAL getKeyPressed
GLOBAL outb
GLOBAL inb
GLOBAL saveRegisters

EXTERN makeBackup

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

; Puede ir en otro archivo
getKeyPressed:
	push rbp
	mov rbp, rsp

    mov rax, 0

.cicle:
	in al, 64h
    and al, 0x01
    je .cicle
    in al, 60h

	mov rsp, rbp
	pop rbp
    ret

saveRegisters:
	enter 0,0
	mov [regsArr], rax
	mov [regsArr + 1*8], rbx
	mov [regsArr + 2*8], rcx
	mov [regsArr + 3*8], rdx
	mov [regsArr + 4*8], rsi
	mov [regsArr + 5*8], rdi
	mov [regsArr + 6*8], rbp
	mov [regsArr + 7*8], r8
	mov [regsArr + 8*8], r9
	mov [regsArr + 9*8], r10
	mov [regsArr + 10*8], r11
	mov [regsArr + 11*8], r12
	mov [regsArr + 12*8], r13
	mov [regsArr + 13*8], r14
	mov [regsArr + 14*8], r15
	mov [regsArr + 15*8], rsp
	mov rax, [rsp]    				;RIP
    mov [regsArr + 16*8], rax
    mov rax, [rsp+8]  				;RFLAGS
    mov [regsArr + 17*8], rax
	
	mov rdi, regsArr
	call makeBackup
	leave
	
	ret

outb:
	mov rdx, rdi
	mov rax, rsi
	out dx, al
	ret

inb:
	mov rdx, rdi
	in al, dx
	ret

section .bss
    regsArr: resb 144