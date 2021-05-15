let qrCodeDetector = new cv.QRCodeDetector();

function getQRCode(image) {
    let [decodedText, ..._] = qrCodeDetector.detectAndDecode(image)

    return decodedText;
}


function test(file) {
    let img = cv.imread(file);

 //   let gray = cv.cvtColor(img, cv.COLOR_RGB2GRAY)

    let result = "";
    let num = 0;
    result = getQRCode(img);
    if (result == "") {
        let [t, newImg] = cv.threshold(img, 0, 255, cv.THRESH_OTSU);

        console.log(file);
        while (result == "" && t < 255) {
            num++
            [t, newImg] = cv.threshold(newImg, t, 255, cv.THRESH_BINARY);
            result = getQRCode(newImg);
            t += 20;
        }
    }
    console.log("try ", num, " and result: ", result);
}


test("./opencv/qrcode/2020-8-14-11-18-43-0.png");


let dir = new Qt.DirIterator("./opencv/qrcode/", Qt.Dir.Filter.NoDotAndDotDot | Qt.Dir.Filter.Files);

while (dir.hasNext()) {
    //test(dir.next());
}

