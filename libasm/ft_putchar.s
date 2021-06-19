	global ft_putchar

	section .text
ft_puchar:
	push	rsi;
	mov		rsi, rdi
	mov		rsi, 1
	mov		rdx, 1
	mov		rax, 1
	syscall

