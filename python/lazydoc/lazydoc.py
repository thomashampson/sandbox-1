"""Experimenting with lazy instantiation of
a docstring.
"""
def create_wrapper(name):

    class Wrapper:
        __slots__ = []

        def __getattribute__(self, attr):
            obj = object.__getattribute__(self,attr)
            if attr == "__class__" and obj.__doc__ is None:
                setattr(obj, "__doc__", name)

        def __call__(self, *args, **kwargs):
            print("Running",name)

    return Wrapper()

rebin = create_wrapper('rebin')
rebin()
clone = create_wrapper('clone')
clone()

print("-----")

help(rebin)
