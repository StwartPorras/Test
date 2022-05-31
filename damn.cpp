#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

typedef array<double,10> filas;
typedef array<filas,5> matriz;

 void inicializar_matriz(matriz &box){
     for(int i=0;i<=4;i++){
         for(int j=0;j<=9;j++){
             box[i][j]=0;
         }
     }
 }

 double probalidad(int posicion,char cifra){
     double x = 0;
     double prob;
     fstream data;
    data.open("data.txt",ios::in);
    string numero;
    if(data.is_open()){
        while(getline(data,numero)){
            if(numero[posicion]==cifra){
                x++;
            }
        }
        prob = x/552;
        data.close();
    }
    return prob;
 }
 void rellenar_columna(matriz &box,int columna, char valor){
     for(int i=0;i<=4;i++){
             box[i][columna]=probalidad(i,valor);
     }
     
 }
 void leer_matrix(matriz box){
     for(int i=0;i<=4;i++){
         for(int j=0;j<=9;j++){
             cout<<" "<<box[i][j]<<" ";
         }
         cout<<"\n";
     }
 }
 void rellenar_matriz(matriz &box){
     int columna=0; char valor='0';
     while(columna<=9){
        rellenar_columna(box,columna,valor);
        columna++;
        valor++;
     }
 }

int main(){
    matriz idk;
    inicializar_matriz(idk);
    rellenar_matriz(idk);    
    leer_matrix(idk);
    
}
    
