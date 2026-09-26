#include <Servo.h>
#define TRIG 10
#define ECHO 11
#define SERVO 9

//motor A
#define in1 7
#define in2 5 
//motor B
#define in3 2
#define in4 4
// Pinos enable (velocidade dos motores)
#define enA 3
#define enB 6

Servo meuServo;

class Robo {
private:
    const int vel = 180;
    const long tempoGiro = 350;   
    const long tempoServo = 500;
public:
    void ir_frente();
    void ir_tras();
    void virar_direita();
    void virar_esquerda();
    void parar_motores();

    void servo_frente();
    void servo_direita();
    void servo_esquerda();

    bool detectar_parede();
    float pegar_dist();
};

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

void Robo::parar_motores() {
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
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, vel);
    analogWrite(enB, vel);
}

void Robo::virar_esquerda() {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, vel);
    analogWrite(enB, vel);
}

void Robo::servo_frente() {
    meuServo.write(90);
}

void Robo::servo_esquerda() {
    meuServo.write(180);
}

void Robo::servo_direita() {
    meuServo.write(0);
}

float Robo::pegar_dist() {
    long tempo;
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    tempo = pulseIn(ECHO, HIGH, 30000);

    if (tempo == 0) {
        return -1;
    }

    return tempo * 0.034 / 2;
}

bool Robo::detectar_parede() {
    float distancia = pegar_dist();
    return (distancia > 0 && distancia < 10);
}

Robo robo;

enum EstadoRobo {
    ANDANDO,
    OLHANDO_DIREITA,
    OLHANDO_ESQUERDA,
    VIRANDO_DIREITA,
    VIRANDO_ESQUERDA,
    GIRANDO_180
};

EstadoRobo estadoAtual = ANDANDO;
long tempoInicioEstado = 0;

void mudarEstado(EstadoRobo novoEstado) {
    estadoAtual = novoEstado;
    tempoInicial = millis();
}

void setup() {
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
    robo.servo_frente();

    mudarEstado(ANDANDO);
}

void loop() {
    long momentoAtual = millis();

    switch (estadoAtual) {

        case ANDANDO:
            if (robo.detectar_parede()) {
                robo.parar_motores();
                robo.servo_direita();
                mudarEstado(OLHANDO_DIREITA);
            } else {
                robo.ir_frente();
            }
            break;

        case OLHANDO_DIREITA:
            if (momentoAtual - tempoInicial >= tempo_servo) {
                if (!robo.detectar_parede()) {
                    robo.servo_frente();
                    mudarEstado(GIRANDO_DIREITA);
                } else {
                    robo.servo_esquerda();
                    mudarEstado(OLHANDO_ESQUERDA);
                }
            }
            break;

        case OLHANDO_ESQUERDA:
            if (momentoAtual - tempoInicial >= tempo_servo) {
                if (!robo.detectar_parede()) {
                    robo.servo_frente();
                    mudarEstado(GIRANDO_ESQUERDA);
                } else {
                    // cercado nos 3 lados -> meia-volta
                    robo.servo_frente();
                    mudarEstado(GIRANDO_180);
                }
            }
            break;

        case VIRANDO_DIREITA:
            robo.virar_direita();
            if (momentoAtual - tempoInicial >= tempo_servo) {
                robo.parar_Motores();
                mudarEstado(ANDANDO);
            }
            break;

        case VIRANDO_ESQUERDA:
            robo.virar_esquerda();
            if (momentoAtual - tempoInicial >= tempo_giro) {
                robo.parar_Motores();
                mudarEstado(ANDANDO);
            }
            break;

        case GIRANDO_180:
            robo.virar_direita();
            if (momentoAtual - tempoInicial >= tempo_giro * 2) {
                robo.parar_Motores();
                mudarEstado(ANDANDO);
            }
            break;
    }
}
