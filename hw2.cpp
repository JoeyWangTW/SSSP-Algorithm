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
	struct list *next;
};

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

int main(int argc, char* argv[])
{	
	ifstream input(argv[1]);
	string temp;
	int V,E;	
	cout<<"this is v0.1"<<endl;
	
	input>>temp;
	input>>temp;
	input>>temp;
	input>>V;
	input>>E;
	input>>temp;//direct?
	VertexList* Vx= new VertexList[V]();
	Vx = buildGraph(input,Vx,V,E);
}
