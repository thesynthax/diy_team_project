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

void LightDueToWalk(int);

void setup()
{
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    distance = GetDistance();

    currentState = GetCurrentState();   

    LightDueToWalk(currentState);
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
        analogWrite(rPin, 255);
        analogWrite(gPin, 255);
        analogWrite(bPin, 255);
    }
    else
    {
        analogWrite(rPin, 0);
        analogWrite(gPin, 0);
        analogWrite(bPin, 0);
    }
}
