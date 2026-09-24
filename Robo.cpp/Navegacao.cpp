#include <Servo.h>

//PINOS SENSOR E SERVO
#define TRIG 10
#define ECHO 11
#define SERVO 9

// Motor a
#define in1 7
#define in2 5 // verificar pinos
// Motor b
#define in3 4
#define in4 2
// pinos enables (vel dos motores)
#define enA 3
#define enB 6

Servo meuServo;

class Robo {
private:
    int vel = 255;
public:
    void virar_direita(); //move motor A sentido horário
    void virar_esquerda(); //move motor B sentido horário
    void ir_frente(); //gira motores sentido horário
    void ir_tras(); //gira motores sentido antihorário
    void parar_Motores(); 

    int servo_frente();
    int servo_direita();
    int servo_esquerda();

    bool detectar_parede();
};

//funções dos motores
void Robo::ir_frente() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, vel);
    analogWrite(enB, vel);
}

void Robo::ir_tras() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, vel);
    analogWrite(enB, vel);
}

void Robo::parar_Motores() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

void Robo::virar_direita() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, vel);
    analogWrite(enB, 0);
    delay(1000);
    parar_Motores();
}

void Robo::virar_esquerda(){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, vel);
    delay(1000);
    parar_Motores();
}

//funções do servo
int Robo::servo_frente(){
    meuServo.write(90);
    delay(1000);
    return 90;
}

int Robo::servo_esquerda(){
    meuServo.write(180);
    delay(1000);
    return 180;
}

int Robo::servo_direita(){
    meuServo.write(0);
    delay(1000);
    return 0;
}

//função do sensor
bool Robo::detectar_parede(){
    long tempo, distancia;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    tempo = pulseIn(ECHO, HIGH, 30000); 

    distancia = tempo * 0.034 / 2;

    if(distancia < 5){
        return true;
    } 
    else{
        return false;
    }
}

void setup(){
    Serial.begin(9600);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    meuServo.attach(SERVO);
}

Robo robo;

void loop(){
    bool paredeFrente = robo.detectar_parede();

    if(!paredeFrente){
        robo.ir_frente();
    }
    else{
        robo.parar_Motores();

        robo.servo_direita();
        bool paredeDireita = robo.detectar_parede();

        if(!paredeDireita){
            robo.servo_frente();

            robo.virar_direita();
        }
        else{
            robo.servo_esquerda();
            bool paredeEsquerda = robo.detectar_parede();

            if(!paredeEsquerda){
                robo.servo_frente();

                robo.virar_esquerda();
            }
            else{
                robo.servo_frente();

                robo.virar_direita();

                robo.virar_direita();
            }
        }
    }
}