;Division of signed numbers

.model small
.stack 256
.data

ten dw 10
newLine db 10,13,'$'
errorMsg db 10, 13,"Input error:", 10, 13, '$'
repeatInput db 10, 13,"Repeat input!", 10, 13, '$'
enter2 db "Enter the divisor:", 10, 13, '$'
enter1 db "Enter a dividend:", 10, 13, '$'
result db "Result:", 10, 13, '$'
remainder db "Remainder:", 10, 13, '$'

.code
PrintStr proc
    push AX
    mov AH,09h
    int 21h
    pop AX
    ret
PrintStr endp

DeleteSymbolFromDisplay proc
    push AX
    push DX
    push CX

    mov AH, 03h
    int 10h

    dec DL
    mov AH, 02h
    int 10h

    mov AL, 20H
    mov AH, 0AH
    int 10h

    pop CX
    pop DX
    pop AX
    ret
DeleteSymbolFromDisplay endp

DeleteNumFromDisplay proc
    push AX
    push CX
    push DX

    mov AH, 03h
    int 10h

    mov BL, DL
    inc BL

    mov DL, 0
    mov AH, 02h
    int 10h

    xor DH, DH
    mov CL, BL
    mov AL, 20H
    mov AH, 0AH
    int 10h

    pop DX
    pop CX
    pop AX
    ret
DeleteNumFromDisplay endp

PrintAX proc
    push AX
    push CX
    push DX
    push SI
    mov SI, 0
    mov CX, 0
    test AX, AX
    jns isPosNum
    neg AX
    mov SI, 1
    isPosNum:

    pushDigit:                ;adding a character to a number on the stack 
        mov DX,0
        div ten
        add DX, '0'
        push DX
        inc CX
        cmp AX, 0
    JNZ pushDigit
    
    cmp SI,1
    jnz isPosNum1
    inc CX
    push 2Dh
    isPosNum1:

    printDigit:                ;character printing
        pop DX
        mov AH, 02h
        int 21h
    LOOP printDigit

    pop SI
    pop DX
    pop CX
    pop AX
    ret
PrintAX endp

ReadAX proc
    push DI
    push CX
    push BX
    push DX
    push SI

    mov SI, 0
    mov DX, 0
    mov CX, 0
    readSymbol:

        mov AH,08h            ;character reading
        int 21h

        cmp AL, 8h            ;check for a backspace
        jnz noBackSpace
        cmp CX, 0            ;check for a digit
        jz readSymbol
        cmp CX, 1            ;delete sign
        jnz isPosNum2
        mov SI, 0
        isPosNum2:
        pop AX
        dec CX
        call DeleteSymbolFromDisplay
        jmp readSymbol
        noBackSpace:

        cmp AL, 1Bh            ;check for a ESC
        jnz noESC
        popSymbol:
        pop AX
        LOOP popSymbol
        call DeleteNumFromDisplay
        xor SI, SI
        jmp readSymbol
        noESC:
        
        cmp AL, 13            ;if the entered character is skipped processing of the entered character
        jz addDigitsToNum

        cmp AL, 2Dh
        jnz isNotMinus

        cmp SI, 1
        jnz isNotSecondMinus
        xor SI, SI
        jmp error

        isNotSecondMinus:

        mov SI, 1
        push 2Dh
        inc CX
        mov DL, AL            ;printing sign
        mov AH,02h
        int 21h

        jmp readSymbol

        isNotMinus:

        mov SI, 1
        cmp AL, '0'            ;check for a digit
        jb error
        cmp AL, '9'
        ja error

        mov DL, AL            ;output of the entered character
        mov AH, 02h
        int 21h

        mov AH, 0            ;adding a digit to the stack
        sub AL, '0'
        push AX

        inc CX            ;count of the number of digits in the number
    jmp readSymbol

    jmp flag3
    flag4:
    jmp readSymbol
    flag3:

    addDigitsToNum:

        mov SI, CX            ;SI - length of the num
        mov DI, 0

    cycle:                    ;Adding number to the AX
        pop BX                ;extract a digit from the stack

        cmp BX, 2Dh
        jnz isNotMinus1

        cmp DI, 32769
        jnc forError
        neg DI
        jmp stopAdding

        isNotMinus1:

        mov AX, SI            
        sub AX, CX    
        xor DX, DX
        call tenInDegreeAX
        
        cmp DX, 0
            JNZ forError

        mul BX
        add DI, AX

        jmp continue

        forError:
        dec CX
        jmp error

        continue:
    LOOP cycle

    cmp DI, 32768
    JNC error

    stopAdding:

    mov AX, DI

    pop SI
    pop DX
    pop BX
    pop CX
    pop DI

    jmp exit
    error:
        lea DX, errorMsg
        call PrintStr
        lea DX, repeatInput
        call PrintStr
        cmp CX, 0
        JZ flag4
        popDigit:
            pop AX
        LOOP popDigit
        jmp flag4
    exit:

    ret
ReadAX endp

TenInDegreeAX proc
    cmp AX, 0
    JZ flag1
    push CX
    mov CX, AX
    mov AX, 1
    cycle3:
        mul ten
    LOOP cycle3
    pop CX

    jmp flag2
    flag1:
    mov AX, 1
    flag2:
    ret
TenInDegreeAX endp
main:
    mov AX, @data
    mov DS, ax

    lea DX, enter1
    call PrintStr

    call ReadAX
    mov SI, AX

    lea DX, newLine
    call PrintStr

    call PrintAX

    lea DX, newLine
    call PrintStr
    lea DX, enter2
    call PrintStr

    call ReadAX
    mov DI, AX

    lea DX, newLine
    call PrintStr

    cmp AX, 0
    jz main

    call printAX

    lea DX, newLine
    call PrintStr

    lea DX, result
    Call PrintStr

    mov DX, 0
    mov AX, SI
    
    CWD
    idiv DI
    
    call PrintAX
    
    push DX
    lea DX, newLine
    call PrintStr

    lea DX, remainder
    call PrintStr
    pop DX

    mov AX, DX

    call PrintAX

    lea DX, newLine
    call PrintStr

    mov ax, 4c00h
    int 21h
end main