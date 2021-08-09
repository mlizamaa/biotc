#include <stdio.h>
#include <string.h>
int no_parameter_response();
int process();
int exit_secuency();

#define DEFAULT_TEMPERATURE_SYMBOL "c"
#define SHOW_SYMBOL 1

int temperature(char * terminal);
int terminal_on(char * terminal);
int terminal_off(char * terminal);
char * get_symbol();

int main(int argc, char * argv []){
    
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

char * get_symbol(){
    if(SHOW_SYMBOL == 1){
        return "°c";   
    }
    return "";
}

int no_parameter_response(){
        printf("must specify a parameter\n");    
        printf("a parameter can be any of [t,h,on,of]\n\n");
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
        printf("18");
    }
    else if(strcmp(terminal,"living")==0){
        printf("23");
    }
    else{
        printf("no existe el terminal solicitado\n");
    }
}

int terminal_on(char * terminal){

}

int terminal_off(char * terminal){}