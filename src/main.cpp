#include "DFolder.hpp"

int main(int argc,char *argv[]){

    DFolder mainfolder(argv[1],argv[2]);
    mainfolder.remove_duplicate();

    return 0;
}