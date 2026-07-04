section .data
    msg db "Hello, Reverse Engineering!", 0x0a
    len equ $ - msg

section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel msg]
    mov rdx, len
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall
