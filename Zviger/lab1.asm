;� ������ �� ������� ���������� a, b, c, d ������������ � �������� ������ � ����� ����������� �����.
;���������� ��������� ��� ���� �������� �������������� � ���������� ��������, � ��������� ��������� � ������� AX.
;��� ���������� ��������� �������, ��� ��������� ��������� � �����.
;��� ���������� ������� �������, ��� ��� �������������. ���������� ��������� ���������� �������� � ���������.

;6) ���� a OR (a + 1) = b ��
;        ��������� = (a * b + c) % d
;     �����
;        ���� a AND b = c OR d ��
;           ��������� = b AND (b - 1)
;        �����
;           ��������� = c % d + b * a

.model small
.stack 256
.data
    a dw 14
    b dw 58
    c dw 24
    d dw 112
.code
main:
    mov ax, @data
    mov ds, ax
    
    mov AX, d
    cmp d, 0
    jz exit

    mov AX,a
    mov BX,b
    
    mov DI, AX
    inc DI
    or AX, DI
    cmp AX, BX
    
    JNZ flag1
    
    mov AX, a
    mul BX
    add CX, D
    mov CX, d
    div CX
    mov AX, DX
    jmp exit
    
    flag1:
    
    mov AX, a
    and AX, BX
    mov CX, c
    or CX, d
    cmp AX,CX
    
    JNZ flag2
    
    mov DI, BX
    dec DI
    and BX, DI
    mov AX, BX
    jmp exit
    
    flag2:
    
    mov AX, c
    mov DX, 0
    div d
    
    mov CX,DX
    mov AX, a
    mul BX
    add AX,CX
    
    exit:
    mov ax, 4c00h
    int 21h
end main