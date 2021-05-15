mouse.move(1669, 231);

//mouse.mouse(new Point(300, 300));

//mouse.click();


var hhk = mouse.installHook((wParam, msll)=>{
    if (wParam == windows.WM_LBUTTONDOWN) {
        console.log("click");
        mouse.removeHook();
        quit();
    }
    console.log("hooked..");
})


processEvents();

