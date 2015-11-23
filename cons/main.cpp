#include <iostream>
#include <cstring>

#include <vemc2/core/universe.h>

#include <Logging.hpp>

#define worldCount 256

using namespace std;
using namespace vemc2;
using namespace Vesper;
using namespace Vesper::LoggingTypes;
using namespace vemc2::mymath;

int main(int argc, char *argv[]){

    Logging out(Vesper::LoggingTypes::client);

    universe **allWorlds      = new universe*[worldCount];
    for (int i=0; i<worldCount; i++)
        allWorlds[i] = 0;
    string   **universe_names = new string*[256];

    string input;
    char input_buffer[256];
    char command_buffer[256], argument_buffer[256];
    string command, arguments;

    int selectedUniverse = -1;

    while (input != "quit" && input != "exit"){

        if (selectedUniverse == -1){
            out << "none" << ">";out.flush();
        }
        else{
            out << selectedUniverse << ">";out.flush();
        }

        for (int i=0; i<sizeof(input_buffer); i++){
            input_buffer[i] = '\0';
        }
        for (int i=0; i<sizeof(command_buffer); i++){
            command_buffer[i] = '\0';
        }
        input.clear();

        cin.getline(input_buffer, sizeof(input_buffer));
        input = input_buffer;

        int i=0;
        for (;i<input.size();i++){
            if (input[i] == ' ')
                break;
            command_buffer[i]=input[i];
        }
        command_buffer[i] = '\0';
        i++;

        int j=0;
        for (;i<input.size();i++,j++){
            argument_buffer[j] = input[i];
        }
        argument_buffer[j] = '\0';

        command = command_buffer;
        arguments = argument_buffer;

        //cout << "Command " << command << " Arguments " << arguments << endl;

        if (selectedUniverse < 0){
            if ( command == "create"){
                int selected = -1;
                try {
                    selected = atoi(arguments.c_str());
                }
                catch (...){
                    out << "error while parsing argument" << eom;
                }
                if (allWorlds[selected] != 0){
                    out << "Universe already exists. Try deleting it please." << eom;
                }
                else {
                    allWorlds[selected] = new universe();
                    selectedUniverse = selected;
                    out << "Switching to universe #" << selected << eom;
                }

            }
            else if (command == "select"){
                int selected = -1;
                try {
                    selected = atoi(arguments.c_str());
                }
                catch (...){
                    out << "error while parsing argument" << eom;
                }
                if (allWorlds[selected] != 0){
                    selectedUniverse = selected;
                }
                else {
                    out << "cannot select universe, try creating it with create" << eom;
                }
            }
            else if (input == "quit" || input == "exit"){

            }
            else {
                out<<"unknown command; Available: \ncreate - creates a universe\nselect - select a universe\nexit - exit the program"<<eom;
            }
        }
        else{
            if (input == "deselect"){
                selectedUniverse = -1;
            }
            else if (input == "delete"){
                delete allWorlds[selectedUniverse];
                allWorlds[selectedUniverse] = 0;
                selectedUniverse = -1;
            }
            else if (input == "quit" || input == "exit"){

            }
            else
                allWorlds[selectedUniverse]->parse(input);
        }

    }

    for (int i=0; i<worldCount; i++)
        if (allWorlds[i] != 0)
            delete allWorlds[i];

    delete[] allWorlds;

    out << "Client over and out." << eom;
    return 0;
}
