#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <ostream>

static std::string generate(long gen, long range, char c) {
    std::string r;
    std::ifstream urandom("/dev/urandom");
    if (!urandom)
        return NULL;
    std::string genS = std::to_string(gen);
    std::ofstream out("result_gen" + genS + ".txt" );
    
    bool have_print = false;
    unsigned int num = 0;
    int old_pr = 0;
    long stack_max = 10000;

    for (long i = 0; i < gen; ++i)
    {
        long pr = (i * 100) / gen;
        if ((old_pr + 2) == pr) {
            have_print = false;
        }
        if ((pr % 2) == 0 && !have_print) {
            std::cout << "\r" << "Generating... " << pr << "%";
            std::cout.flush();
            have_print = true;
            old_pr = pr;
        }
        if (!urandom.read(reinterpret_cast<char *>(&num), sizeof(num)))
            return NULL;
        long res = static_cast<long>(num % static_cast<unsigned long>(range));
        r += std::to_string(res);
        if (i < gen - 1)
            r += ", ";
        if (c == '1' && i == stack_max) {
            out << r;
            stack_max += 10000;
            r = "";
        }
    }
    out << r;
    out.close();
    std::cout << "\r" << "Generating... " << 100 << "%" << std::endl;
    return r;
}

int main(int ac, char **av) {
    if (ac < 4) {
        std::cout << "Usage: ./name [many num] [range max] [in file or not 1/0]";
        return 1;
    }
    std::string r;
    if (av[3][0] == '1')
        generate(atol(av[1]), atol(av[2]), av[3][0]);
    else 
        r = generate(atol(av[1]), atol(av[2]), av[3][0]);
        std::cout << r << std::endl;
    return 0;
}