#include "NeuralNetwork.hpp"
#include "json.hpp"

using json = nlohmann::json;

void NeuralNetwork::loadWeights(string filename) {

  std::ifstream i(filename);
  json jWeights;
  i >> jWeights;

  vector< vector< vector<double> > > temp = jWeights["weightsFile"];

  for(int i = 0; i < this->weightMatrices.size(); i++) {
    for(int r = 0; r < this->weightMatrices.at(i)->getNumRows(); r++) {
      for(int c = 0; c < this->weightMatrices.at(i)->getNumCols(); c++) {
        this->weightMatrices.at(i)->setValue(r, c, temp.at(i).at(r).at(c));
        cout<<i<<" "<<r<<" "<<c<<endl;
      }
    }
  }
  cout<<"\nWEIGHTS LOADED\n";
}