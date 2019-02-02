#include "NeuralNetwork.hpp"

void NeuralNetwork::setErrors() {
  switch(costFunctionType) {
    case(COST_MSE): this->setErrorMSE(); break;
    default: this->setErrorMSE(); break;
  }
}

void NeuralNetwork::setErrorMSE() {

  //system("clear");
    //cout<<"\t\t\t\033[1;92mSetting Up errors for Optimum result .... \033[0m\n";

  int outputLayerIndex            = this->layers.size() - 1;
  vector<Neuron *> outputNeurons  = this->layers.at(outputLayerIndex)->getNeurons();

  this->error = 0.00;

  for(int i = 0; i < target.size(); i++) {
    double t  = target.at(i);
    double y  = outputNeurons.at(i)->getActivatedVal();

    errors.at(i)        = 0.5 * pow(abs((t - y)), 2);

    derivedErrors.at(i) = (y - t);

    this->error += errors.at(i);
  }
}