#include <Servo.h>

//PINOS SENSOR E SERVO
#define TRIG 10
#define ECHO 11
#define SERVO 9

// Motor a
#define in1 2
#define in2 3
// Motor b
#define in3 4
#define in4 7
// pinos enables (vel dos motores)
#define enA 3
#define enB 6

Servo meuServo;

class Robo {
public:
    void Menu();
    void virar_direita(); //move motor A sentido horário
    void voltar_direita(); //move motor A sentido antihorário
    void virar_esquerda(); //move motor B sentido horário
    void voltar_esquerda(); //move motor B sentido antihorário
    void ir_frente(); //gira motores sentido horário
    void ir_tras(); //gira motores sentido antihorário
    void pararMotores();
    void motoresHorario();
};
