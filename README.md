![logo](https://i.ibb.co/YthtbLh/Giifff-mid.gif)
***
# Comunicação Serial: Arduino com ESP-01
Neste guia, você criará uma comunicação Serial entre o Arduino e o módulo WiFi ESP-01. Você aprenderá a filtrar e selecionar os dados corretos para a sua aplicação.
***
## Contextualização
Iremos programar um contador no ESP-01 e enviar as informações via Serial para o Arduino. O Arduino, por sua vez, irá verificar se os dados estão completos. Após a verificação irá exibir as informações coerentes.
> Muitas vezes, em projetos que utilizam WiFi, os dados acabam chegando corrompidos. Dependendo da importância do dado para o seu projeto, isso pode ser um grande problema. Por esse motivo, o Arduino irá verificar se o dado é consistente antes de imprimir no Display.

## Requerimentos
- Placa Arduino Uno;
- Módulo ESP-01 (https://www.robocore.net/wifi/modulo-wifi-esp8266);
- Adaptador para 5V do ESP-01 (https://www.robocore.net/placa-robocore/adaptador-para-esp8266);
- Display OLED (usei um de 128x32);
- Jumpers para conexão de componentes.

## Preparando a IDE do Arduino para utilizar o módulo ESP-01.
Para programar o ESP-01 você pode utilizar adaptadores USB, porém neste guia iremos programar o ESP-01 diretamente do Arduino Uno, sem a necessidade de utilizar adaptadores.
> Vale ressaltar que o ESP-01 possui um chip microcontrolador, o ESP8266. Então é necessário criar um código para o ESP-01 e outro para o Arduino.

Em sua Arduino IDE vá em: Arquivo > Preferências

<p align="center">
  <img src="https://i.ibb.co/pfNTZ7p/preparando-1.png" alt="1"/>
</p>

Em "URLs Adicionais para Gerenciadores de Placas" escreva: http://arduino.esp8266.com/stable/package_esp8266com_index.json

Dê "OK" para salvar.

<p align="center">
  <img src="https://i.ibb.co/KLMDpYC/preparando-2.png" alt="2"/>
</p>

Em sua Arduino IDE vá em: Ferramentas > Placa > Gerenciador de Placas

<p align="center">
  <img src="https://i.ibb.co/yspM6M3/preparando-3.png" alt="3"/>
</p>

Pesquise por "ESP8266", escolha a opção da imagem e clique em "Instalar" (como eu já tinha instalado, não apareceu a opção "Instalar").

<p align="center">
  <img src="https://i.ibb.co/1nfSQYM/preparando-4.png" alt="4"/>
</p>

Pronto! Com isso a IDE do Arduino já está pronta para utilizar o módulo ESP-01.

## Biblioteca do Display OLED
Para utilizar o display OLED é necessário instalar bibliotecas.

Em sua Arduino IDE vá em: Sketch > Incluir Biblioteca > Gerenciar Bibliotecas

<p align="center">
  <img src="https://i.ibb.co/xC958xP/preparando-5.png" alt="5"/>
</p>

Pesquise por "SSD1306", escolha a opção da imagem e clique em "Instalar" (como eu já tinha instalado, não apareceu a opção "Instalar").

<p align="center">
  <img src="https://i.ibb.co/K6cwQsX/preparando-6.png" alt="6"/>
</p>

> Caso apareça alguma caixa pedindo a instalação de bibliotecas adicionais, clique em "Install All".

## Esquema de Montagem para Enviar o Código para o ESP-01

Adaptador ESP-01 | Arduino
:---: | :---:
5V | 5V
GND | GND
TX | TX
RX | RX
GPIO-0 | GND

> Conectar o RESET do Arduino ao GND para realizar o upload do código do ESP-01.

<p align="center">
  <img src="https://i.ibb.co/6DCrcsj/proj1-fim-esp.png" alt="7"/>
</p>

## Código do ESP-01

```cpp
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
```

## Entendendo o Código do ESP-01
Inicialmente é criado uma variável (viContador) para iniciar o contador.

```cpp
int viContador = 0;
```

Na função setup o Serial é iniciado. É pelo Serial que iremos mandar as informações para o Arduino.

```cpp
void setup() {
  
  Serial.begin(9600);
  delay(500);
}
```

Na função loop iremos imprimir a variável do contador (viContador) com uma letra "O" no início e uma letra "K" no final. Essas letras serão usadas pelo Arduino como forma de verificação de integridade da informação.

Logo em seguida iremos somar "+1" ao contador e iremos dar um itervalo de 5 segundos entre os envios.

```cpp
void loop() {

  Serial.println("O" + String(viContador) + "K");
  viContador += 1;
  delay(5000);
}
```

## Enviando o Código para o ESP-01
Após realizar a montagem do esquema da imagem anterior, é necessário selecionar o módulo na IDE do Arduino.

Em sua Arduino IDE vá em: Ferramentas > Placa > ESP8266 Boards > Generic ESP8266 Module

<p align="center">
  <img src="https://i.ibb.co/P6g926K/esp01module.png" alt="9"/>
</p>

Após selecionar o módulo ESP8266 é só enviar o código para o ESP-01.

## Esquema de Montagem Final

Arduino | Adaptador ESP-01 | Display OLED
:---: | :---: | :---:
5V | 5V | 5V
GND | GND | GND
A4 | - | SDA
A5 | - | SDK
A10 | TX | -
A11 | RX | -

<p align="center">
  <img src="https://i.ibb.co/yg5Dkks/proj1-fim.png" alt="8"/>
</p>

## Código do Arduino

```cpp
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial cdSerial_ESP(10, 11);


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
    if (vsData.startsWith("O") && vsData.endsWith("K\r\n"))
    {
      vsData = vsData.substring(1, (vsData.length() - 3));
      display.clearDisplay();
      display.setCursor(0,16);
      display.print("Dado recebido: " + vsData);
      display.display();
    }
  }

  delay(1000);
}
```

## Entendendo o Código do Arduino
Inicialmente importamos as bibliotecas necessárias para o funcionamento do código.

```cpp
#include <SoftwareSerial.h> // Comunicação Serial
#include <SPI.h> // Display OLED
#include <Wire.h> // Display OLED
#include <Adafruit_GFX.h> // Display OLED
#include <Adafruit_SSD1306.h> // Display OLED
```

Em seguida definimos alguns parâmetros para o Display OLED e criamos a comunicação Serial com o ESP-01 (cdSerial_ESP).

```cpp
#define SCREEN_WIDTH 128 // Comprimento do Display
#define SCREEN_HEIGHT 32 // Altura do Display
#define OLED_RESET     4  // Pino de Reset
#define SCREEN_ADDRESS 0x3C // Endereço I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Display OLED


SoftwareSerial cdSerial_ESP(10, 11); // Comunicação Serial com o ESP-01 (TX e RX)
```

Na função setup iniciamos a comunicação Serial com o ESP-01 e ligamos o Display.

```cpp
void setup() {

  cdSerial_ESP.begin(9600); // Iniciando a comunicação Serial
  delay(500);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Ligando o Display
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
```

Na função loop criamos a variável (vsData) que receberá as informações do ESP-01.

Utilizamos as funções startsWith() e endsWith() para verificar como inicia e como termina a informação enviada pelo ESP-01 (https://docs.arduino.cc/built-in-examples/strings/StringStartsWithEndsWith). 

No código "if (vsData.startsWith("O") && vsData.endsWith("K\r\n"))" usamos duas condições para permitir a impressão da informação no display. Verificamos se o dado recebido inicia com "O" e se termina com "K". Se as duas condições forem satisfeitas, o Arduino remove os dois caracteres e imprime somente o valor do contador.

> Note que em "vsData.endsWith("K\r\n")" foi acrescentado "\r\n" além do caractere "K". O "\r" representa a ação de pressionar a tecla ENTER para pular um parágrafo. O "\n" representa o parágrafo criado. Esses caracteres surgem devido o uso da função "Serial.printl()" usada no código do ESP-01.

A função "substring()" serve para selecionar uma parte de uma variável de texto. Neste caso selecionamos somente os valores do contador (https://www.arduino.cc/reference/pt/language/variables/data-types/string/functions/substring/).

```cpp
void loop() {

  String vsData;
  
  if (cdSerial_ESP.available() > 0)
  {
    vsData = cdSerial_ESP.readString();
    if (vsData.startsWith("O") && vsData.endsWith("K\r\n"))
    {
      vsData = vsData.substring(1, (vsData.length() - 3));
      display.clearDisplay();
      display.setCursor(0,16);
      display.print("Dado recebido: " + vsData);
      display.display();
    }
  }

  delay(1000);
}
```

## Enviando o Código para o Arduino
Após realizar a montagem do esquema da imagem anterior, é necessário selecionar a placa Arduino Uno na IDE do Arduino.

Em sua Arduino IDE vá em: Ferramentas > Placa > Arduino AVR Boards > Arduino Uno

<p align="center">
  <img src="https://i.ibb.co/y5hGgch/arduinouno.png" alt="10"/>
</p>

Após selecionar a placa Arduino Uno é só enviar o código.

## Conclusão
Esse tipo de projeto é bastante útil quando o se utiliza o ESP-01 para coletar dados em algum banco de dados e enviar para o Arduino, que por sua vez, irá tomar alguma decisão. Com o verificador de integridade do dado é possível evitar falhas no projeto.

Este guia apresenta somente uma informação básica de comunicação Serial entre Arduino e ESP-01.

# Obrigado(a)!
<p align="center">
  <img src="https://i.ibb.co/09f12gG/ezgif-com-gif-maker-1.gif" alt="12"/>
</p>
