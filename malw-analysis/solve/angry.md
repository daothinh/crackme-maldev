ByteBrew's angry file
https://crackmes.one/crackme/64c5295f8117d58ab380f9e9
"Very simple, but that does not mean it's easy. There are multiple possible passwords."

# Challenge

x64 elf file
No obvious obfuscation or packing

There's no input prompt and no response after entering an incorrect input.
Apparently it is a passive-aggressive kind of angry.

Taking a look at the disassembly in IDA, it looks like the success response is:

```
"%s is a valid flag!"
```

Where %s is our input.

Let's get into it.

# Diving in

After receiving our input, the program checks if the length is 12,
and skips to the failure condition if not:

```
.text:00000000000011C2                 call    _strlen
.text:00000000000011C7                 cmp     rax, 0Ch
.text:00000000000011CB                 jnz     loc_132B
```

So our flag has to be 12 characters long.

After this, it starts doing math on pairs of characters from the flag,
and comparing them to hardcoded values:

```
.text:00000000000011D1                 movzx   eax, [rbp+flag]
.text:00000000000011D5                 movsx   edx, al
.text:00000000000011D8                 movzx   eax, [rbp+flag+1]
.text:00000000000011DC                 movsx   eax, al
.text:00000000000011DF                 add     eax, edx
.text:00000000000011E1                 cmp     eax, 0A6h
.text:00000000000011E6                 jnz     loc_132B		; failure

.text:00000000000011EC                 movzx   edx, [rbp+flag+5]
.text:00000000000011F0                 movzx   eax, [rbp+flag+3]
.text:00000000000011F4                 xor     eax, edx
.text:00000000000011F6                 cmp     al, 50h ; 'P'
.text:00000000000011F8                 jnz     loc_132B
...
```

Ghidra actually does a fairly decent job chewing through these and saves us a lot of squinting.

The constraints a valid flag has to meet are:
flag[0] + flag[1]   = 0xA6
flag[3] ^ flag[5]   = 0x50
flag[2] + flag[6]   = 0xD7
flag[4] / flag[7]   = 0x01
flag[4] * flag[11]  = 0x3c0f
flag[8] - flag[2]   = 0x09
flag[9] + flag[3]   = 0x97
flag[11] & flag[10] = 0x64
flag[0] + flag[11]  = 0xf3
flag[1] + flag[10]  = 0x94
flag[9] % flag[2]   = 0x33
flag[3] ^ flag[8]   = 0x16
flag[4] | flag[7]   = 0x7f
flag[5] + flag[6]   = 0xa2

I've been looking for an excuse to learn z3, so I guess this will do.

# Constraint solving with z3

We need to install z3 solver:

```
pip3 install z3-solver
```

Then, as with most programming challenges, we can still some code and modify it to our end.

https://stackoverflow.com/questions/11867611/z3py-checking-all-solutions-for-equation
https://theory.stanford.edu/~nikolaj/programmingz3.html#sec-blocking-evaluations

Modifying this to solve our problem, we get:

```
#/usr/bin/python3
import itertools
from z3 import *

def models(formula, max = 100):
    " a generator of up to max models "
    solver = Solver()
    solver.add(formula)

    count = 0
    while count < max:
        count +=1
        
        if solver.check() == sat:
            model = solver.model()
            yield model
            
            # exclude this model
            block = []
            for z3_decl in model: # FuncDeclRef
                arg_domains = []
                for i in range(z3_decl.arity()):
                    domain, arg_domain = z3_decl.domain(i), []
                    for j in range(domain.num_constructors()):
                        arg_domain.append( domain.constructor(j) () )
                    arg_domains.append(arg_domain)
                for args in itertools.product(*arg_domains):
                    block.append(z3_decl(*args) != model.eval(z3_decl(*args)))
            solver.add(Or(block))

flag = []
F = []

for i in range(12):
    flag.append(BitVec(f"flag_{str(i).zfill(2)}", 8))
    F += [ flag[i] >= 0x21, flag[i] <= 0x7e ]

F += [flag[0] + flag[1]   == 0xA6,
      flag[3] ^ flag[5]   == 0x50,
      flag[2] + flag[6]   == 0xD7,
      flag[4] / flag[7]   == 0x01,
      flag[4] * flag[11]  == 0x3c0f,
      flag[8] - flag[2]   == 0x09,
      flag[9] + flag[3]   == 0x97,
      flag[11] & flag[10] == 0x64,
      flag[0] + flag[11]  == 0xf3,
      flag[1] + flag[10]  == 0x94,
      flag[9] % flag[2]   == 0x33,
      flag[3] ^ flag[8]   == 0x16,
      flag[4] | flag[7]   == 0x7f,
      flag[5] + flag[6]   == 0xa2 ]

for m in models(F):
    m_dict = {d.name():m[d].as_long() for d in m}
    print(''.join([chr(m_dict[k]) for k in sorted(m_dict.keys())]))
```

And we get the following valid flags:

```
v0id{4n?r3d}
v0id{4n_r3d}
v0id{4nWr3d}
v0id{4nGr3d}
v0id{4nFr3d}
v0id{4nfr3d}
v0id{4nvr3d}
v0id{4nwr3d}
v0id{4ngr3d}
v0id{4ner3d}
v0id{4ndr3d}
v0id{4ntr3d}
v0id{4nur3d}
v0id{4nEr3d}
v0id{4nMr3d}
v0id{4nOr3d}
v0id{4nNr3d}
v0id{4nnr3d}
v0id{4nlr3d}
v0id{4nDr3d}
v0id{4nTr3d}
v0id{4nLr3d}
v0id{4n\r3d}
v0id{4n]r3d}
v0id{4nmr3d}
v0id{4nor3d}
v0id{4n>r3d}
v0id{4n^r3d}
v0id{4nVr3d}
v0id{4nUr3d}
```

Trying one of them:

```
$ ./a.out
v0id{4n?r3d}
v0id{4n?r3d} is a valid flag!
```

There we go!

QED