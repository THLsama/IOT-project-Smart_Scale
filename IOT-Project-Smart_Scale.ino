#define BLYNK_TEMPLATE_ID "TMPL6pj_Ti5Eq"
#define BLYNK_TEMPLATE_NAME "ESP32 Smart Scale"
#define BLYNK_AUTH_TOKEN "9J1dqZ31UK_tRGS-9y6vmlhvsoXC2wfg"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Hehe-boi";
char pass[] = "1011010220";

#define TRIG_PIN 13
#define ECHO_PIN 12
#define GREEN_LED 4
#define RED_LED 2

BlynkTimer timer;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    timer.setInterval(1000L, sendDataToBlynk);
}

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2; // Convert to cm
    return distance;
}

void sendDataToBlynk() {
    float distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Blynk.virtualWrite(V1, distance);

    if (distance > 10) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        Blynk.virtualWrite(V2, "Nice Distance");  // Show status in Blynk
    } else {
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        Blynk.virtualWrite(V2, "Too close!!!!!!!");  // Show status in Blynk
    }
}

void loop() {
    Blynk.run();
    timer.run();
}
