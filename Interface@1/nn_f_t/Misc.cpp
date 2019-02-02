#include "Misc.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <assert.h>

using namespace std;

vector< vector<double> > utils::Misc::fetchData(string path , string labelfile , vector<int> &labeldata) {
  vector< vector<double> > data;

  ifstream infile(path);
  ifstream lab(labelfile);
  ifstream file(path);

  if(!file.is_open())
  {
    getchar();
    assert("file can't be open");
  }

  file.seekg( 0 , ios::end );

  int filesize = file.tellg();

  file.close();

  string line;
  system("clear");
  cout << "\t\033[1;93mNow I am fetching supervised data of about "  << filesize/1024 <<" KB from path : "<<path<<" (Please be patience) \n ";
  cout<<"\n\t\tMay I continue  'press Enter in order to continue.. or press ctrl-c to quite..' \033[0m\n";
  getchar(); 
  

  int labl;
  while(lab >> labl )
  {
    labeldata.push_back(labl);
  }

  int tot = labeldata.size();
  int upto = 1;
  
  while(getline(infile, line)) {

    vector<double>  dRow;
    string          tok;
    stringstream    ss(line);

    while(getline(ss, tok, ',')) {
      dRow.push_back(stof(tok));

    }
        double x = ((double)upto / tot) * 100;
        cout<<"\n\t\t\t\033[1;95mLOADING .. "<< x <<" % \033[0m";
        system("clear");

        upto++;

    data.push_back(dRow);
  }

  cout<<"\t\033[1;93mData fetched up : :) :) \033[0m\n"<<endl;

  infile.close();

  return data;
}