#include<iostream>
#include"listag.h"
using namespace std;

int main(){
lista l;
/*
int opc,opc2,inicio,final,peso,vertice,ruta;
string NomEs;
char cont;*/

l.Insertarv(1, "Metro_CU", 3);
l.Insertarv(3, "Anexo_Ingenieria", 3);
l.Insertarv(2, "Facultad_de_Ciencias", 3);
l.creararco(1,2,0);
l.creararco(2,3,0);
l.creararco(3,1,0);

l.Mostrarv();

l.RecorridoProfundidad();

/*
do{
system("cls");cout<<"\nMENU:\n\n1- Crear Grafo\n2- Ver Matriz de Adyacencia\n3- Ver Matriz de Caminos\n4- Mostar Lista de Nodos Adyacencentes\n5- Recorrido En Profundidad\n6- Recorrido En Anchura\n7- Salir\n\n Ingrese la opcion: ";cin>>opc;
switch(opc){
	case 1:
		do{system("cls");cout<<"\nMENU:\n1- Nuevo Vertice\n2- Crear Arco\n\nIngrse la opcion: ";cin>>opc2;}while(opc2<1||opc>2);
		switch(opc2)
		{
			case 1:
				system("cls");
				if(opc==1)
				{
					l.BorrarListav();
				}
				do{system("cls");cont=' ';
                	cout<<"\nIngrese el vertice: ";cin>>vertice;
                	cout<<"\nIngrese nombre de la estacion: ";cin>>NomEs;
                	cout<<"\nIngrese la ruta: ";cin>>ruta;
                	l.Insertarv(vertice, NomEs, ruta);
                	cout<<"\n\nDesea Ingresar Otro Vertice (S/N): ";cin>>cont;
				}while(cont!='n'&&cont!='N');
				break;
			break;
			case 2:
				do
				{
					cont=' ';
					cout<<"\nIngrse el vertice de inicio: ";cin>>inicio;
					cout<<"\nIngrse el vertice de fin: ";cin>>final;
					cout<<"\nIngrse el peso: ";cin>>peso;
					l.creararco(inicio,final,peso);
					cout<<"\n\nDesea crear otro arco (S/N): ";
					cin>>cont;
				}while(cont!='n'&&cont!='N');break;
		}
		break;
	case 2:
		system("cls");
		if(l.ListavVacia())
		{
			cout<<"\n\nGrafo Vacio\n\n";}else{
			cout<<"\n\nMatriz de adyacencia"<<"\n\n";
			l.CrearMatrizAdyacencia();
			l.mostrarmatriz();
		}
		break;
	case 3:
		system("cls");
		if(l.ListavVacia())
		{
			cout<<"\n\nGrafo Vacio\n\n";
		}
		else
		{
			cout<<"\n\nMatriz de caminos\n\n";
			l.CrearMatrizCaminos();
			l.MostrarMatrizCaminos();
		}
		break;
	case 4:
		system("cls");
		if(l.ListavVacia())
		{
			cout<<"\n\nGrafo Vacio\n\n";
		}
		else
		{
			cout<<"\n\nVertices Adyacentes\n\n";
			l.Mostrarv();
		}
		break;
	case 5:
		system("cls");
		if(l.ListavVacia())
		{
			cout<<"\n\nGrafo Vacio\n\n";
		}
		else
		{
			cout<<"\n\nRecorrido Profundidad\n\n";
			l.RecorridoProfundidad();
		}
		break;
	case 6:
		system("cls");
		if(l.ListavVacia())
		{
			cout<<"\n\nGrafo Vacio\n\n";
		}
		else
		{
         cout<<"\n\nRecorrido Anchura\n\n";
		 l.RecorridoAnchura();
		}
		break;
	
}
cout<<"\n\n";system("pause");
}while(opc!=7); */
return 0;
}
