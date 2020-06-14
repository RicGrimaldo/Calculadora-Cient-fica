#include <windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define n 40

///Esta es una prueba de pull request (Git)
///Botones
HWND ventana,caja_texto;
HWND bsin,bcos,btan,bsec,bcsc,bcot,barcsin,barccos,barctan,barcsec,barccsc,barccot;
HWND bpot,bmul,bdiv,boff,bac,braiz,bsum,bfact,bporc,bpariz,bparder,bpunto,bresta,bresultado;
HWND b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;

///Etiquetas estáticas
HWND tipos_conversion,lbin,binl,loct,octl,lhex,hexl,lgrados,gradosl,font,fun_trigl;

///Función para ocultar la pantalla negra al ejecutarse el programa
void Ocultar_pantalla(void)
{
    HWND console;
    AllocConsole();
    console = FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(console,0);
}
struct PILAA {
	int t;
	char a[n];
};
struct struct_nodo_float{
    float valor;
    struct struct_nodo_float *siguiente;
};
typedef struct struct_nodo_float nodo_float;

///Funciones necesarias
char enteroACaracter(int numero);
int limite_cadena(char cad[n],HWND hwnd);
int Encontrar_cadena2 (char cad1[n],char cad2[n]);
int factorial(float operando);

///Funciones de conversiones

void conversion_hex(float resultado);
void conversion_oct (float resultado);
void conversion_bin (float resultado);
 void conversion_grados(float resultado);

///Funciones de validación
int esDigito (char car);
int es_operador(char car);
int letras_permitidas (char car);
int Primer_letra_funcion(char a);
int encontrarCaracter(char cad[n], char car);
int decimal(char a[n],HWND hwnd);

///Funciones de 'errores' secundarias

int Encontrar_cadena (char cad1[n],char cad2[n]);
int parentesis_paridad(char a[n],HWND hwnd);
int parentesis_vacio(char a[n], HWND hwnd);
int validacion_caracter(char a[n],HWND hwnd);
int verificacion_funciones(HWND hwnd,char cad[n]);

///Funciones de 'errores' principales

int error_lexico(char a[n], HWND hwnd);
int error_sintatico(char a[n],HWND hwnd);
int Detectar_Errores(char a[n],HWND hwnd);

///Funciones pertenecientes para calcular el resultado

int potencia(int x, int y);
void multi_parentesis(char entrada [n]);
void funciones_tri(char entrada [n]);
int operando (char c);
int priori[21][22]={
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Suma
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Resta
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Multiplicacion
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Division
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Exponente
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///SQRT
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Factorial
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Porcentaje
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Sin
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Cos
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Tan
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Cot
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Sec
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Csc
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arcsin
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arccos
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arctan
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arccot
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arcsec
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arccsc
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  ///Parentesis izquierdo
};
int prioridad (char op1, char op2);

///Funciones para la pila
char tope(struct PILAA p);
void init_pila(struct PILAA *p);
int pila_vacia (struct PILAA *p);
void ins_pila(struct PILAA *p, char s);
void retira_pila(struct PILAA *p, char *s);
nodo_float *crear_pila_float(nodo_float *pila);
nodo_float *push_float(float valor, nodo_float *pila);
nodo_float *pop_float(float *valor, nodo_float *pila);

///Funciones para el resultado
void pos(char entrada[n], char postfija[n]);
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]);
float operacion(float operando1, float operando2, char operador, int *error,HWND hwnd);
float operacion_trig(float operando1, char operador, int *error,HWND hwnd);
float ObtenerResultado(char postfija[n], int *error, HWND hwnd);

///Función principal
void Procedimiento(char entrada[n], char postfija[n], HWND hwnd);

///Interfaz gráfica
LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam);

char app[] = "Calculadora";
int WINAPI WinMain(HINSTANCE ins,HINSTANCE ins2,LPSTR cmd, int estado){
    //Ocultar_pantalla();
    WNDCLASSEX vtn;
    vtn.cbClsExtra=0;
    vtn.cbSize=sizeof(WNDCLASSEX);
    vtn.cbWndExtra = 0;
    vtn.hbrBackground = (HBRUSH) (COLOR_HIGHLIGHT+1);
    vtn.hCursor = LoadCursor(NULL,IDC_ARROW);
    vtn.hIcon = NULL;
    vtn.hIconSm = NULL;
    vtn.hInstance = ins;
    vtn.lpfnWndProc = winProc;
    vtn.lpszClassName = app;
    vtn.lpszMenuName = NULL;
    vtn.style = CS_HREDRAW | CS_VREDRAW;

    if(!RegisterClassEx(&vtn)){
        MessageBox(HWND_DESKTOP,"Error al crear la clase","Error",MB_ICONERROR|MB_OK);
    }

///Ventana principal

    ventana = CreateWindow(app,"Calculadora Científica basada en Win32 API",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,380,HWND_DESKTOP,NULL,ins,NULL);

///Caja de texto
    caja_texto = CreateWindow("EDIT","",WS_CHILD | WS_VISIBLE  | ES_LOWERCASE | WS_BORDER | ES_RIGHT,6,12,610,34,ventana,NULL,ins,NULL);

///Creación de etiquetas

    tipos_conversion = CreateWindow("STATIC","Tipos de conversion",WS_CHILD | WS_VISIBLE | SS_LEFT ,6,62,140,30,ventana,NULL,ins,NULL);
    lbin = CreateWindow("STATIC","Bin:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,116,30.1,29.75,ventana,NULL,ins,NULL);
    binl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,36.1,116,113.5,29.75,ventana,NULL,ins,NULL);
    loct = CreateWindow("STATIC","Oct:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,166,34.25,29.75,ventana,NULL,ins,NULL);
    octl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,166,105,29.75,ventana,NULL,ins,NULL);
    lhex = CreateWindow("STATIC","Hex:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,216,34.25,29.75,ventana,NULL,ins,NULL);
    hexl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,216,105,29.75,ventana,NULL,ins,NULL);
    lgrados = CreateWindow("STATIC","Grad:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,266,34.25,29.75,ventana,NULL,ins,NULL);
    gradosl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,266,105,29.75,ventana,NULL,ins,NULL);
    fun_trigl = CreateWindow("STATIC","Funciones trigonométricas",WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER ,166,62,228,30,ventana,NULL,ins,NULL);

///Creación de botones

    //Funciones trigonométricas

    bsin = CreateWindow("BUTTON","sin",WS_CHILD | WS_VISIBLE | SS_CENTER ,168,120,75,50,ventana,NULL,ins,NULL);
    bcos = CreateWindow("BUTTON","cos",WS_CHILD | WS_VISIBLE | SS_CENTER ,168,170,75,50,ventana,NULL,ins,NULL);
    btan = CreateWindow("BUTTON","tan",WS_CHILD | WS_VISIBLE | SS_CENTER ,168,220,75,50,ventana,NULL,ins,NULL);
    bcsc = CreateWindow("BUTTON","csc",WS_CHILD | WS_VISIBLE | SS_CENTER ,243,120,75,50,ventana,NULL,ins,NULL);
    bsec = CreateWindow("BUTTON","sec",WS_CHILD | WS_VISIBLE | SS_CENTER ,243,170,75,50,ventana,NULL,ins,NULL);
    bcot = CreateWindow("BUTTON","cot",WS_CHILD | WS_VISIBLE | SS_CENTER ,243,220,75,50,ventana,NULL,ins,NULL);
    barcsin = CreateWindow("BUTTON","arcsin",WS_CHILD | WS_VISIBLE | SS_CENTER ,318,120,75,50,ventana,NULL,ins,NULL);
    barccos = CreateWindow("BUTTON","arccos",WS_CHILD | WS_VISIBLE | SS_CENTER ,318,170,75,50,ventana,NULL,ins,NULL);
    barctan = CreateWindow("BUTTON","arctan",WS_CHILD | WS_VISIBLE | SS_CENTER ,318,220,75,50,ventana,NULL,ins,NULL);

    //Operaciones principales y básicas

    bpot = CreateWindow("BUTTON","^",WS_CHILD | WS_VISIBLE | SS_CENTER ,405,65,45,45,ventana,NULL,ins,NULL);
    braiz = CreateWindow("BUTTON","sqrt(x)",WS_CHILD | WS_VISIBLE | SS_CENTER ,405,110,45,45,ventana,NULL,ins,NULL);
    bfact = CreateWindow("BUTTON","x!",WS_CHILD | WS_VISIBLE | SS_CENTER ,405,155,45,45,ventana,NULL,ins,NULL);
    bporc = CreateWindow("BUTTON","%",WS_CHILD | WS_VISIBLE | SS_CENTER ,405,200,45,45,ventana,NULL,ins,NULL);
    bpariz = CreateWindow("BUTTON","(",WS_CHILD | WS_VISIBLE | SS_CENTER ,405,245,45,45,ventana,NULL,ins,NULL);
    bmul = CreateWindow("BUTTON","*",WS_CHILD | WS_VISIBLE | SS_CENTER ,450,65,45,45,ventana,NULL,ins,NULL);
    b7 = CreateWindow("BUTTON","7",WS_CHILD | WS_VISIBLE | SS_CENTER ,450,110,45,45,ventana,NULL,ins,NULL);
    b4 = CreateWindow("BUTTON","4",WS_CHILD | WS_VISIBLE | SS_CENTER ,450,155,45,45,ventana,NULL,ins,NULL);
    b1 = CreateWindow("BUTTON","1",WS_CHILD | WS_VISIBLE | SS_CENTER ,450,200,45,45,ventana,NULL,ins,NULL);
    bparder = CreateWindow("BUTTON",")",WS_CHILD | WS_VISIBLE | SS_CENTER ,450,245,45,45,ventana,NULL,ins,NULL);
    bdiv = CreateWindow("BUTTON","/",WS_CHILD | WS_VISIBLE | SS_CENTER ,495,65,45,45,ventana,NULL,ins,NULL);
    b8 = CreateWindow("BUTTON","8",WS_CHILD | WS_VISIBLE | SS_CENTER ,495,110,45,45,ventana,NULL,ins,NULL);
    b5 = CreateWindow("BUTTON","5",WS_CHILD | WS_VISIBLE | SS_CENTER ,495,155,45,45,ventana,NULL,ins,NULL);
    b2 = CreateWindow("BUTTON","2",WS_CHILD | WS_VISIBLE | SS_CENTER ,495,200,45,45,ventana,NULL,ins,NULL);
    b0 = CreateWindow("BUTTON","0",WS_CHILD | WS_VISIBLE | SS_CENTER ,495,245,45,45,ventana,NULL,ins,NULL);
    boff = CreateWindow("BUTTON","OFF",WS_CHILD | WS_VISIBLE | SS_CENTER ,540,65,45,45,ventana,NULL,ins,NULL);
    b9 = CreateWindow("BUTTON","9",WS_CHILD | WS_VISIBLE | SS_CENTER ,540,110,45,45,ventana,NULL,ins,NULL);
    b6 = CreateWindow("BUTTON","6",WS_CHILD | WS_VISIBLE | SS_CENTER ,540,155,45,45,ventana,NULL,ins,NULL);
    b3 = CreateWindow("BUTTON","3",WS_CHILD | WS_VISIBLE | SS_CENTER ,540,200,45,45,ventana,NULL,ins,NULL);
    bpunto = CreateWindow("BUTTON",".",WS_CHILD | WS_VISIBLE | SS_CENTER ,540,245,45,45,ventana,NULL,ins,NULL);
    bac = CreateWindow("BUTTON","AC",WS_CHILD | WS_VISIBLE | SS_CENTER ,585,65,45,45,ventana,NULL,ins,NULL);
    bsum = CreateWindow("BUTTON","+",WS_CHILD | WS_VISIBLE | SS_CENTER ,585,110,45,45,ventana,NULL,ins,NULL);
    bresta = CreateWindow("BUTTON","-",WS_CHILD | WS_VISIBLE | SS_CENTER ,585,155,45,45,ventana,NULL,ins,NULL);
    bresultado = CreateWindow("BUTTON","=",WS_CHILD | WS_VISIBLE | SS_CENTER ,585,200,45,90,ventana,NULL,ins,NULL);


    if(!ventana){
        MessageBox(HWND_DESKTOP,"Error al crear la ventana","Error",MB_ICONERROR|MB_OK);

    }

    ShowWindow(ventana,SW_SHOWNORMAL);
    MSG msj;

    while(GetMessage(&msj,NULL,0,0)){
        DispatchMessage(&msj);
        TranslateMessage(&msj);

    }

    return (int) msj.wParam;

}
char enteroACaracter(int numero){
	return numero + '0';
}
int limite_cadena(char cad[n],HWND hwnd)
 {
     int error = 0;
     if(strlen(cad) >= 31)
     {
        MessageBox(hwnd,"Se excedió el límite de carácteres permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
        return error = 1;
     }
    else
        return error = 0;
 }
 int Encontrar_cadena2 (char cad1[n],char cad2[n]){
	int resultado = 1;
	for(int i=0; cad1[i] != '\0'; i++){
        if(cad1[i] != cad2[i]){
            resultado = 0;
            break;
        }
    }
	return resultado;
}
int factorial(float operando){
    int fact = 1;
    for(int i=1; i<=operando; i++){
        fact *= i;
    }
    return fact;
}
void conversion_hex(float resultado){
    char hextxt[33];
    int res;
    if(resultado<=999999999){
    res=trunc(resultado);
    ltoa(res, hextxt,16);
    SetWindowText(hexl,hextxt);
    }
    else SetWindowText(octl,"Límite rebasado");
}
void conversion_oct (float resultado)
{
    char octtxt[33];
    int res;
    if(resultado<=99999990){
    res=trunc(resultado);
    ltoa(res, octtxt, 8);
    SetWindowText(octl,octtxt);
    }
    else SetWindowText(octl,"Límite rebasado");
}

void conversion_bin (float resultado)
{
    char bintxt[50];
    int res;
    res = trunc(resultado);
    if(resultado<=16300){
    ltoa(res,bintxt,2);
    SetWindowText(binl,bintxt);
    }
    else SetWindowText(binl,"Límite rebasado");
}

 void conversion_grados(float resultado){
    float dec,ope1,ope2;
    int grados,minutos,segundos;
	char m[30],s[30],res[33];
	if(resultado<=9999999){
    grados=trunc(resultado);
    dec=resultado-grados;
    ope1=dec*60;
    minutos=trunc(ope1);
    ope2=ope1-minutos;
    segundos=ope2*60;
	itoa(grados,res,10);
	itoa(minutos,m,10);
	itoa(segundos,s,10);
	strcat(res,"° "); strcat(res,m); strcat(res," ' "); strcat(res,s); strcat(res,"''");
	SetWindowText(gradosl,res);
	}
	else SetWindowText(gradosl,"Límite rebasado");
}
int esDigito (char car){
    int resultado=0;
    if(car>47 && car<58){
            return resultado=1;
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
        case 'a': case'c': case 'n': case'e': case'i': case 'o': case'r': case 's': case 't': case 'q':resultado=1;
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

int encontrarCaracter(char cad[n], char car){
     int r=0;
     for(int i=0;i<strlen(cad);i++){
        if(cad[i]==car){
            r=i+1;
            break;
        }
     }
     return r-1;
 }

int decimal(char a[n],HWND hwnd){

    int error = 0,x;
    x = encontrarCaracter(a,'.');
    for(int i=x+1;i<strlen(a);i++){
            if(esDigito(a[i])==1) continue;
        if(es_operador(a[i]) == 1 && a[i]!= '.'){
            break;
        }
        else{
            if(a[i] == '.')
                MessageBox(hwnd,"El número decimal únicamente debe llevar un solo punto.","Error léxico",MB_ICONWARNING | MB_OK);
                return error = 1;
        }
    }

    return error;
}
int Encontrar_cadena (char cad1[n],char cad2[n]){
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
	if(i<strlen(cad1)) return resultado=0;
	return resultado;
}

int parentesis_paridad(char a[n],HWND hwnd){
    int b=0,c=0,error=0,m; /*Contadores para contar cantidad de paréntesis en la cadena*/
    m=strlen(a);
    for(int i=0;i<m;i++){
        if(a[i]=='(') b++;
        if(a[i]==')') c++;
        }
        if(c>b){
            error = 1;
            MessageBox(hwnd,"Error de paréntesis","Error sintáctico",MB_ICONWARNING | MB_OK);
            return error;
        }
    if(c!=b){
            error=1;
            MessageBox(hwnd,"Error debido a falta de un parentesis","Error sintáctico",MB_ICONWARNING | MB_OK);
    }
    return error;
}

int parentesis_vacio(char a[n], HWND hwnd){
    int error=0;
    for(int i=0;i<strlen(a);i++){
        if(a[i]=='('&& a[i+1]==')' && a[i+1]!='\0'){/*Al encontrar un par de paréntesis vacíos, se sale del bucle*/
                MessageBox(hwnd,"Error al haber dejado un par de paréntesis vacíos","Error sintáctico",
                           MB_ICONWARNING | MB_OK);
                return error=1;
        }
    }
    return error;
}

int validacion_caracter(char a[n],HWND hwnd){
	int error=0,f;
	if(es_operador(a[0])==1 && a[0]!='(' && a[0]!='-' && esDigito(a[0])==0){
		error=1; /*Validará que el primer carácter no sea ningún operador a excepción del '(', y cualquier primer letra de las funciones*/
        MessageBox(hwnd,"Error con el primer carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
		}
	else{///Caso especial si es una letra
		if(letras_permitidas(a[0])==1 && Primer_letra_funcion(a[0])==0){
			error = 1;
			MessageBox(hwnd,"Error en el primer carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
		}
	}

	if(error == 0){
	f=strlen(a)-1;
	if(a[f]!=')' && a[f]!='!' && a[f]!='%' && es_operador(a[f])==1 || letras_permitidas(a[f])==1 ){
		error=1; /*Validará que el último carácter no sea un operador a excepción de ')', ! y %*/
		MessageBox(hwnd,"Error con el último carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
	}
	}

	if(error==0){
		for(int i=1;i<strlen(a),a[i+1]!='\0';i++){
			if(a[i-1]=='(' && es_operador(a[i])==1 && a[i]!='(' && a[i]!='-' && esDigito(a[i])==0){
				/*Validará que el primer carácter no sea ningún operador a excepción del '(', y cualquier primer letra de las funciones*/
                MessageBox(hwnd,"Error con el primer carácter después del paréntesis","Error sintáctico",
                           MB_ICONWARNING | MB_OK);
                           return error = 1;
			}
			else{///Caso especial si es una letra errónea con la que se empieza una función
				if(a[i-1]=='(' && letras_permitidas(a[i])==1 && Primer_letra_funcion(a[i])==0){
					MessageBox(hwnd,"Error con el primer carácter después del paréntesis","Error sintáctico",
                               MB_ICONWARNING | MB_OK);
                    return error = 1;
				}
				else{
					if(es_operador(a[i-1])==1 && a[i]==')' && a[i-1]!='!' && a[i-1]!='%' && a[i-1]!=')'){
                    /*Aquí se verifica que no haya un operador antes de un paréntesis cerrado*/
						MessageBox(hwnd,"Error con el carácter antes del paréntesis cerrado","Error sintáctico",
                                   MB_ICONWARNING | MB_OK);
						return error = 1;
					}
				}
			}
			}
	}

		return error;
	}

int verificacion_funciones(HWND hwnd,char cad[n])
 {
     int error = 0;
     for(int i=0;i<strlen(cad);i++)
     {
         if(esDigito(cad[i])==0 && es_operador(cad[i])==0){
                if (Encontrar_cadena("sqrt(",cad) == 1)  error=0;
                else if (Encontrar_cadena("arccsc(",cad) == 1) error=0;
                else if (Encontrar_cadena("arcsec(",cad ) == 1) error=0;
                else if (Encontrar_cadena("arccot(",cad) == 1) error=0;
                else if (Encontrar_cadena("arctan(",cad ) == 1) error=0;
                else if (Encontrar_cadena("arccos(",cad ) == 1) error=0;
                else if (Encontrar_cadena("arcsin(",cad) == 1) error=0;
                else if (Encontrar_cadena("csc(",cad) == 1) error=0;
                else if (Encontrar_cadena("sec(",cad) == 1) error=0;
                else if (Encontrar_cadena("cot(",cad) == 1) error=0;
                else if (Encontrar_cadena("tan(",cad) == 1) error=0;
                else if (Encontrar_cadena("cos(",cad) == 1) error=0;
                else if (Encontrar_cadena("sin(",cad ) == 1) error=0;
                else error=1;
     }
     }
     if(error == 1) MessageBox(hwnd,"Es necesario escribir las funciones con la sintaxis correcta","Error sintáctico",
                               MB_ICONWARNING | MB_OK);
     return error;
 }
int error_lexico(char a[n], HWND hwnd){
    int error=1;
    for(int i=0;i<strlen(a);i++){
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
                    if(esDigito(a[i-1])==1 && esDigito(a[i+1])==1){
                        error = decimal(a,hwnd);
                        break;
                    }
                else{
                    MessageBox(hwnd,"Error en ubicación del punto decimal.","Error léxico",MB_ICONWARNING | MB_OK);
                    return error = 1;
                }
                }
                else{
                MessageBox(hwnd,"No se permiten caracteres inválidos","Error léxico",MB_ICONWARNING | MB_OK);
                return error = 1;
            /*Saliéndose del bucle*/
                }
        }
    } /*Devolverá 1 en caso de que se haya encontrado un error léxico, 0 en caso contrario*/
    return error;
}

int error_sintatico(char a[n],HWND hwnd){
    int error=0;
    if(parentesis_paridad(a,hwnd)!=1){ /*Primero, se validará si hay la misma cantidad de pares de paréntesis*/
    for(int i=0;i<strlen(a);i++){

        if(a[i]=='('||a[i]==')'){
                continue; /*Ignorará los operadores válidos, en este caso los paréntesis*/
        }
        if(es_operador(a[i])==1 && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!='!' && a[i+1]!='%'){
            /*Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis,
			factorial, porcentaje o que primero esté un signo negativo*/
			MessageBox(hwnd,"No es posible calcular con 2 operadores seguidos","Error sintáctico",MB_ICONWARNING | MB_OK);
			return error = 1;
        }
        else{
                 if(i>=2 && a[i]=='-' && a[i-1]=='('  && esDigito(a[i-1])==0){
                    MessageBox(hwnd,"Error con la ubicación del '-'","Error sintáctico",MB_ICONWARNING | MB_OK);
                    return error = 1;
                }
                else
            error = 0;
            /*El error será 0 en caso de que el carácter leído no haya presentado error*/
        }
    }
    }
    else{
        return error = 1;
        /*Habrá error sintático en caso de que la cantidad de pares de paréntesis sea diferente*/
    }
    if (parentesis_vacio(a,hwnd)==1) return error=1;
            /*Habrá error sintático en caso de haber paréntesis vacíos*/
    if(validacion_caracter(a,hwnd)==1) return error=1;
    /*Habrá error sintático en caso de haber un operador al inicio o al final de la sentencia*/
    if(verificacion_funciones(hwnd,a)==1) return error=1;
        else error = 0;

    return error;
}

int Detectar_Errores(char a[n],HWND hwnd){
	int error=0;
	if(limite_cadena(a,hwnd)==1) return error = 1;
	if(error_lexico(a,hwnd)==1) return error = 1;
	if(error_sintatico(a,hwnd)==1)return error = 1;
	return error;
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
    printf("Esta es la entrada: ");
    puts(entrada);
    for(int i = 0; i<strlen(entrada); i++){
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
    printf("Esta es la entrada: ");
    puts(entrada);
}

void funciones_tri(char entrada [n]){
    int I = 0, J = 0;
    char operador, trig[10];
    for(int i = 0; entrada[i] != '\0'; i++){
        if(entrada[i] > 96 && entrada [i] < 123){
            for(int j = i; entrada[j] != '('; j++){
                trig[I] = entrada[j];
                I++;
            }
            if (Encontrar_cadena2("sqrt",trig) == 1)            {operador = 'a'; J += 3;}
            else if (Encontrar_cadena2("sin",trig ) == 1)       {operador = 'b'; J += 2;}
            else if (Encontrar_cadena2("cos",trig) == 1)        {operador = 'c'; J += 2;}
            else if (Encontrar_cadena2("tan",trig) == 1)        {operador = 'd'; J += 2;}
            else if (Encontrar_cadena2("cot",trig) == 1)        {operador = 'e'; J += 2;}
            else if (Encontrar_cadena2("sec",trig) == 1)        {operador = 'f'; J += 2;}
            else if (Encontrar_cadena2("csc",trig) == 1)        {operador = 'g'; J += 2;}
            else if (Encontrar_cadena2("arcsin",trig) == 1)     {operador = 'h'; J += 5;}
            else if (Encontrar_cadena2("arccos",trig ) == 1)    {operador = 'i'; J += 5;}
            else if (Encontrar_cadena2("arctan",trig ) == 1)    {operador = 'j'; J += 5;}
            else if (Encontrar_cadena2("arccot",trig) == 1)     {operador = 'k'; J += 5;}
            else if (Encontrar_cadena2("arcsec",trig ) == 1)    {operador = 'l'; J += 5;}
            else if (Encontrar_cadena2("arccsc",trig) == 1)     {operador = 'm'; J += 5;}
            entrada[i] = operador;
            for(int j = (I+i); entrada[j] != '\0'; j++){
                entrada[j-(I-1)] = entrada[j];
            }
            I = 0;
        }
        if(entrada[i+1] == '\0'){
            for(int j = 0; j <= J; j++){
                entrada[(i+1)-j] = '\0';
            }
        }
    }
    printf("Esta es la cadena resultado:\n");
    puts(entrada);
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

    if (op2=='+') j=0;
	else if (op2=='-') j=1;
	else if (op2=='*') j=2;
	else if (op2=='/') j=3;
	else if (op2=='^') j=4;
	else if (op2=='a') j=5;
	else if (op2=='!') j=6;
    else if (op2=='%') j=7;
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
	else if (op1==')') j=21;

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
	}
	else{
        p->t++;
        p->a [p->t - 1] = s;
	}
}
void retira_pila(struct PILAA *p, char *s){
    if(pila_vacia(p)){
		*s = '_';
	}else{
	    *s = p->a [p->t - 1];
        p->t--;
	}
}
nodo_float *crear_pila_float(nodo_float *pila){
    return pila = NULL;
}
nodo_float *push_float(float valor, nodo_float *pila){
    nodo_float *nodo_nuevo;
    nodo_nuevo = (nodo_float *) malloc(sizeof(nodo_float));
    if(nodo_nuevo != NULL){
        nodo_nuevo -> valor = valor;
		printf("El valor guardado en la pila es: %f\n",nodo_nuevo->valor);
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
	void retira_pila (struct PILAA *p, char *s);
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
	printf("Postfija: \n");
	puts(postfija);
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
	puts(postfija);
}


float operacion(float operando1, float operando2, char operador, int *error,HWND hwnd){
    char a_tilde = 160, o_tilde = 162;
    switch(operador){
        case '+':
            /*if(operando1 > 999999999999999999 || operando2 > 999999999999999999){
                printf("Error de longitud");
                *error = 1;
                break;
            }else{*/
                return operando1 + operando2; break;
            //}
        case '-': return operando1 - operando2; break;
        case '*':
            if((operando1 > 99999999999999 && operando2 > 99999999999999) || (operando1 > 999999999999999999 && operando2 != 0 && operando2 != 1) || (operando2 > 999999999999999999 && operando1 != 0 && operando1 != 1)){
                MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return operando1 * operando2; break;
            }
        case '/':
            if(operando2 == 0){
                MessageBox(hwnd,"No es posible dividir entre cero","Error matemático",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return operando1 / operando2; break;
            }
        case '^':
            if((operando2 > 97 && operando1 != 1 && operando1 != 0 && operando1 != (-1))){
               MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                *error = 1;
                 break;
            }else{
                return potencia(operando1, operando2); break;
            }
    }
}
float operacion_trig(float operando1, char operador, int *error,HWND hwnd){
    char a_tilde = 160, i_tilde = 161, u_tilde = 163;
    puts("Estamos en funciones trigonometricas");
        switch(operador){
        case 'a':
            if(operando1 < 0){
                MessageBox(hwnd,"No es posible calcular la raíz de un número negativo","Error matemático",
                           MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                printf("El operando 1 es: %f y su raiz es : %f\n",operando1,sqrt(9));
                return sqrt(operando1);
                break;
            }
        case 'b': return sin(operando1); break;
        case 'c': return cos(operando1); break;
        case 'd':
            if(cos(operando1) == 0){
                MessageBox(hwnd,"Hubo un error con el dominio de la función","Error matemático",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return tan(operando1);
                break;
            }
        case 'e': return 1/tan(operando1); break;
        case 'f': return 1/cos(operando1); break;
        case 'g': return 1/sin(operando1); break;
        case 'h':
            if(operando1 > 1 || operando1 < -1){
                MessageBox(hwnd,"Hubo un error con el dominio de la función","Error matemático",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return asin(operando1);
                break;
            }
        case 'i':
            if(operando1 > 1 || operando1 < -1){
                MessageBox(hwnd,"Hubo un error con el dominio de la función","Error matemático",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return acos(operando1);
                break;
            }
        case 'j': return atan(operando1); break;
        case 'k': return 1/atan(operando1); break;
        case 'l': return 1/acos(operando1); break;
        case 'm': return 1/(asin(operando1)); break;
        case '!':
            if(operando1 < 0){
                MessageBox(hwnd,"No es posible calcular el factorial de un número negativo","Error matemático",
                           MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                if(operando1 > 28){
                    MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                    *error = 1;
                    break;
                }else{
                    int operando_int;
                    float operando_float;
                    operando_int = operando1;
                    operando_float = operando_int;
                    if(operando1 != operando_float){
                        MessageBox(hwnd,"No es posible calcular el factorial de un no-entero","Error matemático",
                                   MB_ICONWARNING | MB_OK);
                        *error = 1;
                        break;
                    }else{
                        return factorial(operando1);
                        break;
                    }
                }
            }
        case '%': return operando1/100;
    }
}

float ObtenerResultado(char postfija[n], int *error, HWND hwnd){
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
                resultado = operacion(operando1, operando2, postfija[i], &*error,hwnd);
                pila = push_float(resultado, pila);
            }else{
                if(postfija[i] == 'a' || postfija[i] == 'b' || postfija[i] == 'c' || postfija[i] == 'd' || postfija[i] == 'e'
                   || postfija[i] == 'f' || postfija[i] == 'g' || postfija[i] == 'h' || postfija[i] == 'i' || postfija[i] == 'j'
                   || postfija[i] == 'k' || postfija[i] == 'l' || postfija[i] == 'm' || postfija[i] == '!' || postfija[i] == '%'){
                    pila = pop_float(&operando1, pila);
                    resultado = operacion_trig(operando1, postfija[i], &*error,hwnd);
                    printf("Resultado guardado trigonometrico%f\n\n",resultado);
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
    if(pila -> valor > 999999999999999999){
        MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
        *error = 1;
    }else{
		printf("Se devoldio %f\n\n",pila->valor);
        return pila -> valor;
    }
}
void Procedimiento(char entrada[n], char postfija[n], HWND hwnd){
    float resultado = 0, resultado_aux;
    int error = 0, func_multi = 0, resultado_int = 0;
    char resultado_txt[n];
    if(Detectar_Errores(entrada,hwnd) == 0){
        funciones_tri(entrada);
        multi_parentesis(entrada);
        ConversionInfijaAPostfija(entrada, postfija);
        resultado = ObtenerResultado(postfija, &error,hwnd);
        printf("El resultado es: %.4f (estamos en proc)\n", resultado);
        if(error == 0){
            resultado_int = resultado;
            resultado_aux = resultado_int;
            if(resultado == resultado_aux){
                    sprintf(resultado_txt,"%i",resultado_int);
                    printf("El resultado es: %i\n", resultado_int);
                    SetWindowText(caja_texto,resultado_txt);
            }else{
                printf("El resultado es: %.4f", resultado);
                sprintf(resultado_txt,"%.4f",resultado);
                SetWindowText(caja_texto,resultado_txt);
            }
            conversion_hex(resultado);
            conversion_oct(resultado);
            conversion_bin(resultado);
            conversion_grados(resultado);
        }
    }
    else SetWindowText(caja_texto,entrada);
}
LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam)
{
    ///Declaración de cadenas
    char texto[n];
    switch(msj){

    case WM_COMMAND: ///Referente a cuando se hace click en algún botón

///Funcionalidad de botones

    //Funciones trigonométricas

    if((HWND)lParam == barcsec){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arcsec(");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == barccsc){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arccsc(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == barccot ){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arccot(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == barcsin ){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arcsin(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == barccos){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arccos(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == barctan ){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"arctan(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == bsec ){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"sec(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == bcsc){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"csc(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == bcot){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"cot(");
            SetWindowText(caja_texto,texto);
        }

     if((HWND)lParam == bsin){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"sin(");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bcos){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"cos(");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == btan){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"tan(");
            SetWindowText(caja_texto,texto);
        }

    //Operaciones principales y básicas

    if((HWND)lParam == bpot){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"^");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == braiz){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"sqrt(");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bfact){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"!");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bporc){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"%");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bpariz){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"(");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bparder){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,")");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bmul){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"*");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bdiv){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"/");
            SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bsum){
        GetWindowText(caja_texto,texto,33);
        strcat(texto,"+");
        SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bresta){
        GetWindowText(caja_texto,texto,33);
        strcat(texto,"-");
        SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bpunto){
        GetWindowText(caja_texto,texto,33);
        strcat(texto,".");
        SetWindowText(caja_texto,texto);
        }

    if((HWND)lParam == bac){
        GetWindowText(caja_texto,texto,33);
        strcpy(texto,"");
        SetWindowText(caja_texto,texto);
        SetWindowText(octl,texto);
        SetWindowText(binl,texto);
        SetWindowText(hexl,texto);
        SetWindowText(gradosl,texto);
        }

    //Función especial
    ///OFF

    if((HWND)lParam == boff){
        if(MessageBox(hwnd,"¿Estás seguro que quieres salir del programa?","Aviso",MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
            PostQuitMessage(0);
        }

    //Números y dígitos

        if((HWND)lParam == b1){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"1");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b2){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"2");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b3){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"3");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b4){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"4");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b5){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"5");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b6){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"6");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b7){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"7");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b8){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"8");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b9){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"9");
            SetWindowText(caja_texto,texto);
        }

        if((HWND)lParam == b0){
            GetWindowText(caja_texto,texto,33);
            strcat(texto,"0");
            SetWindowText(caja_texto,texto);
        }

        ///Funciones que se llevarán a cabo cuando se de click en el botón de "Resultado"

        if((HWND)lParam == bresultado){
                char postfija [n];
                GetWindowText(caja_texto,texto,33);
                puts(texto);
                Procedimiento(texto,postfija,hwnd);
        }
        break;

        break;

    case WM_DESTROY :
        PostQuitMessage(0);
        break;
    }
    DefWindowProc(hwnd,msj,wParam,lParam);
}
