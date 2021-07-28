#include "MHZ19.h"

const int rx_pin = 13; //Serial rx pin no
const int tx_pin = 15; //Serial tx pin no

const int pwmpin = 14;

MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);
//MHZ19 *mhz19_pwm = new MHZ19(pwmpin);

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
    Serial.begin(115200);
    mhz19_uart->begin(rx_pin, tx_pin);
    mhz19_uart->setAutoCalibration(false);
    delay(3000); // Issue #14
    Serial.print("MH-Z19 now warming up...  status:");
    Serial.println(mhz19_uart->getStatus());
    delay(1000);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
    measurement_t m = mhz19_uart->getMeasurement();
    Serial.println("---------------");
    Serial.print("co2: ");
    Serial.println(m.co2_ppm);
    Serial.print("aquecido: ");
    Serial.println(mhz19_uart->isWarming());
//    Serial.print("temp: ");
//    Serial.println(m.temperature);

//    int co2ppm = mhz19_pwm->getPpmPwm();
//    Serial.print("pwm co2: ");
//    Serial.println(co2ppm);
//    Serial.println("{\"medicao\":\""+(String)m.co2_ppm+"\",\"idSensor\":\"teste\",\"ambiente\":{\"nome\":\"teste 1\",\"id\":\"esp8266\"}}");
    
    delay(5000);
}
