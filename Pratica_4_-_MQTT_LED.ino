#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient

#include <ESP8266mDNS.h>


//defines de id mqtt e tópicos para publicação e subscribe

#define TOPICO_SUBSCRIBE_P1 "pratica-4/LED"     //tópico MQTT de escuta luz 1



                                                   
#define ID_MQTT  "id_led"     //id mqtt (para identificação de sessão)
                               //IMPORTANTE: este deve ser único no broker (ou seja, 
                               //            se um client MQTT tentar entrar com o mesmo 
                               //            id de outro já conectado ao broker, o broker 
                               //            irá fechar a conexão de um deles).

#define USER_MQTT  "login"   // usuario no MQTT
#define PASS_MQTT  "senha"  // senha no MQTT 

                               
 
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
const char* SSID = "Silva"; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "MaFs1972"; // Senha da rede WI-FI que deseja se conectar
 
// MQTT
const char* BROKER_MQTT = "test.mosquitto.org"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
 
//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient

 
//Cria as funções para que elas possam ser chamadas entre si
void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);
 
/* 
 *  Implementações das funções
 */
void setup() 
{
    //inicializações:
    initSerial(); //inicia o monitor serial
    initWiFi(); //realiza a conexao com o wi-fi
    initMQTT(); //faz a cnexao com o mqtt
    InitOutput(); //chama funcoes para o led acender e apagar

}
 

void initSerial() // inicia a comunicação serial com a velocidade de 115200
{
    Serial.begin(115200);
}
 
void initWiFi()//realiza a conexão com o wi-fi 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    
    reconectWiFi();
}
 
void initMQTT() //chama funções para inicializar a conexao com o mqtt
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
 
void mqtt_callback(char* topic, byte* payload, unsigned int length) //funcao que é chamada toda vez que uma informação dos tópicos sobreescritos chega
{
    String msg;
 
    for(int i = 0; i < length; i++) //faz a string do payload
    {
       char c = (char)payload[i];
       msg += c;
      
    }

    Serial.println("msg = " +  msg); //imprime no serial a mensagem

   if (msg.equals("ON")) // liga led
   {
      digitalWrite(D1, HIGH);
      Serial.println("Ligado led");
   }

   if (msg.equals("OFF")) //apaga led
   {
      digitalWrite(D1, LOW);
      Serial.println("Desligado led");
   }   

 
}


void reconnectMQTT() //caso a conexao com o MQTT nao funcione, essa funcao é chamada para que tente reconectar
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
//        if (MQTT.connect(ID_MQTT, USER_MQTT,PASS_MQTT)) // parameros usados para broker proprietário
                                                          // ID do MQTT, login do usuário, senha do usuário
 
           if (MQTT.connect(ID_MQTT))
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE_P1); //quando ele consegue conectar, sobreescreve o tópico
 
        } 
        else 
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

 
void reconectWiFi() //reconexao com wi-fi
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
        
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


void VerificaConexoesWiFIEMQTT(void) //checa se há conexao com o mqtt e com o wifi
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
    
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
 

void InitOutput(void) //envia sinal para led acender ou apagar
{
    //enviar HIGH para o output faz o Led acender / enviar LOW faz o Led apagar)
    
    pinMode(D1, OUTPUT);
    digitalWrite(D1, LOW);
              
}

 
 
//programa principal
void loop() 
{   

    //garante funcionamento das conexões WiFi e ao broker MQTT
    VerificaConexoesWiFIEMQTT();
    
 
    //keep-alive da comunicação com broker MQTT
    MQTT.loop();
   
}
