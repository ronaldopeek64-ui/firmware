#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void scanWiFi() {
    // Очищаем экран черным цветом перед началом сканирования
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 20);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    
    // Выводим статус на экран
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
        tft.setTextSize(1); // Переключаемся на мелкий шрифт для списка сетей

        // Ограничиваем количество строк, чтобы они не уходили за физические границы экрана
        int maxLines = 10; 
        for (int i = 0; i < n && i < maxLines; ++i) {
            // Выводим: Номер) Имя сети (Сила сигнала RSSI в dBm)
            tft.printf("%d) %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            delay(10);
        }
    }
    
    tft.println("\n");
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(2);
    tft.println("Re-scanning in 10s...");
    
    // Очищаем результаты сканирования из оперативной памяти
    WiFi.scanDelete();
}

void setup() {
    Serial.begin(115200);

    // ВАЖНО ДЛЯ T-EMBED: Активация главной шины питания периферии и экрана
    pinMode(46, OUTPUT);
    digitalWrite(46, HIGH); 
    delay(200); // Даем время подсистеме питания стабилизироваться

    // Инициализация дисплея TFT
    tft.init();
    
    // Принудительный вывод контроллера экрана из зависшего режима сна (Sleep Out)
    tft.writecommand(0x11); 
    delay(150);

    tft.setRotation(3); // Горизонтальный режим отображения (для T-Embed)
    tft.fillScreen(TFT_BLACK);

    // Переводим Wi-Fi модуль в правильный режим станции для сканирования эфира
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    delay(200);
}

void loop() {
    // Вызываем функцию сканирования
    scanWiFi();
    
    // Задержка 10 секунд перед следующим автоматическим циклом сканирования
    delay(10000);
}
