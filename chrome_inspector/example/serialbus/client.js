var app = new Application();

var device = new ModbusTcpClient();

device.errorOccurred = () => {
  console.log(device.errorString());
}

function read1(){
  let unit = new ModbusDataUnit(ModbusDataUnit.RegisterType.HoldingRegisters, 1100, 1);

  let reply = device.sendReadRequest(unit, 1);
  if (!reply.isFinished()) {
    reply.finished = () => {
     const unit = reply.result();
     for (let i = 0; i < unit.valueCount(); ++i){
        console.log("matrix：", unit.value(i));
     }
     console.log("matrix read finsihed");
    }
  }
}

function read2(){
  let unit = new ModbusDataUnit(ModbusDataUnit.RegisterType.HoldingRegisters, 1110, 8);

  let reply = device.sendReadRequest(unit, 1);
  if (!reply.isFinished()) {
    reply.finished = () => {
     const unit = reply.result();
     console.log("----------------");
     console.log("x: ", toNumber([unit.value(0), unit.value(1), unit.value(2), unit.value(3)]))
     console.log("y:", toNumber([unit.value(4), unit.value(5), unit.value(6), unit.value(7)]))
     console.log("[x,y]read finsihed");
    }
  }
}
let num = 1;
function write() {
  sleep(1000);
  let unit = new ModbusDataUnit(ModbusDataUnit.RegisterType.HoldingRegisters, 1000, 8);
  
  console.log("---------------write num:", num);
  unit.setValue(0, num % 2 + 1);
  unit.setValue(2, num++);

  let reply = device.sendWriteRequest(unit, 1);

  if (!reply.isFinished()) {
    reply.finished = () => {
      console.log("write finsihed");
    }
  }
  else{
    console.log("write finsihed direct");
  }
}

function connect(){
  if (!device.connectDevice()) {
    console.log("error:", device.errorString());
  }
}

device.stateChanged = (state) => {
  console.log("state: " + state);

  if (state == ModbusDevice.State.ConnectedState) {
    console.log("connected.");
  }
}

//const url = Url.fromUserInput("127.0.0.1:502");
const url = Url.fromUserInput("10.0.0.138:1502");

device.setConnectionParameter(ModbusDevice.ConnectionParameter.NetworkPortParameter, url.port());
device.setConnectionParameter(ModbusDevice.ConnectionParameter.NetworkAddressParameter, url.host());

device.setTimeout(200);

connect();

let timer = new Timer;

timer.setInterval(3000);

timer.timeout = ()=>{
  if (device.state() != ModbusDevice.State.ConnectedState)  {
    console.log("no connect.")
    connect();
    return;
  }
  write();
  sleep(1000);
  read1();
  sleep(300);
  read2();

  if (num %5 == 0){
    console.log("prepare to close.");
    device.disconnectDevice();
    connect();
  }
}
timer.start();

Application.exec();
