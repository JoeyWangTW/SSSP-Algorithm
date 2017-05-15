#include<iostream>
#include<fstream>
#include<string>
#include<float.h>
using namespace std;

struct list{
	int des;
	int weight;
	struct list *next;	
};

struct VertexList{
	int num;
	double push;
	int PV;
	struct list *next;
};

void heapify(VertexList *a, int* Q, int i, int max) 
{
		int l = 2*i+1;
		int r = 2*i+2;
		int k = i;
		if (l<max && a[Q[l]].push<a[Q[i]].push) 
			k = l;
		if (r<max && a[Q[r]].push<a[Q[k]].push) 
			k = r;
		if (k!=i) {
			int temp = Q[i];
			Q[i] = Q[k];
			Q[k] = temp;
			heapify(a, Q, k, max);
		}
}

/*void heapsort(VertexList *a, int n) 
{
		for (int i=n/2-1; i>=0; i--) { //build heap 
			heapify(a,i,n);
		}
		for (int i=n-1; i>=1; i--) {
			VertexList temp = a[0]; 
			a[0] = a[i];
			a[i] = temp;
			heapify(a, 0, i);
		}
}*/

VertexList* buildGraph(ifstream &input, VertexList* Vx, int V, int E)
{
	string temp;	
	for(int i=0; i<E ;i++){
		int s,e,w;
		getline(input,temp,',');
		s=stoi(temp);
		getline(input,temp,',');
		e=stoi(temp);
		input>>temp;
		w=stoi(temp);

		//cout<<s<<":"<<e<<":"<<w<<endl;
		if(Vx[s].push!=DBL_MAX){
			Vx[s].num=s;
			Vx[s].push=DBL_MAX;
			list* newVertex = new list();
			newVertex->des=e;
			newVertex->weight=w;
			Vx[s].next = newVertex;
		}
		else{
			list *it=Vx[s].next;
			while(1){
				if(it->next==NULL){
					list* newVertex = new list();
					newVertex->des=e;
					newVertex->weight=w;
					it->next=newVertex;
					it=newVertex;
					break;
				}
				else{
					it=it->next;
				}
			}
		}			
	}
	cout<<endl;	
	for(int i=0; i<V; i++){
		list* check=Vx[i].next;
		if(Vx[i].push!=DBL_MAX){
			Vx[i].num=i;
			Vx[i].push=DBL_MAX;
			cout<<"["<<Vx[i].num<<"]"<<endl;
			continue;
		}
		cout<<"["<<Vx[i].num<<"]"<<"<---";
		while(1){
			if(check->next==NULL){
				cout<<check->des<<":"<<check->weight;
				break;
			}
			cout<<check->des<<":"<<check->weight<<"<---";
			check=check->next;
		}
		cout<<endl;
	}
	return Vx;
}

VertexList* Dijkstra(VertexList* S,VertexList* Vx, int V)
{
	int* check = new int[V]; 
	for(int i=0; i<V; i++)
		check[i]=i;
	int Q=V-1;
	Vx[0].push=0;
	for (int i=V/2-1; i>=0; i--) { //build heap 
		heapify(Vx,check,i,V);
	}
	while(Q!=0)
	{
		//Extract-Min+S<-S+u
		S[check[0]]=Vx[check[0]];
		cout<<check[0]<<endl;
		int temp = check[0]; 
		check[0] = check[Q];
		check[Q] = temp;
		Q--;
		if(Q==0){
			S[check[0]]=Vx[check[0]];
			break;
		}
		if(S[check[Q+1]].next!=NULL){
			list* it=S[check[Q+1]].next;
			while(1){
				if(Vx[it->des].push>S[check[Q+1]].push+it->weight){
					Vx[it->des].push=S[check[Q+1]].push+it->weight;
					Vx[it->des].PV=check[Q+1];
				}
				if(it->next==NULL)
					break;
				it=it->next;
			}
		}
		heapify(Vx, check, 0, Q);
	}

	return S;	
}

int main(int argc, char* argv[])
{	
	ifstream input(argv[1]);
	string temp;
	int V,E;	
	cout<<"this is v0.2"<<endl;
	cout<<"this is v0.1"<<endl;
	
	input>>temp;
	input>>temp;
	input>>temp;
	input>>V;
	input>>E;
	input>>temp;//direct?

	VertexList* Vx= new VertexList[V]();
	Vx = buildGraph(input,Vx,V,E);
	
	VertexList* SSSP= new VertexList[V]();
	SSSP = Dijkstra(SSSP,Vx,V);
	for(int i=0; i<V; i++){
		if(SSSP[i].next==NULL)
			continue;
		list* it=SSSP[i].next;
		while(1){
			if(SSSP[it->des].PV==i)
				cout<<i<<","<<it->des<<","<<it->weight<<endl;
			if(it->next==NULL)
				break;
			it=it->next;
		}
	}
}
