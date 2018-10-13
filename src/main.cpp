#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
//
// ロボットアーム側制御
//
//

const int slave_address = 0x10;
// アームの軸数
const int axis_num = 6;
// モータードライバへ出力するoutチャンネル
const int arm_axis_up[axis_num] = {2,4,6,8,10,12};
const int arm_axis_down[axis_num] = {3,5,7,9,11,13};
// 処理遅延時間
const int delay_time = 500;
// アーム格納時の初期角度
int initial_angle[axis_num];

int ctrl_axis[18];
void ReceiveMassage(int n){
  Serial.print("Received ");
  Serial.println(n);

  // 受け取った値３つをつなげて数値に変換し、リストに格納する
  int index = 0;
  char msg[3] = "";
  for (int i = 0; i < n-1; i++) {
    int ret = Wire.read();
    if (i == 0) {
      // 最初の文字はパスする
      continue;
    }
    if (strlen(msg) ==3){
      Serial.print("lan3");
      char msg[3] = {"\0"};
    }
    char buf[1] = "";
    sprintf(buf, "%d", ret);
    // Serial.print("buf: ");
    // Serial.println(buf);
    strcat(msg, buf);

    if (i%3 == 0) {
      //３の倍数だった場合、配列に追加
      Serial.print("msg");
      Serial.println(msg);
      ctrl_axis[index] = atoi(msg);
      Serial.print("ctrl_axis[");
      Serial.print(index);
      Serial.print("]=");
      Serial.println(ctrl_axis[index]);
      index++;
    }
  }

  // コントローラーの角度を受信する
  Serial.println("[get_num]");
  // アームの角度を読み取る
  int arm_axis[axis_num];
  arm_axis[0] = analogRead(0);
  arm_axis[1] = analogRead(1);
  arm_axis[2] = analogRead(2);
  arm_axis[3] = analogRead(3);
  arm_axis[4] = analogRead(4);
  arm_axis[5] = analogRead(5);

  for (size_t x = 0; x < axis_num; x++) {
    // トークンの値を出力
    Serial.print(x);
    Serial.print(" : ctrl_axis "+String(ctrl_axis[x]));
    Serial.println(" : arm_axis "+String(arm_axis[x]));

    if (initial_angle[x] > arm_axis[x]) {
      // アームの角度が初期位置よりも小さかった場合
      Serial.println("initial > arm");

      digitalWrite(arm_axis_down[x],LOW);
      digitalWrite(arm_axis_up[x],HIGH);
    }else if (ctrl_axis[x] > arm_axis[x]) {
       //アームの角度が小さかった場合
       Serial.println("ctrl > arm");
       digitalWrite(arm_axis_down[x],LOW);
       digitalWrite(arm_axis_up[x],HIGH);
    }else if (ctrl_axis[x] < arm_axis[x]) {
       //アームの角度が大きかった場合
       Serial.println("ctrl < arm");
       digitalWrite(arm_axis_up[x],LOW);
       digitalWrite(arm_axis_down[x],HIGH);
    } else {
       //角度が同じだった場合
       Serial.println("ctrl == arm");
       digitalWrite(arm_axis_down[x],LOW);
       digitalWrite(arm_axis_up[x],LOW);
    }
  }
}

void setup() {
    Serial.begin( 9600 );
    Wire.begin(slave_address);

    // アーム格納時の初期角度を設定
    initial_angle[0] = analogRead(0);
    initial_angle[1] = analogRead(1);
    initial_angle[2] = analogRead(2);
    initial_angle[3] = analogRead(3);
    initial_angle[4] = analogRead(4);
    initial_angle[5] = analogRead(5);

    for (size_t i = 0; i < axis_num; i++) {
      pinMode(arm_axis_up[i],OUTPUT);
      pinMode(arm_axis_down[i],OUTPUT);
    }
    Wire.onReceive(ReceiveMassage);
}

void loop() {
  //I2Cで受信したときに呼び出す関数を登録する
  delay(delay_time);
}
