let ok = false

let dwProcessId = 0
windows.enumProcess((entry) => {
    if (entry.exeFile == "shelllet.exe") {
        dwProcessId = entry.processID;
        return false;
    }
});

windows.enumWindows((wnd) => {
    if (!wnd) {
        return true;
    }
    let processId = wnd.getProcessID();

    if (processId == dwProcessId && !wnd.getOwner()) {
        wnd.show(windows.show.NORMAL);
        wnd.foreground();
        ok = true;
        return false;
    }

});

(()=>{return ok})()