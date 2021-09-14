from interpreter import Property
from interpreter import Container


class SequencePoperty(Property):
    def __init__(self, node):
        Property.__init__(self, node)


class SequenceView(Container):
    def __init__(self, node, parent):
        Container.__init__(self, parent)
        self.property = SequencePoperty(node)

    def get_prop(self):
        return self.property
