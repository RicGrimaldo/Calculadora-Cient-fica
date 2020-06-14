#include<stdio.h>
#include <string.h>
#define n 34
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
int Primer_letra_funcion(char a);
int Encontrar_cadena (char cad1[],char cad2[]);
int main(){
    char a[n];
    int r,m;
    char e_tilde = 130,o_tilde = 162;
    printf("Ingrese expresi%cn aritm%ctica: \n",o_tilde,e_tilde);
    fgets(a,n,stdin);
    r=encontrar_error(a);
    m=Longitud_cadena(a);
    printf("\n\n1 Si se encontr%c error, 0 si no se encontr%c: %i\n\n",o_tilde,o_tilde,r);
    printf("\n%i",r);
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
		int error=1;
		for(int i=0;i<strlen(a);i++){
			printf("%i: %c\n",i,a[i]);
			if(esDigito(a[i])==1 || es_operador(a[i])==1  && a[i]!='.' || letras_permitidas(a[i])==1){
				error=0;
				/*Como la condición es falsa si y solo si ambos casos son falsos, entonces el carácter leído es dígito u operaror,
				procediendo a leer el siguiente carácter de la candena*/
				continue;
			}
			else{
				/*En caso de que el carácter leído no sea dígito u operador, se detectará el error léxico*/
				error=1;
				if(a[i]=='.'){ /*Si el carácter inválido es un punto decimal, hará una impresión diferente*/
					error = decimal(a);
					break;
				}
				else{
					puts("No se permiten caracteres inválidos");
					printf("Caracter invalido: %c\n",a[i]);
					break; /*Saliéndose del bucle*/
				}
			}
		} /*Devolverá 1 en caso de que se haya encontrado un error léxico, 0 en caso contrario*/
		return error;
	}

int error_sintatico(char a[]){
    int resultado=0;
    if(parentesis_paridad(a)!=1){ /*Primero, se validará si hay la misma cantidad de pares de paréntesis*/
    for(int i=0;i<strlen(a);i++){

        if(a[i]=='('||a[i]==')'){
                continue; /*Ignorará los operadores válidos, en este caso los paréntesis*/
        }
        if(es_operador(a[i])==1 && a[i]!='-' && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!='!' && a[i+1]!='%'){
            resultado=1; /*Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis,
			factorial, porcentaje o que primero esté un signo negativo*/
            puts("No es posible calcular con 2 operadores seguidos");
            break;
        }
        else{
            resultado=0;
            /*El resultado será 0 en caso de que el carácter leído no haya presentado error*/
        }
    }
    }
    else{
        puts("Error debido a falta de un parentesis");
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
	
int Primer_letra_funcion(char a)
{
	int resultado = 0;
	switch(a){
		case 'a': case 's' : case 'c' : case 't': resultado = 1;
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
				puts("El número decimal únicamente debe llevar un solo punto.");
				error = 1;
			}
		}
		return error;
	}

int parentesis_paridad(char a[]){
    int b=0,c=0,error=0,m; /*Contadores para contar cantidad de paréntesis en la cadena*/
    m=Longitud_cadena(a);
    for(int i=0;i<m;i++){
        switch(a[i]){
        case '(': b++;
        break;
        case ')': c++;
        break;
        }
    }
    if(c!=b)error=1;
    return error;
}

int parentesis_vacio(char a[]){
    int error=0;
    for(int i=0;i<strlen(a);i++){
        if(a[i]=='('&& a[i+1]==')'){
                error=1; /*Al encontrar un par de paréntesis vacíos, se sale del bucle*/
                puts("Error al haber dejado un par de paréntesis vacíos");
                break;
        }
    }
    return error;
}

int validacion_caracter(char a[]){
	int error=0,f;
	if(es_operador(a[0])==1 && a[0]!='(' && a[0]!='-' && esDigito(a[0])==0){
		error=1; /*Validará que el primer carácter no sea ningún operador a excepción del '(', y cualquier primer letra de las funciones*/
		puts("Error con el primer caracter");
		}
	else{///Caso especial si es una letra
		if(letras_permitidas(a[0])==1 && Primer_letra_funcion(a[0])==0){
			error = 1;
			puts("Error en el primer catacter");
		}
	}
	
	if(error == 0){
	f=strlen(a)-1;
	if(es_operador(a[f])==1 && a[f]!=')' && a[f]!='!' && a[f]!='%'){
		error=1; /*Validará que el último carácter no sea un operador a excepción de ')', ! y %*/
		puts("Error con el ultimo caracter");
	}
	}
	
	if(error==0){
		for(int i=1;i<strlen(a);i++){
			if(a[i-1]=='(' && es_operador(a[i])==1 && a[i]!='(' && a[i]!='-' && esDigito(a[i])==0){
				error=1; /*Validará que el primer carácter no sea ningún operador a excepción del '(', y cualquier primer letra de las funciones*/
				puts("Error con el primer caracter despues del parentesis");
			}
			else{///Caso especial si es una letra
				if(a[i-1]=='(' && letras_permitidas(a[i])==1 && Primer_letra_funcion(a[i])==0){
					error = 1;
					puts("Error con el primer caracter despues del parentesis");
				}
				else{
					if(es_operador(a[i-1])==1 && a[i]==')' && a[i-1]!='!' && a[i-1]!='%'){
						error=1; /*Aquí se verifica que no haya un operador antes de un paréntesis cerrado*/
						puts("Error con el caracter antes del parentesis cerrado");
						break;
					}
				}
			}
			}
	}

		return error;
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
 
 int Encontrar_cadena (char cad1[],char cad2[]){
	 int resultado=0,i=0;
	 ///Si no se encuentra cadena, devuelve 0.
	 while(i<strlen(cad1)){
		 for(int j=0;j<strlen(cad2);j++){
			 if(cad1[i]=='\0')break;
			 if(cad1[i]==cad2[j]){
				 i++;
				 resultado=1;
			 }
			 else{
				 if(i>0){
					 resultado=0;
					 break;}
			 }
		 }
		 if(cad1[i]=='\0'){
			 break;}
		 break;
	 }
	 printf("%i\n",resultado);
	 return resultado;
 }


 int verificacion_funciones(char cad[])
 {
	 int error = 0;
	 for(int i=0;i<strlen(cad);i++)
	 {
		 if(esDigito(cad[i])==0 && es_operador(cad[i])==0){
			 if(cad[i] == 'a'){
				 if(Encontrar_cadena("arcsec(",cad) == 1){ error = 0; break;}
				 else{
					 if(Encontrar_cadena("arccsc(",cad) == 1){ error = 0; break;}
					 else{
						 if(Encontrar_cadena("arccot(",cad) == 1){ error = 0; break;}
						 else{
							 if(Encontrar_cadena("arcsin(",cad) == 1){ error = 0; break;}
							 else{
								 if(Encontrar_cadena("arccos(",cad) == 1){ error = 0; break; }
								 else{
									 if(Encontrar_cadena("arctan(",cad) == 1){ error = 0; break; }
									 else{ error = 1; break;}
								 }
							 }
						 }
					 }
				 }
			 }
			 else{
				 if(cad[i] == 's'){
					 if(Encontrar_cadena("sec(",cad) == 1){ error = 0; break;}
					 else{
						 if(Encontrar_cadena("sin(",cad) == 1){ error = 0; break;}
						 else{
							 if(Encontrar_cadena("sqrt(",cad) == 1){ error = 0; break;}
							 else{ error = 1; break;}
						 }
					 }
				 }
				 else{
					 if(cad[i] == 'c'){
						 if(Encontrar_cadena("csc(",cad) == 1){ error = 0; break;}
						 else{
							 if(Encontrar_cadena("cos(",cad) == 1){ error = 0; break;}
							 else{
								 if(Encontrar_cadena("cot(",cad) == 1){ error = 0; break;}
								 else{ error = 1; break;}
							 }
						 }
					 }
					 else{
						 if (cad[i] == 't' && Encontrar_cadena("tan(",cad) == 1){ error = 0; break;}
						 else{ error = 1; break;}
					 }
				 }
			 }
		 }
	 }
	 
	 if(error == 1) puts("Es necesario escribir las funciones con la sintaxis correcta");
	 return error;
 }
