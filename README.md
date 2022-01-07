![alt tag](https://i.ibb.co/YthtbLh/Giifff-mid.gif)
***
# Comunicação Serial: Arduino com ESP-01
Neste guia, você criará uma comunicação Serial entre o Arduino e o módulo WiFi ESP-01. Você aprenderá a filtrar e selecionar os dados corretos para a sua aplicação.
***
## Contextualização
Iremos programar um contador no ESP-01 e enviar as informações via Serial para o Arduino. O Arduino, por sua vez, irá verificar se os dados estão completos. Após a verificação irá exibir as informações coerentes.
> Muitas vezes, em projetos que utilizam WiFi, os dados acabam chegando corrompidos. Dependendo da importância do dado para o seu projeto, isso pode ser um grande problema. Por esse motivo, o Arduino irá verificar se o dado é consistente antes de imprimir no Display.

## Requerimentos
- Placa Arduino Uno;
- Módulo ESP-01;
- Display OLED (usei um de 128x32);
- Jumpers para conexão de componentes.

## Preparando a IDE do Arduino para utilizar o módulo ESP-01.
Para programar o ESP-01 você pode utilizar adaptadores USB, porém neste guia iremos programar o ESP-01 diretamente do Arduino Uno, sem a necessidade de utilizar adaptadores.
> Vale ressaltar que o ESP-01 possui um chip microcontrolador, o ESP8266. Então é necessário criar um código para o ESP-01 e outro para o Arduino.

Em sua Arduino IDE vá em: Arquivo > Preferências

<p align="center">
  <img src="https://i.ibb.co/pfNTZ7p/preparando-1.png" alt="Teste"/>
</p>

Em "URLs Adicionais para Gerenciadores de Placas" escreva: http://arduino.esp8266.com/stable/package_esp8266com_index.json

Dê "OK" para salvar

<p align="center">
  <img src="https://i.ibb.co/KLMDpYC/preparando-2.png" alt="Teste"/>
</p>

Em sua Arduino IDE vá em: Ferramentas > Placa > Gerenciador de Placas

<p align="center">
  <img src="https://i.ibb.co/yspM6M3/preparando-3.png" alt="Teste"/>
</p>

Pesquise por "ESP8266", escolha a opção da imagem e clique em "Instalar" (como eu já tinha instalado, não apareceu a opção "Instalar")

<p align="center">
  <img src="https://i.ibb.co/1nfSQYM/preparando-4.png" alt="Teste"/>
</p>

Pronto! Com isso a IDE do Arduino já está pronta para utilizar o módulo ESP-01.

## Biblioteca do Display OLED
Para utilizar o display OLED é necessário instalar bibliotecas.

Em sua Arduino IDE vá em: Sketch > Incluir Biblioteca > Gerenciar Bibliotecas

<p align="center">
  <img src="https://i.ibb.co/xC958xP/preparando-5.png" alt="Teste"/>
</p>

Pesquise por "SSD1306", escolha a opção da imagem e clique em "Instalar" (como eu já tinha instalado, não apareceu a opção "Instalar")

<p align="center">
  <img src="https://i.ibb.co/K6cwQsX/preparando-6.png" alt="Teste"/>
</p>

> Caso apareça alguma caixa pedindo a instalação de bibliotecas adicionais, clique em "Install All".

## Esquema de Montagem

## Código do ESP-01

```cpp
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
```

## Código do Arduino

```cpp
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Comprimento do Display
#define SCREEN_HEIGHT 32 // Altura do Display
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C // Endereço I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial cdSerial_ESP(10, 11); // Comunicação Serial com o ESP-01 (TX e RX)


void setup() {

  cdSerial_ESP.begin(9600);
  delay(500);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.print("Inicializando...");
  display.display();
  delay(500);
}

void loop() {

  String vsData;
  
  if (cdSerial_ESP.available() > 0)
  {
    vsData = cdSerial_ESP.readString();
    if (vsData.startsWith("i") && vsData.endsWith("f"))
    {
      vsData = vsData.substring(1, (vsData.length() - 1));
      display.clearDisplay();
      display.setCursor(0,16);
      display.print("Dado recebido: " + vsData);
      display.display();
    }
  }

  delay(1000);
}
```
