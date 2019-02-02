#include "NeuralNetwork.hpp"
#include "Math.hpp"

using namespace std;

void NeuralNetwork::feedForward() {
  Matrix *a;  // Matrix of neurons to the left
  Matrix *b;  // Matrix of weights to the right of layer
  Matrix *c;  // Matrix of neurons to the next layer

  for(int i = 0; i < (this->topologySize - 1); i++) {
    
    cout<<"\t\t\t\033[1;95mperforming Feed forwarding.... \033[0m\n";

    a = this->getNeuronMatrix(i);
    b = this->getWeightMatrix(i);
    c = new Matrix(
          a->getNumRows(),
          b->getNumCols(),
          false
        );

    if(i != 0) {
      a = this->getActivatedNeuronMatrix(i);
    }

    utils::Math::multiplyMatrix(a, b, c);
    for(int c_index = 0; c_index < c->getNumCols(); c_index++) {
      this->setNeuronValue(i + 1, c_index, c->getValue(0, c_index) + this->bias);
    }

    delete a;
    delete b;
    delete c;
  }
}