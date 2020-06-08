#include<stdio.h>
#include <string.h>
#define n 30
int encontrar_error(char a[]);
int error_sintatico(char a[]);
int error_lexico(char a[]);
int esDigito (char car);
int es_operador(char car);
int Longitud_cadena(char a[]);
int parentesis_paridad(char a[]);
int parentesis_vacio(char a[]);
int validacion_caracter(char a[]);
void decimal(char a[]);
int parentesis_operador(char a[]);
int encontrarCaracter(char cad[], char car);

int main(){
    char a[n];
    int r,m;
    char e_tilde = 130,o_tilde = 162;
    printf("Ingrese expresi%cn aritm%ctica: \n",o_tilde,e_tilde);
    fgets(a,n,stdin);
    r=encontrar_error(a);
    m=Longitud_cadena(a);
    printf("1 Si se encontr%c error, 0 si no se encontr%c: %i",o_tilde,o_tilde,r);
    printf("\nEsta es la longitud: %i",m);
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
    int resultado=1,m;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    for(int i=0;i<m;i++){
        if(esDigito(a[i])==1 || es_operador(a[i])==1){
                resultado=0;
/*Como la condici�n es falsa si y solo si ambos casos son falsos, entonces el car�cter le�do es d�gito u operaror,
procediendo a leer el siguiente car�cter de la candena*/
            continue;
        }
        else{
        /*En caso de que el car�cter le�do no sea d�gito u operador, se detectar� el error l�xico*/
                resultado=1;
                printf("Error l%cxico.\n",e_tilde);
                if(a[i]=='.'){ /*Si el car�cter inv�lido es un punto decimal, har� una impresi�n diferente*/
                        decimal(a);
                        break;
                }
                else{
                printf("Observaci%cn.\nError en el car%cter inv%clido '%c'\n",o_tilde,a_tilde,a_tilde,a[i]);
            break; /*Sali�ndose del bucle*/
                }
        }
    } /*Devolver� 1 en caso de que se haya encontrado un error l�xico, 0 en caso contrario*/
    return resultado;
}

int error_sintatico(char a[]){
    int resultado=0,m;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    if(parentesis_paridad(a)!=0){ /*Primero, se validar� si hay la misma cantidad de pares de par�ntesis*/
    for(int i=0;i<m;i++){

        if(a[i]=='('||a[i]==')'){
                continue; /*Ignorar� los operadores v�lidos, en este caso los par�ntesis*/
        }
        if(es_operador(a[i])==1 && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!=')'){
            resultado=1; /*Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c'\n",o_tilde,a[i],a[i+1]);
            break;
        }
        else{
            resultado=0;
            /*El resultado ser� 0 en caso de que el car�cter le�do no haya presentado error*/
        }
    }
    }
    else{
        printf("Error sint%ctico. \n",a_tilde);
        printf("Observaci%cn. \nError debido a falta de un par%cntesis.\n",o_tilde,e_tilde);
        resultado=1;
        /*Habr� error sint�tico en caso de que la cantidad de pares de par�ntesis sea diferente*/
    }
    if(resultado==0){
            if(parentesis_vacio(a)==1) resultado=1;
    /*Habr� error sint�tico en caso de haber par�ntesis vac�os*/
            if(validacion_caracter(a)==1) resultado=1;
    /*Habr� error sint�tico en caso de haber un operador al inicio o al final de la sentencia*/
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

int Longitud_cadena(char a[]){
    int i=0;
    for(i=0;a[i]!='\0';i++){
    }
    return i-1;
}

void decimal(char a[]){
    int m;
    char a_tilde = 160,e_tilde = 130,o_tilde = 162;
    m=Longitud_cadena(a);
    for(int i=0;i<m;i++){
            if(a[i]=='.'){
        if(i!=0 && i+1!=m){ /*Primero veamos si el punto no est� como primer car�cter, y su siguiente car�cter no est� vac�o*/
                printf("Observaci%cn. \nError en la secuencia '%c%c%c'\n",o_tilde,a[i-1],a[i],a[i+1]);
                break;
        }
        else{
            if(i==0 && i+1!=m) { /*En caso de que el punto est� como primer elemento del arreglo, solamente se imprimir� �ste y el siguiente elemento*/
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\n",o_tilde,a[i],a[i+1]);
                    break;
            }
                    else{
                            printf("Observaci%cn. \nError en la secuencia '%c%c'\n",o_tilde,a[i-1],a[i]);
                            /*En caso que los �nicos 2 elementos del arreglo sean  un n�mero y un punto*/
                    }
    }
    }
}
}

int parentesis_paridad(char a[]){
    int b=0,c=0,resultado=0,m; /*Contadores para contar cantidad de par�ntesis en la cadena*/
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
                resultado=1; /*Al encontrar un par de par�ntesis vac�os, se sale del bucle*/
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
        resultado=1; /*Validar� que el primer car�cter no sea ning�n operador a excepci�n del '('*/
        printf("Error sint%ctico. \n",a_tilde);
        printf("Observaci%cn.\nError en la secuencia '%c%c'\n",o_tilde,a[0],a[1]);
    }
    else{
    f=Longitud_cadena(a)-1;
    if(es_operador(a[f])==1 && a[f]!=')'){
            resultado=1; /*Validar� que el �ltimo car�cter no sea un operador a excepci�n de ')'*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn.\nError en la secuencia '%c%c'\n",o_tilde,a[f-1],a[f]);
    }
    }
    if(resultado==0){
        m=Longitud_cadena(a);
    for(int i=1;i<m;i++){
        if(es_operador(a[i])==1 && a[i]!='('&& a[i]!=')' && a[i-1]=='(' && a[i+1]==')'){
            resultado=1; /*Aqu� se verifica que no haya un operador s�lo entre par�ntesis*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c%c'\n",o_tilde,a[i-1],a[i],a[i+1]);
            break;
        }
        else{
            if(es_operador(a[i])==1 && a[i]!='('&& a[i]!=')'&& a[i+1]==')'){
                resultado=1; /*Aqu� se verifica que no haya un operador antes de un par�ntesis cerrado*/
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
            resultado=1; /*Aqu� se verifica que no haya un n�mero o par�ntesis izquierdo antes de un par�ntesis derecho*/
            printf("Error sint%ctico. \n",a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador antes del par%cntesis.\n",o_tilde,a[i-1],a[i],e_tilde);
            break;
            }
        }
        else{
            if(a[i]==')'){
                if(a[i+1]=='('|| esDigito(a[i+1])==1){
                    resultado=1; /*Aqu� se verifica que no haya un n�mero o par�ntesis derecho antes de un par�ntesis izquierdo*/
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