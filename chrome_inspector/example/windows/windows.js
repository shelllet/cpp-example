
var w = winapi.findWindow("Qt5QWindowIcon");

console.log("w: " + w.width);
console.log("h: " + w.height);


w.width = 1000;
w.height = 500;


console.log("w: " + w.width);
console.log("h: " + w.height);
console.log("title: ", w.title);

winapi.enumWindows((w)=>{
   console.log("title: ", w.title) ;
});


w.close();
//w.shutdown();