//HC-SR04 (ultrasonic sensor)
const int trigPin = 3;
const int echoPin = 7;
long duration;
int distance;
int currentState = 0; //0: neutral, 1: enter, 2: exit
float soundSpeed = 0.034; //unit: cm/us
float avgWalkingSpeed = 1.3; //unit: m/s
int GetDistance();
int GetCurrentState();

//RGB Light
const int rPin = 2;
const int gPin = 4;
const int bPin = 5;
bool lightOn = false;
void LightDueToWalk(int);
void RGBLight(int, int, int);
void LightColor(int);

//Sound Sensor
const int soundPin = 8;
const int clapWindowMin = 250; //unit: us
const int clapWindowMax = 500; //unit: us
const int timeout = 1000; //unit: us
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
    LightColor(ClapType());
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
        RGBLight(255, 255, 255);
        lightOn = true;
    }
    else
    {
        RGBLight(0, 0, 0);
        lightOn = false;
    }
}

int ClapType()
{
    int noOfClaps = 0;
    int duration1 = 0, duration2 = 0, duration3 = 0;

    int sound = digitalRead(soundPin);
    if (sound == 1)
    {
        noOfClaps++;
        duration1 = pulseIn(soundPin, LOW, timeout);
        if (duration1 > clapWindowMin && duration1 < clapWindowMax)
        {
            noOfClaps++;
            duration2 = pulseIn(soundPin, LOW, timeout);
            if (duration2 > clapWindowMin && duration2 < clapWindowMax)
            {
                noOfClaps++;
                duration3 = pulseIn(soundPin, LOW, timeout);
                if (duration3 > clapWindowMin && duration3 < clapWindowMax)
                {
                    noOfClaps++;
                }
            }
        }
    }
    return noOfClaps;
}

void LightColor(int claps)
{
    if (lightOn)
    {
        switch(claps)
        {
            case(1):
                RGBLight(255, 0, 0);
                break;
            case(2):
                RGBLight(0, 255, 0);
                break;
            case(3):
                RGBLight(0, 0, 255);  
                break;
        }
    }
}

void RGBLight(int r, int g, int b)
{
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);    
}
