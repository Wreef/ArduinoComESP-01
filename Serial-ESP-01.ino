int viContador = 0;


void setup() {
  
  Serial.begin(9600);
  delay(500);
}

void loop() {

  Serial.println("i" + String(viContador) + "f");
  viContador += 1;
  delay(5000);
}
