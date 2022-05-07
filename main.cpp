#include <iostream>
#include <vector>

using namespace std;

//PUNTO
struct Punto
{
    double x, y;
    Punto(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
};

//CUADRADO
class Cuadro
{
public:
    Cuadro(double x, double y, double a);
    double x, y, a;
    bool contiene(Punto pto);
};

Cuadro::Cuadro(double x_ = 0, double y_ = 0, double a_ = 0)
{
    x = x_;
    y = y_;
    a = a_;
}

bool Cuadro::contiene(Punto p) {
    return(p.x >= x - a && p.x < x + a && p.y >= y - a && p.y < y + a);
}


//QUADTREE
class Quadtree
{
public:
    Quadtree(Cuadro cuadro, int n);
    bool insertar(Punto p);

private:
    Cuadro cuadro;
    int profundidad;
    vector<Punto> puntos;
    bool dividido;

    Quadtree* derechaArriba;
    Quadtree* derechaAbajo;
    Quadtree* izquierdaAbajo;
    Quadtree* izquierdaArriba;

    void dividir();
};

Quadtree::Quadtree(Cuadro cuadro_, int profundidad_)
{
    cuadro = cuadro_;
    profundidad = profundidad_;
    dividido = false;
    derechaArriba = derechaAbajo = izquierdaAbajo = izquierdaArriba = 0;
}




bool Quadtree::insertar(Punto p) {
    if (!cuadro.contiene(p))
        return false;

    if (profundidad == 0) {
        puntos.push_back(p);

        cout << "Se inserto el punto :" << p.x << " ; " << p.y << endl;
        cout << "en el cuadrante : " << cuadro.x << " ; " << cuadro.y << endl;
        cout << endl;

        return true;
    }
    else {
        if (!dividido) {
            dividir();
        }
        if (derechaArriba->insertar(p))
            return true;
        if (derechaAbajo->insertar(p))
            return true;
        if (izquierdaAbajo->insertar(p))
            return true;
        if (izquierdaArriba->insertar(p))
            return true;
    }
}

void Quadtree::dividir() {
    Cuadro DAb(cuadro.x + cuadro.a/2, cuadro.y - cuadro.a / 2, cuadro.a/2);
    Cuadro DAr(cuadro.x + cuadro.a / 2, cuadro.y + cuadro.a / 2, cuadro.a / 2);
    Cuadro IAb(cuadro.x - cuadro.a / 2, cuadro.y - cuadro.a / 2, cuadro.a / 2);
    Cuadro IAr(cuadro.x - cuadro.a / 2, cuadro.y + cuadro.a / 2, cuadro.a / 2);
    
    derechaAbajo = new Quadtree(DAb, profundidad-1);
    derechaArriba = new Quadtree(DAr, profundidad-1);
    izquierdaAbajo = new Quadtree(IAb, profundidad-1);
    izquierdaArriba = new Quadtree(IAr, profundidad-1);

    cout << "Se dividio el cuadrante: " << cuadro.x << ", " << cuadro.y << endl;
    cout << endl;

    dividido = true;
}

int main(){
    
    Cuadro cuadro(30,30,25); 
    Quadtree QT(cuadro, 2);

    Punto p1(29,45);
    Punto p2(19, 90);
    Punto p3(30, 11);
    Punto p4(19, 65);

    QT.insertar(p1);
    QT.insertar(p2);
    QT.insertar(p3);
    QT.insertar(p4);

    return 0;
}