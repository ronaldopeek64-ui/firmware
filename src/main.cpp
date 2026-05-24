#include <Arduino.h>

// Пины периферии LilyGO T-Embed
#define POWER_PIN    46  // Главное питание всей платы (включает всё)
#define LED_PIN      21  // Стандартный RGB/сигнальный пин (в некоторых ревизиях Брюса)
#define LCD_BL_PIN   15  // Пин подсветки экрана
#define LED_DATA_PIN 42  // Data-пин кольца джойстика APA102
#define LED_CLK_PIN  45  // Clock-пин кольца джойстика APA102

void setup() {
    Serial.begin(115200);

    // Переводим все возможные пины индикации в режим вывода
    pinMode(POWER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LCD_BL_PIN, OUTPUT);
    pinMode(LED_DATA_PIN, OUTPUT);
    pinMode(LED_CLK_PIN, OUTPUT);
}

void loop() {
    Serial.println("TEST: Turning EVERYTHING ON");
    
    // Подаем питание на плату и зажигаем пины
    digitalWrite(POWER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LCD_BL_PIN, HIGH);
    digitalWrite(LED_DATA_PIN, HIGH);
    digitalWrite(LED_CLK_PIN, HIGH);
    
    delay(1000); // Ждем 1 секунду

    Serial.println("TEST: Turning EVERYTHING OFF");
    
    // Гасим все пины и отключаем питание периферии
    digitalWrite(POWER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LCD_BL_PIN, LOW);
    digitalWrite(LED_DATA_PIN, LOW);
    digitalWrite(LED_CLK_PIN, LOW);
    
    delay(1000); // Ждем 1 секунду
}
