import sys
import os

ns = sys.argv[1]
module_name = sys.argv[2]
class_name = sys.argv[3]

print("namespace is: " + ns)
print("module is: " + module_name)
print("class is: " + class_name)


# cpp
try:
    fcpp = open("./modules/" + module_name + "/src/" +
                class_name.lower() + ".cpp", "x")

    content = f'''#include "{module_name + "/" +class_name.lower() + ".h"}"'''
    content += "\n"
    content += f'''#include "{module_name + "/private/" +class_name.lower() + "_p.h"}"'''
    content += "\n"
    content += f'''
namespace {ns}{{
    namespace {module_name}{{
        
    }}
}}
using namespace {ns}::{module_name};
{class_name}::{class_name}(Object* parent /*= nullptr*/)
    :{class_name}(*new {class_name}Private, parent)
{{

}}
{class_name}::{class_name}({class_name}Private& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{{

}}
'''
    fcpp.write(content)

    fcpp.close()
except OSError as err:
    print(err)

# hpp
try:
    fhpp = open("./include/" + module_name + "/" +
                class_name.lower() + ".h", "x")

    content = f'''#pragma once
#include "common.hpp"
namespace {ns} {{
    namespace {module_name}{{
        class {class_name}Private;
        class {class_name} : public Object {{
            Q_DECLARE_PRIVATE({class_name})
        public:
            {class_name}(Object*parent = nullptr);
        protected:
            {class_name}({class_name}Private& d, Object*parent = nullptr);
        }};
    }}
}}
    '''
    fhpp.write(content)
    fhpp.close()
except OSError as err:
    print(err)


try:
    os.mkdir("./include/" + module_name + "/private")
except OSError as err:
    print(err)

# private
try:
    fprivate = open("./include/" + module_name + "/private/" +
                    class_name.lower() + "_p.h", "x")

    content = f'''#pragma once
namespace {ns} {{
    namespace {module_name}{{
        class {class_name}Private : public ObjectPrivate {{
            Q_DECLARE_PUBLIC({class_name})
        public:
        }};
    }}
}}
'''

    fprivate.write(content)
    fprivate.close()
except OSError as err:
    print(err)
