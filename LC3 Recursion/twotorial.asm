;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000

	LD R6, STACK			; load the stack pointer

	LD R0, N				; R0 = N
	ADD R6, R6, -1			; push argument N on stack
	STR R0, R6, 0			

	JSR TWOTORIAL

	LDR R0, R6, 0			; load return value off top of stack
	ADD R6, R6, 2 			; restore stack to previous value

	ST R0, ANSWER			; store answer
	HALT

N 		.fill 6
ANSWER 	.blkw 1
STACK 	.fill xF000


TWOTORIAL
	; your code here!
	ADD R6, R6, -3			; Move R6 up for stack frame
	STR R7, R6, 1			; Store return address
	STR R5, R6, 0			; Store old frame pointer
	ADD R5, R6, -1			; Set new frame pointer

	LDR R0, R5, 4			; if (n <= 0)
	BRP ELSE
	
	AND R0, R0, 0			; return 0
	STR R0, R5, 3
	BR RETURN

ELSE
	ADD R0, R0, -2			; Push n - 2 for recursive call
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR TWOTORIAL

	LDR R0, R6, 0			; Pop answer and param (N-2) off stack
	ADD R6, R6, 2			
	
	LDR R1, R5, 4			; Get N into R1
	ADD R0, R0, R1			; retval = N + twotorial(N - 2)
	STR R0, R5, 3		
	

RETURN
	ADD R6, R5, 3			; set R6 to point to return value
	LDR R7, R5, 2			; restore return address
	LDR R5, R5, 1			; restore old frame pointer
	RET
	
.end
