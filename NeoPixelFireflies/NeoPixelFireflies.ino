#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 7
#define MAX_GLOWING_PIXELS 4

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
Firefly ff[NUM_PIXELS];

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
  delay(100); // Allow time for the first movement check
}

void loop() {
  int glowingPixelCount = 0;
  // do we have enough lit pixels?
  for(int i = 0; i < NUM_PIXELS; i++) {
    if(ff[i].isGlowing()) {
      glowingPixelCount++;
    }
  }
  
  for(int i = 0; i < NUM_PIXELS; i++) {
    if(!ff[i].isGlowing() && glowingPixelCount < MAX_GLOWING_PIXELS && random(100) < 5) {
      ff[i].ignite();
      glowingPixelCount++;
    }
    ff[i].animate();
    strip.setPixelColor(i, ff[i].getColor());
  }
  strip.show();
  delay(10);
}



