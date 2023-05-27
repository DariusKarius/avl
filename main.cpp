#include <iostream>
#include <ctime>
using namespace std;
#include "avl.h"
#include "prueba.h"

struct Fecha {
    int dia;
    int mes;
    int anio;

    Fecha() : dia(0), mes(0), anio(0) {}
    Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}
};


int main() {

    AVLTree<int> avl;
    avl.insert(2000);
    avl.insert(1700);
    avl.insert(3600);
    avl.insert(800);
    avl.insert(1900);
    avl.insert(4000);
    avl.insert(3500);
    avl.insert(350);
    avl.displayPretty();
    cout << endl;
    cout << avl.getInOrder() << endl;
    cout << avl.search_by_range(1900,2001);
}