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
		if (l<=max && a[Q[l]].push<a[Q[i]].push) 
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
//	cout<<endl;	
	for(int i=0; i<V; i++){
		list* check=Vx[i].next;
		if(Vx[i].push!=DBL_MAX){
			Vx[i].num=i;
			Vx[i].push=DBL_MAX;
//			cout<<"["<<Vx[i].num<<","<<Vx[i].push<<"]"<<endl;
			continue;
		}
//		cout<<"["<<Vx[i].num<<","<<Vx[i].push<<"]"<<"<---";
		while(1){
			if(check->next==NULL){
//				cout<<check->des<<":"<<check->weight;
				break;
			}
//			cout<<check->des<<":"<<check->weight<<"<---";
			check=check->next;
		}
//		cout<<endl;
	}
	return Vx;
}

VertexList* Dijkstra(VertexList* Vx, int V)
{
	int* check = new int[V]; 
	for(int i=0; i<V; i++)
		check[i]=i;
	int Q=V-1;
	Vx[0].push=0;
	while(Q!=0)
	{
		//Extract-Min+S<-S+u
		heapify(Vx, check, 0, Q);
		int temp = check[0]; 
		check[0] = check[Q];
		check[Q] = temp;
		if(Vx[check[Q]].next!=NULL){
			list* it=Vx[check[Q]].next;
			while(1){
				if(Vx[it->des].push>Vx[check[Q]].push+it->weight){
					Vx[it->des].push=Vx[check[Q]].push+it->weight;
					Vx[it->des].PV=check[Q];
		//			cout<<Vx[it->des].PV<<":"<<Vx[it->des].push<<endl;
				}
				if(it->next==NULL)
					break;
				it=it->next;
			}
		}
		Q--;
	}
	return Vx;	
}

void swap(VertexList* a, int i, int j) {
	VertexList tmp = a[j];
	a[j] = a[i];
	a[i] = tmp;
}
int partition(VertexList* a, int l, int r) {
	swap(a,(l+r)/2,r); //pick the middle as the pivot
	int p = l;
	for (int i=l; i<r; i++) {
		if (a[i].PV<=a[r].PV) {
			swap(a,i,p);
			p++;
		}
	} 
	swap(a,p,r);
	return p;
}
void quicksort(VertexList* a, int l, int r) {
	if (l<r) {
		int p = partition(a,l,r);
		quicksort(a,l,p-1);
		quicksort(a,p+1,r);
	}
}


int main(int argc, char* argv[])
{	
	ifstream input(argv[1]);
	string temp;
	int V,E;	
	
	input>>temp;
	input>>temp;
	input>>temp;
	input>>V;
	input>>E;
	input>>temp;//direct?

	VertexList* Vx= new VertexList[V]();
	Vx = buildGraph(input,Vx,V,E);
	
	Vx = Dijkstra(Vx,V);
	quicksort(Vx,1,V-1);	
	for(int i=1; i<V; i++){
		cout<<Vx[i].PV<<","<<Vx[i].num<<","<<Vx[i].push<<endl;
	}
}
