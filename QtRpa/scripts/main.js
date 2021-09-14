import * as impl from "./implement.js"
import * as wrp from "./wrapper.js"
import * as pri from "./private.js"

var data = {
    name: "Dir",
    className: "QDir",
    namespace: "core",
    parent: "Object",
    parentNamespace: "",
    canNew: true,
    public: ` 

      `,
    virtual: `    
    `,

    static: `    

    
    `,
    signals: `   

    
    `,
    propeties: `
 
    `,
    enums: `
    Filter { Dirs, AllDirs, Files, Drives, NoSymLinks, NoDotAndDotDot, NoDot, NoDotDot, AllEntries, Readable, Writable, Executable, Modified, Hidden,System,CaseSensitive }
    `
}


impl.create(data, data.className.toLowerCase().replace("_", "") + `_implement.h`);
pri.create(data, data.className.toLowerCase().replace("_", "") + `_p.h`);
wrp.create(data, data.className.toLowerCase().replace("_", "") + `_wrapper.h`);
