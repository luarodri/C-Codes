
#include <ESP8266WiFi.h>  // Inclui a biblioteca

//Variáveis e objetos globais
WiFiClient espClient; // Cria espClient

// WIFI
const char* myHostname = "escolha_um_nome"; // Nome do host na rede
const char* SSID = "Hopekook"; // SSID / nome da rede WI-FI 
const char* PASSWORD = "010997jk"; // Senha da rede WI-FI
void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------"); //imprime no visor o nome do dispositivo
    Serial.print("Conectando-se na rede: "); // imprime no visor "conectando"
    Serial.println(SSID); // imprime no visor o nome do dispositivo, Hopekook
    Serial.println("Aguarde"); // está aguardando a conexão restante
    
    reconectWiFi();
}


void reconectWiFi() 
{
   //loop para saber se está conectado ou não, caso não esteja, será feito novas tentativas. 
  
    if (WiFi.status() == WL_CONNECTED)  // se conectado retorna
        return;
    
    WiFi.hostname(myHostname); // define o nome do dispositivo na rede 
                               // caso não seja definido o host assumirá o nome padrão do dispositivo   
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
    
    while (WiFi.status() != WL_CONNECTED)  // entra no loop do while até se conectar
    {
        delay(100); // Aguarda 100 ms
        Serial.print("Li");
    }
  
    Serial.println(); // imprime na tela
    Serial.print("Conectado com sucesso na rede: "); //conectou
    Serial.print(SSID);
    Serial.println();
    Serial.print("IP obtido: "); 
    Serial.print(WiFi.localIP());  // mostra o endereço IP obtido via DHCP
    Serial.println();
    Serial.print("Endereço MAC: ");
    Serial.print(WiFi.macAddress()); // mostra o endereço MAC do esp8266
}


void setup() {
  Serial.begin(115200); // observe a velocidade de conexão com o terminal
  initWiFi();
}

void loop() {
  
  reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita

}
