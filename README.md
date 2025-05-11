# 🔥 Fire Detection & Alert System (ESP32 + WhatsApp)

This project monitors temperature and flame conditions using an ESP32, LM35 temperature sensor, and a flame sensor.  
In case of fire detection, it automatically sends a **WhatsApp alert** using the CallMeBot API.

---

## 🧰 Hardware Components
- ESP32 Dev Board
- LM35 Temperature Sensor (Analog)
- Flame Sensor (Digital)
- Buzzer + LED for alarm
- Push Button (to acknowledge alert)
- I2C 16x2 LCD Display

---

## 🧠 Features
- Real-time temperature display on LCD
- Flame detection with visual/audio alarm
- WhatsApp alert via CallMeBot
- User acknowledgment required via button
- Message sent only once per fire event

---

## 🪛 Pin Configuration

| Component       | ESP32 Pin |
|----------------|-----------|
| Flame Sensor   | 15        |
| Temp Sensor    | 34        |
| Buzzer         | 18        |
| LED            | 4         |
| Button         | 14        |
| LCD (I2C)      | SDA/SCL   |

---

## 📨 WhatsApp Setup (CallMeBot)
1. Save the number `+34 621073059` to your WhatsApp contacts.
2. Send `I allow callmebot to send me messages` to it via WhatsApp.
3. Get your API key from the reply.
4. Replace `phoneNumber` and `apiKey` in the code.

---

## ▶️ How to Use
1. Upload the `fire_alert_system_cleaned.ino` to your ESP32 using Arduino IDE.
2. Monitor temperature and flame status on LCD and Serial Monitor.
3. In case of fire:
   - LED and buzzer will activate
   - WhatsApp alert will be sent
   - Alert resets when button is pressed

---

## 📄 License
MIT License.
