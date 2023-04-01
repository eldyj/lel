import re
from sys import argv
from sys import set_int_max_str_digits, setrecursionlimit
from os.path import exists, dirname, abspath
from os import environ

set_int_max_str_digits(10000)
setrecursionlimit(10000)

class Tmp:
    stack = []
    comment = False
    functions = {}
    macros = {}
    current_macro = ''
    get_macro_name = False
    skip_next = False

spop = Tmp.stack.pop
spush = Tmp.stack.append

def lel_fn(fn):
    def wrapper():
        #print(Tmp.macros)
        #print(Tmp.stack)
        #print(f"{fn.__name__}")
        fn()
        #print(Tmp.stack)

    Tmp.functions[fn.__name__] = wrapper

@lel_fn
def eq():
    spush(spop() == spop())

@lel_fn
def gt():
    spush(spop() > spop())

@lel_fn
def lt():
    spush(spop() < spop())

@lel_fn
def no():
    spush(not spop())

@lel_fn
def unl():
    Tmp.skip_next = spop()

@lel_fn
def sum():
    spush(spop() + spop())

@lel_fn
def sub():
    spush(spop() - spop())

@lel_fn
def mul():
    spush(spop() * spop())

@lel_fn
def div():
    spush(spop() / spop())

@lel_fn
def mod():
    spush(spop() % spop())

@lel_fn
def pow():
    spush(spop() ** spop())

@lel_fn
def dup():
    i=spop()
    spush(i)
    spush(i)

@lel_fn
def rm():
    spop()

@lel_fn
def swp():
    i1=spop()
    i2=spop()
    spush(i1)
    spush(i2)

@lel_fn
def sumn():
    for i in range(int(spop())):
        Tmp.functions['sum']()

@lel_fn
def subn():
    for i in range(int(spop())):
        Tmp.functions['sub']()

@lel_fn
def muln():
    for i in range(int(spop())):
        Tmp.functions['mul']()

@lel_fn
def divn():
    for i in range(int(spop())):
        Tmp.functions['div']()

@lel_fn
def modn():
    for i in range(int(spop())):
        Tmp.functions['mod']()

@lel_fn
def pown():
    for i in range(int(spop())):
        Tmp.functions['pow']()

@lel_fn
def dupn():
    for i in range(int(spop())):
        Tmp.functions['dup']()

@lel_fn
def pr():
    print(spop(),end="")

@lel_fn
def sj():
    spush(''.join([str(spop()),str(spop())]))

@lel_fn
def rd():
    spush(input())

@lel_fn
def rf():
    with open(spop(),'r') as f:
        spush(f.read())

@lel_fn
def wf():
    with open(spop(),'w') as f:
        f.write(spop())

@lel_fn
def ge():
    n = spop()
    spush('' if n not in environ else environ[n])

@lel_fn
def ga():
    p = spop()
    a = argv[1:]
    spush(' ' if p not in a else a[p])

@lel_fn
def load():
    load_file(spop())

@lel_fn
def use():
    use_std(spop())

@lel_fn
def do():
    eval_string(spop())

@lel_fn
def fl():
    spush(float(int(spop())))

def eval_op(line):
    l = line.strip()

    if len(l) == 0:
        return

    if l == '/*':
        Tmp.comment = True
        return
    if l == '*/':
        Tmp.comment = False
        return

    if Tmp.comment:
        return

    if Tmp.skip_next:
        Tmp.skip_next = False
        return

    if l == "=":
        Tmp.get_macro_name = True
        return

    if l == ".":
        Tmp.current_macro = ''
        return

    if Tmp.current_macro != '':
        Tmp.macros[Tmp.current_macro] += f" {l}"
        return

    if l in Tmp.macros:
        eval_string(Tmp.macros[l])
        return

    if l.replace('.','').isdecimal():
        spush(float(l))
        return

    if Tmp.get_macro_name:
        Tmp.current_macro = l
        Tmp.macros[l]=''
        Tmp.get_macro_name = False
        return

    if l in Tmp.functions:
        Tmp.functions[l]()
        return

    if l[0] in {'"',"'"} and l[-1] in {'"',"'"}:
        spush(eval(l))
        return

    raise ValueError(f"wtf is {l}?")

def eval_string(s):
    pattern = r'''("[^"]*"|'[^']*'|\S+)'''
    stripped = s.replace('\n',' ').strip()
    parts = re.findall(pattern, stripped)

    for i in parts:
        eval_op(i)

def load_file(fn):
    if not exists(fn):
        print(f"Error: {fn} no such file")
        exit(1)
    with open(fn, "r") as f:
        eval_string(f.read())

def use_std(n):
    load_file(f"{dirname(abspath(__file__))}/std/{n}.lel")

if len(argv) > 1:
    use_std("stdop")
    load_file(argv[1])
else:
    print('usage:')
    print('\tlel <filename>')
    exit(1)
