import ast
import astunparse


class CodeAnalyzer(ast.NodeVisitor):
    def visit_Import(self, node):
        print("### local:", locals())
        global astunparse
        self.dicts.append(astunparse.unparse(node))

    def visit_ImportFrom(self, node):
        self.dicts.append(astunparse.unparse(node))
    dicts = list()


try:
    code
except NameError:
    code = None


result = ""

print(locals())
#print("""{code}""".format(**locals()))

print("xxxxxx-")

print(code)

if 'code' in locals():
    print("----------", code)
    print(locals())

    node = ast.parse(code)
    analyzer = CodeAnalyzer()
    analyzer.visit(node)
    result = "".join(analyzer.dicts)

print(result)
