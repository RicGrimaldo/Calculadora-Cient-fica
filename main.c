#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>

///Esta es una prueba de pull request (Git)
///Botones
HWND ventana,texto;
HWND bsin,bcos,btan,bsec,bcsc,bcot,barcsin,barccos,barctan,barcsec,barccsc,barccot;
HWND bpot,bmul,bdiv,boff,bac,braiz,bsum,bfact,bporc,bpariz,bparder,bpunto,bresta,bresultado;
HWND b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;

///Etiquetas estáticas
HWND tipos_conversion,lbin,binl,loct,octl,lhex,hexl,lgrados,gradosl,font,fun_trigl;

int Longitud_cadena(char cad[]){
    int i=0;
    for(i=0;cad[i]!='\0';i++){
    }
    return i;
}

char enteroACaracter(int numero){
    return numero + '0';
}

LRESULT CALLBACK winProc(HWND hwnd,UINT msj,WPARAM wParam,LPARAM lParam){
    switch(msj){

    case WM_COMMAND: ///Referente a cuando se hace click

        if((HWND)lParam == b1){
            MessageBox(hwnd,"1","Aviso",MB_OK | MB_ICONASTERISK);
        }


        if((HWND)lParam == bpot){
            MessageBox(hwnd,"^","Aviso",MB_OK | MB_ICONASTERISK);
        }

        if((HWND)lParam == bresultado){
    ///La función getwindow es para copiar lo que hay en la caja de texto en la cadena "gtext"
            ///char gtext[100],c[2];
            ///GetWindowText(texto,gtext,100);
           /// MessageBox(hwnd,gtext,"Longitud de texto",MB_OK | MB_ICONINFORMATION);
            break;
        }

        break;

    case WM_DESTROY :
        PostQuitMessage(0);
        break;
    }
    DefWindowProc(hwnd,msj,wParam,lParam);
}

char app[] = "Mi clase";
int WINAPI WinMain(HINSTANCE ins,HINSTANCE ins2,LPSTR cmd, int estado){
    ///Ventana madre------"Contenido de la ventana","Título","Comportamiento y apariencia con botones y/o íconos"



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

    ventana = CreateWindow(app,"Mi ventana",WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,380,HWND_DESKTOP,NULL,ins,NULL);
    texto = CreateWindow("EDIT","",WS_CHILD | WS_VISIBLE  | ES_LOWERCASE | WS_BORDER | ES_RIGHT,6,12,610,34,ventana,NULL,ins,NULL);

///Creación de etiquetas

    tipos_conversion = CreateWindow("STATIC","Tipos de conversion",WS_CHILD | WS_VISIBLE | SS_LEFT ,6,62,140,30,ventana,NULL,ins,NULL);
    lbin = CreateWindow("STATIC","Bin:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,116,34.25,29.75,ventana,NULL,ins,NULL);
    binl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,116,105,29.75,ventana,NULL,ins,NULL);
    loct = CreateWindow("STATIC","Oct:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,166,34.25,29.75,ventana,NULL,ins,NULL);
    octl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,166,105,29.75,ventana,NULL,ins,NULL);
    lhex = CreateWindow("STATIC","Hex:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,216,34.25,29.75,ventana,NULL,ins,NULL);
    hexl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,216,105,29.75,ventana,NULL,ins,NULL);
    lgrados = CreateWindow("STATIC","Grad:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,26A6,34.25,29.75,ventana,NULL,ins,NULL);
    gradosl = CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,266,105,29.75,ventana,NULL,ins,NULL);
    fun_trigl = CreateWindow("STATIC","Funciones trigonométricas",WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER ,166,62,228,30,ventana,NULL,ins,NULL);

///int x(posición horizontal),int y(posición vertical),nWidth (anchura),int nHeight(altura).

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
