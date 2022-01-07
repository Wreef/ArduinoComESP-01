![alt tag](https://i.ibb.co/YthtbLh/Giifff-mid.gif)
# Arduino com ESP-01
Neste guia, você criará uma comunicação Serial entre o Arduino e o módulo WiFi ESP-01. Você aprenderá a filtrar e selecionar os dados corretos para a sua aplicação.

## Contexto
Iremos programar um contador no ESP-01 e enviar as informações via Serial para o Arduino. O Arduino, por sua vez, irá verificar se os dados estão completos. Após a verificação irá exibir as informações coerentes.
> Muitas vezes, em projetos que utilizam WiFi, os dados acabam chegando corrompidos. Dependendo a importância do dado para o seu projeto, isso pode ser um grande problema. Por esse motivo o Arduino irá verificar se o dado é consistente antes de imprimir no Display.

## Requerimentos
- Placa Arduino Uno;
- Módulo ESP-01;
- Display OLED (usei um de 128x32);
- Jumpers.
