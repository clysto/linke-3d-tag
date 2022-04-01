; 生成 num 个 NOP 指令
.macro NOPN num
.rept \num
NOP
.endr
.endm
