;
;
;
.ORIG x3000

;your code goes here
;Introduction
;Partner: staceyl2
;This program functions as a stack calculator, when the program is done it should have printed all the typed characters and the hexadecimal value of the function result. In the cases of invalid characters or if the number operator and operands does not add up, the program would output "invalid expression". Space inputs are allowed but negative inputs are not. This program tackles stack underflow but not overflow, in the case of underflow, "invalid expression" would also be printed.
;The expression that this program deals with should be in postfix experssions format, this serves to simulate how stack actually does its calculation because it is LIFO.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Receive and echo the input character from console. Determintes if the input is space, operator, operand, equal sign, or invalid, and act accordingly.

;R0 - character input from keyboard
;R1 - temporary register
;R2 - temporary register
;R3 - temporary register and STACK_TOP pointer
;R4 - Stores STACK_START
EVALUATE

;your code goes here


	
GETC	; Read the value of input character into R0
OUT	; Print character out on screen

NOT R1, R0 ; Negate R0 and store in temporary registor R1
ADD R1, R1, #1; 
LEA R2, EQUAL ; load EQUAL address to R2
LDR R3, R2, #0	; Load EUQAL value to R3
ADD R1, R1, R3; R1 = equal sign ascii - input
BRnp CHECK_SPACE


LD  R4, STACK_START			; Load STACK_START to R2
LD R3, STACK_TOP			; Load STACK_TOP to R2
NOT R3, R3					; Negate R3
ADD R3, R3, #1				; R3= R3 + 1
ADD R4, R4, R3				; R4 = R4 + R3
ADD R4, R4, #-1				; R4 = R4 - 1
BRnp INVALID				; If isn't zero, shift to INVALID 


BRnzp PRINT_HEX					; Shift to PRINT_HEX


CHECK_SPACE

NOT R1, R0 				; Negate R0 and store in temporary registor R1
ADD R1, R1, #1			; 
LEA R2, SPACE 			; load SPACE address to R2
LDR R2, R2, #0			; Load SPACE value to R2
ADD R1, R1, R2 			; R1 = space sign ascii - input
BRz EVALUATE			; If encounter space, loop back to EVALUATE

CHECK_VALID

NOT R1, R0 				; Negative R0 and store in temporary registor R1
ADD R1, R1, #1			; 
LEA R2, COMMA 			; load COMMA address to R2
LDR R2, R2, #0			; Load COMMA value to R2
ADD R1, R1, R2			; r1 = comma sign ascii -input
BRz INVALID				; Invalid if ","

NOT R1, R0 				; Negative R0 and store in temporary registor R1
ADD R1, R1, #1			; 
LEA R2, DOT				; load DOT address to R2
LDR R2, R2, #0			; Load DOT value to R2
ADD R1, R1, R2			; r1 = dot sign ascii -input
BRz INVALID				; Invalid if "."

LEA R2, NEG_EXP 		; load NEG_EXP address to R2
LDR R2, R2, #0			; Load NEG_EXP value to R2
ADD R1, R0, R2			; R1 = R0 - "^"
BRz OPERATOR			; Shift to OPERATOR if "^" detected

LEA R2, NEG_MUL 		; load NEG_MUL address to R2
LDR R2, R2, #0			; Load NEG_MUL value to R2
ADD R1, R0, R2 			; R1 = R0- "*" sign value
BRn INVALID 			; Invalid if before "*"
LEA R2, NEG_NINE 		; load NEG_NINE address to R2
LDR R2, R2, #0			; Load NEG_NINE value to R2
ADD R1, R0, R2 			; R1 =  R0 - "9" value
BRp INVALID				; Invalid if after "9"

LEA R2, NEG_ZERO 		; load NEG_ZERO address to R2
LDR R2, R2, #0			; Load NEG_ZERO value to R2
ADD R1, R0, R2			; R1 = R0 - "0"
BRn OPERATOR			; If before "0" shift to OPERATOR

LEA R3, SWITCH			; Load SWITCH address into R3
LDR R3, R3, #0			; Load SWITCH value to R3
ADD R0, R0, R3			; SUbtract the output value R0 by SWITCH value in order to get actual integers

JSR PUSH 
ADD R0, R0, #0		; Check status without changing value
BRnzp EVALUATE ; Go back to read new input after PUSH

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Branches here when encounters invalid character inputs, stack underflow, or if the total number of operands and operators don't add up
;R0 - temprary register for storing address of "invalid expression"

INVALID
LEA R0, INVALID_LINE		; Load INVALID_LINE address into R0
PUTS						; Print "invalid expression" in console
ADD R0, R0, #0
BRnzp DONE						; End program


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Branches here if receive operator input
;POPs two numbers and identify the operator, prepares number to branch to specific operator subroutine

OPERATOR

ST R0, SAVE_OPERATOR 	; Save R0 if it's operator
JSR POP 				; Jump to POP
LDI R4, STACK_TOP		; Save first POP value in R4
JSR POP					; Jump to POP
LDI R3, STACK_TOP		; Save second POP value in R3

LD R0, SAVE_OPERATOR	; Restore R0 operator

LEA R2, NEG_PLUS		; Load NEG_PLUS address into R2
LDR R2, R2, #0			; Load NEG_PLUS value to R2
ADD R1, R0, R2			; R1 = R0 - "+"
BRz PLUS				; Shift to PLUS if "+" detected

LEA R2, NEG_MINUS		; Load NEG_MINUS address into R2
LDR R2, R2, #0			; Load NEG_MINUS value to R2
ADD R1, R0, R2			; R1 = R0 - "-"
BRz MIN					; Shift to PLUS if "-" detected

LEA R2, NEG_MUL			; Load NEG_MUL address into R2
LDR R2, R2, #0			; Load NEG_MUL value to R2
ADD R1, R0, R2			; R1 = R0 - "*"
BRz MUL					; Shift to MUL if "*" detected

LEA R2, NEG_DIV			; Load NEG_DIV address into R2
LDR R2, R2, #0			; Load NEG_DIV value to R2
ADD R1, R0, R2			; R1 = R0 - "/"
BRz DIV					; Shift to PLUS if "/" detected
	
LEA R2, NEG_EXP			; Load NEG_EXP address into R2
LDR R2, R2, #0			; Load NEG_EXP value to R2
ADD R1, R0, R2			; R1 = R0 - "^"
BRz EXP					; Shift to EXP if "^" detected





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Print result in hexadecimal format in the console
;R5- value to print in hexadecimal
PRINT_HEX

AND R1, R1, #0			; Clear R1 for temp digit counter
ADD R1, R1, #4			; Load 4 into R1

PRINT_DIGIT

AND R3, R3, #0			; Clear out digit for upper 4 bit
ADD R2, R3, #4			; Set up counter R2 with 4 bits left to read

READ_BIT
ADD R3, R3, R3			; make room in digit for the next coming bit
ADD R5, R5, #0			; Read status
BRzp SHIFT				; Branch to skip adding 1 if not negative

ADD R3, R3, #1			; Shift in 1 to digit

SHIFT
ADD R5, R5, R5			; Leftshift R5
ADD R2, R2, #-1			; Decrement counter
BRp READ_BIT			; If positive, loop back to read new bit

LEA R4, CHARMAP			; Load address of character map into R4
ADD R4, R4, R3			; Add character offset to R4
LDR R3, R4, #0			; fetch character
ADD R0, R3, #0			; Put output in R0

OUT

ADD R1, R1, #-1			; decrement digit counter
BRp PRINT_DIGIT			; If positive, loop to print new digits

ADD R1, R1, #0			; Check status
BRnzp DONE				; DONE


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

ADD R0, R3, R4		; Store the sum of R3, R4 in R0
BRnzp RESULT		; Shift to RESULT

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

NOT R4, R4		; Negate R4
ADD R4, R4, #1	; R4 = R4 + 1
ADD R0, R3, R4	; R0 = R3 - R4 (original)
BRnzp RESULT	; Shift to RESULT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
AND R0, R0, #0		; Clear R0
ADD R4, R4, #0
BRz RESULT
ADD R4, R4, #0		; Check status without changing
BRp MULTP			; If positive branch to MULTP
ADD R4, R4, #0		; Check status without changing
BRn MULTN			; If negative branch to MULTN


MULTP
ADD R0, R3, R0		; R0 = R3 + R0
ADD R4, R4, #-1		; Decrement count
BRp MULTP
ADD R4, R4, #0		; Check status without changing
BRnzp RESULT

MULTN
ADD R0, R3, R0		; R0 = R3 + R0
ADD R4, R4, #1		; Increment count
BRn MULTN
ADD R4, R4, #0		; Check status without changing
NOT R0, R0			; Negate R0
ADD R0, R0, #1
BRnzp RESULT		; Shift to RESULT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here

AND R0, R0, #0		; Clear R0
ADD R4, R4, #-1		; R4 = R4-1
NOT R4, R4			; R4 = -R4

DIVLOOP
ADD R0, R0, #1		; Increment quocient
ADD R3, R3, R4		; Subtract divisor R4 from dividend R3
BRzp DIVLOOP		; loop back

ADD R0, R0, #-1		; If went too far decrease the quocient by 1
NOT R4, R4			; Recover R4
ADD R4, R4, #1		; Recover R4
BRnzp RESULT
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

AND R0, R0, #0		; Clear R0
ADD R4, R4, #0	; Decrement exponent counter
BRz RESULT			; If original R4 = 0, Shift to RESULT
ADD R5, R4, #-1		; Check R5 value
BRp EXPLOOP			; If original R4 >1, Shift to RESULT
ADD R0, R0, #1		; Otherwise (case original R4 = 1), R0 = 1
BRp RESULT			; Shift to RESULT

EXPLOOP 
ADD R0, R0, R3		; Load R3 value into R0
ADD R2, R2, R3		; Load R3 into R2 for counter
ADD R2, R2, #-1		; Use R2 as counter, R2 = R2-1
BRp EXPLOOP			; If counter is positive, loop back to EXPLOOP

ADD R4, R4, #-1		; Decrement exponent counter
BRz RESULT 			; If zero, SHift to RESULT

LOOPONE
ADD R5, R0, #0		; set R5 = R0 as the new counter
AND R0, R0, #0		; Clear R0

LOOPTWO
ADD R0, R0, R3		; R0 = R0 + R3
ADD R5, R5, #-1		; Decrement R5 counter
BRp LOOPTWO			; If counter is positive, loop back to LOOPTWO
ADD R4, R4, #-1		; Decrement R4 exponent counter
BRz RESULT			; If zero, Shift to RESULT
BRnzp LOOPONE		; Loop bakc to LOOPONE


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Branches here after operating the two numbers with their operator with result incoming as R0
;Loads result in R5 and moves on to next input

RESULT
JSR PUSH				; PUSH result on stack
ADD R5, R0, #0			; R5 = R0
BRnzp EVALUATE			; Move on to next character input


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;

PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
	BRnzp INVALID
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


DONE

HALT					;Stop program

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;

EQUAL .FILL x003D		; "=" ASCII
SPACE .FILL x0020		; " " ASCII
COMMA .FILL x002C		; "," ASCII
DOT   .FILL x002E		; "." ASCII

NEG_NINE .FILL #-57		; neg "9" ASCII
NEG_ZERO .FILL #-48		; neg "0" ASCII
NEG_MUL .FILL #-42		; neg "*" ASCII
NEG_PLUS	.FILL #-43	; neg "+" ASCII
NEG_MINUS	.FILL #-45	; neg "-" ASCII
NEG_DIV		.FILL #-47	; neg "/" ASCII
NEG_EXP		.FILL #-94	; neg "^" ASCII
SAVE_OPERATOR .BLKW #1	; Save R0 if it's operator
SWITCH		.FILL xFFD0	; Used to subtract from a number character ASCII value to switch them to actual integers
INVALID_LINE .STRINGZ "invalid expression"
CHARMAP .STRINGZ "0123456789ABCDEF"
.END
