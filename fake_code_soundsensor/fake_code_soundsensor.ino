const int rPin = 9;
const int gPin = 10;
const int bPin = 11;
void RGBLight(int r, int g, int b)
{
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  Serial.println("Clap in 5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Clap!!");
  delay(1000);
  RGBLight(150, 200, 200);
  Serial.println("wait for 10 seconds");
  delay(10000);
  Serial.println("Clap in 5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Clap!!");
  delay(1000);
  RGBLight(255, 0, 0);
  Serial.println("wait for 10 seconds");
  delay(10000);
  Serial.println("Clap in 5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Clap!!");
  delay(1000);
  RGBLight(0, 255, 0);
  Serial.println("wait for 10 seconds");
  delay(10000);
  Serial.println("Clap in 5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Clap!!");
  delay(1000);
  RGBLight(0, 0, 255);
  Serial.println("wait for 10 seconds");
  delay(10000);
  Serial.println("Clap in 5...");
  delay(1000);
  Serial.println("4...");
  delay(1000);
  Serial.println("3...");
  delay(1000);
  Serial.println("2...");
  delay(1000);
  Serial.println("1...");
  delay(1000);
  Serial.println("Clap!!");
  delay(1000);
  RGBLight(0, 0, 0);
}
