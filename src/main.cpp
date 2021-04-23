#include "DFolder.hpp"

int main(int argc,char *argv[]){

    cout << "Reading files..."<< endl;
    DFolder mainfolder(argv[1],argv[2]);
    mainfolder.remove_duplicate();

    return 0;
}