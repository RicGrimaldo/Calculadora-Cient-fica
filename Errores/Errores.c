#include<stdio.h>
#include <string.h>
#define n 33
int encontrar_error(char a[]);
int error_sintatico(char a[]);
int error_lexico(char a[]);
int esDigito (char car);
int es_operador(char car);
int Longitud_cadena(char a[]);
int parentesis_paridad(char a[]);
int parentesis_vacio(char a[]);
int validacion_caracter(char a[]);
int decimal(char a[]);
int parentesis_operador(char a[]);
int encontrarCaracter(char cad[], char car);
int limite_cadena (char cad[]);
int letras_permitidas(char car);
int verificacion_funciones(char cad[]);
int main(){
    char a[n];
    int r,m;
    char e_tilde = 130,o_tilde = 162;
    printf("Ingrese expresi%cn aritm%ctica: \n",o_tilde,e_tilde);
    fgets(a,n,stdin);
    r=encontrar_error(a);
    m=Longitud_cadena(a);
    ///printf("\n\n1 Si se encontr%c error, 0 si no se encontr%c: %i\n\n",o_tilde,o_tilde,r);
    printf("\n%i",verificacion_funciones(a));
    printf("\n\nLongitud: %i",strlen(a));

    return 0;
}

int encontrar_error(char a[]){
    int error=0;
    if(error_lexico(a)==1){
        error=1;
    }
    else{
        if(error_sintatico(a)==1)error=1;
    }
    return error;
}

int error_lexico(char a[]){
    int resultado=1;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    for(int i=0;i<strlen(a);i++){
        if(esDigito(a[i])==1 || es_operador(a[i])==1 && a[i]!='.' || letras_permitidas(a[i])==1){
                resultado=0;
/*Como la condición es falsa si y solo si ambos casos son falsos, entonces el carácter leído es dígito u operaror,
procediendo a leer el siguiente carácter de la candena*/
            continue;
        }
        else{
        /*En caso de que el carácter leído no sea dígito u operador, se detectará el error léxico*/
                resultado=1;
                if(a[i]=='.'){ /*Si el carácter inválido es un punto decimal, hará una impresión diferente*/
                        resultado = decimal(a);
                        break;
                }
                else{
                ///printf("Observaci%cn.\nError en el car%cter inv%clido '%c'\n",o_tilde,a_tilde,a_tilde,a[i]);
            break; /*Saliéndose del bucle*/
                }
        }
    } /*Devolverá 1 en caso de que se haya encontrado un error léxico, 0 en caso contrario*/
    return resultado;
}

int error_sintatico(char a[]){
    int resultado=0,m;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    if(parentesis_paridad(a)!=0){ /*Primero, se validará si hay la misma cantidad de pares de paréntesis*/
    for(int i=0;i<m;i++){

        if(a[i]=='('||a[i]==')'){
                continue; /*Ignorará los operadores válidos, en este caso los paréntesis*/
        }
        if(es_operador(a[i])==1 && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!=')'){
            resultado=1; /*Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c'\n",o_tilde,a[i],a[i+1]);
            break;
        }
        else{
            resultado=0;
            /*El resultado será 0 en caso de que el carácter leído no haya presentado error*/
        }
    }
    }
    else{
        printf("Error sint%ctico. \n",a_tilde);
        printf("Observaci%cn. \nError debido a falta de un par%cntesis.\n",o_tilde,e_tilde);
        resultado=1;
        /*Habrá error sintático en caso de que la cantidad de pares de paréntesis sea diferente*/
    }
    if(resultado==0){
            if(parentesis_vacio(a)==1) resultado=1;
    /*Habrá error sintático en caso de haber paréntesis vacíos*/
            if(validacion_caracter(a)==1) resultado=1;
    /*Habrá error sintático en caso de haber un operador al inicio o al final de la sentencia*/
    }
    return resultado;
}

int esDigito (char car){
    int resultado=0;
    if(car>47 && car<58){
            resultado=1;
    }
    return resultado;
}

int es_operador(char car){
    int resultado=0;
    switch(car){
    case'+': case'-': case'*': case'/': case '^': case'(': case ')': case '%': case '.': case '!': resultado=1;
    break;
    }
    return resultado;
}

int letras_permitidas (char car){
    int resultado = 0;

    switch(car){
        case 'a': case'c': case'e': case'i': case 'o': case'r': case 's': case 't':resultado=1;
        break;
    }
    return resultado;
}

int Longitud_cadena(char a[]){
    int i=0;
    for(i=0;a[i]!='\0';i++){
    }
    return i-1;
}

int decimal(char a[]){

    int error = 0,x;
    x = encontrarCaracter(a,'.');
    for(int i=x+1;i<strlen(a);i++){
        if(es_operador(a[i]) == 1 && a[i]!= '.'){
            break;
        }
        else{
            if(a[i] == '.')
                error = 1;
        }
    }
    return error;
}

int parentesis_paridad(char a[]){
    int b=0,c=0,resultado=0,m; /*Contadores para contar cantidad de paréntesis en la cadena*/
    m=Longitud_cadena(a);
    for(int i=0;i<m;i++){
        switch(a[i]){
        case '(': b++;
        break;
        case ')': c++;
        break;
        }
    }
    if(c==b)resultado=1;
    return resultado;
}

int parentesis_vacio(char a[]){
    int m,resultado=0;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    for(int i=0;i<m;i++){
        if(a[i]=='('&& a[i+1]==')'){
                resultado=1; /*Al encontrar un par de paréntesis vacíos, se sale del bucle*/
                printf("Error sint%ctico. \n",a_tilde);
                printf("Observaci%cn.\nError en la secuencia '()'\n",o_tilde);
                break;
        }
    }
    return resultado;
}

int validacion_caracter(char a[]){
    int resultado=0,f,m;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    if(es_operador(a[0])==1 && a[0]!='('){
        resultado=1; /*Validará que el primer carácter no sea ningún operador a excepción del '('*/
        printf("Error sint%ctico. \n",a_tilde);
        printf("Observaci%cn.\nError en la secuencia '%c%c'\n",o_tilde,a[0],a[1]);
    }
    else{
    f=Longitud_cadena(a)-1;
    if(es_operador(a[f])==1 && a[f]!=')'){
            resultado=1; /*Validará que el último carácter no sea un operador a excepción de ')'*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn.\nError en la secuencia '%c%c'\n",o_tilde,a[f-1],a[f]);
    }
    }
    if(resultado==0){
        m=Longitud_cadena(a);
    for(int i=1;i<m;i++){
        if(es_operador(a[i])==1 && a[i]!='('&& a[i]!=')' && a[i-1]=='(' && a[i+1]==')'){
            resultado=1; /*Aquí se verifica que no haya un operador sólo entre paréntesis*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c%c'\n",o_tilde,a[i-1],a[i],a[i+1]);
            break;
        }
        else{
            if(es_operador(a[i])==1 && a[i]!='('&& a[i]!=')'&& a[i+1]==')'){
                resultado=1; /*Aquí se verifica que no haya un operador antes de un paréntesis cerrado*/
                printf("Error sint%ctico. \n",a_tilde);
                printf("Observaci%cn. \nError en la secuencia '%c%c'\n",o_tilde,a[i],a[i+1]);
                break;
        }
    }
    }
    if(resultado==0 && parentesis_operador(a)==1)resultado=1;
    return resultado;
}
}

int parentesis_operador(char a[]){
    int m,resultado=0;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    for(int i=1;i<m;i++){
        if(a[i]=='('){
           if(a[i-1]==')' || esDigito(a[i-1])==1){
            resultado=1; /*Aquí se verifica que no haya un número o paréntesis izquierdo antes de un paréntesis derecho*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador antes del par%cntesis.\n",o_tilde,a[i-1],a[i],e_tilde);
            break;
            }
        }
        else{
            if(a[i]==')'){
                if(a[i+1]=='('|| esDigito(a[i+1])==1){
                    resultado=1; /*Aquí se verifica que no haya un número o paréntesis derecho antes de un paréntesis izquierdo*/
                    printf("Error sint%ctico. \n",a_tilde);
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador despu%cs del par%cntesis.\n",o_tilde,a[i],a[i+1],e_tilde,e_tilde);
                    break;
                   }
            }
        }
    }
        return resultado;
}

int encontrarCaracter(char cad[], char car){
     int r=0;
     for(int i=0;i<strlen(cad);i++){
        if(cad[i]==car){
            r=i+1;
            break;
        }
     }
     return r-1;
 }

 int limite_cadena(char cad[])
 {
     int error = 0;
     if(strlen(cad) >= 32)
        error = 1;
    else
        error = 0;

    return error;
 }


 int verificacion_funciones(char cad[])
 {
     int error = 0;
     for(int i=0;i<strlen(cad);i++)
     {
         if(cad[i]=='s'){
            if(cad[i+1]=='i' && cad[i+2]=='n')
            {
                error = 0;
                break;
            }
            else{
                if(cad[i+1]=='e' && cad[i+2]=='c'){
                    error = 0;
                    break;
                }
                else{
                    if(cad[i+1]=='q'&& cad[i+2]=='r' && cad[i+3]=='t'){
                        error = 0;
                        break;
                    }
                    else {error = 1; break;}
                }
            }
         }
         else{
            if(cad[i]=='c'){
                if(cad[i+1]=='o' && cad[i+2]=='s' || cad[i+2]=='t'){
                    error = 0;
                    break;
                }
                else
                {
                    if(cad[i+1]=='s' && cad[i+2]=='c'){
                        error = 0;
                        break;
                    }
                    else{error = 1;}
                }
            }
            else{
                if(cad[i]=='t' && cad[i+1]=='a' && cad[i+2]=='n'){
                    error = 0;
                    break;
                }
                else
                {
                    if(cad[i]=='a'&& cad[i+1]=='r'&& cad[i+2]=='c'){
                        if(cad[i+3]=='s' && cad[i+4]=='i' && cad[i+5]=='n' || cad[i+4]=='e' && cad[i+5]=='c'){
                            error = 0;
                            break;
                        }
                        else{
                            if(cad[i+3]=='c'&& cad[i+4]=='s' && cad[i+5]=='c' || cad[i+4]=='o' && cad[i+5]=='t'){
                                error = 0;
                                break;
                            }
                            else{
                                if(cad[i+4]=='o' && cad[i+5]=='s'){
                                    error = 0;
                                    break;
                                }
                            else{
                                if(cad[i+3]=='t' && cad[i+4]=='a' && cad[i+5]=='n'){
                                    error = 0;
                                    break;
                                }
                                else{
                                    error = 1;
                                    break;
                                }
                            }
                            }
                        }
                    }
                }
            }
         }

     }
     if(error == 1)
        puts("Es necesario escribir las funciones con la sintaxis correcta");
     return error;
 }
