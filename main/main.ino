//HC-SR04 (ultrasonic sensor)
const int trigPin = 3;
const int echoPin = 7;
const float soundSpeed = 0.034; //unit: cm/us
const float minWalkingSpeed = 50; //unit: cm/s
const float timeToWait = 100; //unit: ms
const float lightChangeWindow = 2000; //unit: ms
long duration;
int distance;
int distance1 = 0, distance2 = 0;
int currentState = 0; //0: neutral, 1: enter, 2: exit
int people = 0;
int GetDistance();
int GetCurrentState();

//RGB Light
const int rPin = 9;
const int gPin = 10;
const int bPin = 11;
int lightType = 0; //0-off, 1-white, 2-r, 3-g, 4-b
bool lightChanged = false;
void LightDueToWalk(int);
void LightDueToClap(int);
void RGBLight(int, int, int);
void AssignLight(int);

//Sound Sensor
const int soundPin = A1;
const int clapWindowMin = 250; //unit: us
const int clapWindowMax = 750; //unit: us
const int timeout = 1000; //unit: us
const int clapThreshold = 50;
bool clapped = false;
int lastSound;
int sound;
long lastClapTime = 0;
long currentClapTime = 0;
long lastLightChange = 0;
bool Clap();

//Relay
const int fan = 3;
const int bulb = 5;
const int charger = 4;
const int bell = 6;
void Relay();

void setup()
{
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    pinMode(soundPin, INPUT);

    pinMode(fan, OUTPUT);
    pinMode(bulb, OUTPUT);
    pinMode(charger, OUTPUT);
    pinMode(bell, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    distance = GetDistance();

    currentState = GetCurrentState();   
    
    LightDueToWalk(currentState);

    clapped = Clap();
    LightDueToClap(clapped);
    delay(25);
    AssignLight(lightType);
    Relay();

    
}

int GetDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    return (duration * soundSpeed)/2;
}

int GetCurrentState()
{
    int curState;
    
    distance1 = GetDistance();
    if (currentState != 0)
    {
        delay(timeToWait);
    }
    distance2 = GetDistance();

    double speed = (distance1 - distance2) / (timeToWait/1000); //unit: cm/s

    if (speed < -minWalkingSpeed)
    {     
        people -= 1;
        curState = 2;
    }
    else if (speed > minWalkingSpeed)
    {
    	people += 1
        curState = 1;
    }
    else
       curState = 0;

    return curState;
}

void LightDueToWalk(int curState)
{
    if (people >= 1)
    {
        lightType = 1;       
    }
    else if (people == 0)
    {
        lightType = 0;
    }

    if (people < 0) people = 0;
}

// int ClapType()
// {
//     int claps = 0;
//     int duration1 = 0, duration2 = 0;

//     sound = digitalRead(soundPin);
//     if (sound == 1)
//     {
//         claps++;
//         duration1 = pulseIn(soundPin, LOW, timeout);
//         if (duration1 > clapWindowMin && duration1 < clapWindowMax)
//         {
//             claps++;
//             duration2 = pulseIn(soundPin, LOW, timeout);
//             if (duration2 > clapWindowMin && duration2 < clapWindowMax)
//             {
//                 claps++;
//             }
//         }
//     }
//     return claps;
// }

// int ClapType()
// {
//     int claps = 0;
//     sound = analogRead(soundPin);
//     currentClapTime = millis();

//     if (sound > 600) 
//     { 
//         if ((currentClapTime > lastClapTime + clapWindowMin) && (lastSound == 0) && (currentClapTime < lastClapTime + clapWindowMax) && (currentClapTime > lastLightChange + timeout)) 
//         { 
//             claps = 2;
//             lastLightChange = currentClapTime;
//         }
//         else
//             claps = 1;        
//         lastClapTime = currentClapTime;
//     }
//     lastSound = sound;
    
//     return claps;
// }

bool Clap()
{
    Serial.println(analogRead(soundPin));
    return (analogRead(soundPin) > clapThreshold);
}

void LightDueToClap(bool clap)
{
    if (clap)
    {
        lightType = (lightType != 4) ? lightType + 1 : 0;  
    } 
}

void AssignLight(int lightType)
{
    switch(lightType)
    {
        case(0):
            RGBLight(0, 0, 0);
            break;  
        case(1):
            RGBLight(20, 25, 25);
            break;  
        case(2):
            RGBLight(25, 0, 0);
            break;  
        case(3):
            RGBLight(0, 25, 0);
            break;  
        case(4):
            RGBLight(0, 0, 25);
            break;       
    }  
}

void RGBLight(int r, int g, int b)
{
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);  
    //delay(lightChangeWindow);  
}

void Relay()
{
    if (Serial.available() == 1)
    {
        String val = Serial.readString();
        //Serial.println(val);
        //For Fan
        if (val == "fan on")
        {
            digitalWrite(fan, HIGH);
        }
        else if (val == "fan off")
        {
            digitalWrite(fan, LOW);
        }
        //For bulb
        if (val == "bulb on")
        {
            digitalWrite(bulb, HIGH);
        }
        else if (val == "bulb off")
        {
            digitalWrite(bulb, LOW);
        }
        //For charger
        if (val == "charger on")
        {
            digitalWrite(charger, HIGH);
        }
        else if (val == "charger off")
        {
            digitalWrite(charger, LOW);
        }
        //For bell
        if (val == "bell on")
        {
            digitalWrite(bell, HIGH);
        }
        else if (val == "bell off")
        {
            digitalWrite(bell, LOW);
        }
        //for everything
        if (val == "all on")
        {
            digitalWrite(fan, HIGH);
            digitalWrite(bulb, HIGH);
            digitalWrite(charger, HIGH);
            digitalWrite(bell, HIGH);
        }
        else if (val == "all off")
        {
            digitalWrite(bulb, LOW);
            digitalWrite(fan, LOW);
            digitalWrite(charger, LOW);
            digitalWrite(bell, LOW);
        }
    }
}
