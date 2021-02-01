#include<time.h>
#include<windows.h>
#include"lista.h"
#include"Colas.h"
#include"Pila.h"
#define Max 100
#define INF 999
#include <string>
using namespace std;
// funcion gotoxy
void gotoxy(short x, short y);
//funcion para cambiar el color del texto
void text_color( int col );
//matriz de adyacencia
int MatrizAdyacente[Max][Max];
//matriz de caminos o valorada
int MatrizCaminos[Max][Max];
//matriz de floyd y de warshall
int mat_floyd_warshall[Max][Max];
int visitado[Max];
int marcado[Max];
class nodo {
  public:
    int Id;
    string Estacion;
    int Ruta;
    nodoa *puntero;
    nodo *siguiente;
	//constructor
    nodo(int v, string NomEstacion, int ruta, nodo *sig = NULL,nodoa *punt=NULL)
    {
      Id = v;
      Estacion = NomEstacion;
      Ruta = ruta;
      siguiente = sig;
      puntero=punt;
    }
    // friend class listaa;
    class lista;
};

typedef nodo *pnodo;

class lista{
  public:
    //listaa ad;
    pnodo primero;
    //constructor
    lista() { primero =  NULL; }// crea la lista vacia
    //metodos
    void Insertarv(int v, string NomRuta, int ruta); // insert
    void Borrarv(int v);// delete
    bool ListavVacia();  //empty
    void Mostrarv();// recorrer
    pnodo Buscarv( int v);// seek
    void BorrarListav(); //clear
    bool listavexiste(int i,int f);
    void creararco(int i,int f,int peso);
    void CrearMatrizAdyacencia();
  	int CantidadVertices();
  	int ExisteArco(int i,int f);
  	void mostrarmatriz();
  	bool BuscarAdy(pnodo aux,int ad);
  	void CrearMatrizCaminos();
  	void MostrarMatrizCaminos();
  	void RecorridoAnchura();
  	int NodoVisitado(int v, int t);
  	void RecorridoProfundidad();
  	void Floyd();
  	void Warshall();
  	void copiarMatrizCaminos();
  	void mostrar_mat_floyd_warshall();
  	int Posicion(int v);
  	bool marca(int ady ,int ident[Max],int i);
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::creararco(int i,int f,int peso){
	pnodo pos;
	pos=primero;
	if(listavexiste(i,f)){
	while(pos!=NULL){ // se recorre la lista  hasta encontrar el valor buscado
		if(i == pos->Id ){

			if(pos->puntero==NULL){
				pos->puntero=new nodoa(f,peso);
			}
			else {
				nodoa *temp=pos->puntero;
					while(temp->siguiente!=NULL){
						temp=temp->siguiente;
					}
					temp->siguiente=new nodoa(f,peso);
					temp=NULL;
					delete temp;
				}
				}
			pos=pos->siguiente;
			}
	}
	else cout<<"no se puede crear arco"<<endl;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool lista::listavexiste(int i,int f){
	if(Buscarv(i)!=NULL&&Buscarv(f)!=NULL){return true;}
	else{return false;}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::Insertarv(int v, string NomRuta, int ruta)
{
   pnodo  anterior;
   if(ListavVacia()) // Si la lista est� vac�a
   {
	  primero = new nodo(v, NomRuta, ruta, primero);
   }else { if(v<=primero->Id){ //si el valor a insertar es menor que el
	      primero =new nodo(v, NomRuta, ruta, primero) ; //se inserta el nodo antes del primer dato de la lista
		}else{
			//en caso contrario se busca el nodo que tenga un dato menor a valor
			anterior = primero; // Avanzamos hasta que el siguiente tenga un valor mayor que valor
			while((anterior->siguiente) && (anterior->siguiente->Id<=v)){
				anterior = anterior->siguiente; }
			   // Creamos un nuevo nodo despu�s del nodo anterior, y cuyo siguiente
               // es el siguiente del anterior
			   anterior->siguiente = new nodo(v, NomRuta, ruta, anterior->siguiente);
			}
   }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::Borrarv(int v)
{
   pnodo anterior, nodo;
   nodo = primero;
   anterior = NULL;
   if(primero){  // si la lista tiene  datos se busca el nodo a borrar

	   while((nodo) && nodo->Id !=v) {// busca el dato igual al valor
		   anterior = nodo;
		nodo = nodo->siguiente;
	    }
	   if(!nodo){// en este caso el valor buscado no esta en la lista
		   cout<<"\n no esxite en la lista";
	  	   }
         else { // Borrar el nodo
			  if(anterior==NULL) //* Primer elemento
				primero = primero->siguiente;
				else  //* un elemento cualquiera
				anterior->siguiente = nodo->siguiente;
      delete nodo; // se libera el nodo es decir se borra
   }
   }else cout<<"\n no hay elementos para borrar";
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::Mostrarv()
{
   pnodo nodo = primero;

   if(ListavVacia()) cout<<"\nLista vac�a"<<'\n'; // si hay datos para mostrar
   else {
	   while(nodo) { // mientras tenga datos la lista
		   cout<<" Id:\t" <<nodo->Id<<"\n";
		   cout<<" Estacion:\t"<<nodo->Estacion<<"\n";
		   cout<<" Ruta:\t"<<nodo->Ruta;
           cout << "\tadyacentes";
           nodoa* temp = nodo->puntero;

		   while(temp)
           {
		        cout<<"\t"<<temp->ady/*<<"peso: "<<temp->peso*/;
			    temp=temp->siguiente;

		   }
           cout<<endl<<endl;
           nodo = nodo->siguiente;
       }
     cout<<'\n';
   }

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
pnodo lista::Buscarv(int valor){
	pnodo indice,n=NULL;
	indice=primero;
	while(indice!=NULL){ // se recorre la lista  hasta encontrar el valor buscado
		if(valor == indice->Id ){
			return indice; // al encontar el valor  lo retorna
			}
		indice=indice->siguiente;
	}
 cout<<"\n no esta en la lista";
 return n; // si el valor buscado no esta en la lista retorna nulo
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::BorrarListav(){
	pnodo nodo;
   while(primero) { //mientras la lista tenda datos los borra
      nodo = primero;
      primero = nodo->siguiente;
      delete nodo; // se libera la memoria de  cada nodo
}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool lista::ListavVacia(){
	return primero == NULL;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int lista::CantidadVertices(){
    pnodo nodo=primero;
    int i=0;
    while(nodo!=NULL){
       i++;
       nodo=nodo->siguiente;
    }
    return i;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::CrearMatrizAdyacencia(){
     pnodo nodo=primero,nodotemp;
     int i,j;
     int cant=CantidadVertices();
     for(i=0;i<cant;i++){
         nodotemp=primero;
       for(j=0;j<cant;j++){
         MatrizAdyacente[i][j]=ExisteArco(nodo->Id,nodotemp->Id);
         nodotemp=nodotemp->siguiente;
       }
        nodo=nodo->siguiente;
     }
     delete nodo;
     delete nodotemp;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int lista::ExisteArco(int i,int f){
  pnodo nodo;
  int a=1;
  nodo=Buscarv(i);
  if(nodo){
    if(BuscarAdy(nodo,f)) return a;
    else return a=0;
  }else return a=0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool lista::BuscarAdy(pnodo aux,int ad){
     nodoa *temp=aux->puntero;
     bool a;
     while(temp){
        if(ad==temp->ady){
           return a=true;}
        temp=temp->siguiente;
     } return a=false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::mostrarmatriz(){
    int i,j,cant;
    pnodo nodo=primero;
    cant=CantidadVertices();cout<<"   ";
    for(i=0;i<cant;i++){text_color(11);cout<<"\t"<<nodo->Id<<" ";nodo=nodo->siguiente; }
    nodo=primero;cout<<"\n\n";
    for( i=0;i<cant;i++){
         text_color(11);cout<<nodo->Id;
         for(j=0;j<cant;j++){
            text_color(7);cout<<"\t"<<MatrizAdyacente[i][j]<<" ";
         }
         nodo=nodo->siguiente;
         cout<<"\n";
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::CrearMatrizCaminos(){
     pnodo nodo=primero,nodotemp,nodoaux;
     nodoa *auxiliar;
     int i,j;
     int cant=CantidadVertices();
     for(i=0;i<cant;i++){
         nodotemp=primero;
       for(j=0;j<cant;j++){
         if(nodo->Id==nodotemp->Id){
              MatrizCaminos[i][j]=0;
         }else{
            if(ExisteArco(nodo->Id,nodotemp->Id)==1){
                 nodoaux=Buscarv(nodo->Id);
                 auxiliar=nodoaux->puntero;
                 while(auxiliar){
                       if(nodotemp->Id==auxiliar->ady){
                           MatrizCaminos[i][j]=auxiliar->peso;
                       }
                    auxiliar=auxiliar->siguiente;
                 }

            }else{
                  MatrizCaminos[i][j]=INF;
            }
         }

         nodotemp=nodotemp->siguiente;
       }
        nodo=nodo->siguiente;
     }
     delete nodo;
     delete nodotemp;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::MostrarMatrizCaminos(){
     int i,j,cant;
     char x=236;
     pnodo nodo=primero;
    cant=CantidadVertices();cout<<"   ";
    for(i=0;i<cant;i++){text_color(11);cout<<"\t"<<nodo->Id<<" ";nodo=nodo->siguiente; }
    nodo=primero;cout<<"\n\n";
    for( i=0;i<cant;i++){
         text_color(11);cout<<nodo->Id<<"  ";
         for(j=0;j<cant;j++){
            if(MatrizCaminos[i][j]==INF){
              text_color(7);cout<<"\t"<<x<<" ";
            }
            else{
            text_color(7);cout<<"\t"<<MatrizCaminos[i][j]<<" ";}
         }
         nodo=nodo->siguiente;
         cout<<"\n";
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::RecorridoAnchura(){
     pnodo v;
    v=primero;
    cola c;

    nodoa *ady;
    ady=v->puntero;
    int i=0,l;
    int col=5,fil=5,col2=col;
    int marcado[100];
    c.ingresar(v->Id);
    Sleep(150);text_color(11);gotoxy(fil,col++);cout<<v->Id;
    marcado[i]=v->Id;
    while(!c.colavacia()){l=c.leer();
    Sleep(150);text_color(7);gotoxy(fil+10,col2);cout<<l<<"\t";col2++;
    v=primero;
    while(v){
   	  if(l==v->Id){
   	  ady=v->puntero;
    	while(ady){
    		if(marca(ady->ady,marcado,i)){
    			c.ingresar(ady->ady);
    				Sleep(400);text_color(11);gotoxy(fil,col++);cout<<ady->ady;
    				marcado[i++]=ady->ady;
            }
           ady=ady->siguiente;

    	}
   	}
    	v=v->siguiente;
    }
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int lista::NodoVisitado(int v, int t){
  int i;
  for(i=0;i<t;i++){
     if(v==marcado[i]||v==visitado[i]){
        return 0;
     }
  }
  return 1;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::RecorridoProfundidad(){
    cout << "Recorrido a profundiad \n";
     pnodo v;
    v=primero;
    pila pil;
    nodoa *ady;
    ady=v->puntero;
    int i=0,l;
    int marcado[100];
    pil.push(v->Id);
    cout<<v->Id<<"\n";
    marcado[i]=v->Id;
    while(!pil.pilavacia()){l=pil.pop();

        //cout<<l<<"\t";col2++;
        v=primero;
        while(v){
	        if(l==v->Id){
	            ady=v->puntero;
	            while(ady){
		            if(marca(ady->ady,marcado,i)){
				        pil.push(ady->ady);
				        cout<<ady->ady<<"\n";
				        marcado[i++]=ady->ady;
				    }ady=ady->siguiente;

	            }
	        }
	        v=v->siguiente;
        }

    }


}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::Floyd(){
     int k,i,j,cant=CantidadVertices();
    copiarMatrizCaminos();
	for(k=0;k<cant;k++){
		for(i=0;i<cant;i++){
			for(j=0;j<cant;j++){
				if(mat_floyd_warshall[i][j] > mat_floyd_warshall[i][k] + mat_floyd_warshall[k][j]){
					mat_floyd_warshall[i][j] = mat_floyd_warshall[i][k] + mat_floyd_warshall[k][j];
				}//fin si
			}//fin for j
		}//fin for i
	}//fin for k
	mostrar_mat_floyd_warshall();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::Warshall(){
      int k,i,j,cant=CantidadVertices();
	copiarMatrizCaminos();
	for(k=0;k<cant;k++){
		for(i=0;i<cant;i++){
			for(j=0;j<cant;j++){
				if(!mat_floyd_warshall[i][j] && (mat_floyd_warshall[i][k] && mat_floyd_warshall[k][j])){
					mat_floyd_warshall[i][j] = mat_floyd_warshall[i][j] || (mat_floyd_warshall[i][k] && mat_floyd_warshall[k][j]);
			    }//fin si
			}//fin for j
		}//fin for i
	}//fin for k
	mostrar_mat_floyd_warshall();

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::copiarMatrizCaminos(){
	int i,j,cant=CantidadVertices();
	CrearMatrizCaminos();
	for( i=0;i<cant;i++){
         for(j=0;j<cant;j++){
			mat_floyd_warshall[i][j] =MatrizCaminos[i][j];
		 }
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void lista::mostrar_mat_floyd_warshall(){
     int i,j,cant=CantidadVertices();
     pnodo nodo=primero;
     char x=236;
     for(i=0;i<cant;i++){text_color(8);cout<<"\t"<<nodo->Id<<" ";nodo=nodo->siguiente; }
    nodo=primero;cout<<"\n\n";
	for( i=0;i<cant;i++){
         text_color(8);cout<<nodo->Id;
         for(j=0;j<cant;j++){
          if(mat_floyd_warshall[i][j]==INF){
              text_color(7);cout<<"\t"<<x;
            }
            else{
            text_color(7);cout<<"\t"<<mat_floyd_warshall[i][j];}
         }cout<<"\n";
         nodo=nodo->siguiente;
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// funcion gotoxy
void gotoxy(short x, short y) {
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x, y};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void text_color( int col ){
     HANDLE hOutput = NULL;
    if( hOutput == NULL )
        hOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOutput, (WORD) col );
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int lista::Posicion(int v){
	pnodo nodo=primero;
	int i=0;
	while(nodo){
		if(nodo->Id==v){
			return i-1;
		}
		i++;
		nodo=nodo->siguiente;
	}
  return i;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool lista::marca(int ady ,int ident[Max],int i){
bool s;

for(int f=0;f<i;f++){
	if(ady==ident[f]){
	return s=false;
	}

}
return s=true;
}
