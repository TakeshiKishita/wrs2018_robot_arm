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

    delay(1000);
}
