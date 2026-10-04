# Wind Tunnel

A small wind tunnel I built to test the aerodynamic drag of different subway cart roof designs.

## What I Made

The wind tunnel is around 1.3 m long, with the intake and exhaust reaching around 0.4 m in height and width at their largest points. I used it to compare the drag force on 5 different hypothetical subway cart roofs.
The goal was to find which roof was the most aerodynamic. I made all 5 roofs using the same basic curvature in Blender and only changed the height increment between them. This meant that I could compare the effect of the roof height without completely changing the shape of the roof each time.
The wind tunnel can reach relative wind speeds of around 35 km/h using a 136 W VEVOR fan.

## Building the Wind Tunnel

I made the intake and exhaust sections using double-layered cardboard, with plywood for the test section. The pieces were held together using wood glue and tape.
The test section is where the subway cart roof was placed and where the drag force was measured.

## Measuring Drag

To measure the drag force, I used:

- Load cell
- HX711 load cell amplifier
- Arduino Uno
- Laptop

I soldered the pins and wires onto the HX711 and connected it to the load cell and Arduino.
The load cell measures the force acting on the roof, but its original output is an electrical value rather than a force measurement. I calibrated the system and programmed the Arduino to convert the readings into force.
For each test, I collected measurements over 20 seconds. The Arduino first averaged every 10 individual readings, giving me one averaged measurement. I then collected 20 of these averaged measurements and calculated their average to get the final force measurement for that test.
This helped reduce the effect of the small fluctuations in the load cell readings.

## Roof Designs

I modelled the 5 roof designs in Blender.
The main thing I changed between the designs was the height of the roof. I kept the same general curvature so that the experiment was mainly testing how the change in height affected the drag.
The roofs were then physically tested in the wind tunnel under the same general conditions.

## Electronics

The basic setup was:
**Load Cell → HX711 → Arduino Uno → Laptop**

The Arduino handled the sensor readings and force calculations, while the laptop was used to receive and record the measurements.

## Software

- **Blender** to model the subway cart roofs
- **Arduino IDE** for programming the Arduino and processing the load-cell data

## What I Was Testing

The main question was:

**How does changing the height of a subway cart roof affect the aerodynamic drag it experiences?**

I compared the measured force from all 5 roofs and used the results to determine which design was the most aerodynamic.

## Materials

- Cardboard
- Plywood
- Wood glue
- Tape
- 136 W VEVOR fan
- Load cell
- HX711 load cell amplifier
- Arduino Uno
- Computer
- 3D-printed roof models

## Photos

<img src="https://github.com/user-attachments/assets/5ea42d4d-614c-4733-89ce-14a865c6b8b2" alt="Wind tunnel" width="700">
<img src="https://github.com/user-attachments/assets/9d9bf943-71f9-462e-80d8-15831f305e79" alt="Wind tunnel test section" width="700">
<img src="https://github.com/user-attachments/assets/dd123c28-a4e6-4a27-8248-39502c4cca03" alt="Wind tunnel setup" width="700">
