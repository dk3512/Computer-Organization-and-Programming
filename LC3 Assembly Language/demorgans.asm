;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000

; CODE GOES HERE! :D
LD R0, A; A = R0
NOT R0, R0; A = !A
LD R1, B; B = R1
NOT R1, R1; B = !B
AND R2, R1, R0; answer = A & B
NOT R2, R2; answer = !answer
ST R2, ANSWER; return ANSWER

HALT
	
A       .fill 0
B       .fill 7
ANSWER  .fill 0		; This answer should contain A | B when finished.
.end
