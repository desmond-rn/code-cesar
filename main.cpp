#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>

using namespace std;


// flush
void flush()//L'usage de flush permet de garantir que le message sera affich� avant de passer � la suite du programme.
{
	while( getchar() != '\n' )
		continue;//De cette fa�on, vous pouvez tester que l'utilisateur n'appuiera pas sur "Entr�e" sans avoir ins�r� num�ro.
}

// programme principal


int main()
{
    int decalage = 0;
	char nom_fichier[256];
	char text[256];
	char choix = 'c';
	// choix
	cout<<"Code de Cesar\n";
	cout<<"\nSaisir le decalage ou la cle de votre texte a chriffrer: ";
	cin>> decalage;
	flush();//L'usage de flush permet de garantir que le message sera affich� avant de passer � la suite du programme.
	cout<<"\nSaisir le nom du fichier a chriffrer: ";// C'est ici que sera stock� le texte entre a �cran ainsi que le r�sultat apr�s op�ration.
	cin>> nom_fichier;
	flush();

	cout<< "\n vous voulez faire un Chiffrement [c] ou Dechiffrement [d] : ";//choix de operation de criptage
	cin>>choix;
	flush();




	cout<<"\nEntrer votre text: ";
	cin.getline(text,255);//C'est un moyen de lire une ligne enti�re d'entr�e de console dans une variable. "getline est plus facile � utiliser pour lire des s�quences d'entr�es que d'autres fonctions telles que l'op�rateur >>, qui est plus orient� vers les mots ou les caract�res.
	// synth�se
	switch( choix )

	{
	case 'c' :
		cout<<"\n Vous avez demander le chiffrement du fichier "<<nom_fichier<< " avec un decalage de \n"<<decalage;
		{
			int index;
			int taille_fichier = 0;
			FILE * fichier_avant = NULL;
			FILE * fichier_apres = NULL;
			int taille_memoire_tamon = 1024;
			char * memoire_tampon = NULL;//D�claratio du fichier trasitoire
			// allocation
			memoire_tampon = (char *)malloc(taille_memoire_tamon);//libere la memoire pour le fichier trasitoire
			if(text[0]!='\n')// verifier si l'utilisateur a entrer du text
            {

            strcpy(memoire_tampon, text);//Copier la cha�ne  point�e par TEXT dans le tableau par memoire_tampon, y compris le caract�re nul de fin (et s'arr�te � ce point).
            taille_fichier = strlen(text);//Le strlen () prend comme argument une cha�ne d'octets termin�e par null et renvoie sa longueur. u
			}
			else{
			// mise en m�moire tampon
			fichier_avant = fopen( nom_fichier, "r" );
			taille_fichier = fread( memoire_tampon, 1, taille_memoire_tamon, fichier_avant );
			fclose( fichier_avant );
			}

			// chiffrement dans le m�moire tampon
			for( index = 0; index != taille_fichier; ++index )
			{
				// chiffrement des majuscules
				if( memoire_tampon[ index ] >=65 && memoire_tampon[ index ] < 91 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 65 ) + decalage ) % 26 + 65;//recherche code ASCII
				// chiffrement des minuscules
				if( memoire_tampon[ index ] >=97 && memoire_tampon[ index ] < 123 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 97 ) + decalage ) % 26 + 97;
			}
			// mise a jour du fichier
			fichier_apres = fopen( nom_fichier, "w" );
			fwrite( memoire_tampon, 1, taille_fichier, fichier_apres );
			cout<< "\nLe resultat du chiffrement est : "<<memoire_tampon;
			fclose( fichier_apres );
			// desallocation
			free( memoire_tampon);
		}
		return 0;
	case 'd' :
		cout<<"\nVous avez demander le dechiffrement du fichier " <<nom_fichier<< " avec un decalage de \n"<< decalage;
		{
			int index;
			int taille_fichier = 0;
			FILE * fichier_avant = NULL;
			FILE * fichier_apres = NULL;
			int taille_memoire_tamon = 1024;
			char * memoire_tampon = NULL;
			// allocation
			memoire_tampon = (char *)malloc(taille_memoire_tamon);
			if(text[0]!='\n')// verifier si l'utilisateur a entrer du text
            {

            strcpy(memoire_tampon, text);
            taille_fichier = strlen(text);
			}
			else{
			// mise en m�moire tampon
			fichier_avant = fopen( nom_fichier, "r" );
			taille_fichier = fread( memoire_tampon, 1, taille_memoire_tamon, fichier_avant );
			fclose( fichier_avant );
			}

			// chiffrement dans le m�moire tampon
			for( index = 0; index != taille_fichier; ++index )
			{
				// chiffrement des majuscules
				if( memoire_tampon[ index ] >=65 && memoire_tampon[ index ] < 91 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 65 ) - decalage ) % 26 + 65;//recherche code ASCII
				// chiffrement des minuscules
				if( memoire_tampon[ index ] >=97 && memoire_tampon[ index ] < 123 )
					memoire_tampon[ index ] = ( ( memoire_tampon[ index ] - 97 ) - decalage ) % 26 + 97;
			}
			// mise a jour du fichier
			fichier_apres = fopen( nom_fichier, "w" );
			fwrite( memoire_tampon, 1, taille_fichier, fichier_apres );
			cout<< "\nLe resultat du dechiffrement est : "<<memoire_tampon;
			fclose( fichier_apres );
			// desallocation
			free( memoire_tampon);
		}
		return 0;
	default:
		return -1;
	}

}
