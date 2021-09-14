from interpreter import Property
from interpreter import Element
from interpreter import LineEditFactory
from interpreter import StringPropertyManager
import subprocess

class ProcessStartPoperty(Property):
    def __init__(self, node):
        Property.__init__(self, node)
        #self.node = node
        # print(node.attribute("display").value())
        self.filename = node.attribute("filename").value()

    def get_doc(self):
        doc = super().get_doc()
        doc.document_element().append_attribute("filename").set_value(self.filename)
        return doc

    def filename_changed(self, new):
        self.filename = new

    def get_input(self, browser):
        group = super().get_input(browser)
        line_edit = LineEditFactory.create()
        str_manager = StringPropertyManager.create()
        filename = str_manager.add_property("Filename")
        group.add_sub_property(filename)
        str_manager.set_value(filename, self.filename)
        str_manager.value_changed.connect(self.filename_changed)
        browser.set_factory_for_manager(str_manager, line_edit)
        return group

    def exec(self):
        if self.filename is None:
            subprocess.Popen(self.filename)
        else:
            #subprocess.Popen([self.filename, self.args])
            subprocess.Popen(self.filename)
        

class ProcessStartView(Element):
    def __init__(self, node, parent):
        Element.__init__(self, parent)
        self.property = ProcessStartPoperty(node)
       # print(node.attribute("display").value())

    def get_prop(self):
        return self.property
