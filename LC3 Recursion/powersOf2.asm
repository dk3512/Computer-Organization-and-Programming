;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000
	; your code here, you need to implement the caller for this one!
	LD R6, STACK			; Initialize Stack
	
	LD R0, N			; Call powersOf2(int n)
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR POWERSOF2

	LDR R0, R6, 0			; Pop return value and arg off stack
	ADD R6, R6, 2

	ST R0, ANSWER			; Save the answer

	HALT

N 		.fill 5
ANSWER 	.blkw 1
STACK 	.fill xF000


POWERSOF2
	; your code here!
	ADD R6, R6, -3			; Move R6 up for stack frame
	STR R7, R6, 1			; Store return address
	STR R5, R6, 0			; Store old frame pointer
	ADD R5, R6, -1			; Set new frame pointer
	
	ADD R6, R6, -2			; Store two local variables
	AND R1, R1, 0			; int temp1 = 0 
	AND R2, R2, 0			; int temp2 = 0
	STR R1, R5, 0
	STR R2, R5, -1
	
	LDR R0, R5, 4			; if (n == 0)
	BRZ RETURN1

	AND R3, R3, 0			; if (n == 1) by...
	ADD R3, R3, 1
	NOT R3, R3			; get two's complement
	ADD R3, R3, 1
	ADD R0, R0, R3			; n - 1
	BRZ RETURN2

	LDR R0, R5, 4			; temp1 = powersOf2(n-1) by ...
	ADD R0, R3, R0			; Push n - 1 for recursive call
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR POWERSOF2

	LDR R0, R6, 0			; Pop answer into R0 so R0 = temp1
	ADD R6, R6, 2
	STR R0, R5, 0			; Store answer into local variable temp1

	LDR R1, R5, 4			; temp2 = powersof2(n-2) by ...
	AND R3, R3, 0			; 2's complement of 2 to get -2
	ADD R3, R3, 2
	NOT R3, R3
	ADD R3, R3, 1	
	ADD R1, R3, R1			; Push n - 2 for recursive call
	ADD R6, R6, -1
	STR R1, R6, 0
	JSR POWERSOF2

	LDR R1, R6, 0			; Pop answer into R1 so R1 = temp 2
	ADD R6, R6, 2
	STR R1, R5, -1			; Store answer into local variable temp2

	LDR R0, R5, 0			; temp1 = R0
	LDR R1, R5, -1			; temp2 = R1
	ADD R2, R0, R0			; return 3 * temp1 - 2 * temp2 by...
	ADD R2, R2, R0			; 3 * temp1
	ADD R3, R1, R1			; 2 * temp2
	NOT R3, R3
	ADD R3, R3, 1			; -2 * temp2 by two's complement
	ADD R0, R2, R3			; retval = 3 * temp1 - 2 * temp2
	STR R0, R5, 3	
	BR RETURN
	


RETURN1
	AND R0, R0, 0			; return 1
	ADD R0, R0, 1
	STR R0, R5, 3
	BR RETURN

RETURN2
	AND R0, R0, 0			; return 2
	ADD R0, R0, 2
	STR R0, R5, 3
	BR RETURN

RETURN
	ADD R6, R5, 3			; set R6 to point to return value
	LDR R7, R5, 2			; restore return address
	LDR R5, R5, 1			; restore old frame pointer
	RET
.end
