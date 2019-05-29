#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>

using namespace std;

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    // printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    // cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction( fnc );
    int inpId1 = getVariable( inp1 );
    int inpId2 = getVariable( inp2 );
    int outId = getVariable( out );
    fncs[fId]->addInput(vars[inpId1]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId1]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::readGraph(string fileName){
    ifstream read( fileName );
    string s;
    while( getline( read , s ) ){
        char * cstr = new char [s.length()+1];
        std::strcpy (cstr, s.c_str());

        // cstr now contains a c-string copy of str

        char * p = std::strtok (cstr," ");
        string s1=p;
        if( s1 == "input" ){
            p=std::strtok( NULL , " " );
            s1=p;
            int id=getVariable( s1 );
            this->inputNodes.push_back( id );
        }else if( s1 == "output" ){
            p=std::strtok( NULL , " " );
            s1=p;
            int id=getVariable( s1 );
            this->outputNode=id;
        }else{
            string out=p;
            p=std::strtok( NULL , " " );
            p=std::strtok( NULL , " " );
            vector <string> op;
            while (p!=0)
            {
                s1=p;
                op.push_back(s1);
                p = std::strtok(NULL," ");
            }
            if( op.size() == 2 )  addUnaryFunction( op[0] , op[1] , out );
            else if( op.size() == 3 ) addBinaryFunction( op[0] , op[1] , op[2] , out );
            else addUnaryFunction( "identity" , op[0] , out );
        }

        delete[] cstr;
    }
}

vector <int> arr;

void go2( Variable *p ){
    int mx=0;
    for( auto e: p->to ){
        go2( e->output );
        mx=max( mx , arr[e->output->id] );
    }
    arr[p->id]=mx+1;
}

void Graph::initTopologicalOrder( vector <int> &TO ){
    for( int i=1 ; i<=this->idCount+5 ; i++ ) arr.push_back( 0 );
    for( auto e:this->inputNodes ){
        Variable *p=vars[e];
        go2( p );
    }
    vector < pair <int,int> > srt;
    for( int i=1 ; i<=this->idCount ; i++ )
        if( type[i] == VARIABLE ){
            srt.push_back( pair <int,int>(arr[i],i) );
        }
    sort( srt.begin() , srt.end() );
    reverse( srt.begin() , srt.end() );
    for( auto e:srt ){
        Variable *p=vars[e.second];
        if( p->from == NULL ) continue;
        TO.push_back(p->from->id);
    }
    //for( int i=0 ; i<(int)vars[14]->to.size() ; i++ ){
    //    cout << vars[14]->to[i]->id << endl;
    //}
    //cout << fncs[15]->output->id << endl;
    //cout << this->inputNodes[1] << endl;

}

int giveNums=0;
typedef pair <int,int> ii;
vector <ii> ar;
vector <bool> as;
stack <int> st;
bool OK=false;

void go( Variable *p ){
    ar[p->id].first=ar[p->id].second=++giveNums;
    as[p->id]=true;
    st.push( p->id );
    int flag=true;
    for( int i=0 ; i<(int)p->to.size() ; i++ ){
        int x=p->to[i]->output->id;
        if( !ar[x].first ){
            go( p->to[i]->output );
            ar[p->id].second=min( ar[p->id].second , ar[x].second );
        }
        else if( as[x] ) ar[p->id].second=min( ar[p->id].second , ar[x].first );
    }
    if( ar[p->id].first == ar[p->id].second ){
        int x,count=0;
        do{
            count++;
            x=st.top();
            st.pop();
            as[x]=false;
        }while( x!=p->id );
        if( count > 1 ) OK=true;
    }
}

string Graph::getOutputName() {
    return name[this->outputNode];
}

vector <string> Graph::getInputNames() {
    vector <string> ret;
    for( auto e:this->inputNodes ){
        ret.push_back( name[e] );
    }
    return ret;
}

bool Graph::isCyclic(){
    for( int i=0 ; i<=this->idCount ; i++ ){
        ar.push_back( ii( 0 , 0 ) );
        as.push_back( false );
    }
    for( auto e:this->inputNodes ){
        go( vars[e] );
    }
    return OK;
}

double Graph::forwardPass( vector< pair <string , double> > inputValues , vector <int> &TO ){
    for( auto e:inputValues )   vars[id[e.first]]->value=e.second;
    for( auto e:TO ){
        fncs[e]->doForward();
        fncs[e]->output->derivative=0;
        //cout << e << ' ' << fncs[e]->output->value << endl;
    }
    return vars[this->outputNode]->value;
}

vector<double> Graph::backwardPass( vector <int> &TO ){
    for( auto e:this->inputNodes ){
        vars[e]->derivative=0;
    }
    vars[this->outputNode]->derivative=1;
    for( int i=(int)TO.size()-1 ; i>=0 ; i-- ){
        fncs[TO[i]]->doBackward();
    }
    vector <double> ret;
    for( auto e:this->inputNodes ) ret.push_back( vars[e]->derivative );
    return ret;
};

Graph::~Graph() {

}