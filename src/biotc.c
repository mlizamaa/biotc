#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "./headers/biotc.h"
#include "config.c"
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */


struct sample_parameters parms;
char temperature_symbol[3];

int main(int argc, char * argv []){
    init_parameters (&parms);
    parse_config (&parms);
    strcat(temperature_symbol, "°");
    strncat(temperature_symbol,parms.DEFAULT_TEMPERATURE_MEASURE,1);
   /* 
    char * p;
    char * q;
    char * r;
    char cadena[7]="marcelo";
    //p = cadena;
    p = &cadena[0];
    q = &cadena[1];
    r = &cadena[7];

    //printf("DEFAULT_TEMPERATURE_MEASURE: %s\n",temperature_symbol);
    printf("%s\n",p);
    printf("%s\n",q);
    printf("%s\n",r);
    printf("\n");
    printf("%s\n",cadena);
    */
    if(argc == 1){
        no_parameter_response();
        exit_secuency();
    }
    else {
        process(argc, argv);
    }   
    return 0;
}

int process(int argc, char * argv []){
    if(argc > 3){
       printf("too many arguments\n");
        return 0;      
    }
    char * c = argv[1];
    

    if(strcmp(c,"t") ==0){
        char * v = argv[2];
        temperature(v);
        call();
    }
    else if(strcmp(c,"x")==0){
        FILE *fp;
        fp = fopen("./test.txt", "w+");
        fprintf(fp, "This is testing for fprintf...\n");
        fputs("This is testing for fputs...\n", fp);
        fclose(fp);
    }
    printf("\n");
    return 0;
}


int no_parameter_response(){
        printf("must specify a parameter\n");    
        printf("a parameter can be any of [t,h,on(parameters...),of(parameters...) ]\n\n");
        printf("\t-t : temperature in c° or f° according DEFAULT_TEMPERATURE_SYMBOL \n");
        printf("\t-h : humidity in c° or f° according DEFAULT_TEMPERATURE_SYMBOL \n");
        printf("\t-on : turn on the pin p. Ex : on [pin] \n");
        printf("\t-off : turn off the pin p. Ex : off [pin] \n");
        
        return 0;
}

int exit_secuency(){
    printf("para salir presione enter");
    char key[1];
    fgets(key,2,stdin);
}

int temperature(char *terminal){
    if(strcmp(terminal,"oficina")==0){
          printf("18%s",temperature_symbol);
    }
    else if(strcmp(terminal,"living")==0){
        printf("23%s",temperature_symbol);
    }
    else{
        printf("no existe el terminal solicitado\n");
        return 0;
    }
}

int terminal_on(char * terminal){
return 0;
}

int terminal_off(char * terminal){
  return 0;
}



void error(const char *msg) { perror(msg); exit(0); }

int call()
{
    /* first what are we going to send and where are we going to send it? */
    int portno =        80;
    char *host =        "192.168.0.9";
    char *message_fmt = "GET /CMD/DHT11/H/2 HTTP/1.0\r\n\r\n";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char message[1024],response[4096];

    //if (argc < 3) { puts("Parameters: <apikey> <command>"); exit(0); }

    /* fill in the parameters */
    sprintf(message,message_fmt,"");
    printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    return 0;
}


