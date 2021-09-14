import sys
import os

ns = sys.argv[1]
module_name = sys.argv[2]
class_name = sys.argv[3]

print("namespace is: " + ns)
print("module is: " + module_name)
print("class is: " + class_name)


# hpp
try:
    fhpp = open("./include/" + module_name + "/" +
                class_name.lower() + ".h", "x")

    content = f'''#pragma once
namespace {ns} {{
    namespace {module_name}{{
        class {class_name} {{
        public:
            {class_name}(Object*parent = nullptr);
        protected:
        }};
    }}
}}
    '''
    fhpp.write(content)
    fhpp.close()
except OSError as err:
    print(err)
