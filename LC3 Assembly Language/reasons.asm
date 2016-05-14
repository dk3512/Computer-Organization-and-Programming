;;===============================
;;Name: Daniel Kim
;;===============================

.orig x3000



;; YOUR CODE HERE! :D
LD R1, N; N = R1
LEA R0, START_MSG_1; address of START_MSG_1 = R0
PUTS; Prints "The "
LEA R2, GRAMMAR_ARR; loads address of GRAMMAR_ARR into R1
ADD R2, R2, R1; Adds address of GRAMMAR_ARR and N
ADD R2, R2, -1; Subtract 1 from N
LDR R0, R2, 0; loads GRAMMAR_ARR[n-1] into R0
PUTS; Prints GRAMMAR_ARR[n-1]
LEA R0, START_MSG_2; START_MSG_2 = R0
PUTS; Prints " reasons I love CS 2110 so far: /n"
LD R2, N; Reset N
LEA R3, MESSAGE_ARR; loads address of MESSAGE_ARR into R3
MESSAGE LDR R0, R3, 0; gets message_arr[i]
PUTS; Prints out the message
ADD R3, R3, 1; i++
ADD R2, R2, -1; N--
BRP MESSAGE; if N == 0 don't loop again


HALT

N .fill 8


START_MSG_1
    .stringz "The "

START_MSG_2
    .stringz " reasons I love CS 2110 so far:\n"

GRAMMAR_ARR
    .fill GRAM01
    .fill GRAM02
    .fill GRAM03
    .fill GRAM04
    .fill GRAM05
    .fill GRAM06
    .fill GRAM07
    .fill GRAM08
    .fill GRAM09
    .fill GRAM10

MESSAGE_ARR
    .fill MESS01
    .fill MESS02
    .fill MESS03
    .fill MESS04
    .fill MESS05
    .fill MESS06
    .fill MESS07
    .fill MESS08
    .fill MESS09
    .fill MESS10
.end

.orig x5000
GRAM01
    .stringz "one"
GRAM02
    .stringz "two"
GRAM03
    .stringz "three"
GRAM04
    .stringz "four"
GRAM05
    .stringz "five"
GRAM06
    .stringz "six"
GRAM07
    .stringz "seven"
GRAM08
    .stringz "eight"
GRAM09
    .stringz "nine"
GRAM10
    .stringz "ten"
MESS01
    .stringz "One, I made this cool program in assembly!\n"
MESS02
    .stringz "Two, the TAs are super helpful!\n"
MESS03
    .stringz "Three, Professor Leahy is an entertaining lecturer!\n"
MESS04
    .stringz "Four, I now know how to prevent electrical fires!\n"
MESS05
    .stringz "Five, bitwise operations are really useful!\n"
MESS06
    .stringz "Six, I can make state machines now!\n"
MESS07
    .stringz "Seven, memory is no longer a mystery!\n"
MESS08
    .stringz "Eight, I understand how a basic computer works now!\n"
MESS09
    .stringz "Nine, I feel more confident with binary and hex!\n"
MESS10
    .stringz "Ten, I'm looking forward to learning C!\n"
.end
