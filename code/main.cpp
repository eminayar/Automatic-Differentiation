#include <string>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include "graph.h"

using namespace std;


int main( int argc , char* argv[] ){

    Graph myGraph;
    myGraph.readGraph( argv[1] );
    ofstream o1(argv[3]),o2(argv[4]);
    if( myGraph.isCyclic() ){
        o1 << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        o2 << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        return 0;
    }
    o1 << setprecision(15);
    o2 << setprecision(15);
    vector <int> TO;
    myGraph.initTopologicalOrder( TO );
    ifstream nums( argv[2] );
    string s;
    getline( nums , s );
    char * cstr = new char [s.length()+1];
    std::strcpy (cstr, s.c_str());
    char * p = std::strtok (cstr," ");
    vector <string> inputs;
    while( p!=0 ){
        string s1=p;
        inputs.push_back(s1);
        p=std::strtok( NULL , " " );
    }
    o1 << myGraph.getOutputName() << endl;
    string out=myGraph.getOutputName();
    vector <string> inpts=myGraph.getInputNames();
    for( auto e:inpts ) o2 << "d" << out << "/d" <<  e << " ";
    o2 << "\n";
    while( getline( nums , s ) ){
        vector < pair < string,double > > values;
        char * cstr = new char [s.length()+1];
        std::strcpy (cstr, s.c_str());
        char * p = std::strtok (cstr," ");
        int count=0;
        while( p!=0 ){
            string s1=p;
            double val=stod(s1);
            values.push_back(pair<string,double>(inputs[count],val));
            p=std::strtok( NULL , " " );
            count++;
        }
        o1 << myGraph.forwardPass( values , TO ) << endl;
        vector <double > res=myGraph.backwardPass( TO );
        for( auto e:res ){
            o2 << e << " ";
        }
        o2 << "\n";
    }


    return 0;
}
