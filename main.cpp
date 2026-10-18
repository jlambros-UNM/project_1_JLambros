#include <iostream>

//Constants used for calculating the voltage and current.
const double deltaT = 1e-10;
const double finalTime =  5e-6;
const int timesteps = 50000; //finalTime divided by deltaT. For more general code, I would just put that, but for this assignment I will use 50000.
const double resistance =  1000; //1k ohm
const double capacitance = 100e-12; //100 nF
const double current = 1e-2; //Current from the constant current source, in A
const double voltage = 10; //Voltage from the constant voltage supply, in V

struct _capacitor
{
    double *time;       // time array
    double *voltage;    // voltage array
    double *current;    // current array
    double C;           // capacitance value
};
typedef struct _capacitor Capacitor;

int main(){
    //I need loops to calculate the voltage and current? I will go from 1 to 50000, using 0 as the inital conditions. So for the voltage case, the initial voltage is 0, and thus the initial condition is just V = 0. For the current case, I(t = 0) is Vo/R, which is 10/1000.
    //A note on the variables. On second look, I probably could have just used 1 struct variable to hold all the data, putting the first circuit in var.voltage and second circuit in var.current. I chose to split the circuits for my sake, but I could have shortened the code by combining the variables and just using 1 loop to calculate everything.
    //Setting up the first circuit variables
    Capacitor currentCircuit;
    currentCircuit.time = new double[timesteps];
    currentCircuit.voltage = new double[timesteps];
    currentCircuit.current = new double[timesteps];
    currentCircuit.C = capacitance;
    //Setting up the second circuit variables
    Capacitor voltageCircuit;
    voltageCircuit.time = new double[timesteps];
    voltageCircuit.voltage = new double[timesteps];
    voltageCircuit.current = new double[timesteps]; //Not sure if needed
    voltageCircuit.C = capacitance;
    //First loop needed. This loop is calculating the VOLTAGE in the constant current case. Current is constant so no need to calculate that. I also initialize t = 0 values.
    currentCircuit.voltage[0] = 0;
    currentCircuit.current[0] = current;
    currentCircuit.time[0] = 0;
    std::cout << "===CURRENT LOOP CIRCUIT===" << std::endl;
    for(int i = 1; i < timesteps; i++){
        currentCircuit.voltage[i] = currentCircuit.voltage[i-1] + current * deltaT/capacitance; //calculate voltage using the equation given
        currentCircuit.current[i] = current;
        currentCircuit.time[i] = i * deltaT;
        if(i % 200 == 0){ //Every 200 timesteps, output the current
            std::cout << "Time: " << currentCircuit.time[i] << " s, Voltage: " << currentCircuit.voltage[i] << " V | " << "Current: " << currentCircuit.current[i] << " A" <<std::endl; //I miss printf
        }
    }
    std::cout << "The first circuit has finished calculating" << std::endl;
    //Second loop needed. This loop is calculating the CURRENT in the constant voltage case.
    voltageCircuit.current[0] = voltage/resistance;
    voltageCircuit.time[0] = 0;
    voltageCircuit.voltage[0] = voltage;
    std::cout << "---VOLTAGE LOOP CIRCUIT---" << std::endl;
    for(int i = 1; i < timesteps; i++){
        voltageCircuit.current[i] = voltageCircuit.current[i-1] - voltageCircuit.current[i-1]/(resistance*capacitance) * deltaT; //calculate current using the equation given
        voltageCircuit.voltage[i] = voltage;
        voltageCircuit.time[i] = i * deltaT;
        if(i % 200 == 0){ //Every 200 timesteps, output the voltage
            std::cout << "Time: " << voltageCircuit.time[i] << " s, Current: " << voltageCircuit.current[i] << " A | " << "Voltage: " << voltageCircuit.voltage[i] << " V" <<std::endl;
        }
    }
    std::cout << "The second circuit has finished calculating" << std::endl;
    //Free memory
    delete[] currentCircuit.time;
    delete[] currentCircuit.voltage;
    delete[] currentCircuit.current;
    //
    delete[] voltageCircuit.time;
    delete[] voltageCircuit.voltage;
    delete[] voltageCircuit.current;
}
//Sources
//https://www.geeksforgeeks.org/cpp/structures-in-cpp/
//https://www.geeksforgeeks.org/cpp/new-and-delete-operators-in-cpp-for-dynamic-memory/
//https://www.geeksforgeeks.org/cpp/output-in-cpp/
