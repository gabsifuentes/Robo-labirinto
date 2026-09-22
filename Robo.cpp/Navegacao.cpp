#include <Servo.h>

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
