#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix() {
    start = nullptr;
}

void SparseMatrix::add(int value, int xPos, int yPos){
    if(value == 0){
        return;
    }

    Node* nuevo = new Node(value, xPos, yPos);

    if(start == nullptr){
        start = nuevo;
        return;
    }

    Node* actual = start;
    Node* ant = nullptr;

    while (actual != nullptr) {
        if (actual -> posX > xPos || (actual -> posX == xPos && actual -> posY >= yPos))
            break;
        ant = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr && actual -> posX == xPos && actual -> posY == yPos) {
        actual -> valor = value;
        delete nuevo;
        return;
    }

    nuevo -> siguiente = actual;
    if (ant == nullptr){
        start = nuevo;
    }
    else{
        ant -> siguiente = nuevo;
    }
}

int SparseMatrix::get(int xPos, int yPos){
    
}

void SparseMatrix::remove(int xPos, int yPos){
    if(start == nullptr){
        return;
    }

    Node* ant = nullptr;
    Node* actual = start;

    while (actual != nullptr){
        if(actual -> posX == xPos && actual -> posY == yPos){
            Node* eliminar = actual;

            if(ant == nullptr){
                start = start -> siguiente;
            }
            else{
                ant -> siguiente = actual -> siguiente;
            }
            delete eliminar;
            return;
        }
        ant = actual;
        actual = actual -> siguiente;
    }
    return;
}

void SparseMatrix::printStoredValues(){
    if(start == nullptr){
        return;
    }

    Node* actual = start;

    while (actual != nullptr){
        std::cout << "(" << actual -> posX << ", " << actual -> posY << ") --> " << actual -> valor << std::endl;
        actual = actual -> siguiente;
    }
}

int SparseMatrix::density(){
        if(start == nullptr){
        return 0;
    }

    int cantDistinto0 = 0;

    Node* actual = start;

    int maxPosX = -1;
    int maxPosY = -1;

    while (actual != nullptr){
        if(actual -> posX > maxPosX){
            maxPosX = actual -> posX;
        }
        if(actual -> posY > maxPosY){
            maxPosY = actual -> posY;
        }

        cantDistinto0++;

        actual = actual -> siguiente;
    }

    int totalCeldas = (maxPosX + 1) * (maxPosY + 1);
    int porcentajeDensidad =  cantDistinto0 * 100 / totalCeldas;

    return porcentajeDensidad;
}

SparseMatrix* SparseMatrix::multiply(SparseMatrix* second){
    
}

SparseMatrix::~SparseMatrix(){
    Node* actual = start;

    while (actual != nullptr){
        Node* eliminar = actual;
        actual = actual -> siguiente;
        delete eliminar;
    }
    
}