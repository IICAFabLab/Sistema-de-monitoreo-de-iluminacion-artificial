# Sistema de monitoreo de iluminación artificial

Este proyecto consiste en explorar las posibilidades de implementación y escalamiento de la tecnología de luz artificial para cultivos de interés agrícola, como crisantemos y fresas, esto en beneficio de los sectores exportadores.

Para una validación más rigurosa se diseñó una serie de sensores que cuantifican variables de interés en los sistemas de cultivos con iluminación artificial, como lo son: humedad ambiental, humedad del suelo, temperatura ambiental, lux, luz visible, luz infrarroja, índice UV, calidad del aire y CO2, tanto fuera como dentro del invernadero. 

Además, se implementó un sistema de internet de las cosas (IoT) tanto para monitorear en tiempo real las variables mencionadas, como para disponer de un registro web actualizado con los datos de interés.

## Componentes del sistema

- Placa DOIT ESP32 DevKit V1: Este dispositivo funcionará como la unidad de procesamiento de los diferentes periféricos y almacenarlos en la nube.

- Sensor de índice ultravioleta SI1145: Cobertura del espectro de radiación electromagnética para luz visible, infrarroja y ultravioleta.

- Sensor de iluminancia TSL259: Posee una gran precisión en la iluminancia con mediciones de hasta 88 000 lux

- Sensor de temperatura y humedad relativa DHT21

- Sensor de compuestos orgánicos volátiles SGP30

- Sensor de moléculas de CO<sub>2</sub> SCD30

- Sensor capacitivo de humedad de suelo

## Diagrama eléctrico sistema de monitoreo exterior

<img src= "https://user-images.githubusercontent.com/111079577/201004450-5db4b4da-f6c5-4749-ab93-d828aafa26f6.png" width=650/> 

<img src= "https://user-images.githubusercontent.com/111079577/201004462-7b4825f2-a0bc-458a-9f5e-b54b71775edc.png" width=650/> 

## Diagrama eléctrico sistema de monitoreo interior

<img src= "https://user-images.githubusercontent.com/111079577/201004548-8ff07bcc-399e-471b-a611-50b34ba72604.png" width=650/> 

<img src= "https://user-images.githubusercontent.com/111079577/201004555-9d85cc91-3137-43dd-9397-d0f2a2a3a5c6.png" width=650/> 

## Sistema ensamblado

<img src= "https://user-images.githubusercontent.com/111079577/201004717-94cc8964-5d79-438f-a332-1b84ef6023ba.png" width=650/> 

## Despliegue de datos en el dashboard del sevicio de Blynk

<img src= "https://user-images.githubusercontent.com/111079577/201004735-ff8f9551-e526-4e04-a344-4c807a0eb3e8.png" width=650/> 
