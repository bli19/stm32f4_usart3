stm32f4_usart3
==============

Weird USART control by assigning value to registers 

This code control registers directly, but i think it is much harder than ordinary library version. The baud rate is 
just endless problem to me. I ended up find 0x0000018C is the baud rate that can represent numbers and letters, but it
does not obey the ASCII talbe sequence, which made me o confuse.
