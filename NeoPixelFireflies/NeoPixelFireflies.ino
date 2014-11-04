#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 7
#define MAX_GLOWING_PIXELS 4
#define MOVE_THRESHOLD 1.0 // Quite sensitive
#define STATIONARY_LATENCY 30000 // 30s glow after last move 

class Firefly {
  private:
    float _brightness;
    float _fadeSpeed;
    float _hue;
    boolean _isGlowing;
    
  public:
    Firefly ();
	
    float hueCenter;
    float hueRange;
    float baseSpeed;
    boolean isGlowing();    
    uint32_t getColor();
    
    void ignite();
    void animate();    
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

Firefly ff[NUM_PIXELS];
boolean moving;
double lastVector;
unsigned long lastSensorTime;
unsigned long lastMovingTime;

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  if (!accel.begin()) {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
  checkMoving();
  delay(100); // Allow time for the first movement check
}

void loop() {
  // Check for movement every 100ms
  unsigned long time = millis();
  if(abs(time - lastSensorTime) >= 100) {
    checkMoving();
    lastSensorTime = time;
    if(moving) {
      lastMovingTime = time;
    }
  }

  int glowingPixelCount = 0;
  // do we have enough lit pixels?
  for(int i = 0; i < NUM_PIXELS; i++) {
    if(ff[i].isGlowing()) {
      glowingPixelCount++;
    }
  }
  
  for(int i = 0; i < NUM_PIXELS; i++) {
    if(abs(time - lastMovingTime) <= STATIONARY_LATENCY && !ff[i].isGlowing() && glowingPixelCount < MAX_GLOWING_PIXELS && random(100) < 5) {
      ff[i].ignite();
      glowingPixelCount++;
    }
    ff[i].animate();
    strip.setPixelColor(i, ff[i].getColor());
  }
  strip.show();
  delay(10);
}

void checkMoving() {
  sensors_event_t event; 
  accel.getEvent(&event);
  double newVector = sqrt(event.acceleration.x*event.acceleration.x + event.acceleration.y*event.acceleration.y + event.acceleration.z*event.acceleration.z);

  // are we moving 
  moving = (abs(newVector - lastVector) > MOVE_THRESHOLD);
  lastVector = newVector;
}




