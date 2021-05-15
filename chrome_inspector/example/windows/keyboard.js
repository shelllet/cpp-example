console.log(keyboard.keyCode("a")); 
console.log(keyboard.keyCode("A")); 



var notepad = winapi.findWindow(/.+记事本/);


winapi.setForegroundWindow(notepad.winId());


//keyboard.simulate([0x41]);

//keyboard.sendText("abc");
//keyboard.sendText("你好，我是机器人");
//keyboard.sendText("你好，我是机器人123");

keyboard.installHook((wParam, lParam) => {
    if (wParam == windows.WM_KEYDOWN) 
    {
    
        const name = keyboard.keyName( lParam.vkCode);
        console.log("you pressed: " + name);
        
        if (lParam.vkCode ==keyboard.keyCode("x") && keyboard.getAsyncKeyState(windows.VK_CONTROL))
        {
            keyboard.removeHook();
            quitApp();
        }
    }
});

processEvents();