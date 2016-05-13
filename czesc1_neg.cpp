#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char ** argv) {
    if(argc<7){
        cout << "Podałeś za mało argumentów!!\n";
    }
    else{
        int t[6];
        for(int i=0;i<6;i++){
            t[i]=atoi(argv[i+1]);
        }

        if((t[0]>=t[1]||t[0]%t[1]!=t[0])||(t[1]>=t[2]||t[1]%t[2]!=t[1])||(t[2]>=t[3]||t[2]%t[3]!=t[2])||(t[3]>=t[4]||t[3]%t[4]!=t[3])||(t[4]>=t[5]||t[4]%t[5]!=t[4]))
            cout << "1" << endl;
        else
            cout << "0" << endl;

    }
    return 0;
}
