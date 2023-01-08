#include "mbed.h"

DigitalOut Dig[4] = {A4, D2, D4, D7};       // DigitalOut型でデジタル信号(モーターの回転方向)を出力するピンを宣言　※Digは変数名
PwmOut P[4] = {D3, D5, D9, D10};        // PwmOut型でPWM信号(モーターの回転速度)を出力するピンを宣言　※Pは変数名

void Move(double x, double y, double z);        //Move関数のプロトタイプ宣言(xはx軸方向への動作、yはy軸方向への動作、zは回転動作を示す)

double motor[4];        //各モーターの制御状態を管理するため、double型で変数motorを宣言

void Move(double x, double y, double z) {
   int i;

   if(z != 0) {     // 回転指示であるか？(zが0以外の値であるか？)
    // 回転指示は全モーターを同じ方向へ回転させれば良いだけである。(全モーターを右方向に回せば右回転が出来る)
    motor[0] = z;
    motor[1] = z;
    motor[2] = z;
    motor[3] = z;
   }
   else {       //回転指示でない場合(zが0である)
    // ここは各モーターの速度制御を調整するが、理解が困難なので各自図などを描いて要領を得ると良い。
    motor[0] = x + y;       // 左方前側のモーター。x方向、y方向共に正回転させると正方向に動く。
    motor[1] = x - y;       // 右方前側のモーター。x方向は正回転させると、y方向は逆回転させると正方向に動く。
    motor[2] = -x + y;      // 左方後側のモーター。x方向は逆回転させると、y方向は正回転させると正方向に動く。
    motor[3] = -x - y;      // 右方後側のモーター。x方向、y方向共に逆回転させると正方向に動く。
   }

   for(i = 0;i < 4;i++) {       //各モーター制御用のfor文
       if(motor[i] >= 0) {
           Dig[i] = 0;      // モーターの回転速度が正の場合、Dig(モーターの回転方向を制御するデジタル信号変数)を0(正回転)とする
       }else {
           Dig[i] = 1;      // モーターの回転速度が負の場合、Digを1(逆回転)とする
       }
       P[i] = fabs(motor[i]);       // 回転速度をPWM信号変数Pに代入。PWMの値域は0~1なので、回転速度指定変数motorの絶対値を取る。(fabsは絶対値の関数)
    }
}

int main() {
    while(1){
        // ここからは試走用のゴリゴリプログラムなので使用用途に合わせて適宜書き換えて下さい
        Move(0, 0, 0);      // 停止状態
        wait_us(1000);  //1000㍉秒(1秒)待機
        Move(1, 0, 0);      // x方向：右方に全速移動(速度1)
        wait_us(1000);
        Move(0, 1, 0);      // y方向：前方に全速移動(速度1)
        wait_us(1000);
        Move(-1, 0, 0);     // -x方向：左方に全速移動(速度1)
        wait_us(1000);
        Move(0, -1, 0);     // -y方向：後方に全速移動(速度1)
        wait_us(1000);
        Move(0.5, 0.5, 0);      // x+y方向：右斜め前方に半速移動(速度0.7：三平方の定理より導出)
        wait_us(1000);
        Move(0.5, -0.5, 0);     // x-y方向：右斜め後方に半速移動(速度0.7：三平方の定理より導出)
        wait_us(1000);
        Move(-0.5, -0.5, 0);    // -x-y方向：左斜め後方に半速移動(速度0.7：三平方の定理より導出)
        wait_us(1000);
        Move(-0.5, 0.5, 0);     //-x+y方向：左斜め前方に半速移動(速度0.7：三平方の定理より導出)
        wait_us(1000);
        Move(0, 0, 0);      // 停止状態
        wait_us(1000);
        Move(0, 0, 1);      // 正回転：全速右回転(速度1)
        wait_us(1000);
        Move(0, 0, 0);      // 停止状態
        wait_us(1000);
        Move(0, 0, -1);     // 逆回転：全速左回転(速度1)
        wait_us(1000);
        /*各方向へそれぞれ速度1で動かしたい場合は、方向角θを求め、x成分をcos(θ)より、y成分をsin(θ)より導出できる。*/
    }
}