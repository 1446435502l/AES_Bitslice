section .data
    array times 100 dq 0 ;[0-7]为映射新向量
    gf256_square_v times 5 dq 0
    gf16_mul1_add times 10 dq 0
    gf16_mul_upmul times 10 dq 0
    gf16_mul_downmul times 10 dq 0
    gf16_cheng_N times 10 dq 0
    gf256_mul times 10 dq 0
    temp dq 0
    temp1 dq 0
    temp2 dq 0
    h_inverse_res times 10 dq 0
    h_inverse_add times 10 dq 0
    h_inverse_mul_N times 10 dq 0
    h_inverse_mul times 10 dq 0
    h_inverse_temp1 dq 0
    h_inverse_temp2 dq 0
    h_inverse_temp3 dq 0
    h_inverse_temp4 dq 0
section .text
global g256_inverse
g256_inverse:
    ;调用约定：r8-r15按顺序传参，rabcdx依次返回参数
    push rbp
    mov rbp,rsp
    mov r8,[rcx]
    mov r9,[rcx+1*8]
    mov r10,[rcx+2*8]
    mov r11,[rcx+3*8]
    mov r12,[rcx+4*8]
    mov r13,[rcx+5*8]
    mov r14,[rcx+6*8]
    mov r15,[rcx+7*8]
;    mov r8,0xFFFFFFFFFFFFFFFF
;    mov r9,0
;    mov r10,0xFFFFFFFFFFFFFFFF
;    mov r11,0
;    mov r12,0
;    mov r13,0
;    mov r14,0
;    mov r15,0xFFFFFFFFFFFFFFFF
    ;映射GF（2222）
    mov rsi,r8
    xor rsi,r9
    xor rsi,r10
    xor rsi,r13
    xor rsi,r14
    xor rsi,r15
    mov [array],rsi
    ;a[7]
    mov rsi,r9
    xor rsi,r10
    xor rsi,r11
    xor rsi,r15
    mov [array+1*8],rsi
    ;a[6]
    mov rsi,r9
    xor rsi,r10
    xor rsi,r14
    xor rsi,r15
    mov [array+2*8],rsi
    ;a[5]
    mov rsi,r8
    xor rsi,r9
    xor rsi,r10
    xor rsi,r15
    mov [array+3*8],rsi
    ;a[4]
    mov rsi,r8
    xor rsi,r11
    xor rsi,r12
    xor rsi,r14
    xor rsi,r15
    mov [array+4*8],rsi
    ;a[3]
    mov rsi,r15
    mov [array+5*8],rsi
    ;a[2]
    mov rsi,r9
    xor rsi,r10
    xor rsi,r15
    mov [array+6*8],rsi
    ;a[1]
    mov rsi,r9
    xor rsi,r12
    xor rsi,r13
    xor rsi,r14
    xor rsi,r15
    mov [array+7*8],rsi
    ;a[0]
    ;映射完成,重新把向量赋值回r8-r15
    mov r8,[array]
    mov r9,[array+1*8]
    mov r10,[array+2*8]
    mov r11,[array+3*8]
    mov r12,[array+4*8]
    mov r13,[array+5*8]
    mov r14,[array+6*8]
    mov r15,[array+7*8]
    ;映射结束
    xor r8,r12
    xor r9,r13
    xor r10,r14
    xor r11,r15
    ;gf256 up add
    mov [gf256_square_v],r9
    xor [gf256_square_v],r11
    mov [gf256_square_v+1*8],r8
    xor [gf256_square_v+1*8],r10
    mov [gf256_square_v+2*8],r10
    xor [gf256_square_v+2*8],r11
    mov [gf256_square_v+3*8],r11
    ;square_v end
    mov r8,[array]
    mov r9,[array+1*8]
    mov r10,[array+2*8]
    mov r11,[array+3*8]
    ;即将开始gf16的乘法
    sub rsp,32
    call gf16_mul
    add rsp,32
    mov [gf256_mul],rax
    mov [gf256_mul+1*8],rbx
    mov [gf256_mul+2*8],rcx
    mov [gf256_mul+3*8],rdx
    ;结束gf16乘法
    push r8
    push r9
    push r10
    push r11
    mov r8,[gf256_square_v]
    mov r9,[gf256_square_v+1*8]
    mov r10,[gf256_square_v+2*8]
    mov r11,[gf256_square_v+3*8]
    xor r8,[gf256_mul]
    xor r9,[gf256_mul+1*8]
    xor r10,[gf256_mul+2*8]
    xor r11,[gf256_mul+3*8]
    sub rsp,32
    call g256_h_inverse
    add rsp,32
    pop r11
    pop r10
    pop r9
    pop r8
    mov [h_inverse_res],rax
    mov [h_inverse_res+1*8],rbx
    mov [h_inverse_res+2*8],rcx
    mov [h_inverse_res+3*8],rdx
    mov r8,[h_inverse_res]
    mov r9,[h_inverse_res+1*8]
    mov r10,[h_inverse_res+2*8]
    mov r11,[h_inverse_res+3*8]
    mov r12,[array+4*8]
    mov r13,[array+5*8]
    mov r14,[array+6*8]
    mov r15,[array+7*8]
    push r8
    push r9
    push r10
    push r11
    sub rsp,32
    call gf16_mul
    add rsp,32
    pop r11
    pop r10
    pop r9
    pop r8
    mov [array+8*8],rax
    mov [array+9*8],rbx
    mov [array+10*8],rcx
    mov [array+11*8],rdx
    push r8
    push r9
    push r10
    push r11
    mov r12,[array+0*8]
    mov r13,[array+1*8]
    mov r14,[array+2*8]
    mov r15,[array+3*8]
    sub rsp,32
    call gf16_mul
    add rsp,32
    pop r15
    pop r14
    pop r13
    pop r12
    mov [array+12*8],rax
    mov [array+13*8],rbx
    mov [array+14*8],rcx
    mov [array+15*8],rdx
    mov r8,[array+8*8]
    mov r9,[array+9*8]
    mov r10,[array+10*8]
    mov r11,[array+11*8]
    mov r12,[array+12*8]
    mov r13,[array+13*8]
    mov r14,[array+14*8]
    mov r15,[array+15*8]
    mov rsi,r10
    xor rsi,r12
    mov [array+8*8],rsi
    ;a[7]
    mov rsi,r8
    xor rsi,r12
    mov [array+9*8],rsi
    ;a[6]
    mov rsi,r9
    xor rsi,r15
    mov [array+10*8],rsi
    ;a[5]
    mov rsi,r8
    xor rsi,r10
    xor rsi,r12
    mov [array+11*8],rsi
    ;a[4]
    mov rsi,r8
    xor rsi,r9
    xor rsi,r10
    xor rsi,r11
    xor rsi,r12
    mov [array+12*8],rsi
    ;a[3]
    mov rsi,r9
    xor rsi,r10
    xor rsi,r12
    xor rsi,r13
    xor rsi,r15
    mov [array+13*8],rsi
    ;a[2]
    mov rsi,r10
    xor rsi,r11
    xor rsi,r14
    mov [array+14*8],rsi
    ;a[1]
    mov rsi,r9
    xor rsi,r11
    xor rsi,r14
    mov [array+15*8],rsi
    ;a[0]
    mov rsi,[array+8*8]
    xor rsi,0
    mov [array+8*8],rsi
    ;a[7]
    mov rsi,[array+9*8]
    xor rsi,0xFFFFFFFFFFFFFFFF
    mov [array+9*8],rsi
    ;a[6]
    mov rsi,[array+10*8]
    xor rsi,0xFFFFFFFFFFFFFFFF
    mov [array+10*8],rsi
    ;a[5]
    mov rsi,[array+11*8]
    xor rsi,0
    mov [array+11*8],rsi
    ;a[4]
    mov rsi,[array+12*8]
    xor rsi,0
    mov [array+12*8],rsi
    ;a[3]
    mov rsi,[array+13*8]
    xor rsi,0
    mov [array+13*8],rsi
    ;a[2]
    mov rsi,[array+14*8]
    xor rsi,0xFFFFFFFFFFFFFFFF
    mov [array+14*8],rsi
    ;a[1]
    mov rsi,[array+15*8]
    xor rsi,0xFFFFFFFFFFFFFFFF
    mov [array+15*8],rsi
    ;a[0]
    lea rax,[array+8*8]
    leave
    ret

gf16_mul:
    push rbp
    mov rbp,rsp
    mov [gf16_mul1_add],r8
    mov [gf16_mul1_add+1*8],r9
    mov [gf16_mul1_add+2*8],r12
    mov [gf16_mul1_add+3*8],r13
    xor [gf16_mul1_add],r10
    xor [gf16_mul1_add+1*8],r11
    xor [gf16_mul1_add+2*8],r14
    xor [gf16_mul1_add+3*8],r15
    push r10
    push r11
    mov r10,r12
    mov r11,r13
    sub rsp,32
    call g4_mul
    add rsp,32
    pop r11
    pop r10
    mov [gf16_mul_upmul],rax
    mov [gf16_mul_upmul+1*8],rbx
    push r8
    push r9
    push r10
    push r11
    mov r8,r10
    mov r9,r11
    mov r10,r14
    mov r11,r15
    sub rsp,32
    call g4_mul
    add rsp,32
    pop r11
    pop r10
    pop r9
    pop r8
    mov [gf16_mul_downmul],rax
    mov [gf16_mul_downmul+1*8],rbx
    push r8
    push r9
    push r10
    push r11
    mov r8,[gf16_mul1_add]
    mov r9,[gf16_mul1_add+1*8]
    mov r10,[gf16_mul1_add+2*8]
    mov r11,[gf16_mul1_add+3*8]
    sub rsp,32
    call g4_mul_N
    add rsp,32
    pop r11
    pop r10
    pop r9
    pop r8
    mov [gf16_cheng_N],rax
    mov [gf16_cheng_N+1*8],rbx
    mov rsi,[gf16_mul_upmul]
    xor rsi,[gf16_cheng_N]
    mov rax,rsi
    mov rsi,[gf16_mul_upmul+1*8]
    xor rsi,[gf16_cheng_N+1*8]
    mov rbx,rsi
    mov rsi,[gf16_cheng_N]
    xor rsi,[gf16_mul_downmul]
    mov rcx,rsi
    mov rsi,[gf16_mul_downmul+1*8]
    xor rsi,[gf16_cheng_N+1*8]
    mov rdx,rsi
    leave
    ret

g4_mul:
    push rbp
    mov rbp,rsp
    mov [temp],r8
    and [temp],r11
    ;a1b0
    mov [temp1],r9
    and [temp1],r10
    ;a0b1
    mov rax,[temp]
    xor rax,[temp1]
    ;a1b0+a0b1
    mov [temp],r9
    and [temp],r11
    ;a0b0
    xor rax,[temp]
    ;add three
    mov [temp],r8
    and [temp],r10
    ;a1b1
    mov [temp1],r8
    and [temp1],r11
    ;a1b0
    mov rbx,[temp]
    xor rbx,[temp1]
    ;a1b1+a1b0
    mov [temp],r9
    and [temp],r10
    xor rbx,[temp]
    ;add three
    leave
    ret

g4_mul_N:
    push rbp
    mov rbp,rsp
    mov [temp],r8
    and [temp],r10
    ;a1b1
    mov [temp1],r8
    and [temp1],r11
    ;a1b0
    mov rax,[temp]
    xor rax,[temp1]
    ;a1b1+a1b0
    mov [temp],r9
    and [temp],r10
    ;a0b1
    xor rax,[temp]
    ;add three
    mov [temp],r8
    and [temp],r10
    ;a1b1
    mov rbx,[temp]
    mov [temp],r9
    and [temp],r11
    xor rbx,[temp]
    ;a1b1+a0b0
    leave
    ret

g256_h_inverse:
    push rbp
    mov rbp,rsp
    mov [h_inverse_add],r8
    xor [h_inverse_add],r10
    mov [h_inverse_add+1*8],r9
    xor [h_inverse_add+1*8],r11
    mov rsi,[h_inverse_add]
    mov [h_inverse_mul_N],rsi
    mov rsi,[h_inverse_add]
    xor rsi,[h_inverse_add+1*8]
    mov [h_inverse_mul_N+1*8],rsi
    sub rsp,32
    call g4_mul
    add rsp,32
    mov [h_inverse_mul],rax
    mov [h_inverse_mul+1*8],rbx
    mov rsi,[h_inverse_mul_N]
    xor rsi,rax
    mov rdi,[h_inverse_mul_N+1*8]
    xor rdi,rbx
    mov [temp],rsi
    mov rsi,rdi
    mov rdi,[temp]
    push r8
    push r9
    push r10
    push r11
    mov r10,rsi
    mov r11,rdi
    sub rsp,32
    call g4_mul
    add rsp,32
    pop r11
    pop r10
    pop r9
    pop r8
    mov [h_inverse_temp1],rax
    mov [h_inverse_temp2],rbx
    push r8
    push r9
    mov r8,rsi
    mov r9,rdi
    sub rsp,32
    call g4_mul
    add rsp,32
    pop r9
    pop r8
    mov [h_inverse_temp3],rax
    mov [h_inverse_temp4],rbx
    mov rax,[h_inverse_temp3]
    mov rbx,[h_inverse_temp4]
    mov rcx,[h_inverse_temp1]
    mov rdx,[h_inverse_temp2]
    leave
    ret