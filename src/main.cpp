#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void scanWiFi() {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 20);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    
    tft.println("Scanning WiFi...");
    Serial.println("Starting WiFi scan...");

    int n = WiFi.scanNetworks();
    
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);

    if (n == 0) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.println("No networks found.");
    } else {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.printf("Found %d networks:\n\n", n);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(1);

        int maxLines = 10; 
        for (int i = 0; i < n && i < maxLines; ++i) {
            tft.printf("%d) %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            delay(10);
        }
    }
    
    tft.println("\n");
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Re-scanning in 10s...");
    
    WiFi.scanDelete();
}

void setup() {
    Serial.begin(115200);

    // 1. ВКЛЮЧАЕМ ГЛАВНОЕ ПИТАНИЕ ПЛАТЫ (Секрет LilyGO)
    pinMode(46, OUTPUT);
    digitalWrite(46, HIGH); 
    delay(200); 

    // 2. ИНИЦИАЛИЗАЦИЯ И ВКЛЮЧЕНИЕ ПОДСВЕТКИ ЭКРАНА (Пин 15)
    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH); // Подаем высокий уровень, чтобы зажечь экран
    delay(50);

    // 3. ЗАПУСК ДИСПЛЕЯ
    tft.init();
    tft.writecommand(0x11); // Выход из режима сна контроллера
    delay(150);

    tft.setRotation(3); // Поворот экрана (горизонтальный)
    tft.fillScreen(TFT_BLACK);

    // 4. НАСТРОЙКА WI-FI
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    delay(200);
}

void loop() {
    scanWiFi();
    delay(10000);
}
