#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <list>

using namespace std;

int counter = 0;

void print_path(int arrayPi[], int distanc, int s,int v);

int main(){

	int vertices;
	bool v_check = false;
	const char comma = ',';
	vector<int> edges;
	list<int>* AdjList = NULL;
	int* color = NULL;
	int* d = NULL;
	int* pi = NULL;

	while (!cin.eof()) {
		string line;
        getline(cin, line);
		while(!line.empty() && isspace(*line.begin()))
            line.erase(line.begin());
		if (line[0] == 'V' || line[0] == 'v') {
			if (v_check == true){
				cerr << "Error: Invalid command. Enter an E command." << endl;
			}
			else {
				vertices = 0;
				istringstream input(line);
				string subs;
				input >> subs;
				input >> vertices;
				v_check = true;
				if(AdjList != NULL){
					delete [] AdjList;
				}
				if(color != NULL){
					delete [] color;
				}
				if(d != NULL){
					delete [] d;
				}
				if(pi != NULL){
					delete [] pi;
				}
				AdjList = new list<int>[vertices];
				color = new int[vertices];
				d = new int[vertices];
				pi = new int[vertices];
			}
		}
		else if (line[0] == 'E' || line[0] == 'e') {
			if (v_check == false) {
				cerr << "Error: Enter a new V command before entering a new E command. Or enter an s command" << endl;
			}
			if (v_check == true) {
				v_check = false;
				edges.clear();
				istringstream input(line);
				string subs;
				input >> subs;

				while (!input.eof()){
					char separator;
					input >> separator;
					input >> separator;
					if (separator == comma){
						input >> separator;
					}
					int num;
					input >> num;
					if (input.eof())
						break;
					if (num > (vertices-1)){
						edges.clear();
						v_check = true;
						cerr << "Error: An edge specified for a vertex that does not exist\n";
						break;
					}
					edges.push_back(num);
					input >> separator;
					input >> num;
					if (num > (vertices-1)){
						edges.clear();
						v_check = true;
						cerr << "Error: An edge specified for a vertex that does not exist\n";
						break;
					}
					edges.push_back(num);
				}

				if (!edges.empty()){
					for(unsigned j =0; j< edges.size(); j=j+2){
						AdjList[edges[j]].push_back(edges[j+1]);
						AdjList[edges[j+1]].push_back(edges[j]);
						//cout << AdjList[edges[j]].front() << endl;
					}
				}
			}
		}

		else if (line[0] == 's' || line[0] == 'S') {
			if(v_check == false) {
				istringstream input(line);
				string subs;
				int sourceVertex, desVertex;
				input >> subs;
				input >> sourceVertex;
				input >> desVertex;
				if (sourceVertex >= vertices || desVertex >= vertices || sourceVertex < 0 || desVertex < 0) {
					cerr << "Error: Shortest path asked for a vertex that does not exist" << endl;
					continue;
				}
				for(int m = 0; m < vertices; m++){
					if (m!= sourceVertex){
						color[m] = 0;
						d[m] = numeric_limits<int>::max();
						pi[m] = -1;
					}
				}
				color[sourceVertex] = 1;
				d[sourceVertex] = 0;
				pi[sourceVertex] = -1;
				queue<int> myQueue;
				myQueue.push(sourceVertex);
				while (!myQueue.empty()) {
					int u = myQueue.front();
					myQueue.pop();
					list <int> :: iterator it;
					for(it = AdjList[u].begin(); it != AdjList[u].end(); it++){
						if (color[*it] == 0) {
							color[*it] = 1;
							d[*it] = d[u] +1;
							pi[*it] = u;
							myQueue.push(*it);
						}
					}
					color[u] = 2;
				}

				print_path(pi, d[desVertex], sourceVertex, desVertex);
			}

			else {
				cerr << "Error: First enter a graph to find the shortest path." << endl;
			}

		}
        else if (line.length()==0) {
                break;
            }

	 //   else {
	//		 cerr << "Error: Invalid input format\n";
	//    }
	}

	if(AdjList != NULL){
		delete [] AdjList;
	}
	if(color != NULL){
		delete [] color;
	}
	if(d != NULL){
		delete [] d;
	}
	if(pi != NULL){
		delete [] pi;
	}

	return 0;
}

void print_path(int arrayPi[], int distanc, int s,int v){
	counter = 0;
	if (v==s){
		counter++;
		cout << s;
		if (distanc == 0)
			cout << endl;
		else
			cout << "-";
	}
	else if (arrayPi[v] == -1)
		cerr << "Error: no path exists from " << s << " to " << v << endl;
	else {
		print_path(arrayPi, distanc, s, arrayPi[v]);
		cout << v;
		if (counter < distanc)
			cout << "-";
		else
			cout << endl;
		counter++;
	}
}
