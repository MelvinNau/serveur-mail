#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <argp.h>
#include <iostream>
#include <string.h>


#include <time.h>

#include "socklib.hpp"



using namespace socklib;
using namespace std;


string port;
string serveur;



static int 
parse_opt (int key, char *arg, struct argp_state *state) 
{ 
  switch (key) 
    { 
        case 'i': 
        { 
            cout << "Initialisation du serveur"<<endl;
            serveur = arg;
            cout << " " << serveur << endl;
            break; 
        } 

        case 'p': 
        {  
            cout << "Initialisaion du port"<<endl;
            port = arg;
            cout << " " << port << endl; 
            break; 
        } 
    } 
  return 0; 
} 


int entree_donne(int s_discu) ///Parametre = socket de discussion
{
    BufferedReaderWriter readWrite(s_discu);

    string buff_in;

    buff_in = readWrite.read_line('\r');
    cout << "Client" << ": " << buff_in << "'" << endl;
    if(buff_in.substr(0,4) == "EHLO")
    {
        readWrite.write("250 \r\n");

    }else{
        readWrite.write("C PAS BON \r\n");
        return 0;
    }
    buff_in.clear();
    buff_in = readWrite.read_line();
    cout << "YA LE CLIENT QUI REDIT (JE CITE): " << buff_in << "'" << endl;

    if(buff_in.substr(0,10) == "MAIL FROM:"){


        readWrite.write("220-quelque-chose \r\n");
    }else{
        readWrite.write("C PAS BON  \r\n");
        return 0;

    }
    readWrite.close();

    return 1;
}


int main (int argc, char *argv[])
{
    struct argp_option options[] = 
    { 
        { "ip", 'i', "NUM IP", 0, "Numero de l'ip"}, 
        { "port", 'p', "NUM PORT", 0, "Numero du port" },
        { 0 } 
    }; 
    struct argp argp = { options, parse_opt, 0, 0 };
    argp_parse (&argp, argc, argv, 0, 0, 0);

    if (argc == 1){
        cout << "Attention, par defaut on se connecte sur 0.0.0.0:0"<<endl;
        cout << "Pour plus d'information --usage"<<endl;
    }

    pid_t pid = 0;
    int s_attente = CreeSocketServeur(port);

    do{
        int pipefd[2];
        pipe(pipefd);    ///RAJOUTER CAS ERREUR
        pid = fork();
        if(pid == 0){ 
            cout << "Dans le fils " << endl;

            close(pipefd[0]); ///Le fils ecrit au père;
            BufferedReaderWriter writePipe(pipefd[1]); 
            ///FAIT UN PIPE POUR INDIQUER AU PERE QUE CLIENT RECU


            int s_discu = AcceptConnexion(s_attente);
            writePipe.write("1");
            writePipe.close();


            entree_donne(s_discu);


            cout << "Fils fermé" << endl;
            exit(0);

        }else{

            cout << "Dans le pere " << endl;

            BufferedReaderWriter readPipe(pipefd[0]);
            ///FAIT UN PIPE POUR SAVOIR SI LE FILS A RECU UN CLIENT

            close(pipefd[1]);
            string pipe_in;
            pipe_in = readPipe.read_line();

            cout << endl << "Fils n° " << pid << " : " << pipe_in << endl;

        }
    }while(true);

    return 0;
}
