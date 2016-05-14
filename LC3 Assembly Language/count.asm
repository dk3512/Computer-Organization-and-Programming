;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000

; CODE GOES HERE! :D
LD R0, ANSWER; ANSWER = R0
LD R1, ARRAY; int k = 0
LD R2, LENGTH; LENGTH = R2
AND R3, R3, 0; int count = 0
GETNUM LDR R4, R1, 0; array[k] = R4
BRZP INCK; if array[k] is not negative, just increment k
ADD R3, R3, 1; count++
INCK ADD R1, R1, 1; k++
ADD R2, R2, -1; LENGTH--
BRP GETNUM; if LENGTH == 0 don't loop again
ST R3, ANSWER; ANSWER = count

HALT

	
ARRAY   .fill x6000
LENGTH  .fill 10
ANSWER	.fill 0		; The answer should have the number of negative values when finished.
.end

.orig x6000
.fill -20
.fill 14
.fill 7
.fill 0
.fill -3
.fill -11
.fill -9
.fill -9
.fill -2
.fill -5
.end
