/* 
  Programa controlador del arduino: Lee el estado de los botones del "Joystick Shield" y lo escribe en el puerto serial
*/

//Constantes que representan los pines de los botones
const int b1 = 3;
const int b2 = 4;
const int b3 = 5;
const int b4 = 2;
const int jb = 8;
const int jx = A0;
const int jy = A1;

//Estado actual y previo de cada botón
int b1_stat_prev = 0;
int b2_stat_prev = 0;
int b3_stat_prev = 0;
int b4_stat_prev = 0;
int jb_stat_prev = 0;

int b1_stat = 0;
int b2_stat = 0;
int b3_stat = 0;
int b4_stat = 0;
int jb_stat = 0;

int jx_read = 0;
int jx_stat = -1;
int jx_stat_prev = -1;
int jy_read = 0;
int jy_stat = -1;
int jy_stat_prev = -1;

void setup() {
  Serial.begin(9600);
  
  //Usa las resistencias internas de arduino, de ahí el digitalWrite
  pinMode(b1, INPUT);
  digitalWrite(b1, HIGH);
  pinMode(b2, INPUT);
  digitalWrite(b2, HIGH);
  pinMode(b3, INPUT);
  digitalWrite(b3, HIGH);
  pinMode(b4, INPUT);
  digitalWrite(b4, HIGH);
}

void loop(){
  
  jx_read = analogRead(jx);
  if (jx_read < 10) jx_stat = 0;
  if (jx_read > 1000) jx_stat = 1;
  if (jx_read < 1000 && jx_read > 10) jx_stat = -1;  
  
  if (jx_stat != jx_stat_prev){
    if (jx_stat == 0){
      Serial.println("jX0");
      jx_stat_prev = 0;
    }
    if (jx_stat == 1){
      Serial.println("jX1");
      jx_stat_prev = 1;
    }
    if (jx_stat == -1){
      Serial.println("jX-");
      jx_stat_prev = -1;
    }
  }  
  
  jy_read = analogRead(jy);
  if (jy_read < 10) jy_stat = 0;
  if (jy_read > 1000) jy_stat = 1;
  if (jy_read < 1000 && jy_read > 10) jy_stat = -1;  
  
  if (jy_stat != jy_stat_prev){
    if (jy_stat == 0){
      Serial.println("jY0");
      jy_stat_prev = 0;
    }
    if (jy_stat == 1){
      Serial.println("jY1");
      jy_stat_prev = 1;
    }
    if (jy_stat == -1){
      Serial.println("jY-");
      jy_stat_prev = -1;
    }
  }  
  
  /*Niega la lectura, ya que al usar las resistencias internas.
    el estado HIGH es el estado 'normal' y el LOW es el estado activado */
  b1_stat = !digitalRead(b1);
  b2_stat = !digitalRead(b2);
  b3_stat = !digitalRead(b3);
  b4_stat = !digitalRead(b4);
  
  if (b1_stat != b1_stat_prev){
      if (b1_stat == HIGH){
        Serial.println("b11");
        b1_stat_prev = 1;
      }
      else{
        Serial.println("b10");
        b1_stat_prev = 0;
      }
   }
   
   if (b2_stat != b2_stat_prev){
      if (b2_stat == HIGH){
        Serial.println("b21");
        b2_stat_prev = 1;
      }
      else{
        Serial.println("b20");
        b2_stat_prev = 0;
      }
   }
   
   if (b3_stat != b3_stat_prev){
      if (b3_stat == HIGH){
        Serial.println("b31");
        b3_stat_prev = 1;
      }
      else{
        Serial.println("b30");
        b3_stat_prev = 0;
      }
   }
   
   if (b4_stat != b4_stat_prev){
      if (b4_stat == HIGH){
        Serial.println("b41");
        b4_stat_prev = 1;
      }
      else{
        Serial.println("b40");
        b4_stat_prev = 0;
      }
   }

}
