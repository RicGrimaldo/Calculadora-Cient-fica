#include <windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define n 35

///HWND es un tipo de dato (identificador) en WINAPI para crear cosas

///Botones
HWND ventana,caja_texto;
HWND bsin,bcos,btan,bsec,bcsc,bcot,barcsin,barccos,barctan;
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

///Estructuras necesarias para la pila
struct PILAA {
	int t;    ///Posición en que se encuentra
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
void negatividad(char entrada[n]);
void multi_parentesis(char entrada [n]);
void funciones_tri(char entrada [n]);
int operando (char c);
int priori[18][19]={ ///Fila / Columna
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  ///Suma
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  ///Resta
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  ///Multiplicacion
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},  ///Division
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},  ///Exponente
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},  ///SQRT
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},  ///Factorial
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},  ///Porcentaje
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Sin
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Cos
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Tan
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Cot
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Sec
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///Csc
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arcsin
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arccos
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},  ///arctan
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  ///Parentesis izquierdo
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

///Funciones para calcular el resultado
void pos(char entrada[n], char postfija[n]);
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]);
float operacion(float operando1, float operando2, char operador, int *error,HWND hwnd);
float operacion_trig(float operando1, char operador, int *error,HWND hwnd);
float ObtenerResultado(char postfija[n], int *error, HWND hwnd);

///Función principal
void Procedimiento(char entrada[n], char postfija[n], HWND hwnd);

///Eventos de la Interfaz gráfica
LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam);

///Creación de la interfaz gráfica
char app[] = "Calculadora";

int WINAPI WinMain(HINSTANCE ins,HINSTANCE ins2,LPSTR cmd, int estado){
    Ocultar_pantalla();
    WNDCLASSEX vtn; ///Estructura acerca de la clase de ventana
    vtn.cbClsExtra=0; ///Bytes extra que se van a reservar para nuestra clase de ventana
    vtn.cbSize=sizeof(WNDCLASSEX); ///Tamaño de la estructura
    vtn.cbWndExtra = 0; ///Bytes extra que se reservarán para las ventanas
    vtn.hbrBackground = (HBRUSH) (COLOR_HIGHLIGHT+1); ///Color de fondo
    vtn.hCursor = LoadCursor(NULL,IDC_ARROW); ///Cursor de la clase
    vtn.hIcon = NULL; ///Ícono establecido por defecto
    vtn.hIconSm = NULL; ///Ícono pequeño establecido por defecto
    vtn.hInstance = ins; ///Número que representa la app en el Sistema operativo
    vtn.lpfnWndProc = winProc; ///Proceso/función de mensajes a recibir (eventos)
    vtn.lpszClassName = app;///Nombre de la clase de la ventana
    vtn.lpszMenuName = NULL;///No tendrá menú, por lo que será NULL
    vtn.style = CS_HREDRAW | CS_VREDRAW;///Estilo de ventana
    ///En este caso, se redibuja la ventana cada que se cambie el tamaño de la ventana (si fuera el caso)

///MessageBox(Manipulador de la ventana principal (hwnd), mensaje, título de la ventana, estilo)

    if(!RegisterClassEx(&vtn)){
        MessageBox(HWND_DESKTOP,"Error al crear la clase","Error",MB_ICONERROR|MB_OK);
    }

///CreateWindow= (Clase, nombre, estilo, posición horizontal, posición vertical, ancho, alto, ventana madre,
///               , manipulador a la instancia de la app, valores que se les pueden pasar a otras ventanas);

///Ventana principal

    ventana = CreateWindow(app,"Calculadora Científica basada en Win32 API",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                           WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,380,HWND_DESKTOP,NULL,ins,NULL);

///Caja de texto = EDIT
    caja_texto = CreateWindow("EDIT","",WS_CHILD | WS_VISIBLE  | ES_LOWERCASE | WS_BORDER | ES_RIGHT,6,12,610,34,ventana,NULL,ins,NULL);

///Creación de etiquetas = STATIC

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

///Creación de botones = BUTTON

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


    if(!ventana){ ///Se presentará en el caso de que no se haya podido crear la ventana
        MessageBox(HWND_DESKTOP,"Error al crear la ventana","Error",MB_ICONERROR|MB_OK);

    }

    ShowWindow(ventana,SW_SHOWNORMAL);///Esta función especifica cómo se mostrará la ventana.
    MSG msj;///Variable que guarda mensajes


    while(GetMessage(&msj,NULL,0,0)){
        DispatchMessage(&msj);///Se envían los mensajes a WinProc
        TranslateMessage(&msj);///Traduce el msj

    }

    return (int) msj.wParam;///Guarda el estatus de salida de la app

}

///Funciones
char enteroACaracter(int numero){
	return numero + '0';
}
int limite_cadena(char cad[n],HWND hwnd)
 {
     int error = 0;
     if(strlen(cad) >= 31) ///Se verifica si la entrada no se excede del límite establecido
     {
        MessageBox(hwnd,"Se excedió el límite de carácteres permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
        return error = 1;
     }
    else
        return error = 0;
 }
 int Encontrar_cadena2 (char cad1[n],char cad2[n]){
	int resultado = 1;
	for(int i=0; cad1[i] != '\0'; i++){ ///Todos los carácteres deben ser completamente iguales
        if(cad1[i] != cad2[i]){         ///Compara 2 cadenas, 1 si son iguales y 0 si no
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
    if(resultado<=999999999 && resultado>=0){
    res=trunc(resultado); ///Se truncará para convertir únicamente el número entero
    ltoa(res, hextxt,16); ///Número que se desea convertir, cadena en que se guardará, base
    SetWindowText(hexl,hextxt);
    }
    else{ ///Casos si es negativo o rebasó el límite permitido
        if(resultado<0) SetWindowText(hexl," ");
        else SetWindowText(hexl,"Límite rebasado");
    }
}
void conversion_oct (float resultado)
{
    char octtxt[33];
    int res;
    if(resultado<=99999990 && resultado>=0){
    res=trunc(resultado);
    ltoa(res, octtxt, 8);
    SetWindowText(octl,octtxt);
    }
    else{
        if(resultado<0) SetWindowText(octl," ");
        else SetWindowText(octl,"Límite rebasado");
    }
}

void conversion_bin (float resultado)
{
    char bintxt[50];
    int res;
    res = trunc(resultado);
    if(resultado<=16300 && resultado>=0){
    ltoa(res,bintxt,2);
    SetWindowText(binl,bintxt);
    }
    else{
        if(resultado<0) SetWindowText(binl," ");
        else SetWindowText(binl,"Límite rebasado");
    }
}

 void conversion_grados(float resultado){
    float dec,ope1,ope2;
    int grados,minutos,segundos;
	char m[30],s[30],res[33];
	if(resultado<=9999999 && resultado>=0){
    grados=trunc(resultado);
    dec=resultado-grados;
    ope1=dec*60;
    minutos=trunc(ope1);
    ope2=ope1-minutos;
    segundos=ope2*60;
	itoa(grados,res,10);
	itoa(minutos,m,10);
	itoa(segundos,s,10);
	///Con la función strcat, se unen cadenas y carácteres, todo guardado en la cadena 'res'
	strcat(res,"° "); strcat(res,m); strcat(res," ' "); strcat(res,s); strcat(res,"''");
	SetWindowText(gradosl,res);
	}
	else{
        if(resultado<0) SetWindowText(gradosl," ");
        else SetWindowText(gradosl,"Límite rebasado");
	}
}
int esDigito (char car){
    int resultado=0;
    if(car>47 && car<58){
            return resultado=1;
    }
    return resultado;
}

int es_operador(char car){
    int resultado=0; ///Función para verificar si un carácter es operador, 1 si lo es, 0 caso contrario.
    switch(car){
    case'+': case'-': case'*': case'/': case '^': case'(': case ')': case '%': case '.': case '!': resultado=1;
    break;
    }
    return resultado;
}

int letras_permitidas (char car){
    int resultado = 0; ///Función para verificar si un carácter es alguna de las letras permitidas, 1 si lo es, 0 caso contrario.
    switch(car){
        case 'a': case'c': case 'n': case'e': case'i': case 'o': case'r': case 's': case 't': case 'q':resultado=1;
        break;
    }
    return resultado;
}

int Primer_letra_funcion(char a)
{
    int resultado = 0; ///Primeras posibles letras de todas las funciones
    switch(a){
    case 'a': case 's' : case 'c' : case 't': resultado = 1;
    break;
    }
    return resultado;
}

int encontrarCaracter(char cad[n], char car){
     int r=0; ///Una función que verifica si el carácter se encuentra en la cadena.
     ///Si lo encuentra devuelve la posición, 0 en caso contrario
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
            if(esDigito(a[i])==1) continue; ///En el caso de que el carácter después de . es número, se verifica el siguiente carácter
        if(es_operador(a[i]) == 1 && a[i]!= '.'){
            break; ///En el caso de que sea un operador, no se encontró error alguno
        }
        else{
            if(a[i] == '.') ///Particulares casos como '2.2.2'
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
	} ///En el caso que hayan coincidido algunas letras, pero la longitud de la cadena es más pequeña que el contador
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
        if(c>b){ ///Ej: 4)(6
            MessageBox(hwnd,"Error de paréntesis","Error sintáctico",MB_ICONWARNING | MB_OK);
            return error = 1;
        }
    if(c!=b){///En el caso de falte un paréntesis
            MessageBox(hwnd,"Error debido a falta de un parentesis","Error sintáctico",MB_ICONWARNING | MB_OK);
            return error = 1;
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
	for(int i = 1; i<strlen(a);i++)
    {
        if(Primer_letra_funcion(a[i])==1){
            if (esDigito(a[i-1])==1 || a[i-1]=='!' || a[i-1]=='%'){ ///Validará que, antes de una función, no haya un número, ! o %
            MessageBox(hwnd,"Error con la declaración de la función","Error sintáctico",
                                   MB_ICONWARNING | MB_OK);
            return error = 1;
        }
    }
    }
	if(es_operador(a[0])==1 && a[0]!='(' && a[0]!='-' && esDigito(a[0])==0 && a[0]!='+' && a[0]!='.'){
    ///Validará que el primer carácter no sea ningún operador a excepción del '(',cualquier primer letra de las funciones, - o +.
        MessageBox(hwnd,"Error con el primer carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
        return error=1;
		}
	else{///Caso especial si es una letra y NO es la primer letra de una función
		if(letras_permitidas(a[0])==1 && Primer_letra_funcion(a[0])==0){
			MessageBox(hwnd,"Error en el primer carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
			return error=1;
		}
	}

	if(error == 0){
	f=strlen(a)-1;
	if(a[f]!=')' && a[f]!='!' && a[f]!='%' && es_operador(a[f])==1 || letras_permitidas(a[f])==1 ){
        ///Validará que el último carácter no sea un operador a excepción de ')', ! y %
		MessageBox(hwnd,"Error con el último carácter","Error sintáctico",MB_ICONWARNING | MB_OK);
		return error = 1;
	}
	}
	if(error==0){
		for(int i=1;i<strlen(a),a[i+1]!='\0';i++){ ///Después de un (...
			if(a[i-1]=='(' && es_operador(a[i])==1 && a[i]!='(' && a[i]!='-' && esDigito(a[i])==0 && a[i]!='.' && a[i]!='+'){
            ///Validará que el primer carácter no sea ningún operador a excepción del '(',cualquier primer letra de las funciones, ., - o +
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
				else{///Aquí se verifica que no haya un operador antes de un paréntesis cerrado a excepción de ),! o %
					if(es_operador(a[i-1])==1 && a[i]==')' && a[i-1]!='!' && a[i-1]!='%' && a[i-1]!=')'){
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
     int error = 0; ///Validación de la correcta escritura de las funciones permitidas
     for(int i=0;i<strlen(cad);i++)
     {
         if(esDigito(cad[i])==0 && es_operador(cad[i])==0){
                if (Encontrar_cadena("sqrt(",cad) == 1)  error=0;
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
                if(a[i]=='.'){ /*Si el carácter inválido es un punto decimal, hará una impresión diferente*/
                    if(esDigito(a[i-1])==1 && esDigito(a[i+1])==1){
                        error = decimal(a,hwnd);
                        break;
                    }
                else{
                    if(a[i+1]=='.'){ ///Ej: 3..5
                    MessageBox(hwnd,"Error en ubicación del punto decimal.","Error léxico",MB_ICONWARNING | MB_OK);
                    return error = 1;}
                }
                }
                else{ ///Si no es letra, operador ni número, entonces es un carácter inválido
                MessageBox(hwnd,"No se permiten caracteres inválidos","Error léxico",MB_ICONWARNING | MB_OK);
                return error = 1;
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
        if(es_operador(a[i])==1 && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!='!' && a[i+1]!='%'
                        && a[i]!='!' && a[i]!='%' && a[i+1]!='.' && a[i]!='.'){
        ///Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis,
        ///!, % o que primero esté un signo - o +*/
			MessageBox(hwnd,"No es posible calcular con 2 operadores seguidos","Error sintáctico",MB_ICONWARNING | MB_OK);
			return error = 1;
        }
        else error = 0;
            /*El error será 0 en caso de que el carácter leído no haya presentado error*/
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
void negatividad(char entrada[n]){
    int longitud = strlen(entrada);
    for(int i=0; entrada[i] != '\0'; i++){///Un - en la primera posición o después de un paréntesis
        if(entrada[i] == '-' && (i == 0 || entrada[i-1] == '(')){
            for(int j = longitud; j > i; j--){
                entrada[j] = entrada[j-1]; ///Corre la cadena hacia la cadena una posición
           }
           entrada[i] = '0';///Y se coloca un 0 hasta el principio
        }
    }
}
void multi_parentesis(char entrada [n]){
    int longitud = strlen(entrada);
    for(int i = 0; i<strlen(entrada); i++){///(2)(3) o (2)3
        if(entrada[i] == ')' && (entrada[i+1] == '(' || entrada[i+1] > 47 && entrada[i+1] < 58)){
            for(int j = longitud-1; j > i; j--){
                entrada[j+1] = entrada[j];
            }
            entrada[i+1] = '*';
        }else{///Si hay un número antes de un paréntesis izquierdo
            if(i != 0 && entrada[i] == '(' && entrada[i-1] > 47 && entrada[i-1] < 58){
            for(int j = longitud-1; j >= i; j--){
                entrada[j+1] = entrada[j];
            }
            entrada[i] = '*';
            }
        }
    }
}

void funciones_tri(char entrada [n]){
    int I = 0, J = 0;
    char operador, trig[10];
    for(int i = 0; entrada[i] != '\0'; i++){
        if(entrada[i] > 96 && entrada [i] < 123){///Verifica si el carácter es una letra
            for(int j = i; entrada[j] != '('; j++){///Hasta que encuentre un paréntesis, guarda las letras en otra cadena
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
}

int operando(char c){
	if (c != '+' &&
         c != '-' &&
         c != '*' &&
		 c != '/' &&
		 c != '^' &&
         c != 'a' &&
         c != '!' &&
         c != '%' &&
         c != 'b' &&
         c != 'c' &&
         c != 'd' &&
         c != 'e' &&
         c != 'f' &&
         c != 'g' &&
         c != 'h' &&
         c != 'i' &&
         c != 'j' &&
         c != '(' &&
         c != ')' &&
         c != ',' &&
         c != '_'){
             return 1;
         }
         return 0;
}
int prioridad (char op1, char op2){
	int i, j, prioridaad;
	switch(op1){
	    case '+': i=0; break;
	    case '-': i=1; break;
	    case '*': i=2; break;
	    case '/': i=3; break;
	    case '^': i=4; break;
	    case 'a': i=5; break;
	    case '!': i=6; break;
	    case '%': i=7; break;
	    case 'b': i=8; break;
	    case 'c': i=9; break;
	    case 'd': i=10; break;
	    case 'e': i=11; break;
	    case 'f': i=12; break;
	    case 'g': i=13; break;
	    case 'h': i=14; break;
	    case 'i': i=15; break;
	    case 'j': i=16; break;
	    case '(': i=17; break;
	}
	switch(op2){
	    case '+': j=0; break;
	    case '-': j=1; break;
	    case '*': j=2; break;
	    case '/': j=3; break;
	    case '^': j=4; break;
	    case 'a': j=5; break;
	    case '!': j=6; break;
	    case '%': j=7; break;
	    case 'b': j=8; break;
	    case 'c': j=9; break;
	    case 'd': j=10; break;
	    case 'e': j=11; break;
	    case 'f': j=12; break;
	    case 'g': j=13; break;
	    case 'h': j=14; break;
	    case 'i': j=15; break;
	    case 'j': j=16; break;
	    case '(': j=17; break;
	    case ')': j=18; break;
	}
 ///Determina qué operador va primero
	prioridaad = priori[i][j]; ///Regresará el valor de la prioridad
	return (prioridaad);
}

char tope(struct PILAA p){
	return (p.a[p.t-1]); ///Regresa el carácter sin eliminarlo
}
void init_pila(struct PILAA *p){
	p->t = 0; ///Inicializar pila
}
int pila_vacia (struct PILAA *p){
    return(!p->t);
}
void ins_pila(struct PILAA *p, char s){
	if(p->t == n){
	} ///Valida que la entrada no tenga límite de caracteres, pero no es útil
	else{
        p->t++; ///Insertar valor nuevo
        p->a [p->t - 1] = s;
	}
}
void retira_pila(struct PILAA *p, char *s){
    if(pila_vacia(p)){ ///Si la pila está vacía, se le pasa el guión bajo por referencia
		*s = '_'; ///último carácter de la cadena
	}else{
	    *s = p->a [p->t - 1];///Carácter por referencia = carácter del tope (último agregado) de la pila
        p->t--; ///Como se elimina el último carácter de la pila, entonces la posición se borra
	}
}
nodo_float *crear_pila_float(nodo_float *pila){
    return pila = NULL; ///Crea una pila NULL (Vacía)
}
nodo_float *push_float(float valor, nodo_float *pila){
    nodo_float *nodo_nuevo; ///Como ins_pila, guarda valores float - insertar
    nodo_nuevo = (nodo_float *) malloc(sizeof(nodo_float));
    if(nodo_nuevo != NULL){
        nodo_nuevo -> valor = valor;
        nodo_nuevo -> siguiente = pila;
        pila = nodo_nuevo;
    }
    return pila;
}
nodo_float *pop_float(float *valor, nodo_float *pila){
    nodo_float *nodo_auxiliar; ///Como retira pila, lo regresa y elimina el último valor guardado
    float dato;
    if(pila == NULL){

    }
    else{
        nodo_auxiliar = pila;
        dato = nodo_auxiliar ->valor;
        pila = nodo_auxiliar ->siguiente;
        *valor = dato;
        free(nodo_auxiliar); ///Libera espacio que se ha estado guardando
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
	init_pila(&pila);///Se inicializa la pila
	while(entrada[i] != '_') {
	   if(operando(entrada[i]) == 1){ ///Si el caracter es un número o punto decimal
            postfija [++j] = entrada[i++]; ///Lo pone en postfija
	   }
	   else{///Mientras la pila no esté vacía y la prioridad no sea NULL (último valor de la pila y el carácter que sigue en la cadena
		     while (!pila_vacia (&pila) && prioridad(tope(pila), entrada[i])){
			     retira_pila (&pila, &elemento);
			     postfija[++j] = elemento;///El último elemento que se retiró del tope de la pila se agrega a la cadena postfija
		      }
		      if(operando(postfija[j]) == 1){///Si el carácter es un número/'.'
                postfija[++j] = ',';///Al siguiente carácter de la cadena postfija se le agrega la coma
                } ///La coma sirve para separar un número de otro

                if (entrada[i] == ')'){///Si es un paréntesis derecho, entonces
                    retira_pila(&pila, &elemento);///El último elemento que se retiró del tope de la pila se guarda en elemento
                }
                else{
                    ins_pila(&pila, entrada[i]);///Se inserta el carácter de entrada a la pila
                }
		      i++;
		}
	}
	///Vaciar toda la pila para ponerlas en postfija:
	while (!pila_vacia (&pila)){///Si la pila no está vacía
		retira_pila (&pila, &elemento);///El último elemento que se retiró del tope de la pila se guarda en elemento
		postfija[++j] = elemento;///Se agrega a postfija
	}
	postfija[++j] = '\0'; ///El último carácter de postfija será nulo
}
//Sólo en el cmd, en GUI es obsoleto
void ConversionInfijaAPostfija(char entrada[n], char postfija[n]){
	int longitud;
	longitud = strlen(entrada);
	entrada[longitud] = '_'; ///En la última posición se agrega guión bajo
	entrada[longitud+1] = '\0';
	pos(entrada, postfija);
	for(int i=0; postfija[i] != '\0'; i++){///Solución cuando se agregaban "saltos de línea" en el cmd
		if(postfija[i] == 10){ ///10 en ASCII es salto de línea
			for(int j=i; postfija[j] != '\0'; j++){
				postfija[j] = postfija[j+1];///Ignorando el salto de línea, agrega cada carácter a su posición anterior
			}
		}
	}
}
float operacion(float operando1, float operando2, char operador, int *error,HWND hwnd){
    switch(operador){///Cada caso validará un posible error matemático
        case '+':
           if(operando1 > 999999999999999999 || operando2 > 999999999999999999){
                MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                return operando1 + operando2; break;
            }
        case '-': return operando1 - operando2; break;
        case '*':
           if((operando1 > 999999999 && operando2 > 999999999) || (operando1 > 999999999999999999 && operando2 != 0 && operando2 != 1) || (operando2 > 999999999999999999 && operando1 != 0 && operando1 != 1)){
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
            if((operando2 > 59 && operando1 != 1 && operando1 != 0 && operando1 != (-1))){
               MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                *error = 1;
                 break;
            }else{
                return potencia(operando1, operando2); break;
            }
    }
}
float operacion_trig(float operando1, char operador, int *error,HWND hwnd){
        switch(operador){
        case 'a':
            if(operando1 < 0){
                MessageBox(hwnd,"No es posible calcular la raíz de un número negativo","Error matemático",
                           MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
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
        case '!': if(operando1 < 0){
                MessageBox(hwnd,"No es posible calcular el factorial de un número negativo","Error matemático",MB_ICONWARNING | MB_OK);
                *error = 1;
                break;
            }else{
                if(operando1 > 19){
                    MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
                    *error = 1;
                    break;
                }else{
                    int operando_int;
                    float operando_float;
                    operando_int = operando1;
                    operando_float = operando_int;
                    if(operando1 != operando_float){
                        MessageBox(hwnd,"No es posible calcular el factorial de un no-entero","Error matemático",MB_ICONWARNING | MB_OK);
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
///Se guardan los números como cadenas, pasándose con la función 'atof', agregándose a la pila
float ObtenerResultado(char postfija[n], int *error, HWND hwnd){
    nodo_float *pila;
    int I = 0;///Contador para la cadena 'valor'
    char valor[n];///Se guardan los números en la cadena
    float operando1, operando2, resultado, valor_float;
    pila = crear_pila_float(pila);
    for(int i=0; postfija[i] != '\0'; i++){
        if(postfija[i] >= 48 && postfija[i] <=57 || postfija[i] == '.'){///Si es un número o punto decimal
            for(int j = i; postfija[j] >= 48 && postfija[j] <=57 || postfija[j] == '.'; j++){
                valor[I] = postfija[j];
                I++;
                if(postfija[j+1] >= 48 && postfija[j+1] <= 57 || postfija[j+1] == '.'){
                    i++;
                }
            }
            valor_float = atof(valor);///Guarda el número guardado en la cadena en un float
            pila = push_float(valor_float, pila); ///Se pasa a la lista
            for(int j=0; j<40; j++){
                valor[j] = '\0';///Vacía / inicializa la cadena para volverse a usar
            }
            I = 0;
        }else{
            if(postfija[i] == '+' || postfija[i] == '-' || postfija[i] == '*' || postfija[i] == '/' || postfija[i] == '^'){
                pila = pop_float(&operando2, pila);
                pila = pop_float(&operando1, pila);///Se retiran y se pasan los números de la pila por referencia
                resultado = operacion(operando1, operando2, postfija[i], &*error,hwnd);
                pila = push_float(resultado, pila); ///El resultado se inserta en la pila
            }else{
                if(postfija[i] == 'a' || postfija[i] == 'b' || postfija[i] == 'c' || postfija[i] == 'd' || postfija[i] == 'e'
                   || postfija[i] == 'f' || postfija[i] == 'g' || postfija[i] == 'h' || postfija[i] == 'i' || postfija[i] == 'j'
                   || postfija[i] == '!' || postfija[i] == '%'){///Caso especial debido a que solamente usan 1 operando a la vez
                    pila = pop_float(&operando1, pila);
                    resultado = operacion_trig(operando1, postfija[i], &*error,hwnd);
                    pila = push_float(resultado, pila);
                }else{
                    continue;///Si es una coma, se ignora (la coma sirve para diferenciar dígitos)
                }
            }
        }
        if(postfija[i+1] == 10){///Si había salto de línea, se eliminaban (sólo en el caso del cmd)
            postfija[i+2] = '\0';///Validación obsoleta
        }
    }
   if(pila -> valor > 999999999999999999){
        MessageBox(hwnd,"Se excedió el límite permitido","Error de límite de carácteres",MB_ICONWARNING | MB_OK);
        *error = 1;
    }else return pila -> valor;
}
void Procedimiento(char entrada[n], char postfija[n], HWND hwnd){
    float resultado = 0, resultado_aux;
    int error = 0, func_multi = 0, resultado_int = 0;
    char resultado_txt[n];
    if(Detectar_Errores(entrada,hwnd) == 0){ ///En el caso que no haya ningún error sintáctico, léxico o de límite, se procederá a calcular la expresión
        funciones_tri(entrada);
        multi_parentesis(entrada);
        negatividad(entrada);
        ConversionInfijaAPostfija(entrada, postfija);
        resultado = ObtenerResultado(postfija, &error,hwnd);
        if(error == 0){
            resultado_int = resultado;
            resultado_aux = resultado_int;
            if(resultado == resultado_aux){
    ///Sprintf sirve para guardar en una cadena, un tipo de número
                    sprintf(resultado_txt,"%i",resultado_int); ///Crea una cadena según cierto formato, con datos a guardar
                    SetWindowText(caja_texto,resultado_txt);///Muestra el resultado en forma de cadena en la caja de texto
            }else{
                sprintf(resultado_txt,"%.4f",resultado); ///Sprintf(La cadena de destino, la cadena de formato y los datos a guardar)
                SetWindowText(caja_texto,resultado_txt);
            }
            conversion_hex(resultado);
            conversion_oct(resultado);
            conversion_bin(resultado);
            conversion_grados(resultado);
        }
    }
    else SetWindowText(caja_texto,entrada); ///En caso de que se detecte un error, la expresión quedará tal y como se escribió para que el usuario
    ///pueda corregir su error
}

LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam)
{
    ///Declaración de cadenas
    char texto[n];
    switch(msj){

    case WM_COMMAND: ///Referente a cuando se hace click en algún botón

///Funcionalidad de botones

///GetWindowText = (De dónde se quiere agarrar el texto, dónde se quiere guardar, número máx de caracteres a copiar);
///SetWindowText = (A dónde se quiere mandar el texto guardado, cadena donde se tiene guardado el texto);
///strcat = Copia una cadena en el final de otra

    //Funciones trigonométricas

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
        strcpy(texto,"");///Se vaciará la cadena
        SetWindowText(caja_texto,texto); ///Y las etiquetas también
        SetWindowText(octl,texto);
        SetWindowText(binl,texto);
        SetWindowText(hexl,texto);
        SetWindowText(gradosl,texto);
        }

    ///Función especial OFF

    if((HWND)lParam == boff){ ///En el caso que se halla dado click en 'OK'...
        if(MessageBox(hwnd,"¿Estás seguro que quieres salir del programa?","Aviso",MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
            PostQuitMessage(0); ///Se cerrará la ventana
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
                Procedimiento(texto,postfija,hwnd);
        }
        break;

        break;

    case WM_DESTROY :
        PostQuitMessage(0); ///Cerrar la ventana
        break;
    }
    DefWindowProc(hwnd,msj,wParam,lParam);
}
