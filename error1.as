MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
mcro m1
sub @r1, @r4
bne END
endmcro
prn -5
bne LOOP
m1 dgasdg
mcro m1
sub @r1, @r4
bne END
endmcro
mcro mmm  f
sub @r1, @r4
bne END
endmcro g
mcro .string
sub @r1, @r4
bne END
endmcro
mcro .data
sub @r1, @r4
bne END
endmcro
mcro mov
sub @r1, @r4
bne END
endmcro
mcro mfad:
bne END
endmcro
L1: inc K
bne LOOP
END: stop
STR: .string 
LENGTH: .data 6,-9,15
K: .data 22

