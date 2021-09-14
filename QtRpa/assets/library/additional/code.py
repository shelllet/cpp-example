from interpreter import LayoutItem
from interpreter import Widget
from interpreter import Item
from interpreter import Property
from interpreter import Element
from interpreter import Layout
from interpreter import LinearLayout
from interpreter import Scintilla
from interpreter import LexerPython


class CodePoperty(Property):
    def __init__(self, node):
        Property.__init__(self, node)
        #self.node = node
        # print(node.attribute("display").value())
        self.code = node.attribute("code").value()
        

    def get_doc(self):
        doc = super().get_doc()
        doc.document_element().append_attribute("filename").set_value(self.filename)
        return doc

    def filename_changed(self, new):
        self.code = new

    # def get_input(self, browser):
    #     group = super().get_input(browser)
    #     line_edit = LineEditFactory.create()
    #     str_manager = StringPropertyManager.create()
    #     filename = str_manager.add_property("Filename")
    #     group.add_sub_property(filename)
    #     str_manager.set_value(filename, self.filename)
    #     str_manager.value_changed.connect(self.filename_changed)
    #     browser.set_factory_for_manager(str_manager, line_edit)
    #     return group

    def exec(self):
        if self.filename is not None:
            exec(self.code)


class CodeElement(Element):
    def __init__(self, node, parent):
        Element.__init__(self, parent)
        self.prop = CodePoperty(node)
        self.layout = LinearLayout.create(LinearLayout.Vertical, self)
        self.layout.set_contents_margins(11, 11, 11, 11)

        self.cintilla = Scintilla(self)
        self.cintilla.set_utf8(True)
        self.cintilla.set_text(self.prop.code)
        self.lexer = LexerPython.create()
        self.cintilla.set_lexer(self.lexer)
        self.layout.add_item(self.cintilla.widget())


    def get_prop(self):
        return self.prop
