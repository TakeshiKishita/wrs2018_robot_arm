#include <Arduino.h>

//
// ロボットアーム側制御
//
//

const int arm_axis0_up   = 2;
const int arm_axis0_down = 3;
const int arm_axis1_up   = 4;
const int arm_axis1_down = 5;
const int arm_axis2_up   = 6;
const int arm_axis2_down = 7;
const int arm_axis3_up   = 8;
const int arm_axis3_down = 9;
const int arm_axis4_up   = 10;
const int arm_axis4_down = 11;
const int arm_axis5_up   = 12;
const int arm_axis5_down = 13;

void setup() {
    Serial.begin( 9600 );
}

int change_angle(int arm_angle, int controller_angle) {

    int result = arm_angle * controller_angle;
    return result;
}

void loop() {

    // アームの角度を読み取る
    int arm_axis0 = analogRead(0);
    int arm_axis1 = analogRead(1);
    int arm_axis2 = analogRead(2);
    int arm_axis3 = analogRead(3);
    int arm_axis4 = analogRead(4);
    int arm_axis5 = analogRead(5);

    // コントローラーの角度を受信する
    if (Serial.available() > 0){
        String controller_angle_str = Serial.readStringUntil(';');
    }
    char A;
    A = atoi(strtok(controller_angle_str,","));
    Serial.println(A);         //1つ目のトークン表示

    while(A!=NULL){            //トークンがNULLになるまでループ
        A = atoi(strtok(NULL,","));  //2回目以降は第一引数はNULL
        if(A!=NULL){
            Serial.println(A);
        }
    }

    delay(1000);
}
