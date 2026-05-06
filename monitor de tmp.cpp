#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereço 0x27 com 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = A0;     // Pino do TMP36
const int ledPin = 8;         // Pino do LED vermelho

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int leitura = analogRead(sensorPin);

  // Conversão para temperatura em Celsius para TMP36
  float tensao = leitura * (5.0 / 1023.0);      // converte leitura em volts
  float temperatura = (tensao - 0.5) * 100.0;   // fórmula do TMP36

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);  // mostra 1 casa decimal
  lcd.print(" C");

  if (temperatura > 30.0) {
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ALERTA: Calor");
  } else {
    digitalWrite(ledPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Temperatura ok");
  }

  delay(1000);  // atualiza a cada 1 segundo
}
