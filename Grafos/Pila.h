
#define tam 100
class pila{
private:
	int pilita[tam];
	int cima;
public:
	pila(){
	cima=-1;
	}
void push(int v);
int pop();
int ver(int i);
bool pilavacia();
bool pilallena();
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


bool pila::pilavacia(){
return cima==-1;
}
bool pila::pilallena(){
return cima==tam-1;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int pila::ver(int i){
	
	
	return pilita[i];
	
	}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void pila::push(int v){
	if(pilallena()){
	cout<<"la pila esta llena";

	}
	else{
	cima++;
	pilita[cima]=v;

	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	int pila::pop(){
		if(pilavacia()){
		
		cout<<"lka pila esta vacia";return 0;
		}
		else{
		cima--;
		return pilita[cima+1];
		}
	}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
