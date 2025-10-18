#include <iostream>
#include <random>
#include <vector>
#include "SparseMatrix.h"
#include <unordered_set>
#include <chrono>
#include <cmath>

using namespace std;
using Clock = chrono::steady_clock;
using usec  = chrono::microseconds;

struct Triple { int x, y, v; };

static int calcular_tamano_matriz(int no_nulos, double density) {
    double M = std::sqrt(no_nulos / std::max(1e-9, density));
    return std::max(1, (int)std::ceil(M));
}

static vector<Triple> generar_datos(int cantidad_no_nulos, int M, uint32_t seed) {
    mt19937 generador(seed);

    uniform_int_distribution<int> coord(0, M-1), valor(1, 9);
    unordered_set<long long> usadas;

    auto clave  = [](int x,int y)->long long {
         return ((long long)x<<32) ^ (unsigned long long)y; 
    };

    vector<Triple> datos; 
    datos.reserve(cantidad_no_nulos);

    while ((int)datos.size() < cantidad_no_nulos) {
        int x = coord(generador);
        int y = coord(generador);
        if (usadas.insert(clave(x,y)).second)
            datos.push_back({x,y,valor(generador)});
    }
    return datos;
}

static long long tiempo_add(const vector<Triple>& datos){
    SparseMatrix m;
    auto inicio = Clock::now();
    for (auto& elemento : datos) 
        m.add(elemento.v, elemento.x, elemento.y);

    auto fin = Clock::now();
    return std::chrono::duration_cast<usec>(fin - inicio).count();
}

static long long tiempo_get_existe(const vector<Triple>& datos){
    SparseMatrix m; 
    for(auto& elemento:datos) 
        m.add(elemento.v,elemento.x,elemento.y);

    auto inicio = Clock::now();
    long long sum=0; 
    for(auto& elemento:datos) 
        sum += m.get(elemento.x,elemento.y);

    auto fin = Clock::now(); 
    volatile long long s=sum; (void)s;
    return std::chrono::duration_cast<usec>(fin - inicio).count();
}

static long long tiempo_get_no_existe(const vector<Triple>& datos,int M){
    SparseMatrix m; 
    for(auto& elemento:datos) 
        m.add(elemento.v,elemento.x,elemento.y);

    unordered_set<long long> used; 
    auto clave  = [](int x,int y)->long long {
         return ((long long)x<<32) ^ (unsigned long long)y;
    };

    for(auto& elemento:datos) 
        used.insert(clave(elemento.x,elemento.y));

    mt19937 rng(777); 
    uniform_int_distribution<int> coord(0,M-1);
    vector<pair<int,int>> consultas;
    consultas.reserve(datos.size());

    while((int)consultas.size()<(int)datos.size()){
        int x=coord(rng),y=coord(rng);
        if(!used.count(clave(x,y)))consultas.emplace_back(x,y);
    }

    auto inicio=Clock::now(); 
    long long sum=0; 
    for(auto&q:consultas) 
        sum+=m.get(q.first,q.second);

    auto final=Clock::now(); 
    volatile long long s=sum; (void)s;
    return std::chrono::duration_cast<usec>(final - inicio).count();
}

static long long tiempo_multiply(const vector<Triple>& Adatos,const vector<Triple>& Bdatos){
    SparseMatrix A,B; 
    for(auto&t:Adatos)
        A.add(t.v,t.x,t.y); 
    for(auto&t:Bdatos)
        B.add(t.v,t.x,t.y);

    auto inicio=Clock::now(); 
    SparseMatrix* C=A.multiply(&B); 
    auto final=Clock::now(); delete C;
    return std::chrono::duration_cast<usec>(final - inicio).count();
}

int main(int argc, char** argv) {
    if (argc < 2) { std::cerr << "Uso: " << argv[0] << " N\n"; return 1; }
    int N = std::max(1, std::atoi(argv[1]));
    const double densidades[2] = {0.35, 0.75};

    for (double dens : densidades) {
        int M = calcular_tamano_matriz(N, dens);
        auto Adata = generar_datos(N, M, N*100 + int(dens*100));
        auto Bdata = generar_datos(N, M, N*100 + int(dens*100) + 7);

        long long t_add  = tiempo_add(Adata);
        long long t_hit  = tiempo_get_existe(Adata);
        long long t_miss = tiempo_get_no_existe(Adata, M);
        long long t_mul  = tiempo_multiply(Adata, Bdata);

        cout << "\n--- RESULTADOS ---\n";
        cout << "N = " << N << " | Densidad = " << dens<< " | Dimension = " << M << "x" << M << "\n";
        cout << "add()        : " << t_add  << " us\n";
        cout << "get_hits()   : " << t_hit  << " us\n";
        cout << "get_misses() : " << t_miss << " us\n";
        cout << "multiply()   : " << t_mul  << " us\n";
    }
    return 0;
}