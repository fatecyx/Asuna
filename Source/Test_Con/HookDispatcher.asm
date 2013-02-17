.code

SIZE_OF_CONTEXT             equ     80h
SIZE_OF_DISPATCHER_DATA     equ     10h
SIZE_OF_LOCAL_VAR           equ     SIZE_OF_CONTEXT

__imp_RtlCaptureContext PROTO :QWORD
HookDispatcherx64Internal PROTO :QWORD, :QWORD, :QWORD

DisableWriteProtection1 proc


        mov eax, [rsp + 28h];
        mov r8d, [rsp + 24h];
        xor rcx, rcx;
        xor rdx, rdx;
        push rcx;
        lea r9, [rsp];
        call rax

        mov rax, cr0;
        mov rcx, rax;
        and rcx, not (1 shl 16);
        mov cr0, rcx;
        ret;

DisableWriteProtection1 endp

EnableWriteProtection1 proc

        mov rax, rcx;
        or  rax, 1 shl 16;
        mov cr0, rax;
        ret;

EnableWriteProtection1 endp

;
;   CONTEXT(0x4D0)      <- stack top
;   rcx                 <- ReturnAddress,           push rcx
;   return address      <- CallHookReturnAddress,   pushed by call
;

HookDispatcherx64 proc

    push    rax;        ; one more return address

    lea     rsp, [rsp - SIZE_OF_LOCAL_VAR];

    mov     [rsp + 00h], rax
    mov     [rsp + 08h], rcx
    mov     [rsp + 10h], rdx
    mov     [rsp + 18h], rbx
    mov     [rsp + 20h], rbp
    mov     [rsp + 28h], rsi
    mov     [rsp + 30h], rdi
    mov     [rsp + 38h], r8
    mov     [rsp + 40h], r9
    mov     [rsp + 48h], r10
    mov     [rsp + 50h], r11
    mov     [rsp + 58h], r12
    mov     [rsp + 60h], r13
    mov     [rsp + 68h], r14
    mov     [rsp + 70h], r15
    pushfq;
    pop     [rsp + 78h];
    
    lea     rdx, [rsp];
    lea     rcx, [rsp + SIZE_OF_LOCAL_VAR];     ; [rsp] = push rax; [rsp + 8] = return address
    mov     rdi, rcx;
    xor     rbx, rbx;
    and     qword ptr [rcx], rbx;

    call    HookDispatcherx64Internal;

    or      rbx, [rdi];

    mov     rax, [rsp + 00h];
    mov     rcx, [rsp + 08h];
    mov     rdx, [rsp + 10h];
    mov     rbx, [rsp + 18h];
    mov     rbp, [rsp + 20h];
    mov     rsi, [rsp + 28h];
    mov     rdi, [rsp + 30h];
    mov     r8 , [rsp + 38h];
    mov     r9 , [rsp + 40h];
    mov     r10, [rsp + 48h];
    mov     r11, [rsp + 50h];
    mov     r12, [rsp + 58h];
    mov     r13, [rsp + 60h];
    mov     r14, [rsp + 68h];
    mov     r15, [rsp + 70h];

    lea     rsp, [rsp + SIZE_OF_LOCAL_VAR];
    jnz     @f;
    lea     rsp, [rsp + 8];
    push    [rsp - SIZE_OF_LOCAL_VAR - 8 + 78h];
    jmp     DETECT_HOOK_TYPE_END;

@@:
    push    [rsp - SIZE_OF_LOCAL_VAR + 78h];

DETECT_HOOK_TYPE_END:

    popfq;
    ret;

HookDispatcherx64 endp

end
