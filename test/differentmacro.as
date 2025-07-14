MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
mcro m1
sub @r1, @r4
bne END
endmcro
prn -5
bne LOOP
m1
m1
mcro m2
sub @r2, @r5
bne END
endmcro
L1: inc K
bne LOOP
m2
END: stop
STR: .string 
LENGTH: .data 6,-9,15
K: .data 22
