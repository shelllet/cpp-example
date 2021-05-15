
var id = setTimeout(()=>{
console.log("timeout.");

}, 3000);


setTimeout(()=>{
    console.log("timeout2.");
    clearTimeout(0);
    }, 6000);
    
run();


