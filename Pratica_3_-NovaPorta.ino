#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi

#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

                               
 
//defines - mapeamento de pinos do NodeMCU
#define D0    16
#define D1    5 
#define D2    4 
#define D3    0 
#define D4    2 
#define D5    14  
#define D6    12 
#define D7    13 
#define D8    15 
#define D9    3  
#define D10   1  


                         
 
// WIFI
const char* myHostname = "escolha_um_nome"; // Nome do host na rede
const char* SSID = "IoT"; // SSID / Wi-fi que iremos nos conectar
const char* PASSWORD = "Cefet@123"; // Senha do wi-fi
 

 
//Prototypes"
void initSerial();
void initWiFi();
void initOTA();
void initMQTT();
void reconectWiFi(); 
void InitOutput(void);
 
/* 
 *  Implementações das funções
 */
void setup() 
{
    //chama as funçoes para inicializar o programa:
    initSerial(); 
    initWiFi();
    initOTA();
    Serial.println("Programa carregado");

}
 

void initSerial() //inicializa o monitor serial
{
    Serial.begin(115200);
}

 

void initWiFi() //se conecta com a rede desejada
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    
    reconectWiFi();
}



void initOTA() //função que cria uma nova porta e define a senha para acessa-la
{
  Serial.println();
  Serial.println("Iniciando OTA....");
  ArduinoOTA.setHostname("nova_porta"); // Define o nome da porta

  // No authentication by default
   ArduinoOTA.setPassword((const char *)"cefetrj"); // senha para carga via WiFi (OTA)
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}
 

 
void reconectWiFi() //reconexao com o wi-fi 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
        
    WiFi.hostname(myHostname); // define o nome do dispositivo na rede 
                               // caso não seja definido o host assumirá o nome padrão do dispositivo         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
  
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


void loop() 
{   
    reconectWiFi(); //chama a função que reconecta com o wi-fi para garantir a conexao
    
    ArduinoOTA.handle();
}
