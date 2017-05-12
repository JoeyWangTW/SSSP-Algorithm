#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct list{
	int des;
	int weight;
	double push;
	struct list *next;	
};

list* buildGraph(ifstream &input, list* Vx, int V, int E)
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

		cout<<s<<":"<<e<<":"<<w<<endl;
		if(Vx[s].push!=-1){
			Vx[s].des=e;
			Vx[s].weight=w;
			Vx[s].push=-1;
		}
		else{
			list *it=&Vx[s];
			while(1){
				if(it->next==NULL){
					list* newVertex = new list();
					newVertex->des=e;
					newVertex->weight=w;
					newVertex->push=-1;
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
		list* check=&Vx[i];
		while(1){
			if(check->push==0){
				cout<<"X:X";
				break;
			}
			if(check->next==NULL){
				cout<<check->des<<":"<<check->weight;
				break;
			}
			cout<<check->des<<":"<<check->weight<<":"<<"<---";
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

	
	input>>temp;
	input>>temp;
	input>>temp;
	input>>V;
	input>>E;
	input>>temp;//direct?
	list* Vx= new list[V]();
	Vx = buildGraph(input,Vx,V,E);
}
