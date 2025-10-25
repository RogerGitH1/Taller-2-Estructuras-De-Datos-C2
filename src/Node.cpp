#include "Node.h"

Node::Node(int valor, int posX, int posY){
    this -> valor = valor;
    this -> posX = posX;
    this -> posY = posY;
    siguiente = nullptr;
}

Node::~Node(){}