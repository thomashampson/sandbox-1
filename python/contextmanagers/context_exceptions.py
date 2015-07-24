from contextlib import contextmanager

@contextmanager
def rollback():
    print "In context manager"
    print "   Before yield"
    try:
        yield
    except Exception:
        print "Exception in yield caught"
    print "   After yield"

def foo():
    with rollback():
        raise RuntimeError

# ------------------------------------------------------------------------------
foo()
