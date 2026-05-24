#include <M5Unified.h>
#include <WiFi.h>

void scanWiFi() {
    // Безопасно очищаем экран средствами M5Unified
    M5.Display.clear(BLACK);
    M5.Display.setCursor(10, 20);
    M5.Display.setTextColor(YELLOW);
    M5.Display.setTextSize(2);
    
    M5.Display.println("Scanning WiFi...");
    Serial.println("Starting WiFi scan...");

    // Сканируем частоты
    int n = WiFi.scanNetworks();
    
    M5.Display.clear(BLACK);
    M5.Display.setCursor(10, 10);

    if (n == 0) {
        M5.Display.setTextColor(RED);
        M5.Display.println("No networks found.");
    } else {
        M5.Display.setTextColor(GREEN);
        M5.Display.printf("Found %d networks:\n\n", n);
        M5.Display.setTextColor(WHITE);
        M5.Display.setTextSize(1); // Мелкий шрифт для списка

        // Ограничиваем строки по высоте дисплея T-Embed
        int maxLines = (M5.Display.height() - 40) / 12; 
        for (int i = 0; i < n && i < maxLines; ++i) {
            M5.Display.printf("%d) %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
            delay(10);
        }
    }
    
    M5.Display.println("\n");
    M5.Display.setTextColor(BLUE);
    M5.Display.setTextSize(2);
    M5.Display.println("Re-scanning in 10s...");
    
    WiFi.scanDelete();
}

void setup() {
    // 1. Инициализация T-Embed встроенным алгоритмом Брюса
    auto cfg = M5.config();
    M5.begin(cfg);

    // 2. Настройка экрана
    M5.Display.setRotation(3); // Горизонтальный режим
    M5.Display.setBrightness(200); // Яркость подсветки на максимум
    M5.Display.clear(BLACK);

    // 3. Старт Wi-Fi
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    delay(200);
}

void loop() {
    // Каждые 10 секунд сканируем эфир
    scanWiFi();
    delay(10000);
}
