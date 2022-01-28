;partners netid : zijunz6, staceyl2
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; partner netid: zijunz6, staceyl2

; This part of the program prints out the histogram to the console. 
; In the PRINTING_LOOP, the character is computed (ASCII of '@' + counter 
; of how many characters have been printed) and printed by putting the
; computed ASCII value into R0. Then a space is printed by putting ASCII
; value of a space into R0. For the frequency of the corresponding character,
; the correct address is computed using the start of the histogram plus the 
; counter of how many lines have been printed. The content is put into R2,
; and the corresponding four hexadecimal characters are printed by shifting 
; four values of R2 into R0 and compute the correct ASCII based on number
; and alphabet. After 27 iterations of the PRINTING_LOOP, the histogram is
; printed to the console. 

; table of register use in this part of the code
;    R0 holds the character to be printed 
;    R1 holds the starting address of the histogram
;    R2 holds the frequency of the current character in hexadecimal
;    R3 holds the zero-indexed line number we are printing
;    R4 holds the counter for intializing R0 during printing
;    R5 holds the counter for printing 4 hexadecimal to represent frequency of each character
;    R6 is used as a temporary register

  LD  R1,HIST_ADDR   ; load the starting address of histogram into R1
  AND R3,R3,#0       ; clear R3

PRINTING_LOOP        ; this loop will run 27 times to print 27 bins
  LD  R6,AT          ; load ASCII value of '@' into R6
  ADD R0,R3,R6       ; compute the character being printed and load it to R0
  OUT                ; print character

  LD  R0,SPACE       ; load ASCII value of a space into R0
  OUT                ; print character

  AND R5,R5,#0       ; clear R5
  ADD R5,R5,#4       ; initialize R5 to 4 to count how many numbers have been printed
  ADD R6,R1,R3       ; compute the correct address containing frequency of the character being printed 
  LDR R2,R6,#0       ; load the frequency into R2
FREQUENCY_LOOP       ; this loop prints out the corresponding hexadecimal value of R2 into console
  AND R0,R0,#0       ; clear R0
  AND R4,R4,#0       ; clear R4
  ADD R4,R4,#4       ; initialize R4 as to 4 to correctly shift four bits of R2 into R0
R0_LOOP              ; this loop is iterated 4 times for each hexadecimal value to be shifted into R0
  ADD R2,R2,#0       ; clear R2
  BRzp MSB_ZERO      ; if the most significant bit is 0, don't add 1 to R0
  ADD R0,R0,#1       ; add 1 to R0 if the most significant bit is 1
MSB_ZERO
  ADD R2,R2,R2       ; left shift R2
  ADD R4,R4,#-1      ; decrement the counter to indicate one more bit has been shifted
  BRz R0_INITIALIZED ; if R4 = 0, it means R0 is initialized and ready to be printed
  ADD R0,R0,R0       ; left shift R0 to copy more bits from R2
  BR R0_LOOP         ; go through R0_LOOP again to copy more bits

R0_INITIALIZED       ; R0 should be initialized and contain one hexadecimal value to be printed by now
  ADD R6,R0,#-9      ; check if R0 is a number or an alphabet
  BRp A_TO_F         ; if R0 > 9, it's an alphabet, else it's a number

ZERO_TO_NINE         ; when R0 is 0-9,
  LD  R6,ZERO        ; load ACSII of '0' into R6
  BR  PRINT_HEX      ; jump to print R0 now
A_TO_F               ; when R0 is A-F,
  LD  R6,A           ; load ASCII of 'A' into R6
  ADD R0,R0,#-10     ; correctly compute the character's offset from A
PRINT_HEX            ; now it's printing one hexadecimal value
  ADD R0,R6,R0       ; use R0 as an offset to calculate the correct ASCII of the character being printed
  OUT                ; print character
  ADD R5,R5,#-1      ; decrement the counter of how many characters need to be printed by 1
  BRp FREQUENCY_LOOP ; if R5 is positive, it means we need to print more hexadecimal to represent frequency

; now the frequency is printed, the program is ready to go on to the next line
  LD  R0,NEWLINE     ; load ASCII of newline into R0
  OUT                ; print newline
  ADD R3,R3,#1       ; increment R3 to represent the program is moving to the next line
  LD  R6,NEG_27      ; load -27 into R6
  ADD R6,R3,R6       ; check if 27 lines have been printed
  BRn PRINTING_LOOP  ; if less than 27 lines have been printed, continue printing more lines
  
DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

AT        .FILL x0040 ; the ASCII of '@'
SPACE     .FILL x0020 ; the ASCII of a space
NEWLINE   .FILL x000A ; the ASCII of a newline
ZERO      .FILL x0030 ; the ASCII of '0'
NEG_27    .FILL xFFE5 ; the additive inverse of #-27
A         .FILL x0041 ; the ASCII of 'A'

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
