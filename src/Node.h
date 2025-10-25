#pragma once

class Node{
    public:
        int valor;
        int posX;
        int posY;
        Node* siguiente;

        Node(int valor, int posX, int posY);
        ~Node();
};