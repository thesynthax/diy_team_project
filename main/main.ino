//HC-SR04 (ultrasonic sensor)
const int trigPin = 3;
const int echoPin = 7;
const float soundSpeed = 0.034; //unit: cm/us
const float avgWalkingSpeed = 1.3; //unit: m/s
long duration;
int distance;
int currentState = 0; //0: neutral, 1: enter, 2: exit
int GetDistance();
int GetCurrentState();

//RGB Light
const int rPin = 9;
const int gPin = 10;
const int bPin = 11;
int lightType = 0; //0-off, 1-white, 2-r, 3-g, 4-b
void LightDueToWalk(int);
void LightDueToClap(int);
void RGBLight(int, int, int);
void AssignLight(int);

//Sound Sensor
const int soundPin = A1;
const int clapWindowMin = 250; //unit: us
const int clapWindowMax = 750; //unit: us
const int timeout = 1000; //unit: us
int lastSound;
int sound;
long lastClapTime = 0;
long currentClapTime = 0;
long lastLightChange = 0;
int ClapType();

void setup()
{
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    pinMode(soundPin, INPUT);

    Serial.begin(9600);
}

void loop()
{
    distance = GetDistance();

    currentState = GetCurrentState();   

    LightDueToWalk(currentState);
    LightDueToClap(ClapType());
    AssignLight(lightType);
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
    int curState = -1;

    int timeToWait = 250; //unit: ms
    int distance1 = 0, distance2 = 0;

    distance1 = distance;
    delay(timeToWait);
    distance2 = distance;

    float speed = ((distance2 - distance1)/100) / (timeToWait/1000); //unit: m/s

    if (speed < -avgWalkingSpeed)
        curState = 1;
    else if (speed > avgWalkingSpeed)
        curState = 2;
    else
        curState = 0;

    return curState;
}

void LightDueToWalk(int curState)
{
    if (curState == 1)
    {
        lightType = 1;
    }
    else
    {
        lightType = 0;
    }
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

int ClapType()
{
    int claps = 0;
    sound = digitalRead(soundPin);
    currentClapTime = millis();

    if (sound == 1) 
    { 
        if ((currentClapTime > lastClapTime + clapWindowMin) && (lastSound == 0) && (currentClapTime < lastClapTime + clapWindowMax) && (currentClapTime > lastLightChange + timeout)) 
        { 
            claps = 2;
            lastLightChange = currentNoiseTime;
        }
        else
            claps = 1;        
        lastNoiseTime = currentNoiseTime;
    }
    lastSound = sound;
    
    return claps;
}

void LightDueToClap(int claps)
{
    if (claps == 1)
    {
        lightType = (lightType == 0) ? 1 ; 0;  
    }
    else if (claps == 2)
    {
        if (lightType >= 1 && lightType < 4)
        {
            lightType++;
        }
        else if (lightType == 4)
        {
            lightType = 1;
        }
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
            RGBLight(255, 255, 255);
            break;  
        case(2):
            RGBLight(255, 0, 0);
            break;  
        case(3):
            RGBLight(0, 255, 0);
            break;  
        case(4):
            RGBLight(0, 0, 255);
            break;       
    }  
}

void RGBLight(int r, int g, int b)
{
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);    
}
