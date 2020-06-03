#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#define n 40
///Funciones PRINCIPALES
void Procedimiento(char entrada[n], char postfija[n]);
int DetectarErrores(char entrada[n]);
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]);
float ObtenerResultado(char postfija[n], int *);
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
struct PILAA {
	int t;
	char a[n];
};
void pos(char entrada[n], char postfija[n]);
///Funciones secundarias pertenecientes a la función 'ObtenerResultado'
struct struct_nodo_float{
    char valor;
    struct struct_nodo_float *siguiente;
};
typedef struct struct_nodo_float nodo_float;
nodo_float *crear_pila_float(nodo_float *pila);
nodo_float *push_float(float valor, nodo_float *pila);
nodo_float *pop_float(float *valor, nodo_float *pila);
float operacion(float operando1, float operando2, char operador, int *);
///Funciones secundarias
int potencia(int x, int y);
///Variables globales útiles
char entrada[n], postfija[n];
///Variables globales de impresión(código ASCII para las letras con tildes)
char a_tilde = 160, o_tilde = 162;
int main(){
    printf("Ingrese la expresi%cn:\n", o_tilde);
    fflush(stdin);
    fgets(entrada, n, stdin);
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
void Procedimiento(char entrada[n], char postfija[n]){
    float resultado = 0;
    int error = 0;
    char o_tilde = 162;
    if(DetectarErrores(entrada) == 0){
        ConversionInfijaAPostfija(entrada, postfija);
        resultado = ObtenerResultado(postfija, &error);
        if(error == 0){
            printf("El resultado es: %.0f", resultado);
        }else{
            printf("ERROR: Divisi%cn entre cero", o_tilde);
        }
    }
}
int DetectarErrores(char entrada[n]){
    int resultado = 0;
    if(error_lexico(entrada) == 1){
        resultado = 1;
    }
    else{
        if(error_sintactico(entrada) == 1){
            resultado = 1;
        }
    }
    return resultado;
}
int error_lexico(char entrada[n]){
    int resultado = 1, m;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
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
    }
    return resultado;
}
int error_sintactico(char entrada[n]){
    int resultado = 0, m;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
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
    }
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
    int i = 0;
    for(i=0; entrada[i] != '\0'; i++){
    }
    return i-1;
}
void decimal(char entrada[n]){
    int m;
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
    }
}
int parentesis_paridad(char entrada[n]){
    int b = 0, c = 0, resultado = 0, m;
    m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        switch(entrada[i]){
            case '(': b++; break;
            case ')': c++; break;
        }
    }
    if(c == b){
        resultado = 1;
    }
    return resultado;
}
int parentesis_vacio(char entrada[n]){
    int m, resultado = 0;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
    m = longitud_cadena_errores(entrada);
    for(int i=0; i<m; i++){
        if(entrada[i] == '(' && entrada[i+1] == ')'){
            resultado = 1; /*Al encontrar un par de paréntesis vacíos, se sale del bucle*/
            printf("Error sint%cctico. \n", a_tilde);
            printf("Observaci%cn.\nError en la secuencia '()'\n", o_tilde);
            break;
        }
    }
    return resultado;
}
int validacion_caracter(char entrada[n]){
    int resultado = 0, f, m;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
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
    }
}
int parentesis_operador(char entrada[n]){
    int m, resultado = 0;
    char a_tilde = 160, e_tilde = 130, o_tilde = 162;
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
                    resultado=1; /*Aquí se verifica que no haya un número o paréntesis derecho antes de un paréntesis izquierdo*/
                    printf("Error sint%ctico. \n",a_tilde);
                    printf("Observaci%cn. \nError en la secuencia '%c%c'\nEs necesario la presencia de un operador despu%cs del par%cntesis.\n",o_tilde,entrada[i],entrada[i+1],e_tilde,e_tilde);
                    break;
                   }
            }
        }
    }
        return resultado;
}
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]){
    int longitud;
    longitud = strlen(entrada);
	entrada[longitud] = '.';
	entrada[longitud+1] = '\0';
	pos(entrada, postfija);
	for(int i=0; postfija[i] != '\0'; i++){
        if(postfija[i] == 10){
            for(int j=i; postfija[j] != '\0'; j++){
                postfija[j] = postfija[j+1];
            }
        }
	}
}
void pos(char entrada[n], char postfija[n]){
	struct PILAA pila;
	int i, j;
	char elemento;
	int operando (char c);
	int prioridad (char op1,char op2);
	char tope (struct PILAA p);
	void init_pila (struct PILAA *p);
	int pila_vacia (struct PILAA *p);
	void ins_pila (struct PILAA *p,char s);
	void retira_pila (struct PILAA *p,char *s);
	i = 0;
	j = -1;
	init_pila (&pila);
	while(entrada[i] != '.') {
	   if(operando(entrada[i]) )
		   postfija [++j] = entrada[i++];
	   else{
		     while (!pila_vacia (&pila)  &&
			 prioridad (tope (pila), entrada[i] ) )  {
			     retira_pila (&pila, &elemento);
			     postfija[++j] = elemento;
		      }
		      if (entrada[i] == ')')
			   retira_pila(&pila, &elemento);
		      else ins_pila(&pila, entrada[i]);
		      i++;
		}
	}
	while (!pila_vacia (&pila) ) {
		retira_pila (&pila, &elemento);
		postfija[++j] = elemento;
	}
	postfija[++j] = '\0';
}
int operando (char c){
	return ( c != '+' &&
		 c != '-' &&
		 c != '*' &&
		 c != '/' &&
		 c != '^' &&
		 c != ')' &&
		 c != '('    );
}

 int priori[6][7] =
 {
	{ 1,1,0,0,0,0,1 },
	{ 1,1,0,0,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,0,0,1 },
	{ 1,1,1,1,1,0,1 },
	{ 0,0,0,0,0,0,0 }
};

int prioridad (char op1,char op2){
	int i, j, prioridaad;
	switch (op1){
		case '+': i = 0; break;
		case '-': i = 1; break;
		case '*': i = 2; break;
		case '/': i = 3; break;
		case '^': i = 4; break;
		case '(': i = 5; break;
	}
	switch (op2){
		case '+': j = 0; break;
		case '-': j = 1; break;
		case '*': j = 2; break;
		case '/': j = 3; break;
		case '^': j = 4; break;
		case '(': j = 5; break;
		case ')': j = 6; break;
	}
	prioridaad = priori[i][j];
	return(prioridaad);
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
		*s = '.';
	}else{
	    *s = p->a [p->t - 1];
        p->t--;
	}
}
float ObtenerResultado(char postfija[n], int *error){
    nodo_float *pila;
    int longitud;
    char valor;
    float operando1, operando2, resultado;
    pila = crear_pila_float(pila);
    longitud = strlen(postfija);
    for(int i=0; i<longitud; i++){
        if(postfija[i] >= 48 && postfija[i] <=57){
            valor = postfija[i];
            pila = push_float(atof(&valor), pila);
        }else{
            pila = pop_float(&operando2, pila);
            pila = pop_float(&operando1, pila);
            resultado = operacion(operando1, operando2, postfija[i], &*error);
            pila = push_float(resultado, pila);
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
        printf("Pila Vacia\n");
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
