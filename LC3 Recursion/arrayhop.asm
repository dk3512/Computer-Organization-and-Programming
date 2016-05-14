;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000

	LD R6, STACK			; load the stack pointer

	AND R0, R0, 0
	ADD R6, R6, -1			; push argument idx=0 on stack
	STR R0, R6, 0 

	LD R0, ARRAY3			; R0 = ARRAY1, change later to ARRAY2 and ARRAY3 for testing
	ADD R6, R6, -1 			; allocate spot on stack
	STR R0, R6, 0			; push argument ARRAY on stack

	JSR ARRAYHOP

	LDR R0, R6, 0			; load return value off top of stack
	ADD R6, R6, 3 			; restore stack to previous value

	ST R0, ANSWER			; store answer
	HALT

ARRAY1 	.fill x5000
ARRAY2	.fill x5010
ARRAY3  .fill x5020
ANSWER 	.blkw 1
STACK 	.fill xF000


ARRAYHOP
	; your code here!
	ADD R6, R6, -3			; Move R6 up for stack frame
	STR R7, R6, 1			; Store return address
	STR R5, R6, 0			; Store old frame pointer
	ADD R5, R6, -1			; Set new frame pointer

	ADD R6, R6, -1			; Store local variable n = array[idx] by...
	LDR R1, R5, 5			; Load index
	LDR R0, R5, 4			; Load array address
	ADD R1, R0, R1			; Get array[idx]
	LDR R0, R1, 0	
	STR R0, R5, 0

	ADD R0, R0, 0			; if (n==0)
	BRNP ELSE

	AND R0, R0, 0			; return 0
	STR R0, R5, 3
	BR RETURN

ELSE
	LDR R2, R5, 5			; Push idx + n for recursive call by... Get idx
	LDR R1, R5, 0			; Get n
	ADD R0, R1, R2			; Get idx + n
	ADD R6, R6, -1
	STR R0, R6, 0

	LDR R2, R5, 4			; Push array for recursive call
	ADD R6, R6, -1
	STR R2, R6, 0

	JSR ARRAYHOP

	LDR R0, R6, 0			; Pop answer and params (idx + n and array) off stack
	ADD R6, R6, 3

	AND R1, R1, 0			; Get 1 into R1
	ADD R1, R1, 1
	ADD R0, R1, R0			; retval = 1 + arrayhop(array, idx + n)
	STR R0, R5, 3

RETURN
	ADD R6, R5, 3			; set R6 to point to return value
	LDR R7, R5, 2			; restore return address
	LDR R5, R5, 1			; restore old frame pointer
	RET
.end

; 4 hops
.orig x5000
.fill 2
.fill 1
.fill 3
.fill 0
.fill -1
.fill -1
.end

; 5 hops
.orig x5010
.fill 1
.fill 1
.fill 1
.fill 3
.fill 0
.fill -12
.fill -2
.end

; 12 hops
.orig x5020
.fill 5
.fill 1
.fill 0
.fill -3
.fill 10
.fill -1
.fill 5
.fill 20
.fill 2
.fill 3
.fill 1
.fill -2
.fill 9
.fill 14
.fill 3
.fill 20
.fill -2
.fill -7
.fill 5
.fill 1
.fill -18
.fill -2
.end
