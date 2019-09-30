#include <iostream>
#include <fstream>

#include <cstdlib>

#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;
std::string RemoveChars(const std::string& source, const std::string& chars); 
void extractIntegerWords(string str, vector<char> &vect); 
string space2underscore(string text);
void print (vector<int> &vect); 
int rgen (int con,int q);
void cordgen (int line_seg, int street_no, vector<vector<int> >&mat);
bool get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y);

string Vinput();

vector<char> V;


int n=5;
int l=5;
int c=15;
int s=10;

int main(int argc, char** argv)

{
   //string a;
   

 	
 	//a=Vinput();

 //	if(a.length()==0){break;}

vector<string> inputs;
for(int i=0; i<argc ; i++){
//cout<<"arg v[]=="<<argv[i]<<endl;
inputs.push_back(argv[i]);
}
for(int i=0;i<inputs.size();i++){
if(inputs[i]=="-s"){
s = atoi(inputs[i+1].c_str());
}
if(inputs[i]=="-n"){
n = atoi(inputs[i+1].c_str());
}
if(inputs[i]=="-l"){
l = atoi(inputs[i+1].c_str());
}
if(inputs[i]=="-c"){
c = atoi(inputs[i+1].c_str());
}

}


	while (true){
	 
	 
	 
	 
    
    
 	
   //print(V);
 //  s=V[0];
  // n=V[1];
  // l=V[2];
   
   
   

unsigned int s0= rgen(s,2);
//unsigned int n0= rgen(n,1);
unsigned int l0= rgen(l,5);
//unsigned int c0=rgen(c,1);
//urandom.close();
    
vector<vector<int> > mat(s0);   
  // cout<<s0<<" "<<n0<<" "<<l0<<" "<<c0<<endl;
   
   for (int i=0; i < (s0); i++ ){
   
   unsigned int n0= rgen(n,1);
   cordgen(n0,i,mat);
  
}



  //   cout<<s<<endl; 
  //   cout<<n<<endl; 
    // cout<<l<<endl; 
    
     
    int icheck;
	int counter=0;
    do{
	icheck=0;
	counter++;
	if (counter==25){std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts\n";
    exit(0);
		
	}
    bool inter;
    for (int ii = 0; ii < s0; ii++){
	
    for (int b=2; b<mat[ii].size();b=b+2){
	
    for (int cc=2+b; cc<mat[ii].size();cc=cc+2){
	
    	inter=get_line_intersection(mat[ii][b-2],mat[ii][b-1],mat[ii][b],mat[ii][b+1],mat[ii][cc-2],mat[ii][cc-1],mat[ii][cc],mat[ii][cc+1]);
    	
    	if (inter==true){
    		icheck=1;
    		int counteer=0;
    		do{counteer++;
    			if (counteer==50){std::cerr << "Error: failed to generate valid input for 50 simultaneouss attempts\n";
                exit(0);
		
                  	}
    		mat[ii][cc-2]=rgen(c,1);
			mat[ii][cc-1]=rgen(c,1);
			mat[ii][cc]=rgen(c,1);
			mat[ii][cc+1]=rgen(c,1);
			
			inter=get_line_intersection(mat[ii][b-2],mat[ii][b-1],mat[ii][b],mat[ii][b+1],mat[ii][cc-2],mat[ii][cc-1],mat[ii][cc],mat[ii][cc+1]);

			}while (inter==true);
		}
		}}}
	}while(icheck==1);
     
     
     for (int i = 0; i < s0; i++) { 
     cout<<"a"<<" "<<"\""<<i<<"\""<<" ";
       for (int j = 0; j < mat[i].size(); j=j+2) {
	   
            cout <<"("<<mat[i][j]<<","<<mat[i][j+1]<<")"; 
            }
        	cout<<endl;
         
   }
   cout<<"g"<<endl;
   for (int i=0; i < (s0); i++ ){
   
   	cout<<"r"<<" "<<"\""<<i<<"\""<<endl;
  
}
   

   V.clear();
   usleep(l0*1000000);	
 	
 }
	
	
}

string Vinput()

{
	string resultV;
    getline (cin, resultV); 
    if(resultV.length()==0){exit(0);}
 	string resultv=RemoveChars(resultV, "-");
 	resultv=space2underscore(resultv);
 	extractIntegerWords(resultv, V);
 	
	 
	return resultV;	
	
}


std::string RemoveChars(const std::string& source, const std::string& chars) {
   std::string result="";
   for (unsigned int i=0; i<source.length(); i++) {
      bool foundany=false;
      for (unsigned int j=0; j<chars.length() && !foundany; j++) {
         foundany=(source[i]==chars[j]);
      }
      if (!foundany) {
         result+=source[i];
      }
   }
   return result;
}

  
void extractIntegerWords(string str, vector<char> &vect) 
{ 
    stringstream ss;     
  
    /* Storing the whole string into string stream */
    ss << str; 
  
    /* Running loop till the end of the stream */
    string temp, temp1; 
    int found; 
    int i=0;
    while (!ss.eof()) { 
  
        /* extracting word by word from stream */
        ss >> temp; 
        ss >> temp1;
//         cout<<temp<<endl;
//         cout<<temp1<<endl;
         
        
  
        /* Checking the given word is integer or not */
            if (stringstream(temp1) >> found && temp=="s") 
            {s=found;
			}
            
            
            if (stringstream(temp1) >> found && temp=="c") {
			
			c=found;}
			
			if (stringstream(temp1) >> found && temp=="n") 
            {
			 n=found;
			 
			 }
            
			if (stringstream(temp1) >> found && temp=="l")
			{
			 
			l=found;
			
			}
			
			
            
			
			
			
  
        /* To save from space at the end of string */
      //  temp = " "; 
    } 
} 
  
  string space2underscore(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] == ',')
            text[i] = ' ';
    }
    return text;
}

void print (vector<char> &vect)
{ 
  for (int i=0; i<vect.size(); i++) 
       {cout << vect[i] << " "; 
	   }
	   cout<<endl;
}

int rgen (int con,int q){
	
	std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }
   
   
    unsigned int s00 = 42;
    urandom.read((char*)&s00, sizeof(int));
    int a=0;
    while( (s00%(con+1)) > con || (s00%(con+1)) < q ){
	a++;
    urandom.read((char*)&s00, sizeof(int));
    if (a==25)
    {std::cerr << "Error: failed to generate valid input for 25 simultaneous attempts\n";
    exit(0);
	}
}
    
    s00=s00%(con+1);// number of streets
    
   // std::cout << "s: " << s00<< " ";
    urandom.close();
    return s00;
    
}



void cordgen (int line_seg, int street_no, vector<vector<int> >&mat)
{
	vector<int> xy(line_seg+1+line_seg+1);
    //vector<int> y(line_seg+1);
	mat[street_no]=vector<int>(line_seg+1+line_seg+1);
	for (int i=0; i < (line_seg+1+line_seg); i=i+2 )
        {
		
		xy[i]=rgen(c,1);;
	    xy[i+1]=rgen(c,1);
	    mat[street_no][i]=xy[i];
	    mat[street_no][i+1]=xy[i+1];
	    
		
	}
	

	

	

//	cout<<"a"<<"\""<<street_no<<"\"";
//	cout<<"{";
//	for (int v=0; v < (line_seg+1+line_seg); v=v+2 ){
//		
//		cout<<"("<<xy[v]<<","<<xy[v+1]<<")";
//		if (v!=line_seg+line_seg)
//		cout<<",";
//		
//	}
//	cout<<"}";
//	cout<<endl;

	
	
	
}

bool get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y)
{
    float s02_x, s02_y, s10_x, s10_y, s32_x, s32_y, s_numer, t_numer, denom, t;
    s10_x = p1_x - p0_x;
    s10_y = p1_y - p0_y;
    s02_x = p0_x - p2_x;
    s02_y = p0_y - p2_y;
     s32_x = p3_x - p2_x;
     s32_y = p3_y - p2_y;
    
    
    denom = s10_x * s32_y - s32_x * s10_y;
    bool denomPositive = denom > 0;
    s_numer = s10_x * s02_y - s10_y * s02_x;
   
    t_numer = s32_x * s02_y - s32_y * s02_x;
    
   
    
    if (denom==0)
    {
	 //cout<<"denom: "<<denom<<endl;
       return true;}
 
    
    
    else if ((s_numer <0)  == denomPositive){
	
	    //cout<<"s_numer: "<<s_numer<<endl;
        return false; // No collision
		}
 
    
   
    
    else if ((t_numer < 0 )== denomPositive)
    {
	    //cout<<"t_numer: "<<t_numer<<endl;
        return false; // No collision
        
    }
 
    
    
    else if (((s_numer > denom)==denomPositive) ||( (t_numer > denom)== denomPositive))
        return false; // No collision
        
    
 
    else
	{// Collision detected
    t = t_numer / denom;
    float tt,ttt;
    tt=(p0_x + (t * s10_x));
        //cout<<tt<<" ";
    ttt=(p0_y + (t * s10_y));
        //cout<<ttt<<endl;
 
    return true;
}
}



