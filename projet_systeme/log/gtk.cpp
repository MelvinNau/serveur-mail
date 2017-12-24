//gcc propre.c -o propre.ex `pkg-config --cflags --libs gtk+-2.0`
//g++ propre.cpp -o executable `pkg-config gtkmm-3.0 --cflags --libs`  

//Dois fonctionner en surcouche. Interface graphique doit etre lancé depuis 
// projet_client.cpp. Ecrire le fichier. 
// Si les 2 entry (pour l'instant) ne sont pas vide, (donc si le get.line(), 
// sur le fichier est vide.) Alors soit, on conserve l'ancien resultat (sous forme de 
// --), si il est rentré, soit on demande à l'utlisateur de le rentrer).
// Puis le main de programme_client.cpp s'execute avec les bon parametres, pour 
// envoyer le mail correctement.
// 
// Si l'utilisateur n'a pas rentré plus de -- en parametre (pour le serveur et le port)
// alors on lance l'interface graphiqu

// l'ensemble de projet_client.cpp doit venir dans propre.cpp

#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>  
#include <iostream>



#include <gtk/gtk.h>

using namespace std;
 
void sauvegarde(string From, string To, string Titre, string Texte)
{
    remove("log/message.txt");
    ofstream fichier("log/message.txt");
    if(fichier)
    {
        fichier<<From<<endl;
        fichier<<To<<endl;
        fichier<<Titre<<endl;
        fichier<<Texte<<endl;
    }else{
        cerr<<"Impossible d'ouvrir le fichier"<<endl;
    }
    cout << "Save"<< endl;
}

void button_clicked(GtkWidget *widget, gpointer data) 
{
	//g_print("clicked\n");
	GtkWidget *pTempEntry;
	GtkWidget *pTempEntry2;
    GtkWidget *pTempEntry3;
    GtkWidget *pTempEntry4;
	GtkWidget *pTempLabel;
	GList *pList;

	string expe, dest, titre, texte;


	char tamp[30];

	// /* Recuperation de la liste des elements que contient la GtkVBox */
	pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*) data));

	//On peut recuperer tout ce qui est dans notre container. Donc nos "entry"
	
	//label 1
	pList = g_list_next(pList);

	/*entry 1 */
	pTempEntry = GTK_WIDGET(pList->data);
	pList = g_list_next(pList);

	//Label 2
	pList = g_list_next(pList);

	//entry 2
	pTempEntry2 = GTK_WIDGET(pList->data);
	pList = g_list_next(pList);


    pList = g_list_next(pList);
    pTempEntry3 = GTK_WIDGET(pList->data);
    pList = g_list_next(pList);


    pList = g_list_next(pList);
    pTempEntry4 = GTK_WIDGET(pList->data);
    pList = g_list_next(pList);


	expe = gtk_entry_get_text(GTK_ENTRY(pTempEntry));
	cout << "EXPEDITEUR: " << expe << endl;

	dest = gtk_entry_get_text(GTK_ENTRY(pTempEntry2));
	cout << "DESTINATAIRE: " << dest << endl;

    titre = gtk_entry_get_text(GTK_ENTRY(pTempEntry3));
    cout << "TITRE: " << titre << endl;

    texte = gtk_entry_get_text(GTK_ENTRY(pTempEntry4));
    cout << "TEXTE: " << texte << endl;




    sauvegarde(expe, dest, titre, texte);

	/* Liberation de la memoire utilisee par la liste */
	g_list_free(pList);
    system("pkill propre.ex");
}

/* Fonction callback execute lors du signal "activate" */
//Ne nous ser pas. A enlever
void on_activate_entry(GtkWidget *pEntry, gpointer data)
{
	//g_print("enter\n");
    const gchar *sText;
    char tamp[30];
	
    /* Recuperation du texte contenu dans le GtkEntry */
    sText = gtk_entry_get_text(GTK_ENTRY(pEntry));
    strcpy(tamp, sText);
    //cout << tamp << endl; 
 
    /* Modification du texte contenu dans le GtkLabel */
    gtk_label_set_text(GTK_LABEL((GtkWidget*)data), sText);
}
 
// Doit aller dans le projet_client.cpp
// Mais il faut que je mette correctement les lib
//Ne marche plus car plus de argc et argv
int afficher(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;

    GtkWidget *pEntry;
    GtkWidget *pEntry2;
    GtkWidget *pEntry3;
    GtkWidget *pEntry4;
    GtkWidget *pEntry5;
    GtkWidget *pEntry6;

    GtkWidget *pButton;
    GtkWidget *pLabel;
    GtkWidget *pLabel2;
    GtkWidget *pLabel3;
    GtkWidget *pLabel4;
    GtkWidget *pLabel5;
    GtkWidget *pLabel6;

 
    gtk_init(&argc, &argv);
    //main_client(&argc, &argv);
    //Il faut qu'on fasse comme ca pour interroger l'ancien main de projet_client

 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Envoi de Mail");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    //label
    pLabel = gtk_label_new("Expediteur: ");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);

    /* Creation du GtkEntry */
    pEntry = gtk_entry_new();
    /* Insertion du GtkEntry dans la GtkVBox */
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry, TRUE, FALSE, 0);

    //label
    pLabel2 = gtk_label_new("Destinataire: ");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel2, TRUE, FALSE, 0);

    /* Creation du GtkEntry */
    pEntry2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry2, TRUE, FALSE, 0);

    //label
    pLabel3 = gtk_label_new("Titre: ");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel3, TRUE, FALSE, 0);

    /* Creation du GtkEntry */
    pEntry3 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry3, TRUE, FALSE, 0);

    //label
    pLabel4 = gtk_label_new("Texte: ");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel4, TRUE, FALSE, 0);

    /* Creation du GtkEntry */
    pEntry4 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry4, TRUE, FALSE, 0);




    pButton = gtk_button_new_with_label("Envoyer");
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
 
    
 
    /* Connexion du signal "activate" du GtkEntry */
    //g_signal_connect(G_OBJECT(pEntry), "activate", G_CALLBACK(on_activate_entry), (GtkWidget*) pLabel);
    //g_signal_connect(G_OBJECT(pEntry2), "activate", G_CALLBACK(on_activate_entry), (GtkWidget*) pLabel2);


    g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(button_clicked), (GtkWidget*) pVBox);

    gtk_widget_show_all(pWindow);
 
    gtk_main();
 
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    afficher(argc, argv);
    
    return 0;
}
