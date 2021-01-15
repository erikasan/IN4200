#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int main(){

  string s;
  string time;
  string temperature;

  double T_min, T_max;
  int    i_min, i_max;

  double T;

  double mu         = 0,
         mu_squared = 0,
         sigma      = 0;

  vector <string> times;
  vector <double> temperatures;

  ifstream infile("temperatures.txt");

  // Fill vectors with values
  while (getline(infile, s)){
    istringstream ss(s);
    ss >> time;
    ss >> temperature;

    times.push_back(time);
    temperatures.push_back(stod(temperature));
  }

  // Find the max and min temperatures
  T_min = temperatures[0]; T_max = temperatures[0];
  for (int i = 1; i < times.size(); i++){
    if (temperatures[i] < T_min){
      T_min = temperatures[i];
      i_min = i;
    }

    if (temperatures[i] > T_max){
      T_max = temperatures[i];
      i_max = i;
    }
  }

  // Find average temperature and average squared temperature;
  for (int i = 0; i < temperatures.size(); i++){
    T = temperatures[i];
    mu += T;
    mu_squared += T*T;
  }
  mu         /= temperatures.size();
  mu_squared /= temperatures.size();

  sigma = sqrt(mu_squared - mu*mu);

  cout << "Max temperature T=" << T_max << " occured at " << times[i_max] << endl;
  cout << "Min temperature T=" << T_min << " occured at " << times[i_min] << endl;
  cout << "mu = " << mu << " sigma = " << sigma << endl;

  infile.close();

  return 0;
}
