  import QtQuick 2.0
  import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

  Rectangle {
      width: 200
      height: 200
      color: "red"
      border.color: "black"
      border.width: 5
      radius: 10

      RowLayout {

        Button {
          text: "Ok"
          onClicked: {
          
          rc.color = "blue"
          }
      }

      Rectangle {
      id: "rc"
        width: 100
      height: 100
      color: "red"
      border.color: "black"
      border.width: 1
      radius: 10

       MouseArea {
          anchors.fill: parent
          onClicked: { 
           console.log(parent.color);
          
          if (parent.color == "#000000"){
           parent.color="red";
          }
          else{
                parent.color= "black";
          }
          }
      }
      }
      
      }
  }
