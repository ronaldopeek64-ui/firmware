void setup() {
    Serial.begin(115200);

    // ВАЖНО ДЛЯ T-EMBED: Активация главной шины питания периферии
    pinMode(46, OUTPUT);
    digitalWrite(46, HIGH); 
    delay(200); // Даем время подсистеме питания стабилизироваться

    // Инициализация дисплея TFT
    tft.init();
    
    // Принудительный вывод контроллера экрана из зависшего режима сна (Sleep Out)
    tft.writecommand(0x11); 
    delay(150);

    tft.setRotation(3); // Горизонтальный режим (для T-Embed)
    tft.fillScreen(TFT_BLACK);

    // Переводим Wi-Fi модуль в режим сканирования
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(200);
}
