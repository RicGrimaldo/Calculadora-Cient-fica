#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>

///Botones
HWND ventana,boton,boton2,label,lx,ly,texto,leertxt;
HWND bsin,bcos,btan,bsec,bcsc,bcot,barcsin,barccos,barctan,barcsec,barccsc,barccot;

///Etiquetas est�ticas
HWND tipos_conversion,lbin,binl,loct,octl,lhex,hexl,lgrados,gradosl,font,fun_trigl;
int tx,ty;

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
    case WM_MOUSEMOVE:
        tx = GET_X_LPARAM(lParam);
        ty = GET_Y_LPARAM(lParam);
        char bufferx[100];
        char buffery[100];
        itoa(tx,bufferx,10);
        itoa(ty,buffery,10);
        SetWindowText(lx,bufferx);
        SetWindowText(ly,buffery);
        break;

    case WM_COMMAND: ///Referente a cuando se hace click

        if((HWND)lParam == boton){
            MessageBox(hwnd,"Le diste click al boton","Aviso",MB_OK | MB_ICONASTERISK);
        }


        if((HWND)lParam == label){
            MessageBox(hwnd,"Le diste click al texto","Aviso",MB_OK | MB_ICONASTERISK);
        }

        if((HWND)lParam == leertxt){
            char gtext[100],c[2];
            GetWindowText(texto,gtext,100);

            if(Longitud_cadena(gtext)<10)
            c[0]=enteroACaracter(Longitud_cadena(gtext));
            else{
                c[0]=enteroACaracter(Longitud_cadena(gtext)/10);
                c[1]=enteroACaracter(Longitud_cadena(gtext)%10);
            }
            MessageBox(hwnd,c,"Longitud de texto",MB_OK | MB_ICONINFORMATION);

            strupr(gtext);
            MessageBox(hwnd,gtext,"Mayusculas",MB_OK | MB_ICONASTERISK);
            strlwr(gtext);
            MessageBox(hwnd,gtext,"Minusculas",MB_OK | MB_ICONASTERISK);
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
    ///Ventana madre------"Contenido de la ventana","T�tulo","Comportamiento y apariencia con botones y/o �conos"



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

///Creaci�n de etiquetas

    tipos_conversion = CreateWindow("STATIC","Tipos de conversion",WS_CHILD | WS_VISIBLE | SS_LEFT ,6,62,140,30,ventana,NULL,ins,NULL);
    lbin = CreateWindow("STATIC","Bin:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,116,34.25,29.75,ventana,NULL,ins,NULL);
    binl = CreateWindow("STATIC","1010",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,116,105,29.75,ventana,NULL,ins,NULL);
    loct = CreateWindow("STATIC","Oct:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,166,34.25,29.75,ventana,NULL,ins,NULL);
    octl = CreateWindow("STATIC","12",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,166,105,29.75,ventana,NULL,ins,NULL);
    lhex = CreateWindow("STATIC","Hex:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,216,34.25,29.75,ventana,NULL,ins,NULL);
    hexl = CreateWindow("STATIC","A",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,216,105,29.75,ventana,NULL,ins,NULL);
    lgrados = CreateWindow("STATIC","Grad:",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_LEFT,6,266,34.25,29.75,ventana,NULL,ins,NULL);
    gradosl = CreateWindow("STATIC","10� 00' 00''",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_RIGHT,40.25,266,105,29.75,ventana,NULL,ins,NULL);
    fun_trigl = CreateWindow("STATIC","Funciones trigonom�tricas",WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTER ,166,62,228,30,ventana,NULL,ins,NULL);

///int x(posici�n horizontal),int y(posici�n vertical),nWidth (anchura),int nHeight(altura).

///Creaci�n de botones

    //Funciones trigonom�tricas

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


    //Operaciones principales y b�sicas





    /*boton = CreateWindow("BUTTON","Boton",WS_CHILD | WS_VISIBLE,10,10,80,30,ventana,NULL,ins,NULL);
    boton2 = CreateWindow("BUTTON","Boton2",WS_CHILD | WS_VISIBLE,10,80,80,30,ventana,NULL,ins,NULL);
    label = CreateWindow("STATIC","Hola mundo, soy un label",WS_CHILD | WS_VISIBLE | SS_NOTIFY | SS_CENTER,100,50,150,40,ventana,NULL,ins,NULL);*/

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
