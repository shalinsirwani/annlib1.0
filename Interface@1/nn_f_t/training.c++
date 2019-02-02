#include <iostream>
#include "NeuralNetwork.hpp"
#include <fstream>
#include <iomanip>
#include "Misc.hpp"
#include "json.hpp" 
#include <unistd.h>

#define ANNLIB_VERSION "1.0.0"

using namespace std;
using json = nlohmann::json;

void _about_me()
{
    cout<<"\n\n\n";
    system("clear");
    cout<<"\033[4;45m**********************************************************************************************\033[0m\n";
    cout<<"\n";
    cout <<"\033[1;43m|\033[0m" <<"     \033[4;41mNOTE: \033[0m"<<"                                                                                 \033[1;43m|\033[0m\n";
    cout <<"\033[1;43m|\033[0m" <<"     \033[4;41mThis project is created by Shalin Sirwani ,and represented as FINAL YEAR PROJECT.\033[0m"<< "      \033[1;43m|\033[0m\n";
    cout <<"\033[1;43m|\033[0m" <<"     \033[4;41mFor more details read MIT License. \033[0m"<<"                                                    \033[1;43m|\033[0m\n";
    cout <<"\033[1;43m|\033[0m" <<"     \033[4;41mDO NOT USE THIS PROJECT FOR COMMERCIAL PURPOSE USE WITHOUT INFORMING.\033[0m"<< "                  \033[1;43m|\033[0m\n";
    cout <<"\033[1;43m|\033[0m" <<"     \033[4;41mFor getting in touch with me :- shalinsirwani@gmail.com\033[0m"<< "                                \033[1;43m|\033[0m\n";
    cout<<"\n";
    cout <<"\033[4;45m**********************************************************************************************\033[0m\n";
    cout<<"\n";
    cout<<"\033[1;42mpress any character to continue\033[0m\n\n";
    getchar();
    system("clear");
}



int main()
{

_about_me();


    cout<<"\n\n\t\t\t\033[1;46m******  Library Version :- " << ANNLIB_VERSION << " \nYOU ARE USING Interface@1 of ANNLIB ******\033[0m\n\n\033[1;46mFor more details please refer to 'Readme.md' \n\n\n\033[0m\033[1;46mENJOY \033[0m\n";
    
    ofstream fout("error.csv");
    fstream configFile("config.json");
	getchar();
    string str((istreambuf_iterator<char>(configFile)),
                istreambuf_iterator<char>());
    cout<<"\033[1;46mjson library has performed some operations..:)\n";
    auto config = json::parse(str);

    string trainingFile      = config["trainingData"];
    string labelFile         = config["labelData"];
    string weightFile        = config["weightsFile"];
    int hiddenactivationtype = config["hiddenactivationtype"];
    int outputactivationtype = config["outputactivationtype"];
    int costfunctiontype     = config["costfunctiontype"];
    vector<int> topology     = config["topology"];
    int epoch                = config["epoch"];
    double bias              = config["bias"];
    double momentum          = config["momentum"];
    double learningRate      = config["learningRate"];
    cout<<"loaded all variables from json file\033[0m\n";
    //vector<vector<double> > trainingData =
    //utils::Misc::fetchData(trainingFile);

    NeuralNetwork* nn = new NeuralNetwork(
                                        topology , 
                                        hiddenactivationtype,
                                        outputactivationtype,
                                        costfunctiontype,
                                        bias,
                                        learningRate,
                                        momentum
                                        );

    cout<<"\033[1;43mPlease recheck the configuration you have set , which are as follows  ( Press Enter to continue with this Hyperparameters or press ctrl-c to quite or terminate !! ) :-\033[0m\n\n";


    cout<< "\033[1;91m| weightFile name        \033[0m   :- "<<weightFile<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| trainingFile name      \033[0m   :- "<<trainingFile<<"\n";
    cout<<"\n";   
    cout<< "\033[1;91m| hidden activation type \033[0m   :- "<<hiddenactivationtype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| output activation type \033[0m   :- "<<outputactivationtype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| cost function type     \033[0m   :- "<<costfunctiontype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| epoch                  \033[0m   :- "<<epoch<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| bias                   \033[0m   :- "<<bias<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| momentum               \033[0m   :- "<<momentum<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| learningRate           \033[0m   :- "<<learningRate<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| topology size          \033[0m   :- "<<topology.size()<<"\n";

    getchar();

    system("clear");


    fstream lin(labelFile);
    fstream tin(trainingFile);

    cout<<"\n\033[1;46mTill Now we have performed nlohmann processing, I mean some JSON config parameters extraction\033[0m\n";

    cout<<"\n\033[1;42mclick Enter to let me learn...\033[0m\n\n";


    getchar();

    int color = 91;

    for(int i = 0; i < epoch; i++){

    fstream lin(labelFile);
    fstream tin(trainingFile);

    double ll = double(i);

    double per = (ll+1) / epoch;

    double cal = per * 100;

    //for(unsigned int j = 0; j < trainingData.size(); j++)
    string line;
    int con = 0;
    while(getline(tin, line)) 
    {
        vector<double>  dRow;
        string          tok;
        stringstream    ss(line);
        while(getline(ss, tok, ',')) 
        {
            dRow.push_back(stof(tok));
        }
        con++;
        vector<double> input;
        vector<double> target(10 , 0);

        input = dRow;

        double label;

        lin >> label;
        /*for(int h = 0; h < 43; h++)
        {
            if((label-1) == h)
                target.push_back(1);
            else
                target.push_back(0);
        }*/
        target[label] = 1;

	cout<<"\033[1;94mepoch :- "<<epoch<<endl;

        cout<<"\033[1;95mprocessing image number :- "<<con<<endl;

        cout<<"\033[1;95msetting current Input  \033[0m\n";
 



        nn->setCurrentInput(input);
        nn->setCurrentTarget(target);

        cout<<"\033[1;96msetting up current target \033[0m\n";
    
        cout<<"\033[1;97mBoost up feedForward for current Image target \033[0m\n";
    



        nn->feedForward();
        //nn->layers[1]->matrixifyActivatedVals()->printToConsole();
  
        cout<<"\033[1;94mFetching errors \033[0m\n";



        nn->setErrors();
        //cout<<nn->error<<endl;

       cout<<"\033[1;93mReducing the errors by Backpropogation \033[0m\n";



        nn->backPropagation();
        //cout<<"data : "<<j<<endl;
        //cout<<"image "<<con<<" readed"<<endl;

	system("clear");	
		
	
    }

    lin.close();
    tin.close();


    fout<<nn->error<<endl;
    cout<<cal<<" % learned."<<endl;

    cout<<" \t\t\t\033[1;"<< color <<"m "<<cal<<" % learned.\033[0m"<<endl;
    if(color == 97)
        color = 91;
    else
        color++;

    }
    
    cout<<endl<<endl<<endl;

    cout<<"\t\t\t\033[1;95msaving weights to "<<weightFile<<" file ...\n\t\t\tplease wait\n";

    nn->saveWeights(weightFile);

    cout<<"\t\t\tsaving done\n\n\t\t\tyou may close the cmd prompt :):)\033[0m\n\n";
    
    topology.clear();
    return 0;
}
