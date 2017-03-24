NeoPixelFireflies
=================

Code for simple fireflies-in-a-jar using Adafruit Flora, NeoPixels and Accelerometer. I strung seven pixels together and hid the Flora, lipo battery and accelerometer in the jar lid.

The fireflies glow on and off with a hue picked from a specified range. At any time only MAX_GLOWING_PIXELS out of NUM_PIXELS will be lit. The fireflies will continue to glow for STATIONARY_LATENCY (in ms) after the last detected motion, and will wake immediately to motion.

You can see an example of the results at https://www.youtube.com/watch?v=nOLEo_zldIc

Wiring is essentially the same as Adafruit's Sparkle Skirt, though I used single core wire between the NeoPixels rather the conductive thread.
https://learn.adafruit.com/sparkle-sk...

Parts used:

1x Adafruit Flora 
https://www.adafruit.com/products/659

7x Flora NeoPixels
https://www.adafruit.com/product/1260

1x Flora Accelerometer
https://www.adafruit.com/products/1247

1x 500mAh Lipo battery
https://www.adafruit.com/products/1578
