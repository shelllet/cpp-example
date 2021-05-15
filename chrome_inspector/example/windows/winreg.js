
if (!winreg.registerAssoc(".js", "let.exe"))
    console.log(getLastError());


console.log(winreg.queryAssoc(".bat"));

if (!winreg.removeAssoc(".bat")){
    console.log(getLastError());
}