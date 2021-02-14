#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 


#define max 255

noreturn void raler (const char *msg)
{
    perror (msg) ;
    exit (EXIT_FAILURE) ;
}


int fils(FILE* fichier)
{
	int i=0;
	int c =0;
        
    while((c=fgetc(fichier))!=EOF)
	{
         
	    if(c=='\n')
	    {
	         i++;
	    }
	}
    return i;
}


int main(int argc , char** argv)
{    
	
	int f;
    int nbl[max];
    pid_t pid ; 
    int raison;
    int nbltotal=0;
	FILE *fp ;

    if(argc==0)
    {
        return 0;
    }

    if(argc!=0)
    {
	    for(f= 1; f <= 50; f++)
	    {
            
	    if((fp = fopen(argv[f], "r" )) == NULL) 
            exit(1);
           
        else
        {   
                
		switch ( pid = fork ())
		{
			case -1 :
			    raler ("fork") ;
                break;
			case 0 :                                
            // les fils
			    nbl[f]=fils(fp);
                if(nbl[f]< max)
                {
				    //printf("Il y a %d lignes\n",nbl[f]);
		            exit(nbl[f]);
                }
                else if (nbl[f]==max)
                {
                    exit(max);
                }
                break;
			
            default :  
                // le père
                                
                if ( wait (&raison ) == -1)
				    raler ( "wait" ) ;
				if ( WIFEXITED (raison))
				    printf("exit(%d)\n",WEXITSTATUS(raison));
				else if ( WIFSIGNALED ( raison ))
				    printf ( "signal␣%d\n ",WTERMSIG(raison));
				else
				    printf ( "autre␣raison\n" ) ;
                                
				if(WEXITSTATUS (raison)== max)
                {
                    exit(1);
                }
                else
                {
                    nbltotal+= WEXITSTATUS (raison);
                    //printf("Au total %d lignes \n",nbltotal);

                    // j'ai réussi à calculer la somme de 
                    //toutes les lignes que père à reçu
                    //mais le code de retour nul ne fonctionne pas
                }
                                
                wait(NULL);
                break;
		} 
        }
              
     
	if (fclose (fp) == -1)
    {
	    raler("erreur");
	}
    }
    }
return 0;
}