#include <iostream>
#include <fstream>

using namespace std;


const double ITER_N = 1000000;
const double TIMESTEP = 0.01;

const char* PARAMS_FILE = "Parameters.txt";
const char* X_FILE_EULER = "Euler.txt";
const char* X_FILE_HEUN = "Heun.txt";


struct Oscillator {
    double xCurr, xNext;        
    double vCurr, vNext;
    double aCurr, aNext;
    double w;

    Oscillator(double x0, double w) : xCurr(x0), xNext(0), vCurr(0), vNext(0), aCurr(0), aNext(0), w(w) {}

    void updEuler(double dt=TIMESTEP) {
        aCurr = -w * w * xCurr;
        vNext = vCurr + aCurr * dt;
        xNext = xCurr + vCurr * dt;
        
        vCurr = vNext;
        xCurr = xNext;
    }

    void updHeun(double dt=TIMESTEP) {
        double xTmp, vTmp;

        aCurr = -w * w * xCurr;
        vTmp = vCurr + aCurr * dt;
        xTmp = xCurr + vCurr * dt;

        aNext = -w * w * xTmp;
        vNext = vCurr + (aCurr + aNext) * dt / 2;
        xNext = xCurr + (vCurr + vTmp) * dt / 2;

        vCurr = vNext;
        xCurr = xNext;
    }
};

int main() {
    double w = 1;

    Oscillator osc1(1, w), osc2(1, w);

    ofstream params(PARAMS_FILE);
    params << ITER_N << "\n";
    params << TIMESTEP << "\n";
    params << w << "\n";
    params.close();


    ofstream xEuler(X_FILE_EULER);
    ofstream xHeun(X_FILE_HEUN);

    for (int iter = 0; iter != ITER_N; iter++) {
        xEuler << osc1.xCurr << "\n";
        xHeun << osc2.xCurr << "\n";

        osc1.updEuler();
        osc2.updHeun();
    }

    xEuler.close();
    xHeun.close();

    cout << "Finished saving" << "\n";
}
