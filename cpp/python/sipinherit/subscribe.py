from sipinherit import INamedItem, NamedItemRegistry

class ItemInPython(INamedItem):

    def name(self):
        return b"ItemInPython"

NamedItemRegistry.subscribe(ItemInPython)
