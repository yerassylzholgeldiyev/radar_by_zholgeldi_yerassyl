import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

Serial port;
String angleData = "", distanceData = "", rawData = "", statusMessage;
float distancePixels;
int parsedAngle, parsedDistance;
int commaIndex1 = 0;
PFont fontType;

void setup() {
  size(1200, 700);
  smooth();
  port = new Serial(this, "COM7", 9600);
  port.bufferUntil('.');
  fontType = createFont("Consolas", 24);
  textFont(fontType);
}

void draw() {
  drawBackgroundGradient();
  drawRadarDisplay();
  drawDirectionLine();
  drawDetectedObject();
  displayText();
}

void drawBackgroundGradient() {
  for (int i = 0; i < height; i++) {
    stroke(0, map(i, 0, height, 0, 100), 0);
    line(0, i, width, i);
  }
}

void serialEvent(Serial port) {
  rawData = port.readStringUntil('.');
  if (rawData != null && rawData.length() > 1) {
    rawData = rawData.substring(0, rawData.length() - 1);
    commaIndex1 = rawData.indexOf(",");
    if (commaIndex1 > 0) {
      angleData = rawData.substring(0, commaIndex1);
      distanceData = rawData.substring(commaIndex1 + 1);
      parsedAngle = int(angleData.trim());
      parsedDistance = int(distanceData.trim());
    }
  }
}

void drawRadarDisplay() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  noFill();
  strokeWeight(2);
  for (int i = 1; i <= 4; i++) {
    stroke(100, 255 - i * 30, 100 + i * 20);
    arc(0, 0, width - i * width * 0.21, width - i * width * 0.21, PI, TWO_PI);
  }

  stroke(150, 255, 150);
  line(-width / 2, 0, width / 2, 0);
  for (int angle = 30; angle <= 150; angle += 30) {
    float x = (width / 2) * cos(radians(angle));
    float y = (width / 2) * sin(radians(angle));
    line(0, 0, -x, -y);
  }
  popMatrix();
}

void drawDetectedObject() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  strokeWeight(10);
  distancePixels = parsedDistance * ((height - height * 0.1666) * 0.025);

  if (parsedDistance < 40) {
    stroke(255, 100 + frameCount % 155, 100);
    float x = distancePixels * cos(radians(parsedAngle));
    float y = -distancePixels * sin(radians(parsedAngle));
    point(x, y);
    for (int i = 0; i < 5; i++) {
      noFill();
      stroke(255, 50, 50, 100 - i * 20);
      ellipse(x, y, i * 10, i * 10);
    }
  }
  popMatrix();
}

void drawDirectionLine() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  stroke(50, 255, 100);
  strokeWeight(5);
  float x = (height - height * 0.12) * cos(radians(parsedAngle));
  float y = -(height - height * 0.12) * sin(radians(parsedAngle));
  line(0, 0, x, y);
  popMatrix();
}

void displayText() {
  pushMatrix();
  statusMessage = (parsedDistance > 40) ? "Out of Range" : "In Range";
  fill(0, 180);
  noStroke();
  rect(0, height - height * 0.065, width, height * 0.065);

  fill(0, 255, 0);
  textSize(26);
  textAlign(LEFT);
  text("desertf0x", 20, height - 20);

  textAlign(CENTER);
  text("Burysh: " + parsedAngle + "°", width / 2 - 200, height - 20);
  text("Qashyqtyq: " + (parsedDistance < 40 ? parsedDistance + " cm" : "---"), width / 2 + 20, height - 20);
  text(statusMessage, width - 150, height - 20);
  popMatrix();
}
