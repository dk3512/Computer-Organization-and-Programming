;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000

;; CODE GOES HERE! :D
LD R0, ARRAY; R0 = ARRAY
LD R1, LENGTH; R1 = LENGTH
ADD R2, R0, 0; R2 = address of ARRAY[j], j = k - 1
ADD R3, R0, 1; R2 = address of ARRAY[k]
NOT R6, R0;
ADD R6, R6, 1; 2's complement of ARRAY address

OUTER ADD R1, R1, -1; LENGTH--
BRNZ END; if LENGTH == 0 or LENGTH = -1 go to END because array is sorted
LDR R4, R3, 0; int curr = array[k]

INNER ADD R5, R2, R6; address of ARRAY[j] - address of ARRAY to check if j >= 0
BRN GETOUT; If j < 0 GETOUT of inner loop
LDR R7, R2, 0; ARRAY[j]
NOT R7, R7; NOT ARRAY[j]
ADD R7, R7, 1; ARRAY[j]++ to get 2's complement
ADD R7, R7, R4; curr - ARRAY[j]
BRZP GETOUT; If (curr - ARRAY[j] > 0) GETOUT of inner loop
LDR R7, R2, 0; ARRAY[j]
STR R7, R2, 1; ARRAY[j+1] = ARRAY[j]
ADD R2, R2, -1; j--
BR INNER; Go back to INNER to check conditions

GETOUT STR R4, R2, 1; array[j] = curr
ADD R3, R3, 1; k++
ADD R2, R3, -1; j = k - 1
BR OUTER; go back to OUTER

END HALT


ARRAY   .fill x6000
LENGTH  .fill 12
.end

.orig x6000
.fill 27
.fill -5
.fill -18
.fill -165
.fill -101
.fill -10
.fill -34
.fill 0
.fill -7
.fill -88
.fill -9
.fill -212
.end

