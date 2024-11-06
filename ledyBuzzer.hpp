
void definirColor(int rojo, int verde, int azul, boolean anodoComun)
{
  if(anodoComun == true)
  {
    rojo = 255 - rojo;
    verde = 255 - verde;
    azul = 255 - azul;
  }
  analogWrite(led_R, rojo); // Prende LED ROJO
  analogWrite(led_V, verde); // Prende LED VERDE
  analogWrite(led_A, azul); // Prende LED AZUL
}

void inicializarAccesorios(){
  pinMode(led_R, OUTPUT);  //Inicia LED ROJO
  pinMode(led_V, OUTPUT);  //Inicia LED VERDE
  pinMode(led_A, OUTPUT);  //Inicia LED AZUL
  definirColor(0, 255, 0,anodoComun0);  // empieza con LED en verde

  pinMode(cal_pin, INPUT_PULLUP); // entrada pulsado para calibrar, seteada como pullup para poder conectar pulsador sin poner resistencia adicional

  pinMode(buzzer, OUTPUT); //Inicia buzzer
  tone(buzzer, 55,20);
}
