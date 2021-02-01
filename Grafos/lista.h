#include<iostream>
using namespace std;
class nodoa {
   
   public:
    int ady;
    int peso;
    nodoa *siguiente;
	//constructor
    nodoa(int v,int p, nodoa *sig = NULL)
    {
       ady = v;
       peso=p;
       siguiente = sig;
    }
   
    class listaa;
};

typedef nodoa *pnodoa;

class listaa {      
   public:
    pnodoa primero;
    //constructor
	listaa() { primero =  NULL; }// crea la lista vacia
	//metodos
	void Insertara(int v); // insert
   // void Borrara(int v);// delete
    bool ListaaVacia();  //empty
    void Mostrara();// recorrer	 
    //pnodo Buscara( int v);// seek
   // void BorrarListaa(); //clear
    
};





