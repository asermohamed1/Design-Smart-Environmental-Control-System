# Design-Smart-Environmental-Control-System using Simulide , arduino ide
/*
  1. Temperature Monitoring & Fan Control
     - Read temperature using a thermistor.
     - If temperature >= 30°C:
         -> Turn on fan at high speed (forward direction).
     - If temperature is between 20°C and 30°C:
         -> Turn on fan at low speed (forward direction).
     - If temperature < 20°C:
         -> Turn off the fan.
     - If smoke is detected (smoke sensor HIGH):
         -> Run fan in reverse at full speed to ventilate smoke.

  2. Rain Detection & Canopy Control (Servo Motor)
     - If rain is detected (rain sensor HIGH):
         -> Close canopy (servo to 180°).
     - If no rain and evaluation sensor is HIGH:
         -> Half open canopy (servo to 90°).
     - If no rain and evaluation sensor is LOW:
         -> Fully open canopy (servo to 0°).

  3. Smoke Detection
     - Monitor smoke sensor.
     - If smoke is detected:
         -> Fan runs in reverse regardless of temperature.

  4. Actuator Configuration
     - DC motor (fan) controlled with:
         -> PWM signal for speed.
         -> IN1/IN2 pins for direction.
     - Servo motor controls canopy position:
         -> 0° = Fully open, 90° = Half open, 180° = Closed.

  5. Feedback and Monitoring
     - Use Serial Monitor to display:
         -> Temperature in °C
         -> Fan status (Off, Low Speed, High Speed, Reverse)
         -> Canopy position (Fully Open, Half Open, Closed)
*/

