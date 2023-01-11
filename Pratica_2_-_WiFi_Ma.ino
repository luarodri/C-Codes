
#include <ESP8266WiFi.h>  // Inclui a biblioteca
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

//Variáveis e objetos globais
WiFiClient espClient; // Cria o espClient

// WIFI
const char* myHostname = "escolha_um_nome"; // Nome do host na rede
const char* SSID = "Wifi Anna"; // SSID / nome da rede WI-FI 
const char* PASSWORD = "cefet12345"; // Senha da rede WI-FI 

 
void init_WifiAp() 
{
  WiFi.hostname(myHostname);
  WiFiManager wifiManager;
   
  //wifiManager.resetSettings(); //Usado para resetar sssid e senhas armazenadas
  
  wifiManager.autoConnect(SSID, PASSWORD); //auto conecta com a senha e o wifi
  Serial.print("Conectado com sucesso na rede via WifiManager na rede: "); //imprime na tela conectando
  Serial.println(WiFi.SSID());
  Serial.println();
  Serial.print("IP obtido: ");
  Serial.print(WiFi.localIP());  // mostra o endereço IP obtido via DHCP
  Serial.println();
  Serial.print("Endereço MAC: ");
  Serial.print(WiFi.macAddress()); // mostra o endereço MAC do esp8266
}




void setup() {
Serial.begin(115200); //velocidade de conexão com o terminal
init_WifiAp(); // inicia o WiFiManager
}

void loop() {
       if (WiFi.status() == WL_CONNECTED)
        return;
        
      WiFi.hostname(myHostname);
      WiFi.begin(); // Conecta na rede WI-FI
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print("-");
  
       Serial.println();
       Serial.print("Conectado com sucesso na rede: ");
       Serial.print(SSID);
       Serial.println();
       Serial.print("IP obtido: ");
       Serial.print(WiFi.localIP());  // mostra o endereço IP obtido via DHCP
       Serial.println();
       Serial.print("Endereço MAC: ");
       Serial.print(WiFi.macAddress()); // mostra o endereço MAC do esp8266
}

}