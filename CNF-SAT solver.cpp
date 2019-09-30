#include<iostream>
#include<string.h>
#include<string>
#include<cstdlib>
#include<vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <list>


// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

using namespace std;


class vertix{
public:
int name;
int dist;
int prev;
int visit;




};

class edge{
public :
    int start;
    int dest;
    int weight;
};


vector<vertix> make_vertex_list(string str){
string temp="";
for (int i=2;i<str.length();i++){
    temp=temp+str[i];
}
int num_vertices = atoi(temp.c_str());
vector <vertix> v_set;
for (int i=0;i<num_vertices;i++){
    vertix v;
    v.name=i;
    v_set.push_back(v);

}
return v_set;
}
vector<edge> make_edge_list(string str){

        int stop=0;
        vector <edge> e_set;
       while(stop>=0){
       int temp1= str.find("<");
       int  temp2= str.find(">");
       int var = str.find(",");
       edge e;
       e.start=atoi(str.substr(temp1+1,var-temp1-1).c_str());
       e.dest= atoi(str.substr(var+1,temp2-var-1).c_str());
       e.weight=1;
       e_set.push_back(e);
       //cout<<"Start = "<<e.start<<" End= "<<e.dest<<endl;
       //cout<<"String left = "<<str.substr(temp2+1)<<endl;
       string str1 =str.substr(temp2+1);
       stop = str1.find("<");
       if (stop>=0){
        str = str.substr(temp2+2);
        //cout<<"In if , stop = "<<stop<<endl;
       }
       else if (stop<0){
        //cout <<"In else if "<< "stop = "<<stop<<endl;
        break;
       }

}
return e_set;
}

int main(){
int max_vert=-1;
vector <vertix> v_set;
vector <edge> e_set;

while(1){
string str;
getline(cin,str);

//if (cin.eof()==0){break;}
if(str.length()==0){break;}

//parsing_input(str


if (str[0]=='V'){
    v_set= make_vertex_list(str);
    max_vert = atoi(str.substr(1).c_str())+0 ;


}
if (str[0]=='E'){
    int terminate = -1;
    e_set = make_edge_list(str);

if (e_set.empty()){
cout << endl;
			 }
else{
    //cout<<"inside solver"<<endl;
     // initiallization of variables
     int n=max_vert;
     vector<int> vertex_cover;
     bool solution;
     vertex_cover.clear();
    // solving the vertix cover problem here!!!
    for(int k=1;k<n+1;k++){
   //cout<<"k = "<<k<<endl;
    Minisat::Solver solver;
    vector<Minisat::Lit> lits_row;
    vector<vector<Minisat::Lit> > lits; // matrix of literals
    // intiallization of n*k matrix of literals
    //cout<<"here"<<endl;
    //cout<<"n = "<<n<<endl;
    //cout<<"k = "<<k<<endl;
    for(int i=0;i<n;i++){
    for(int j=0; j<k;j++){
        //cout<<"i="<<i<<endl;
        //cout<<"j="<<j<<endl;
        //making one row of the matrix
        Minisat::Lit lit;
        lit = Minisat::mkLit(solver.newVar());
        lits_row.push_back(lit);
    }
    // combining rows now
    lits.push_back(lits_row);
    lits_row.clear();
    }
    //cout<<"matrix created"<<endl;

    // ADDING CLAUSES NOW

    // Adding clause 1
    Minisat::vec<Minisat::Lit> clause1,clause4;
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){

            clause1.push(lits[j][i]);
        }
        solver.addClause(clause1);
        clause1.clear();

    }
    //cout<<"clause 1 added"<<endl;
    // Adding clause 2
    
    for (int i=0;i<n;i++){
        for(int j1=0;j1<k;j1++){
                for(int j2=j1+1;j2<k;j2++){

            solver.addClause(~lits[i][j1],~lits[i][j2]);
        }
        }

    }
    //cout<<"clause 2 added"<<endl;

    // Adding clause 3
    
    for (int i=0;i<k;i++){
        for(int j1=0;j1<n;j1++){
                for(int j2=j1+1;j2<n;j2++){

            solver.addClause(~lits[j1][i],~lits[j2][i]);
        }
        }
    }

    //cout<<"clause 3 added"<<endl;

    // Adding clause 4

    for(int i=0;i<e_set.size();i++){
        for(int j=0;j<k;j++){

            clause4.push(lits[e_set[i].start][j]);
            clause4.push(lits[e_set[i].dest][j]);

        }
        solver.addClause(clause4);
        clause4.clear();
    }
   //cout<<"clause 4 added"<<endl;

   // Solving the problem
    solution = solver.solve();
    if(solution==true){
        //cout<<"solution found"<<endl;
            vertex_cover.clear();
        for(int i=0;i<n;i++){
            for(int j=0;j<k;j++){
                if (Minisat::toInt(solver.modelValue(lits[i][j])) == 0){
                vertex_cover.push_back(i);

                }
            }
        }
    break;
    }

    }
    std::sort(vertex_cover.begin(), vertex_cover.end());
    // Printing vertex cover list
    //cout<<"printing vertex cover list"<<endl;
    for (int i=0; i<vertex_cover.size();i++){
        cout<<vertex_cover[i]<<" ";
    }
    cout<<""<<endl;

}


}
}

}


