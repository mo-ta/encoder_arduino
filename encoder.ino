/*
 エンコーダーのパルスジェネレータ
 
 実測で固定時間算出しているのでおそらく adrduino uno専用
 cycle_time毎（μs）にパルスを発生
 A相、B相を発信 12、13pin
 コンベア同期では1cycle 4palusで入力すること
 LEDは13番ピント連動
*/
//グローバル変数
#define Aphase 13
#define Bphase 12
#define BaseTime 22    //wait以外の処理時間実測値

/*
 設定値 
 conver_speedかpluse_cons_fdが0時だけcycle_timeで動作
 */
unsigned int conv_speed =  3;     //コンベア速度 mm/sec
unsigned int pluse_cons_fd = 10000; //FDのパルス定数 
unsigned int cycle_time    = 8000;  //サイクルタイム 


unsigned int cnt = 0;   //カウンタ
unsigned int wait_time_usec = 0; // HIGH、LOWの保持時間
void setup() {
  pinMode(Aphase, OUTPUT);
  pinMode(Bphase, OUTPUT);
  digitalWrite(Aphase, LOW);
  digitalWrite(Bphase, LOW);
  wait_time_usec = calc_wait_time();
}
//速度 -> cycle_timeの計算
unsigned int calc_wait_time(){
  if( pluse_cons_fd && conv_speed){
       cycle_time = pluse_cons_fd / (conv_speed  / 4);
  }
  return (cycle_time - BaseTime) / 4;
}
void loop() {
  switch (cnt) {
    case 0:
      digitalWrite(Aphase, HIGH);
      break;
    case 1:
      digitalWrite(Bphase, HIGH);
      break;
    case 2:
      digitalWrite(Aphase, LOW);
      break;
    case 3:
      digitalWrite(Bphase, LOW);
      break;
  }
  delayMicroseconds(wait_time_usec); 
  cnt++;
  if (cnt > 3) cnt = 0;
}
