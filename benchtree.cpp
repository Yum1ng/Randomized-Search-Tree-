#include "RST.hpp"
#include "countint.hpp"
#include <cmath>
#include <vector>
#include <set>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;



int main(int argc, char** argv) {
    cout << "# Benchmarking average number of comparisons for successful find" << endl;
    if (argc != 5){ //test if having 5 arguments
        cout << "Incorrect number of arguments. Usage:" << endl;
        cout << "benchtree [bst|rst|set] [sorted|shuffled] maxSize numRuns" <<endl;
        return 0;
    }
    if (strcmp(argv[1],"bst")!= 0 && strcmp(argv[1],"rst") != 0 &&
         strcmp(argv[1],"set") != 0){ //test validity of first argument
        cout << "Incorrect first argument. Must be either rst, bst or set" << endl;
        return 0;
    }
    //print out data structure
    if (strcmp(argv[1],"bst") == 0){
        cout << "# Data structure: bst" << endl;

    }
    else if (strcmp(argv[1],"rst") == 0){
        cout << "# Data structure: rst" << endl;
    
    }
    else if (strcmp(argv[1],"set") == 0){
        cout << "# Data structure: set" << endl;
    }

    //check validity of second argument
    if (strcmp(argv[2],"sorted") != 0 && strcmp(argv[2],"shuffled") != 0){
        cout << "Incorrect second argument. Must be either sorted or shuffled" << endl;
        return 0;
    }

    

    string structure = argv[1];
    string order = argv[2];
    int N = atoi(argv[3]); 
    int Time = atoi(argv[4]);
    
    cout << "# Data: " << argv[2] << endl;
    cout << "# N is powers of 2, minus 1, from 1 to " << argv[3] << endl;
    cout << "# Averaging over " << atoi(argv[4]) << " runs for each N" << endl;

   	double avgcomps = 0;
    double avgsquare = 0;
    double totalcomps = 0;
    double totalsquare = 0;
    double stdev = 0;
    double ctper = 0;

    // In loop N, which depends on third argument
    for(int j = 2; j <= N; j *=2 ){ 

      //set up the vector
      vector<countint> v;
      v.clear();
      for(int i = 0; i < j-1; ++i){
        v.push_back(i);
      }

      // Inner loop depends on how many time it will run
      for(int i = 0; i < Time; ++i){

        if(strcmp(argv[2],"shuffled")==0){
          random_shuffle(v.begin(), v.end());
        }

        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();

        if(strcmp(argv[1],"bst")==0){//if the structure is bst
          BST<countint> b = BST<countint>();

      	  for(vit = v.begin(); vit != ven; ++vit) {
            b.insert(*vit);
          }

          countint::clearcount();

          for(vit = v.begin(); vit != ven; ++vit) {
            b.find(*vit);
          }


        }

        else if(strcmp(argv[1],"rst")==0){//if the structure is rst
          RST<countint> r = RST<countint>();

      	  for(vit = v.begin(); vit != ven; ++vit) {
            r.insert(*vit);
          }

          countint::clearcount();

          for(vit = v.begin(); vit != ven; ++vit) {
            r.find(*vit);
          }
        }

        else if(strcmp(argv[1],"set")==0){ //if the structure is set
          set<countint> s = set<countint>();

      	  for(vit = v.begin(); vit != ven; ++vit) {
            s.insert(*vit);
          }

          countint::clearcount();

          for(vit = v.begin(); vit != ven; ++vit) {
            s.find(*vit);
          }


        }
        ctper = countint::getcount()/(double)(j-1); // Get the number of count divide by N^2 -1
        totalcomps += ctper;
        totalsquare += ctper*ctper;

      }
  	  avgcomps = totalcomps/(double)Time;
  	  avgsquare = totalsquare/(double)Time; // Calculate average square
      stdev = sqrt(abs(avgsquare - avgcomps*avgcomps)); //Calculate stdev
      cout << j-1 << "\t" << avgcomps << "\t" << stdev << endl; //Print out the value

      totalcomps = 0;
      totalsquare = 0;//set variable to 0
    }
    

    return 0;
}
