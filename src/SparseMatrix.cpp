#include <SparseMatrix.h>

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

int get(int xPos, int yPos){
    
}

void SparseMatrix::remove(int xPos, int yPos){
    
}

void SparseMatrix::printStoredValues(){
    
}

int SparseMatrix::density(){
    
}

SparseMatrix*::multiply(SparseMatrix* second){
    
}

SparseMatrix::~SparseMatrix(){

}