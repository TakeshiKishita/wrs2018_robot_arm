#include <Arduino.h>

//
// ロボットアーム側制御
//
//

// アームの軸数
const int axis_num = 6;
// モータードライバへ出力するoutチャンネル
const int arm_axis_up[axis_num] = {2,4,6,8,10,12};
const int arm_axis_down[axis_num] = {3,5,7,9,11,13};

void setup() {
    Serial.begin( 9600 );

    for (size_t i = 0; i < axis_num; i++) {
      pinMode(arm_axis_up[i],OUTPUT);
      pinMode(arm_axis_down[i],OUTPUT);
    }
}

void loop() {

    // アームの角度を読み取る
    int arm_axis[axis_num];
    arm_axis[0] = analogRead(0);
    arm_axis[1] = analogRead(1);
    arm_axis[2] = analogRead(2);
    arm_axis[3] = analogRead(3);
    arm_axis[4] = analogRead(4);
    arm_axis[5] = analogRead(5);

    // コントローラーの角度を受信する
    String controller_angle_str;
    if (Serial.available() > 0){
        controller_angle_str = Serial.readStringUntil('\r');
        Serial.println("[get_num]"+controller_angle_str);
    }

    // CSV形式のコントローラ角度を各関節に分解する
    int ctrl_axis[6];
    ctrl_axis[0] = atoi(strtok(controller_angle_str.c_str(),","));
    ctrl_axis[1] = atoi(strtok(NULL,","));
    ctrl_axis[2] = atoi(strtok(NULL,","));
    ctrl_axis[3] = atoi(strtok(NULL,","));
    ctrl_axis[4] = atoi(strtok(NULL,","));
    ctrl_axis[5] = atoi(strtok(NULL,","));

    for(int x : ctrl_axis){
      // トークンの値を出力
      Serial.println(ctrl_axis[x]);
	     if (ctrl_axis[x] > arm_axis[x]) {
         //アームの角度が小さかった場合
         digitalWrite(arm_axis_down[x],LOW);
         digitalWrite(arm_axis_up[x],HIGH);
       }else if (ctrl_axis[x] < arm_axis[x]) {
         //アームの角度が大きかった場合
         digitalWrite(arm_axis_up[x],LOW);
         digitalWrite(arm_axis_down[x],HIGH);
       } else {
         //角度が同じだった場合
         digitalWrite(arm_axis_down[x],LOW);
         digitalWrite(arm_axis_up[x],LOW);
       }
     }

    delay(1000);
}
