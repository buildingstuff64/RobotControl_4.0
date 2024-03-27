String getColor() {
  time_now = millis();
  while (millis() < time_now + 1000) {
    String str = getColorString(getHue());
    if (str != "unknown") {
      return str;
    }
  }
  return "unknown";
}

float getHue() {
  float r, g, b;
  tcs.getRGB(&r, &g, &b);
  float h = rgb2hue(r, g, b);
  return h;
}

float rgb2hue(float r, float g, float b) {
  float h;

  float M = max(r, max(g, b));
  float m = min(r, min(g, b));

  float C = M - m;

  if (M == r) {
    h = (g - b) / C + (g < b ? 6 : 0);
  } else if (M == g) {
    h = (b - r) / C + 2;
  } else if (M == b) {
    h = (r - g) / C + 4;
  } else {
    return 0;  // achromatic
  }

  return h * 60;
}

const float RED = 350;
const float GREEN = 115;
const float YELLOW = 37;
const float ORANGE = 11; 

String getColorString(float h){
  if (inColorRange(RED, h))return "C#red";
  if (inColorRange(GREEN, h))return "C#green";
  if (inColorRange(YELLOW, h))return "C#yellow";
  if (inColorRange(ORANGE, h))return "C#orange";
  return "unknown";
}

bool inColorRange(float COLOR, float h){
  return (h > COLOR - 10 && h < COLOR + 10) ? true : false;
}