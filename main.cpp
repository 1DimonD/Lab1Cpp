#include <iostream>
#include <cmath>

double epsilon = 1e-3;
void inputEpsilon() {
    epsilon = 1e-3;
    std::cout << "Change epsilon(current is 1e-3)?" << std::endl;
    std::cout << "Y - to change, N - to resume." << std::endl;
    char input;
    std::cin >> input;
    switch(input) {
        case 'Y':
            std::cout << "Enter epsilon in format (1e-4 or 0.0001): ";
            std::cin >> epsilon;
            break;
        case 'N':
            break;
        default:
            std::cout << "Smth went wrong" << std::endl;
            exit(0);
    }
}

void log(const int& i, const double& x, const double& res) {
    std::cout << "Step: " << i << "\n"
              << "Approximation: " << x << "\n"
              << "Value: " << res << "\n"
              << "***************\n";
}

class Task {
public:
    virtual void start() = 0;
};

class Relax : public Task {
public:

    void start() override {
        double q = (double)21/43, z0 = 0.5;
        double x0 = 0, x = 1;
        int max_iter = 1 + floor(log10(z0/epsilon)/log10(1/q));
        std::cout << "Expected iterations: " << max_iter << std::endl;

        for(int i = 0; i < max_iter && fabs(x-x0) >= epsilon; i++) {
            log(i, x, f(x));
            x0 = x;
            x = phi(x0);
        }

    }

private:
    double f(const double& x) {
        return x*x*x + 3*x*x - x - 1;
    }

    double phi(const double& x) {
        return x - (double)8/43*f(x);
    }
};

class Newton : public Task {
public:
    void start() override {
        double q = 0.6, z0 = 0.5;
        double x0 = 0, x = 2;
        int max_iter = 1 + log(log10(z0/epsilon)/log10(1/q) + 1)/log(2);
        std::cout << "Expected iterations: " << max_iter << std::endl;

        for(int i = 0; i < max_iter && fabs(x-x0) >= epsilon; i++) {
            log(i, x, f(x));
            x0 = x;
            x = x0 - f(x0)/ f_der(x0);
        }
    }

private:
    double f(const double& x) {
        return x*x*x+x*x-4*x-3;
    }

    double f_der(const double& x) {
        return 3*x*x+2*x-4;
    }
};

class SIter : public Task {
public:
    void start() override {
        double q = 0.708, dif_b_a = 1;
        double x0 = 0, x = -1;
        int max_iter = 1 + floor(log10(dif_b_a/epsilon*(1-q))/log10(1/q));
        std::cout << "Expected iterations: " << max_iter << std::endl;

        for(int i = 0; i < max_iter && fabs(x-x0) >= epsilon; i++) {
            log(i, x, f(x));
            x0 = x;
            x = phi(x0);
        }
    }
private:
    double f(const double& x) {
        return x*x*x-4*x*x-4*x+13;
    }

    double phi(const double& x) {
        return x - (double)1/24*f(x);
    }
};

int main() {

    while(true) {
        inputEpsilon();
        std::cout << "What method do you want to show?\n"
                  << "1 - relaxation\n"
                  << "2 - Newton\n"
                  << "3 - simple iteration\n"
                  << "any other key - quit\n";
        char input;
        std::cin >> input;
        Task* t;
        switch(input) {
            case '1':
                t = new Relax();
                break;
            case '2':
                t = new Newton();
                break;
            case '3':
                t = new SIter();
                break;
            default:
                std::cout << "End of the program" << std::endl;
                return 0;
        }
        t->start();
    }

    return 0;
}
