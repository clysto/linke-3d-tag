# MSP430 汇编

## 寻址方式

MSP430 总共有7种寻址方式，分别是：

| 寻址方式                                     | 表达方式 |
| -------------------------------------------- | -------- |
| Register Mode （寄存器寻址）                 | Rn       |
| Indexed Mode（寄存器相对寻址）               | X(Rn)    |
| Symbolic Mode （符号地址寻址）               | ADDR     |
| Absolute Mode（绝对地址寻址）                | &ADDR    |
| Indirect Register Mode（寄存器间接寻址）     | @Rn      |
| Indirect Autoincrement（寄存器间接增量寻址） | @Rn+     |
| Immediate Mode（立即数寻址）                 | #N       |
