int viContador = 0;


void setup() {
  
  Serial.begin(9600);
  delay(500);
}

void loop() {

  Serial.println("O" + String(viContador) + "K");
  viContador += 1;
  delay(5000);
}
