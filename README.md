Integração do módulo Esp8266 e o sensor de CO2 MH-Z19C com uma API Rest para salvar as medições em um banco de dados.

# Execução

Compilar e carregar no Arduino IDE para placa NodeMCU 0.9 (ESP-12 module) ou NodeMCU 1.0 (ESP-12E module) dependendo do modelo do ESP8266.

# Arquivo teste-mhz19.ino

Apenas um teste do sensor onde são printadas as medições realizadas no terminal do Arduino IDE.

# Arquivo sensor_CO2.ino

Programa que conecta ao Wi-Fi e integra as medições com o servidor.

- Alterar valor de "ssid" para o nome da rede utilizada.
- Alterar valor de "password" para a senha da rede utilizada. 
- "authorizationId" é o Id de identificação do sensor e deve ser adicionado previamente na collection "tokens" no banco.
- "serverName" é a url para inserção das medições.
- Caso seja desejado fazer requisições localmente remover fingerprint da requisição.
