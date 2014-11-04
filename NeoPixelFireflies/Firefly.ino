Firefly::Firefly () {
  hueCenter = 0.85;
  hueRange = 0.2;
  baseSpeed = 0.02;
  _brightness = 0.0;
  _fadeSpeed = 0.0;
  _isGlowing = false;
}

void Firefly::ignite() {
  _hue = hueCenter + (random(100)-50)*0.01*hueRange;
  _fadeSpeed = baseSpeed*(random(100)*0.01 + 0.5);
  _isGlowing = true;
}

boolean Firefly::isGlowing() {
  return _isGlowing;
}

void Firefly::animate() {
  if(!_isGlowing) {
    return;
  }
  
  _brightness += _fadeSpeed;
    
  if(_brightness > 1.0) {
    _brightness = 1.0;
    _fadeSpeed *= -0.3;
  } else if(_brightness < 0.0) {
    _brightness = 0.0;
    _fadeSpeed = 0.0;
    _isGlowing = false;
  }
}

uint32_t Firefly::getColor() {
  uint8_t w = 255*_hue;
  if(w < 85) {
    return Adafruit_NeoPixel::Color(w*3*_brightness, (255-w*3)*_brightness, 0);
  } else if(w < 170) {
    w -= 85;
    return Adafruit_NeoPixel::Color((255-w*3)*_brightness, 0, w*3*_brightness);
  } else {
    w -= 170;
    return Adafruit_NeoPixel::Color(0, w*3*_brightness, (255-w*3)*_brightness);
  }  
}


