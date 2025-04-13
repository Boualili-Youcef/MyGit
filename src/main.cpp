#include <iostream>
#include <string>
#include "commands/init.hpp"

using namespace std;

int main(int argc, char *arg[]){

    if(argc < 2){
        cout << "Usage: MyGit <command> " << endl;
        return 1;
    }

    string cmd = arg[2];
    if(cmd == "init"){
        //TODO:  On doit initialiser un nouveau dépôt Git (Je dois chercher comment on fait ca)
        // commands::init(); un truc comme ca je pense
        return commands::init();
    }

    return 0;
}