
HISTORY = []

def record(name, *args, **kwargs):
    args = []
    for k,v in kwargs.iteritems():
        args.append('{}="{}"'.format(k,v))
    HISTORY.append('{}({})'.format(name, ','.join(args)))
    pass


def call_1(*args, **kwargs):
    record('call_1', *args, **kwargs)
    pass

def call_2(*args, **kwargs):
    record('call_2', *args, **kwargs)
    pass

call_2(a=1,b='s')
call_1(c=1,g='u')
call_1(d=2,e='t')

import pprint
pprint.pprint(HISTORY)
