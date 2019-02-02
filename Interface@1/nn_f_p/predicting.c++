#include <iostream>
#include "NeuralNetwork.hpp"
#include <fstream>
#include <iomanip>
#include "Misc.hpp"
#include "json.hpp" 
#include <unistd.h>

using namespace std;
using json = nlohmann::json;

#define ANNLIB_VERSION "1.0.0"

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
    ofstream fout("Result.csv");

	_about_me();


    cout<<"\n\n\t\t\t\033[1;46m******  Library Version :- " << ANNLIB_VERSION << " \nYOU ARE USING Interface@1 of ANNLIB ******\033[0m\n\n\033[1;46mFor more details please refer to 'Readme.md' \n\n\n\033[0m\033[1;46mENJOY \033[0m\n";

getchar();
	system("clear");

	fstream configFile("pconfig.json");

	string str((istreambuf_iterator<char>(configFile)),
                istreambuf_iterator<char>());
		
	cout<<"\033[1;46mjson library has performed some operations..:)\n";

	auto config = json::parse(str);

    string predectionFile  = config["predectionData"];
    string weightFile    = config["weightsFile"];
    string labelFile     = config["labelFile"];
    vector<int> topology = config["topology"];
    int hiddenactivationtype = config["hiddenactivationtype"];
    int outputactivationtype = config["outputactivationtype"];
    int costfunctiontype     = config["costfunctiontype"];
    
    //vector<vector<double> > predectionData =
    //utils::Misc::fetchData(predectionFile);


	cout<<"\033[1;43mPlease recheck the configuration you have set , which are as follows  ( Press Enter to continue with this Hyperparameters or press ctrl-c to quite or terminate !! ) :-\033[0m\n\n";


cout<< "\033[1;91m| weightFile name        \033[0m   :- "<<weightFile<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| predictionFile name      \033[0m   :- "<<predectionFile<<"\n";
    cout<<"\n";   
    cout<< "\033[1;91m| hidden activation type \033[0m   :- "<<hiddenactivationtype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| output activation type \033[0m   :- "<<outputactivationtype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| cost function type     \033[0m   :- "<<costfunctiontype<<"\n";
    cout<<"\n";
    cout<< "\033[1;91m| topology size          \033[0m   :- "<<topology.size()<<"\n";
	getchar();
	system("clear");
	

	NeuralNetwork* nn = new NeuralNetwork(
										topology,
										hiddenactivationtype,
										outputactivationtype,
										costfunctiontype
										);

	fstream lin(labelFile);
        fstream tin(predectionFile);	

	nn->loadWeights(weightFile);

	int right_prediction = 0 , con = 0;

	string line;

    fout<<"Predicted Output\t\t\tReal Output"<<endl;
	//cout<<predectionData.size();

	//for(int k = 0; k < predectionData.size(); k++){

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
        
        input = dRow;

        int label;

        lin >> label;
	
	//input.erase(input.begin() + 0);

	nn->setCurrentInput(input);

	nn->feedForward();

	int result = nn->layers[nn->layers.size()-1]->matrixifyActivatedVals()->getmax();


	nn->layers[nn->layers.size()-1]->matrixifyActivatedVals()->printToConsole();

	cout<< "\n\n\n\t\t\t\033[1;43mPredicted result of image : \033[0m" <<con<<endl;

	system("clear");

	//cout<<"\n"<<predectionData[k][0]<<" : "<<result<<endl;
	if(result == label)
		right_prediction++;
        fout<<result<<"\t\t\t"<<label<<endl;
	
	}
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\033[4;95mPrediction Ratio ";
	cout<<"\t\t\t"<<right_prediction<<" / "<<con<<"\033[0m\n\n";
	topology.clear();
	getchar();
	system("clear");


	return 0;
}
