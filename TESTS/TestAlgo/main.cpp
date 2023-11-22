#include <iostream>

using namespace std;

float calculIncrement(float startFirstServo, float endFirstServo, float startSecondServo, float endSecondServo);

int main() {
    std::cout << "Calcul de l'incrément !" << std::endl;

    float startFirstServo = 230.0;
    float endFirstServo = 180.0;
    float startSecondServo = 40.0;
    float endSecondServo = 80.0;

    float incr = calculIncrement(startFirstServo, endFirstServo, startSecondServo, endSecondServo);
    cout << "Valeur de l'incrément: " << incr << endl;

    startFirstServo = 180.0;
    endFirstServo = 230.0;
    startSecondServo = 40.0;
    endSecondServo = 80.0;

    incr = calculIncrement(startFirstServo, endFirstServo, startSecondServo, endSecondServo);
    cout << "Valeur de l'incrément: " << incr << endl;

    startFirstServo = 230.0;
    endFirstServo = 180.0;
    startSecondServo = 80.0;
    endSecondServo = 40.0;

    incr = calculIncrement(startFirstServo, endFirstServo, startSecondServo, endSecondServo);
    cout << "Valeur de l'incrément: " << incr << endl;

    startFirstServo = 180.0;
    endFirstServo = 230.0;
    startSecondServo = 80.0;
    endSecondServo = 40.0;

    incr = calculIncrement(startFirstServo, endFirstServo, startSecondServo, endSecondServo);
    cout << "Valeur de l'incrément: " << incr << endl;

    return 0;
}

float calculIncrement(float startFirstServo, float endFirstServo, float startSecondServo, float endSecondServo) {

    float todoFirstServo = endFirstServo - startFirstServo;
    if (endFirstServo < startFirstServo) {
        todoFirstServo = todoFirstServo * -1;
    }
    float todoSecondServo = endSecondServo - startSecondServo;
    return todoFirstServo / todoSecondServo;
}