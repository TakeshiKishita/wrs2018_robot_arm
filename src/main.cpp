#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
//
// ロボットアーム側制御
//
//

const int slave_address = 0x10;
// モータードライバへ出力するoutチャンネル
const int drive_ch = 2;
const int rotate_ch = 3;
// 処理遅延時間
const int delay_time = 500;
// アーム格納時の初期角度
int initial_ctrl_angle;
int initial_arm_angle;

//初期アングル用変数
int standard_index = 0;

int ctrl_axis;
void ReceiveMassage(int n){

  // 受け取った値３つをつなげて数値に変換し、リストに格納する
  String msg;
  for (int i = 0; i < n; i++) {
    int ret = Wire.read();
    if (i == 0) {
      // 最初の文字はパスする
      continue;
    }
    msg += String(ret, DEC);

    if (i%3 == 0) {
      //３の倍数だった場合、配列に追加
      ctrl_axis = msg.toInt();
      msg = "";
    }
  }

  //最初のシグナルはスルーする
  if (standard_index < 5){
    standard_index++;
    return;
  }else if (standard_index == 5) {
    //初期位置を代入
      initial_ctrl_angle = ctrl_axis;
    standard_index++;
  }

  // アームの角度を読み取る
  int arm_axis;
  arm_axis = analogRead(0);

  if (ctrl_axis > initial_ctrl_angle){
    //初期位置よりも小さかった場合は動かさない
    Serial.println("");
    Serial.println("stay");
    return 0;
  }

  int arm_angle = arm_axis - initial_arm_angle;
  int ctrl_angle = ctrl_axis - initial_ctrl_angle;
  // トークンの値を出力
  Serial.print(":c "+String(ctrl_axis));
  Serial.print(":a "+String(arm_axis));

  if (abs(ctrl_angle-arm_angle) < 10) {
     //角度が同じだった場合
     digitalWrite(drive_ch, LOW);
     Serial.print(" A, ");
  } else if (ctrl_angle > arm_angle) {
     //アームの角度が小さかった場合
     digitalWrite(drive_ch, HIGH);
     digitalWrite(rotate_ch, HIGH);
     Serial.print(" B, ");
  } else if (ctrl_angle < arm_angle) {
     //アームの角度が大きかった場合
     digitalWrite(drive_ch, HIGH);
     digitalWrite(rotate_ch, LOW);
     Serial.print(" C, ");
  }
  Serial.println("");
}

void setup() {
    Serial.begin( 9600 );
    Wire.begin(slave_address);

    // アーム格納時の初期角度を設定
    initial_arm_angle = analogRead(0);

    pinMode(drive_ch,OUTPUT);
    pinMode(rotate_ch,OUTPUT);
    Wire.onReceive(ReceiveMassage);
}

void loop() {
  //I2Cで受信したときに呼び出す関数を登録する
  delay(delay_time);
}
