/* cliTCPIt.c - Exemplu de client TCP
   Trimite un nume la server; primeste de la server "Hello nume".
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
  while (1) {
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  		// mesajul trimis
  int nr=0;
  char buf[10];

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

  /* citirea mesajului */
  printf ("[client]Introduceti un numar: ");
  fflush (stdout);
  int numread;
  numread = read (0, buf, sizeof(buf));
  //nr=atoi(buf);
  buf[numread]=0;
  char name[20] = "";
  name[0] = '\0';
  strcpy(name, buf);
  //scanf("%d",&nr);
  
  printf("[client] Am citit %s\n",name);


  if (write (sd,&name,strlen(name)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
  if (read (sd, &name,strlen(name)) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  printf ("[client]Mesajul primit este: %s\n", name);

  /* inchidem conexiunea, am terminat */
  close (sd);
}
}
