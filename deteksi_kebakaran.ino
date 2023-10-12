#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "realme 10";
const char* Password = "173006devic";

#define pinSensor 5
#define pinLED 4

String url;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  pinMode(pinSensor, INPUT);
  pinMode(pinLED, OUTPUT);

  WiFi.hostname("NodeMCU");
  WiFi.begin(ssid, Password);

  while(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(pinLED, LOW);
    delay(500);
  }
  digitalWrite(pinLED, HIGH);
}

void loop() {
  int api = digitalRead(pinSensor);
  if(api==1)
  {
    Serial.println("Tidak Ada Api");
  }
  else
  {
    Serial.println("Ada Titik Api");
    kirim_wa("Bahaya!!!\nTelah Ditemukan Titik Api Di Tempat Anda.\n\nSegera Evakuasi barang-barang Anda.");
  }
  delay(500);
}

void kirim_wa(String pesan)
{
  url = "http://api.callmebot.com/whatsapp.php?phone=6289652569947&text="+ urlencode(pesan) +"&apikey=5144849";
  postData();
}

void postData()
{
  int httpCode ;
  HTTPClient http;
  http.begin(client, url);
  httpCode = http.POST(url);
  if(httpCode==200)
  {
    Serial.println("Notifikasi WhatsApp Gagal Terkirim");
  }
  else 
  {
    Serial.println("Notifikasi WhatsApp Berhasil Terkirim");
  }
  http.end();
}

String urlencode(String str)
{
  String encodedString="";
  char c;
  char code0, code1, code2;
  for(int i=0; i<str.length(); i++)
  {
    c = str.charAt(i);
    if(c == ' '){
      encodedString += '+' ;
    }
    else if(isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if((c & 0xf) >9) {
        code1 = (c & 0xf) - 10 + 'A' ;
      }
      c = (c>>4)&0xf;
      code0 = c+'0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
    yield();
  }
  Serial.println(encodedString);
  return encodedString ;
}
