#include <Servo.h>

//PINOS SENSOR E SERVO
#define TRIG 10
#define ECHO 11
#define SERVO 9

// Motor a
#define in1 2
#define in2 3 // verificar pinos
// Motor b
#define in3 4
#define in4 7
// pinos enables (vel dos motores)
#define enA 3
#define enB 6

Servo meuServo;

class Robo {
public:
    void virar_direita(); //move motor A sentido horário
    void voltar_direita(); //move motor A sentido antihorário
    void virar_esquerda(); //move motor B sentido horário
    void voltar_esquerda(); //move motor B sentido antihorário
    void ir_frente(); //gira motores sentido horário
    void ir_tras(); //gira motores sentido antihorário
    void pararMotores(); 

    int servo_frente();
    int servo_direita();
    int servo_esquerda();
};

//funções dos motores
void Robo::virar_direita() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void Robo::voltar_direita(){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
}

void Robo::virar_esquerda(){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void Robo::voltar_esquerda(){
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void Robo::ir_frente() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void Robo::ir_tras() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void Robo::pararMotores() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

//funçês do servo
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