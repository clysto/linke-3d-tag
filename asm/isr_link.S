; RX 信号接收中断
; RX 中断通过 P2.3 连接
.section    __interrupt_vector_37, "xa"
.word       RX_ISR
