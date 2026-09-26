#include <Servo.h>

//PINOS SENSOR E SERVO
#define TRIG 10
#define ECHO 11
#define SERVO 9

// Motor a
#define in1 7
#define in2 5 // verificar pinos
// Motor b
#define in3 2
#define in4 4
// pinos enables (vel dos motores)
#define enA 3
#define enB 6

Servo meuServo;

class Robo {
private:
    const int vel = 255;
    const int vel_giros = 180;
    const int distancia_limite = 10;

    const int angulo_frente = 90;
    const int angulo_esquerda = 180;
    const int angulo_direita = 0;
public:
    void virar_direita(); //move motor A sentido horário e B antihorário
    void virar_esquerda(); //move motor B sentido horário e A antihorário
    void ir_frente(); //gira motores sentido horário
    void ir_tras(); //gira motores sentido antihorário
    void parar_Motores(); 

    int servo_frente();
    int servo_direita();
    int servo_esquerda();

    bool detectar_parede();
    float pegar_dist();
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

void Robo::virar_esquerda() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, vel_giros);
    analogWrite(enB, vel_giros);

    delay(350);
    parar_Motores();
}

void Robo::virar_direita(){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    analogWrite(enA, vel_giros);
    analogWrite(enB, vel_giros);

    delay(350);
    parar_Motores();
}

//funções do servo
void Robo::servo_frente(){
    meuServo.write(angulo_frente);
    delay(500);
}

void Robo::servo_esquerda(){
    meuServo.write(angulo_esquerda);
    delay(500);
}

void Robo::servo_direita(){
    meuServo.write(angulo_direita);
    delay(500);
}

//função do sensor
float Robo::pegar_dist(){
    long tempo, distancia;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    tempo = pulseIn(ECHO, HIGH, 30000); 
    if(tempo == 0){
        return -1;
    }

    distancia = tempo * 0.034 / 2;
    return distancia;
}

bool Robo::detectar_parede(){
    float distancia = pegar_dist();

    if(distancia < 0){
        return false;
    }
    else{
        return (distancia < distancia_limite);
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

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);

    meuServo.attach(SERVO);
}

Robo robo;

void loop(){
    robo.servo_frente();

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