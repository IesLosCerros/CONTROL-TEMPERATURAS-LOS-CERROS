#include <Time.h>
#include <TimeLib.h>
// VARIABLES PARA EL TIEMPO/////////
time_t T0;

//******************


// EJEMPLO PARA CONTROL DE UN COMEDERO AUTOMATICO 
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define HOSTNAME "Comedero-ESP8266" ///< Hostename. The setup function adds the Chip ID at the end.
 
const char* ssid = "BLAVEO-BF925A";
const char* password = "lamejorcontrasenadelmundomundial";
//const char* ssid = "Andared";
//const char* password = "6b629f4c299371737494c61b5a101693a2d4e9e1f3e1320f3ebf9ae379cecf32";


const String Id_Aparato = "AULA 4.01";


unsigned long millisReset;
 int Puerto=8080;

WiFiServer server(Puerto);


IPAddress ip(192, 168, 1, 203); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 1); // set gateway to match your network

String request;
 
void setup() {

 
  Serial.begin(115200);
  delay(10);
 
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
 
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
 
 
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
String routername = Id_Aparato;


WiFi.hostname(routername.c_str()); // change name for router detection - See more at: http://www.esp8266.com/viewtopic.php?f=29&t=11124#sthash.EHt1o5Ni.dpuf
WiFi.mode(WIFI_AP_STA);
//WiFi.mode(WIFI_STA);
  
WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  
 
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
 Serial.println("");
  Serial.println("WiFi connected");
 ArduinoOTA.setPassword((const char *)"2332");
 ArduinoOTA.begin();
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print(":");
    Serial.print(Puerto);
  Serial.println("/");
Serial.println("Mac = "+ String(WiFi.softAPmacAddress().c_str()));
 
 millisReset = millis();


}
 
void loop() {
    ArduinoOTA.handle();

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
  //zona donde poner codigo para ejecutar de forma cíclica   
  
 
 
//
  
  return;
    
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  int contador=0;
  while(!client.available()){
   

    delay(3);
    Serial.println("Esperando cliente disponible para leer");
 if (contador > 4){return;}
  contador ++;
  }
 
  // Read the first line of the request
   request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;

  horaSistema2("HORA_SISTEMA=");//llama a la rutina de poner en hora el sistema

  
  if (request.indexOf("ENCIENDE") != -1) {  //si la cadena no esta en el mensaje devueklve -1 y si no el indice de la primera aparición
   
     Serial.println("ENCIENDE RELE");
      } 
      
  if (request.indexOf("APAGA") != -1) {  //si la cadena no esta en el mensaje devueklve -1 y si no el indice de la primera aparición
  
      Serial.println("APAGA RELE");
    } 
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
 client.println(F("Connection: close"));
 // client.println(F("Refresh: 10"));            // Actualizar cada 5 segs
 client.println(F("")); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   client.print("Fecha en el Arduino="); 
  client.println(StringFecha(now())+ "<br>");

  
          
            //client.println("<h1 align='center'>DIYMakers</h1><h3 align='center'>LED controlado por Servidor Web con Arduino</h3>");
            //Creamos los botones. Para enviar parametres a través de HTML se utiliza el metodo URL encode. Los parámetros se envian a través del símbolo '?'
            client.println("<div style='text-align: left;'>");
           
            client.println("<button onClick=location.href='./ENCIENDE\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 20px;border: 4px solid #3F7CFF;width:150px;'>");
            client.println("ENCIENDE");
           client.println("<button onClick=location.href='./APAGA\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 20px;border: 4px solid #3F7CFF;width:150px;'>");
            client.println("APAGA");
            client.println("</button>");
            client.println("<br>");
            client.println("<form action='/action_page.php' method='get' id='form1'>");
            client.println("<label for='party'>Selecciona Fecha-Hora:</label>");
            client.println("<br>");            
            client.println("<input id='HORASISTEMA' type='datetime-local' name='HORA_SISTEMA' step='1' style='margin:auto;background-color: #84B1FF;color: snow;padding: 20px;border: 4px solid #3F7CFF;width:300px;'>");
            client.println("</form>"); 
            client.println("<button type='submit' form='form1' value='Submit' style='margin:auto;background-color: #84B1FF;color: snow;padding: 20px;border: 4px solid #3F7CFF;width:150px;'>PONER EN HORA</button>");
 //           client.println("<button type='submit' form='form1' value='Submit'>PONER EN HORA</button>");
            //client.println("ACTUALIZAR HORA");   
            client.println("<br>");            
            client.println(WiFi.softAPmacAddress().c_str());
            client.println(Id_Aparato);
          
            client.println("</html>");
 
  delay(1);
  client.stop();
  Serial.println("Client disconnected");
  Serial.println("");
  printFecha(now());
 
}


