#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define n 40
///Funciones PRINCIPALES
void Procedimiento(char entrada[n], char postfija[n]);
int DetectarErrores(char entrada[n]);
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]);
float ObtenerResultado(char postfija[n], int *);
void funciones_tri(char entrada[n]);
void multi_parentesis(char entrada [n]);
///Funciones secundarias pertenecientes a la función 'DetectarErrores'
int error_sintactico(char entrada[n]);
int error_lexico(char entrada[n]);
int es_digito (char car);
int es_operador(char car);
int longitud_cadena_errores(char entrada[n]);
int parentesis_paridad(char entrada[n]);
int parentesis_vacio(char entrada[n]);
int validacion_caracter(char entrada[n]);
void decimal(char entrada[n]);
int parentesis_operador(char entrada[n]);
///Funciones secundarias pertenecientes a la función 'ConvertirInfijaAPostfija'
int Encontrar_cadena (char cad1[],char cad2[]);
struct PILAA {
	int t;
	char a[n];
};
void pos(char entrada[n], char postfija[n]);
///Funciones secundarias pertenecientes a la función 'ObtenerResultado'
struct struct_nodo_float{
    float valor;
    struct struct_nodo_float *siguiente;
};
typedef struct struct_nodo_float nodo_float;
nodo_float *crear_pila_float(nodo_float *pila);
nodo_float *push_float(float valor, nodo_float *pila);
nodo_float *pop_float(float *valor, nodo_float *pila);
float operacion(float operando1, float operando2, char operador, int *);
float operacion_trig(float operando1, char operador, int *);
int factorial(float operando);
///Funciones secundarias
int potencia(int x, int y);
///Variables globales útiles
char entrada[n], postfija[n];
///Variables globales de impresión(código ASCII para las letras con tildes)
char a_tilde = 160, o_tilde = 162;
int main(){
    printf("Ingrese la expresi%cn:\n", o_tilde);
    fflush(stdin);
    fgets(entrada, n ,stdin);
    fflush(stdin);
    Procedimiento(entrada, postfija);
    return 0;
}
int potencia(int x, int y){
    float pot = 1;
    for(int i = 0; i<y; i++){
        pot *= x;
    }
    return pot;
}
void multi_parentesis(char entrada [n]){
    int longitud = strlen(entrada);
    for(int i = 0; entrada[i] != '\0'; i++){
        if(entrada[i] == ')' && (entrada[i+1] == '(' || entrada[i+1] > 47 && entrada[i+1] < 58)){
            for(int j = longitud-1; j > i; j--){
                entrada[j+1] = entrada[j];
            }
            entrada[i+1] = '*';
        }else{
            if(i != 0 && entrada[i] == '(' && entrada[i-1] > 47 && entrada[i-1] < 58){
            for(int j = longitud-1; j >= i; j--){
                entrada[j+1] = entrada[j];
            }
            entrada[i] = '*';
            }
        }
    }
    printf("\nLa cadena resultado es:\n");
    for(int j=0; entrada[j] != '\0'; j++){
        printf("%c", entrada[j]);
    }
}
void Procedimiento(char entrada[n], char postfija[n]){
    float resultado = 0;
    int error = 0, func_multi = 0;
    char o_tilde = 162;
    if(DetectarErrores(entrada) == 0){
        funciones_tri(entrada);
        multi_parentesis(entrada);
        ConversionInfijaAPostfija(entrada, postfija);
        printf("Conversion infija: ");
        for(int i=0; postfija[i] != '\0'; i++){
            printf("%c", postfija[i]);
        }
        printf("\n");
        resultado = ObtenerResultado(postfija, &error);
        if(error == 0){
            printf("El resultado es: %.4f", resultado);
        }else{
            printf("ERROR: Divisi%cn entre cero", o_tilde);
        }
    }
}
int DetectarErrores(char entrada[n]){
    int resultado = 0;
    /*if(error_lexico(entrada) == 1){
        resultado = 1;
    }
    else{
        if(error_sintactico(entrada) == 1){
            resultado = 1;
        }
    }*/
    return resultado;
}
int error_lexico(char entrada[n]){
    int resultado = 1, m;
    /*char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        if(es_digito(entrada[i]) == 1 || es_operador(entrada[i]) == 1){
            resultado = 0;
            continue;
        }
        else{
            resultado = 1;
            printf("Error l%cxico.\n", e_tilde);
            if(entrada[i]=='.'){
                decimal(entrada);
                break;
            }
            else{
                printf("Observaci%cn.\nError en el car%cter inv%clido '%c'\n", o_tilde, a_tilde, a_tilde, entrada[i]);
                break;
            }
        }
    }*/
    return resultado;
}
int error_sintactico(char entrada[n]){
    int resultado = 0, m;
    /*char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    if(parentesis_paridad(entrada) != 0){
        for(int i=0; i<m; i++){
            if(entrada[i] == '(' || entrada[i] == ')'){
                continue;
            }
            if(es_operador(entrada[i]) == 1 && es_operador(entrada[i+1]) == 1 && entrada[i+1] != '(' && entrada[i+1] != ')'){
                resultado = 1;
                printf("Error sint%cctico. \n", a_tilde);
                printf("Observaci%cn. \nError en la secuencia '%c%c'\n", o_tilde, entrada[i], entrada[i+1]);
                break;
            }
            else{
                resultado = 0;
            }
        }
    }
    else{
        printf("Error sint%cctico. \n", a_tilde);
        printf("Observaci%cn. \nError debido a falta de un par%cntesis.\n", o_tilde, e_tilde);
        resultado = 1;
    }
    if(resultado == 0){
        if(parentesis_vacio(entrada) == 1){
            resultado = 1;
        }
        if(validacion_caracter(entrada) == 1){
            resultado = 1;
        }
    }*/
    return resultado;
}
int es_digito(char car){
    int resultado = 0;
    if(car>47 && car<58){
        resultado = 1;
    }
    return resultado;
}
int es_operador(char car){
    int resultado = 0;
    switch(car){
        case'+': case'-': case'*': case'/': case '^': case'(': case ')': resultado = 1; break;
    }
    return resultado;
}
int longitud_cadena_errores(char entrada[n]){
    /*int i = 0;
    for(i=0; entrada[i] != '\0'; i++){
    }
    return i-1;*/
}
void decimal(char entrada[n]){
    /*int m;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        if(entrada[i] == '.'){
            if(i != 0 && i+1 != m){
                printf("Observaci%cn. \nError en la secuencia '%c%c%c'\n", o_tilde, entrada[i-1], entrada[i], entrada[i+1]);
                break;
            }
            else{
                if(i == 0 && i+1 != m){
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\n", o_tilde, entrada[i], entrada[i+1]);
                    break;
                }else{
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\n", o_tilde, entrada[i-1], entrada[i]);
                }
            }
        }
    }*/
}
int parentesis_paridad(char entrada[n]){
    int b = 0, c = 0, resultado = 0, m;
    /*m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        switch(entrada[i]){
            case '(': b++; break;
            case ')': c++; break;
        }
    }
    if(c == b){
        resultado = 1;
    }*/
    return resultado;
}
int parentesis_vacio(char entrada[n]){
    int m, resultado = 0;
    /*char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        if(entrada[i] == '(' && entrada[i+1] == ')'){
            resultado = 1;
            printf("Error sint%cctico. \n", a_tilde);
            printf("Observaci%cn.\nError en la secuencia '()'\n", o_tilde);
            break;
        }
    }*/
    return resultado;
}
int validacion_caracter(char entrada[n]){
    int resultado = 0, f, m;
    /*char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    if(es_operador(entrada[0]) == 1 && entrada[0] != '('){
        resultado = 1;
        printf("Error sint%cctico. \n", a_tilde);
        printf("Observaci%cn.\nError en la secuencia '%c%c'\n", o_tilde, entrada[0], entrada[1]);
    }else{
        f = longitud_cadena_errores(entrada) - 1;
        if(es_operador(entrada[f]) == 1 && entrada[f] != ')'){
            resultado = 1;
            printf("Error sint%cctico. \n", a_tilde);
            printf("Observaci%cn.\nError en la secuencia '%c%c'\n", o_tilde, entrada[f-1], entrada[f]);
        }
    }
    if(resultado == 0){
        m = longitud_cadena_errores(entrada);
        for(int i=1; i<m; i++){
            if(es_operador(entrada[i]) == 1 && entrada[i] != '(' && entrada[i] != ')' && entrada[i-1] == '(' && entrada[i+1] == ')'){
                resultado = 1;
                printf("Error sint%cctico. \n", a_tilde);
                printf("Observaci%cn. \nError en la secuencia '%c%c%c'\n", o_tilde, entrada[i-1], entrada[i], entrada[i+1]);
                break;
            }else{
                if(es_operador(entrada[i]) == 1 && entrada[i] != '(' && entrada[i] != ')' && entrada[i+1] == ')'){
                    resultado = 1;
                    printf("Error sint%cctico. \n", a_tilde);
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\n", o_tilde, entrada[i], entrada[i+1]);
                    break;
                }
            }
        }
        if(resultado==0 && parentesis_operador(entrada)==1){
                resultado=1;
                return resultado;
        }
    }*/
    return resultado;///cuidado
}
int parentesis_operador(char entrada[n]){
    int m, resultado = 0;
    /*char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    for(int i=1;i<m;i++){
        if(entrada[i] == '('){
           if(entrada[i-1] == ')' || es_digito(entrada[i-1]) == 1){
            resultado = 1;
            printf("Error sint%cctico. \n", a_tilde);
            printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador antes del par%cntesis.\n",o_tilde,entrada[i-1],entrada[i],e_tilde);
            break;
            }
        }
        else{
            if(entrada[i]==')'){
                if(entrada[i+1]=='('|| es_digito(entrada[i+1])==1){
                    resultado=1;
                    printf("Error sint%ctico. \n",a_tilde);
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador despu%cs del par%cntesis.\n",o_tilde,entrada[i],entrada[i+1],e_tilde,e_tilde);
                    break;
                   }
            }
        }
    }*/
    return resultado;
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
	return resultado;
}

void funciones_tri(char entrada [n]){
    int I = 0;
    char operador, trig[10];
    for(int i = 0; entrada[i] != '\0'; i++){
        if(entrada[i] > 96 && entrada [i] < 123){
            for(int j = i; entrada[j] != '('; j++){
                trig[I] = entrada[j];
                I++;
            }
            if (Encontrar_cadena("sqrt",trig) == 1) operador = 'a';
            else if (Encontrar_cadena("sin",trig ) == 1) operador = 'b';
            else if (Encontrar_cadena("cos",trig) == 1) operador = 'c';
            else if (Encontrar_cadena("tan",trig) == 1) operador = 'd';
            else if (Encontrar_cadena("cot",trig) == 1) operador = 'e';
            else if (Encontrar_cadena("sec",trig) == 1) operador = 'f';
            else if (Encontrar_cadena("csc",trig) == 1) operador = 'g';
            else if (Encontrar_cadena("arcsin",trig) == 1) operador = 'h';
            else if (Encontrar_cadena("arccos",trig ) == 1) operador = 'i';
            else if (Encontrar_cadena("arctan",trig ) == 1) operador = 'j';
            else if (Encontrar_cadena("arccot",trig) == 1) operador = 'k';
            else if (Encontrar_cadena("arcsec",trig ) == 1) operador = 'l';
            else if (Encontrar_cadena("arccsc",trig) == 1) operador = 'm';
            entrada[i] = operador;
            printf("Se supone que %c y %c son iguales",entrada[i],operador);
            for(int j = (I+i); entrada[j] != '\0'; j++){
                entrada[j-(I-1)] = entrada[j];
            }
            I = 0;
        }
        if(entrada[i+1] == 10){
            entrada[i+2] = '\0';
            entrada[i+3] = '\0';
        }
    }
}
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]){
    int longitud;
    longitud = strlen(entrada);
	entrada[longitud] = '_';
	entrada[longitud+1] = '\0';
	pos(entrada, postfija);
	for(int i=0; postfija[i] != '\0'; i++){
        if(postfija[i] == 10){
            for(int j=i; postfija[j] != '\0'; j++){
                postfija[j] = postfija[j+1];
            }
        }
	}
	printf("\n");
	for(int i=0; postfija[i] != '\0'; i++){
        printf("%c", postfija[i]);
	}
	printf("\n");
}
void pos(char entrada[n], char postfija[n]){
	struct PILAA pila;
	int i, j;
	char elemento;
	int operando (char c);
	int prioridad (char op1, char op2);
	char tope (struct PILAA p);
	void init_pila (struct PILAA *p);
	int pila_vacia (struct PILAA *p);
	void ins_pila (struct PILAA *p,char s);
	void retira_pila (struct PILAA *p,char *s);
	i = 0;
	j = -1;
	init_pila (&pila);
	while(entrada[i] != '_') {
	   if(operando(entrada[i]) == 1){
            postfija [++j] = entrada[i++];
	   }
	   else{
		     while (!pila_vacia (&pila) && prioridad(tope (pila), entrada[i])){
			     retira_pila (&pila, &elemento);
			     postfija[++j] = elemento;
		      }
		      if(operando(postfija[j]) == 1){
                postfija[++j] = ',';
                }
		      if (entrada[i] == ')')
			   retira_pila(&pila, &elemento);
		      else ins_pila(&pila, entrada[i]);
		      i++;
		}
	}
	while (!pila_vacia (&pila)){
		retira_pila (&pila, &elemento);
		postfija[++j] = elemento;
	}
	postfija[++j] = '\0';
}
int operando (char c){
	if  (c != '+' &&
         c != '-' &&
         c != '*' &&
		 c != '/' &&
		 c != '^' &&
		 c != ')' &&
		 c != '(' &&
         c != 'a' &&
         c != 'b' &&
         c != 'c' &&
         c != 'd' &&
         c != 'e' &&
         c != 'f' &&
         c != 'g' &&
         c != 'h' &&
         c != 'i' &&
         c != 'j' &&
         c != 'k' &&
         c != 'l' &&
         c != 'm' &&
         c != ','
    ){
        return 1;
    }
    return 0;
}
int priori[6][7] ={
	{ 1,1,0,0,0,0,1 },
	{ 1,1,0,0,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,1,0,1 },
	{ 0,0,0,0,0,0,0 }
};
int prioridad (char op1, char op2)
{
	int i,j,prioridaad;

	if (op1=='+') i=0;
	else if (op1=='-') i=1;
	else if (op1=='*') i=2;
	else if (op1=='/') i=3;
	else if (op1=='^') i=4;
	else if (op1=='!') i=5;
	else if (op1=='%') i=6;
	else if (op1=='a') i=7;
	else if (op1=='b') i=8;
	else if (op1=='c') i=9;
	else if (op1=='d') i=10;
	else if (op1=='e') i=11;
	else if (op1=='f') i=12;
	else if (op1=='g') i=13;
	else if (op1=='h') i=14;
	else if (op1=='i') i=15;
	else if (op1=='j') i=16;
	else if (op1=='k') i=17;
	else if (op1=='l') i=18;
	else if (op1=='m') i=19;
	else if (op1=='(') i=20;
	else if (op1==')') j=21;

    if (op2=='+') j=0;
	else if (op2=='-') j=1;
	else if (op2=='*') j=2;
	else if (op2=='/') j=3;
	else if (op2=='^') j=4;
	else if (op2=='!') j=5;
	else if (op2=='%') j=6;
	else if (op2=='a') j=7;
	else if (op2=='b') j=8;
	else if (op2=='c') j=9;
	else if (op2=='d') j=10;
	else if (op2=='e') j=11;
	else if (op2=='f') j=12;
	else if (op2=='g') j=13;
	else if (op2=='h') j=14;
	else if (op2=='i') j=15;
	else if (op2=='j') j=16;
	else if (op2=='k') j=17;
	else if (op2=='l') j=18;
	else if (op2=='m') j=19;
	else if (op2=='(') j=20;

	prioridaad=priori[i][j];
	return (prioridaad);
}
char tope(struct PILAA p){
	return (p.a[p.t-1]);
}
void init_pila(struct PILAA *p){
	p->t = 0;
}
int pila_vacia (struct PILAA *p){
    return(!p->t);
}
void ins_pila(struct PILAA *p, char s){
	if(p->t == n){
        printf ("Pila llena");
	}
	else{
        p->t++;
        p->a [p->t - 1] = s;
	}
}
void retira_pila(struct PILAA *p, char *s){
    if(pila_vacia(p)){
        printf ("Pila vacia");
		*s = '_';
	}else{
	    *s = p->a [p->t - 1];
        p->t--;
	}
}
float ObtenerResultado(char postfija[n], int *error){
    nodo_float *pila;
    int I = 0;
    char valor[n];
    float operando1, operando2, resultado, valor_float;
    pila = crear_pila_float(pila);
    for(int i=0; postfija[i] != '\0'; i++){
        if(postfija[i] >= 48 && postfija[i] <=57 || postfija[i] == '.'){
            for(int j = i; postfija[j] >= 48 && postfija[j] <=57 || postfija[j] == '.'; j++){
                valor[I] = postfija[j];
                I++;
                if(postfija[j+1] >= 48 && postfija[j+1] <= 57 || postfija[j+1] == '.'){
                    i++;
                }
            }
            printf("\n\nLa cadena char valor es: ");
            for(int j=0; valor[j] != '\0'; j++){
                printf("%c", valor[j]);
            }
            printf("\n\n\n\n\n");
            valor_float = atof(valor);
            pila = push_float(valor_float, pila);
            for(int j=0; j<40; j++){
                valor[j] = '\0';
            }
            I = 0;
        }else{
            if(postfija[i] == '+' || postfija[i] == '-' || postfija[i] == '*' || postfija[i] == '/' || postfija[i] == '^'){
                pila = pop_float(&operando2, pila);
                pila = pop_float(&operando1, pila);
                resultado = operacion(operando1, operando2, postfija[i], &*error);
                pila = push_float(resultado, pila);
            }else{
                if(postfija[i] == 'a' || postfija[i] == 'b' || postfija[i] == 'c' || postfija[i] == 'd' || postfija[i] == 'e'
                   || postfija[i] == 'f' || postfija[i] == 'g' || postfija[i] == 'h' || postfija[i] == 'i' || postfija[i] == 'j'
                   || postfija[i] == 'k' || postfija[i] == 'l' || postfija[i] == 'm' || postfija[i] == '!' || postfija[i] == '%'){
                    pila = pop_float(&operando1, pila);
                    resultado = operacion_trig(operando1, postfija[i], &*error);
                    pila = push_float(resultado, pila);
                }else{
                    continue;
                }
            }
        }
        if(postfija[i+1] == 10){
            postfija[i+2] = '\0';
            postfija[i+3] = '\0';
            postfija[i+4] = '\0';
            postfija[i+5] = '\0';
            postfija[i+6] = '\0';
        }
    }
    return pila -> valor;
}
nodo_float *crear_pila_float(nodo_float *pila){
    return pila = NULL;
}
nodo_float *push_float(float valor, nodo_float *pila){
    nodo_float *nodo_nuevo;
    nodo_nuevo = (nodo_float *) malloc(sizeof(nodo_float));
    if(nodo_nuevo != NULL){
        nodo_nuevo -> valor = valor;
        nodo_nuevo -> siguiente = pila;
        pila = nodo_nuevo;
    }
    return pila;
}
nodo_float *pop_float(float *valor, nodo_float *pila){
    nodo_float *nodo_auxiliar;
    float dato;
    if(pila == NULL){

    }
    else{
        nodo_auxiliar = pila;
        dato = nodo_auxiliar ->valor;
        pila = nodo_auxiliar ->siguiente;
        *valor = dato;
        free(nodo_auxiliar);
    }
    return pila;
}
float operacion(float operando1, float operando2, char operador, int *error){
    switch(operador){
        case '+': return operando1 + operando2; break;
        case '-': return operando1 - operando2; break;
        case '*': return operando1 * operando2; break;
        case '/':
            if(operando2 == 0){
                *error = 1; break;
            }else{
                return operando1 / operando2; break;
            }
        case '^': return potencia(operando1, operando2); break;
    }
}
float operacion_trig(float operando1, char operador, int *error){
    puts("Estamos en los trigonometricos");
    printf("%f\n\n",1/(asin(operando1)));
        if (operador == 'a') return sqrt(operando1);
        else if (operador == 'b') return sin(operando1);
        else if (operador == 'c') return cos(operando1);
        else if (operador == 'd') return tan(operando1);
        else if (operador == 'e') return 1/tan(operando1);
        else if (operador == 'f') return 1/cos(operando1);
        else if (operador == 'g') return 1/sin(operando1);
        else if (operador == 'h') return asin(operando1);
        else if (operador == 'i') return acos(operando1);
        else if (operador == 'j') return atan(operando1);
        else if (operador == 'k') return 1/atan(operando1);
        else if (operador == 'l') return 1/acos(operando1);
        else if (operador == 'm') return 1/(asin(operando1));
        else if (operador == '!') return factorial(operando1);
        else if (operador == '%') return operando1/100;
}
int factorial(float operando){
    int fact = 1;
    for(int i=1; i<=operando; i++){
        fact *= i;
    }
    return fact;
}
