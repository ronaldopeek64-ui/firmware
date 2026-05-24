#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void scanWiFi() {
    // Очищаем экран черным цветом
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 20);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    
    // Выводим статус
    tft.println("Scanning WiFi...");
    Serial.println("Starting WiFi scan...");

    // Запускаем сканирование сетей
    int n = WiFi.scanNetworks();
    
    // Перерисовываем экран под результаты
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);

    if (n == 0) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.println("No networks found.");
    } else {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.printf("Found %d networks:\n\n", n);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(1); // Переключаемся на мелкий шрифт для списка

        // Ограничиваем количество строк, чтобы они не уходили за экран
        int maxLines = 10; 
        for (int i = 0; i < n && i < maxLines; ++i) {
            // Выводим: Номер) Имя сети (Сила сигнала RSSI)
            tft.printf("%d) %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            delay(10);
        }
    }
    
    tft.println("\n");
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Re-scanning in 10s...");
    
    // Очищаем результаты сканирования из памяти
    WiFi.scanDelete();
}

void setup() {
    Serial.begin(115200);

    // ВАЖНО ДЛЯ T-EMBED: Включение питания периферии и экрана
    pinMode(46, OUTPUT);
    digitalWrite(46, HIGH); 
    delay(100);

    // Инициализация дисплея TFT
    tft.init();
    tft.setRotation(3); // Горизонтальный режим экрана для T-Embed
    tft.fillScreen(TFT_BLACK);

    // Включаем Wi-Fi в режиме сканирования
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop() {
    // Запускаем сканирование
    scanWiFi();
    
    // Ждем 10 секунд перед следующим автоматическим сканированием
    delay(10000);
}
