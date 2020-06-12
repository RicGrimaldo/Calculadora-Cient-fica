#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>

///Esta es una prueba de pull request (Git)
///Botones
HWND ventana,caja_texto;
HWND bsin,bcos,btan,bsec,bcsc,bcot,barcsin,barccos,barctan,barcsec,barccsc,barccot;
HWND bpot,bmul,bdiv,boff,bac,braiz,bsum,bfact,bporc,bpariz,bparder,bpunto,bresta,bresultado;
HWND b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;

///Etiquetas estáticas
HWND tipos_conversion,lbin,binl,loct,octl,lhex,hexl,lgrados,gradosl,font,fun_trigl;

///Funciones necesarias

char enteroACaracter(int numero){
    return numero + '0';
}

int limite_cadena(char cad[])
 {
     int error = 0;
     if(strlen(cad) >= 31)
        error = 1;
    else
        error = 0;

    return error;
 }
///Funciones de conversiones

void conversion_hex(char texto[]){
    char hextxt[33];
    int res;
    float resultado;
    resultado = atof(texto);
    res=trunc(resultado);
    ltoa(res, hextxt,16);
    SetWindowText(hexl,hextxt);
}

void conversion_oct (char texto[])
{
    char octtxt[33];
    int res;
    float resultado;
    resultado = atof(texto);
    if(resultado<=99999990){
    res=trunc(resultado);
    ltoa(res, octtxt, 8);
    SetWindowText(octl,octtxt);
    }
    else{
        SetWindowText(octl,"Límite rebasado.");
    }
}

void conversion_bin (char texto[])
{
    char bintxt[50];
    int res;
    float resultado;
    resultado = atof(texto);
    res = trunc(resultado);
    ltoa(res,bintxt,2);
    SetWindowText(binl,bintxt);
}

 void conversion_grados(char res[]){
    float dec,ope1,ope2,resultado;
    int grados,minutos,segundos;
	char m[30],s[30];
	resultado = atof(res);
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

///Funciones de validación
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

int decimal(char a[],HWND hwnd){

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

///Funciones de 'errores' secundarias

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
	if(i==1) return resultado=0;
	return resultado;
}

int parentesis_paridad(char a[],HWND hwnd){
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

int parentesis_vacio(char a[], HWND hwnd){
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

int validacion_caracter(char a[],HWND hwnd){
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

int verificacion_funciones(HWND hwnd,char cad[])
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

///Funciones de 'errores' principales

int error_lexico(char a[], HWND hwnd){
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

int error_sintatico(char a[],HWND hwnd){
    int error=0;
    if(parentesis_paridad(a,hwnd)!=1){ /*Primero, se validará si hay la misma cantidad de pares de paréntesis*/
    for(int i=0;i<strlen(a);i++){

        if(a[i]=='('||a[i]==')'){
                continue; /*Ignorará los operadores válidos, en este caso los paréntesis*/
        }
        if(es_operador(a[i])==1 && a[i]!='-' && es_operador(a[i+1])==1 && a[i+1]!='('&& a[i+1]!='!' && a[i+1]!='%'){
            /*Sirve para validar que un operador no sea puesto 2 veces seguidas, pero ignorando los parentesis,
			factorial, porcentaje o que primero esté un signo negativo*/
			MessageBox(hwnd,"No es posible calcular con 2 operadores seguidos","Error sintáctico",MB_ICONWARNING | MB_OK);
			return error = 1;
        }
        else{
                if(i>=2 && a[i]=='-' && a[i-1]=='(' && a[i-2]==')'||a[i-2]=='*'){
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

int encontrar_error(char a[],HWND hwnd){
	int error=0;
	if(error_lexico(a,hwnd)==1){
		error=1;
	}
	else{
		if(error_sintatico(a,hwnd)==1)error=1;
	}
	return error;
}

LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam){
    ///Declaración de cadenas
    char texto[33];
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
                int i;
                GetWindowText(caja_texto,texto,33);
                if(limite_cadena(texto) == 1)
                        MessageBox(hwnd,"Se excedió el límite de carácteres permitido","Error",MB_ICONWARNING | MB_OK);
                else{///Después de verificar el límite de carácteres permitido...
                    i=encontrar_error(texto,hwnd);
                    conversion_hex(texto);
                    conversion_oct(texto);
                    conversion_bin(texto);
                    conversion_grados(texto);
                        /*Validación de errores
                  Conversión de bin, oct, hex, grad
                  Resultado final
                  Copiar el resultado con SetWindowText*/
                    strcpy(texto,"");
                    SetWindowText(caja_texto,texto);
                }
                break;
        }
        break;

        break;

    case WM_DESTROY :
        PostQuitMessage(0);
        break;
    }
    DefWindowProc(hwnd,msj,wParam,lParam);
}

char app[] = "Mi clase";
int WINAPI WinMain(HINSTANCE ins,HINSTANCE ins2,LPSTR cmd, int estado){

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
    lbin = CreateWindow("STATIC","Bin:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,116,34.25,29.75,ventana,NULL,ins,NULL);
    binl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,116,105,29.75,ventana,NULL,ins,NULL);
    loct = CreateWindow("STATIC","Oct:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,166,34.25,29.75,ventana,NULL,ins,NULL);
    octl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,166,105,29.75,ventana,NULL,ins,NULL);
    lhex = CreateWindow("STATIC","Hex:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,216,34.25,29.75,ventana,NULL,ins,NULL);
    hexl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,216,105,29.75,ventana,NULL,ins,NULL);
    lgrados = CreateWindow("STATIC","Grad:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,266,34.25,29.75,ventana,NULL,ins,NULL);
    gradosl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,266,105,29.75,ventana,NULL,ins,NULL);
    fun_trigl = CreateWindow("STATIC","Funciones trigonométricas",WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER ,166,62,228,30,ventana,NULL,ins,NULL);

///Creación de botones

    //Funciones trigonométricas

    barcsec = CreateWindow("BUTTON","arcsec",WS_CHILD | WS_VISIBLE | SS_CENTER ,170,116,55,50,ventana,NULL,ins,NULL);
    barccsc = CreateWindow("BUTTON","arccsc",WS_CHILD | WS_VISIBLE | SS_CENTER ,170,166,55,50,ventana,NULL,ins,NULL);
    barccot = CreateWindow("BUTTON","arccot",WS_CHILD | WS_VISIBLE | SS_CENTER ,170,216,55,50,ventana,NULL,ins,NULL);
    barcsin = CreateWindow("BUTTON","arcsin",WS_CHILD | WS_VISIBLE | SS_CENTER ,225,116,55,50,ventana,NULL,ins,NULL);
    barccos = CreateWindow("BUTTON","arccos",WS_CHILD | WS_VISIBLE | SS_CENTER ,225,166,55,50,ventana,NULL,ins,NULL);
    barctan = CreateWindow("BUTTON","arctan",WS_CHILD | WS_VISIBLE | SS_CENTER ,225,216,55,50,ventana,NULL,ins,NULL);
    bsec = CreateWindow("BUTTON","sec",WS_CHILD | WS_VISIBLE | SS_CENTER ,280,116,55,50,ventana,NULL,ins,NULL);
    bcsc = CreateWindow("BUTTON","csc",WS_CHILD | WS_VISIBLE | SS_CENTER ,280,166,55,50,ventana,NULL,ins,NULL);
    bcot = CreateWindow("BUTTON","cot",WS_CHILD | WS_VISIBLE | SS_CENTER ,280,216,55,50,ventana,NULL,ins,NULL);
    bsin = CreateWindow("BUTTON","sin",WS_CHILD | WS_VISIBLE | SS_CENTER ,335,116,55,50,ventana,NULL,ins,NULL);
    bcos = CreateWindow("BUTTON","cos",WS_CHILD | WS_VISIBLE | SS_CENTER ,335,166,55,50,ventana,NULL,ins,NULL);
    btan = CreateWindow("BUTTON","tan",WS_CHILD | WS_VISIBLE | SS_CENTER ,335,216,55,50,ventana,NULL,ins,NULL);


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
