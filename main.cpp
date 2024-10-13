#include "solitaire.h"


int main() {
    std::vector<std::string> piles {
        "9, 8, 7, 6, 5, 4, 3, 1, 2",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 4, 3, 2, 1",
        "9, 8, 7, 6, 5, 1, 2, 3, 4"
    };
  
    Solitaire solitaire(piles);
    int result = solitaire.accurateSolution();
    
    std::cout << result;
}