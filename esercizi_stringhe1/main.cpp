#include <iostream>

int main() {
    srand(time(NULL));
    std::string s;
    int n;
    int scelta;
    std::cin>>n;
    for (int i = 0; i < n; ++i) {
        scelta=rand()%3+1;
        switch (scelta) {
            case 1:
            s += rand()%'z'+'a';
            break;
            case 2:
                s += rand()%'Z'+'A';
                break;
            case 3:
                s += rand()%'9'+'1';
                break;
        }
    }
    std::cout<<s;
    return 0;
}
