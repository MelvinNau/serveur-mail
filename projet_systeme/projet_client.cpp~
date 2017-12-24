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
#include <fstream>
#include <gtk/gtk.h>

#include <time.h>

#include "socklib.hpp"
#include "readerwriter.hpp"



using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

using namespace socklib;
using namespace std;

string port;
string serveur;
string mailDest;
string mailExpe;
string titre;
string texte;

const int buff = 256;
char DATA[buff];



//Pour avoir un affichage, permettant le debug
bool verbose = true;


//Permet de gerer les options sous forme de '-' ou de '--' apres l'executable
//./projet.exe --usage
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

        case 'f': 
        {  
        	cout << "Initialisaion du mail expediteur"<<endl;
	        mailExpe = arg;
	        cout << " " << mailExpe << endl; 
			break; 
        }

        case 't': 
        {  
        	cout << "Initialisaion du mail destinataire"<<endl;
	        mailDest = arg;
	        cout << " " << mailDest << endl; 
			break; 
        }

        case 'b': 
        {  
        	cout << "Initialisaion du titre du mail"<<endl;
	        titre = arg;
	        cout << " " << titre << endl; 
			break; 
        }

        case 'v': 
        {  
        	cout << "Initialisaion du contenu du mail"<<endl;
	        texte = arg;
	        cout << " " << texte << endl; 
			break; 
        }
    } 
  return 0; 
} 

//Permet la lecture du fichier qui est generé par lexecutable dans log
void lecture()
{
  // on ouvre en lecture
  ifstream fichier("log/message.txt", ios::in);
  string chaine1, chaine2, chaine3, chaine4;
  fichier >> chaine1 >> chaine2 >> chaine3 >> chaine4;
  mailExpe = chaine1;
  mailDest = chaine2;
  titre = chaine3;
  texte = chaine4;
}

//Permet de generer une date compréhensible par le serveur
string generer_date_mail()
{
    time_t maintenant = time(NULL);
    struct tm date_courante = *localtime(&maintenant);
    string nom_jour = "";
    char date[4096];
    char mois[4];
    // --- Conversion du numéro du jour en string
    switch (date_courante.tm_wday)
    {
       case 0:
           nom_jour = "Sun";
           break;
            
       case 1:
           nom_jour = "Mon";
           break;
            
       case 2:
           nom_jour = "Tue";
           break;
            
       case 3:
           nom_jour = "Wed";
           break;
        
       case 4:
           nom_jour = "Thu";
           break;
            
       case 5:
           nom_jour = "Fri";
           break;
            
       case 6:
           nom_jour = "Sat";
           break;
            
       default:
           break;
    }

// --- identification mois numéro puis copie dans le tableau
    switch (date_courante.tm_mon)
    {
        case 0:
           strcpy(mois, "Jan");
           break;
        case 1:
           strcpy(mois, "Feb");
           break;
            
        case 2:
           strcpy(mois, "Mar");
           break;
            
        case 3:
           strcpy(mois, "Apr");
           break;
            
        case 4:
           strcpy(mois, "May");
           break;
            
        case 5:
           strcpy(mois, "Jun");
           break;
            
        case 6:
           strcpy(mois, "Jul");
           break;
            
        case 7:
           strcpy(mois, "Aug");
           break;
            
        case 8:
           strcpy(mois, "Sep");
           break;
            
        case 9:
           strcpy(mois, "Oct");
           break;
            
        case 10:
           strcpy(mois, "Nov");
           break;
            
        case 11:
           strcpy(mois, "Dec");
           break;
            
        default:
           break;
    }
    sprintf(date, "Date: %3s, %d %3s %d %d:%d:%d +0000\r\n", nom_jour.c_str(), date_courante.tm_mday, mois, 1900 + date_courante.tm_year, date_courante.tm_hour, date_courante.tm_min, date_courante.tm_sec);
    string str_date(date);
    return str_date;
}





int main (int argc, char **argv) 
{ 
    string input_cli;
    string output;
    string tampon;
    string buff;
    string date = generer_date_mail(); //On genere la date dès le debut

    struct argp_option options[] = 
    { 
        { "ip", 'i', "NUM IP", 0, "Numero de l'ip"}, 
        { "port", 'p', "NUM PORT", 0, "Numero du port" },
        { "from", 'f', "MAIL EXPE", 0, "Mail de l'expediteur"}, 
        { "to", 't', "MAIL DEST", 0, "Mail du destinataire" },
        { "titre", 'b', "TITRE", 0, "Titre"},
        { "texte", 'v', "TEXTE", 0, "Texte"},
        { 0 } 
    }; 
  	struct argp argp = { options, parse_opt, 0, 0 };
  	argp_parse (&argp, argc, argv, 0, 0, 0);


  	if (argc == 1 || (argc > 3 && serveur.empty() && port.empty())) {

		cerr << argv[0] << " <serveur> <port>. Voir --usage" << endl;
		exit(1);
	}else{
		if (argc == 3){
			serveur = argv[1]; 
			port = argv[2];
      	system("log/gtk.exe");
			//Ici on lance l'interface graphique, qui crée un fichier de log

			//On lit le fichier de log
			lecture();
      

      	//On continue (si il n'a pas tout rempli, il devra remplir dans la commande)
		}
		//Proposition pour remplir ce qu'il manque
	  	if (serveur.empty()){
	  		cout << "Veuillez me donner le nom du serveur"<<endl;
	  		cin >> serveur;
	  	}
	  	if (port.empty()){
	  		cout << "Veuillez me donner le port du serveur"<<endl;
	  		cin >> port;
	  	}
	  	if (mailExpe.empty()){
	  		cout << "Veuillez me donner le mail de l'expediteur"<<endl;
	  		cin >> mailExpe;
	  	}
	  	if (mailDest.empty()){
	  		cout << "Veuillez me donner le mail du destinataire"<<endl;
	  		cin >> mailDest;
	  	}   
	  	if(titre.empty()){
	  		cout << "Veuillez me donner le titre du mail"<<endl;
			cin >> titre;
	  	}
	  	if(texte.empty()){
	  		cout << "Veuillez me donner le contenu du mail"<<endl;
			cin >> texte;
	  	}
	  }
    
   
    //Une fois toutes les informations en notre possesion, on peut créer le socket.
	int socket_cli = CreeSocketClient(serveur,port);

    //On crée un reader
    BufferedReaderWriter reader(socket_cli);
    
    if (verbose){
        cout << "socket créé, num socket :" << socket_cli << endl;
        cout << "serveur contacté " << endl;
    }
    

    
    input_cli += "EHLO " + mailDest + "\r\n";
    tampon += input_cli;
    reader.write(input_cli);
    
    string finir;
    //Tant qu'on ne recoit pas "250", on continue. Puisque ces precedentes lignes n'interessent pas  
    do
    {
        buff= reader.read_line();
        cout << "recu: " << buff << endl;
        finir = buff.substr(0, 4);
    }while(finir != "250-");
    
    input_cli.clear();

    //Ici on gere le FROM
    output += "MAIL FROM: ";
    cout << "MAIL FROM:" << endl;
    input_cli = mailExpe;
    output += input_cli + "\r\n";
    if (verbose) {cout << "Commande envoyée: " << output << endl;}
    reader.write(output);
    tampon += output;
    
    string rep = reader.read_line();
    if (verbose) {cout <<"Serveur envoie: "<< rep << endl;}
    if(rep[0] != '2') {
        cerr << "Refusé" << endl;
        exit(1);
    }

    //supprimer ce qu'il y a dans le string pour l'utiliser plus tard
    input_cli.clear();
    output.clear();

	//Ici on gere le RCPT TO
    output += "RCPT TO: ";
    cout << "RCPT TO: " << endl;
    input_cli = mailDest;
    output += input_cli + "\r\n";
    if (verbose) {cout << "Commande envoyée: " << output << endl;}
    reader.write(output);
    tampon += output;
    rep = reader.read_line();
    if (verbose) {cout <<"Serveur envoie: "<< rep << endl;}
    
    if(rep[0] != '2') {
        cerr << "Refusé" << endl;
        exit(1);
    }
    
    input_cli.clear();
    output.clear();


	//DATA POUR ENVOYER LE MAIL AVEC TOUT
    output += "DATA \r\n";
    cout << "DATA: " << endl;
    reader.write(output); // Envoie la commande DATA
    rep = reader.read_line();
    if(rep[0] != '2')
    {
        cerr << "Refusé" << endl;
        exit(1);

    }
    if (verbose) {cout <<"DATA : serveur envoie:" << rep << endl;}
    
    output.clear();

    //Ici on gere le from
    output += "From: ";
    cout << "From: " << endl;
    input_cli = mailExpe;
 	 output += input_cli  + "\r\n";
    rep = reader.read_line(); 
    tampon += output;



    //Ici on gere le Subject
    output += "Subject: ";
    cout << "Subject:" << endl;
    input_cli = titre;
    output += input_cli  + "\r\n";
    tampon += output;

    //Ici on gere la date qui est recuperé des le debut
    cout << "Date:" << endl;
    output += date + "\r\n";

    //Ici on gere le Texte;
    cout << "Corps du message: ";
    input_cli = texte;
    output += input_cli + "\r\n.\r\n";
    tampon += output;
    cout << input_cli <<endl;
    if (verbose) {cout << "Commande envoyée: " << endl << output << endl;}
    
    
    rep = reader.read_line(); // lit la réponse du serveur
    if(rep[0] != '2')
    {
        cerr << "Refusé" << endl;
        exit(1);
    }

    reader.write(output); // envoie au serveur
	
    return 0;
}

