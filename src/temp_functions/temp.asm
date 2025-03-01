bits 32
section .text
  movzx eax, bl
  shl eax, 16
  
  movzx esi, bh
  shl esi, 11
  or eax, esi
  
