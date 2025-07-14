MAIN: mov @r3 ,LENGTH
LOOP: jmp L1
mcro m1
sub @r1, @r4
bne END
endmcro
prn -5
bne LOOP
pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp
m1
mcro m1
sub @r1, @r4
bne END
endmcro
mcro m1  f
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
L1: inc K
bne LOOP
END: stop
STR: .string “abcdef”
LENGTH: .data 6,-9,15
K: .data 22

