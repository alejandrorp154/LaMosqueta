#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
#define cantNombre 20
#define cantJugadores 20
#define cantTopes 5

//ESTRUCTURAS
struct jugador{
    char nombre[cantNombre];
    char nickname[cantNombre];
    int edad;
    int CI;
    int saldo;
    int arFinal[3];
    int arInicial[3];
    int cont;
};

struct listaJugadores{
    jugador lista[cantJugadores];
    bool ocupado[cantJugadores];
    int cantusuarios;
};

struct top5 {
    int saldoInicial;
    int saldoFinal;
    int saldoGanado;
    char nickName[20];
};
//FUNCIONES
void intrucciones();
char instruccionesMI();
char instruccionesMC();
int leo(char arreglo[],int largo);
void leoNombres(char arreglo[],int largo);
void muestroCopas(int cantCopa);
void mensajeAlazar();
bool leerSalir(char arreglo[],int contador);
bool leerMano(char arreglo[],int contador);
bool verificarCopa(char arreglo[], int largo, int victorias, int perdidaTotal, int saldo, int perdidaParcial, int &copa, int cantCopa, int &apuesta);
int ubicacionPelotita(int cantCopa, int victorias, int copa);
void ubicacionGrafica(int cantCopa, int alazar);
int multiplicarApuesta(int cantCopa);
void vicroriaAcertada(int &saldo, int apuesta, int &victorias, int multiplicador, int &perdidaParcial);
void derrotaContundente(int &saldo, int apuesta, int &victorias, int &perdidaParcial, int &perdidaTotal);
int verficarCantCopas(char arreglo[],int largo);
jugador cargarJugador(listaJugadores &player);
void registrarse(listaJugadores &player);
bool logIn(listaJugadores player, int &lugaruser);
void modificarDatos(listaJugadores &player, int lugaruser);
void funcionDelTop5(top5 deLoMejor, top5 masGanadores[], int &y);
void jugarPartida (listaJugadores &player, int lugaruser, top5 masGanadores[]);
bool menuUsuario(char opcMC, top5 masGanadores[], listaJugadores &player, int lugaruser);
void secondMain(listaJugadores &player, top5 mejoresPlayer[]);

int main()
{
    srand(time(NULL));
    listaJugadores player;
    top5 mejoresPlayer[cantTopes];
    secondMain(player,mejoresPlayer);

    return 0;
}

void intrucciones(){
    printf("Bienvenido/a, a continuación comenzaremos a jugar.\n");
    printf("Para cada jugada debes indicar en qué copa se encuentra la bola.\n");
    printf("Recuerda que también puedes optar por retirarte marcando “Salir”.\n");
}

char instruccionesMI(){
    char opcMI;
    printf("\tBienvenido al Menu de inicio:\n");
    printf("Ingrese (I) para Iniciar Sesión. \n");
    printf("Ingrese (R) para Registrarse. \n");
    printf("Ingrese (L) para Listar Jugadores. \n");
    printf("Ingrese (S) para Salir.\n");
    opcMI=getchar();
    getchar();
    return opcMI;
}

char instruccionesMC(){
    char opcMC;
    printf("\tMenu de Cuenta:\n");
    printf("Ingrese (J) para Jugar. \n");
    printf("Ingrese (U) para Últimas 3 Personales. \n");
    printf("Ingrese (T) para Top 5. \n");
    printf("Ingrese (C) para Cerrar Sesión. \n");
    printf("Ingrese (M) para Modificar Datos. \n");
    printf("Ingrese (D) para Dar de Baja. \n");
    opcMC=getchar();
    getchar();
    return opcMC;
}

int leo(char arreglo[],int largo){
    int i,numero;
    char leer;
    bool ret=true;
    while(ret){
        ret=false;
        i=0;
        leer=getchar();
        while(leer!='\n' and i<largo-1){
            arreglo[i]=leer;
            i++;
            leer=getchar();
        }
        arreglo[i]='\0';
        int j;
        for(j=0;j<i;j++){
            if(arreglo[j]<'0' or arreglo[j]>'9')
                ret=true;
        }
        if(ret==false)
            numero=atoi(arreglo);
    }
    return numero;

}

void leoNombres(char arreglo[],int largo){
    int i,j;
    char leer;
    bool ret=true;
    while(ret){
        i=0;
        leer=getchar();
        while(leer!='\n' and i<largo-1){
            arreglo[i]=leer;
            i++;
            leer=getchar();
        }
        arreglo[i]='\0';
        for(j=0;j<i;j++){
            if((arreglo[j]>='a' and arreglo[j]<='z') or (arreglo[j]>='A' and arreglo[j]<='Z'))
                ret=false;
        }
    }
}

void muestroCopas(int cantCopa){
    int i,j;
    for(i=0;i<cantCopa;i++)
        printf("O ");
    printf("\n");
    for(j=0;j<cantCopa;j++)
        printf("%d ",j+1);
    printf("\n");

}

void mensajeAlazar(){
    int mensaje,alazar;
    alazar=rand();
    alazar=alazar%3;
    mensaje=alazar;
    if(mensaje==0){
        printf("Si vuelvo a casa sin plata me matan.\n");
    }else if(mensaje==1){
        printf("Esto no puede quedar así.\n");
    }else if(mensaje==2){
        printf("Si perdí la anterior, de seguro ahora gano.\n");
    }
}

bool leerSalir(char arreglo[], int contador){
    int igualdad;
    bool igualSalir=false;
    igualdad=strcmp(arreglo,"Salir");
    if(igualdad==0){
        igualSalir=true;
    }
    return igualSalir;
}

bool leerMano(char arreglo[], int contador){
    int igualdad;
    bool igualMano=false;
    igualdad=strcmp(arreglo,"Mano");
    if(igualdad==0){
        igualMano=true;
    }
    return igualMano;
}

bool verificarCopa(char arreglo[], int largo, int victorias, int perdidaTotal, int saldo, int perdidaParcial, int &copa, int cantCopa, int &apuesta){
    int contador=0,cont=0;
    char letra;
    bool numero=true,comando=true,Mano,Salir;
    apuesta=-1;
    letra=getchar();
    while(letra!='\n' && contador<largo-1){
        arreglo[contador]=letra;
        contador++;
        letra=getchar();
    }
    arreglo[contador]='\0';
    while(cont<contador&&numero!=false){
        if(arreglo[cont]<'0' || arreglo[cont]>'9'){
            numero=false;
        }
        cont++;
    }
    if(numero==false){
        Mano=leerMano(arreglo,contador);
        Salir=leerSalir(arreglo,contador);
        if(Mano){
            comando=false;
            copa=-1;
            if(victorias==2){
                perdidaTotal=perdidaTotal*2;
                saldo=saldo+perdidaTotal;
                printf("Saldo: %d\n",saldo);
                printf("Tu si que eres perceptivo, te animas a no contarle esto a nadie?\n");
            }else{
                printf("Quien te crees que soy? Vete de aquí.\n");
            }
        }else if(Salir){
            copa=-1;
            if(perdidaParcial>200){
                mensajeAlazar();
            }else{
                comando=false;
                printf("Nos vemos la próxima.\n");
            }
        }
    }else if(numero){
        copa=atoi(arreglo);
        if(copa>0&&copa<=cantCopa){
            comando=false;
            printf("Apuesta?:\n");
            while(apuesta==-1){
                apuesta=leo(arreglo,largo);
                if(apuesta<50 or apuesta>saldo)
                    apuesta=-1;
            }
        }
    }
    return comando;
}

int ubicacionPelotita(int cantCopa, int victorias, int copa){
    int alazar;
    alazar=rand();
    alazar=alazar%cantCopa+1;
    if(victorias==2){
        while(copa==alazar){
            alazar=rand();
            alazar=alazar%cantCopa+1;
        }
    }
    return alazar;
}

void ubicacionGrafica(int cantCopa, int alazar){
    int contador;
    for(contador=1;contador<=cantCopa;contador++){
        if(alazar==contador){
            printf(". ");
        }else{
            printf("0 ");
        }
    }
    printf("\n");
}

int multiplicarApuesta(int cantCopa){
    int multiplicador;
    if(cantCopa>2&&cantCopa<6){
        multiplicador=2;
    }else if(cantCopa>5&&cantCopa<9){
        multiplicador=3;
    }else if(cantCopa==9){
        multiplicador=4;
    }
    return multiplicador;
}

void vicroriaAcertada(int &saldo, int apuesta, int &victorias, int multiplicador, int &perdidaParcial){
    saldo=saldo+(apuesta*multiplicador);
    victorias++;
    perdidaParcial=0;
    printf("Ha acertado\n");
    printf("Saldo: %d\n",saldo);
}

void derrotaContundente(int &saldo, int apuesta, int &victorias, int &perdidaParcial, int &perdidaTotal){
    saldo=saldo-apuesta;
    perdidaParcial=apuesta;
    perdidaTotal=perdidaTotal+perdidaParcial;
    victorias=0;
    printf("No ha acertado\n");
    printf("Saldo: %d\n",saldo);
}

int verficarCantCopas(char arreglo[],int largo){
    int ret=-1,cantCopa;
    while(ret==-1){
        cantCopa=leo(arreglo,largo);
        if(cantCopa>=3 and cantCopa<=9)
            ret=cantCopa;
        else
            ret=-1;
    }
    return ret;

}

jugador cargarJugador(listaJugadores &player){
    jugador ret;
    bool ciIguales,nickIguales=false,salir;
    int i,iguales;
    char arr[cantNombre];
    printf("\n");
    do{
        ciIguales=false;
        printf("Ingrese la cedula: ");
        ret.CI=leo(arr,cantNombre);
        for (i=0;i<player.cantusuarios;i++){
            if(player.lista[i].CI==ret.CI && player.ocupado[i]==true){
                printf("Alguno de estos datos ya están usados, pancho!!!\n");
                printf("Ingrese cedula nuevamente\n");
                ciIguales=true;
            }
        }
    }while(ciIguales);
    do{
        i=0;
        salir=false;
        nickIguales=false;
        printf("Ingrese nickname: ");
        leoNombres(ret.nickname,cantNombre);
        while(i<cantJugadores and !salir){
            iguales=strcmp(ret.nickname,player.lista[i].nickname);
            if(iguales==0 && player.ocupado[i]==true){
                salir=true;
                printf("Ingrese otro nickname ese ya esta en uso.\n");
                nickIguales=true;
            }
            i++;
        }
    }while(nickIguales);
    printf("Edad: ");
    getchar();
    ret.edad=leo(arr,cantNombre);
    printf("Ingrese el nombre: ");
    leoNombres(ret.nombre,cantNombre);
    ret.saldo=5000;
    printf("Su saldo es de: %d\n\n",ret.saldo);
    ret.cont=0;
    for(i=0;i<3;i++){
        ret.arFinal[i]=0;
        ret.arInicial[i]=0;
    }
    return ret;
}

void registrarse(listaJugadores &player){
    int i=0;
    bool encontre=false;
    if(player.cantusuarios<cantJugadores){
        while(i<cantJugadores and !encontre){
            if(player.ocupado[i]==false){
                player.lista[i]=cargarJugador(player);
                player.ocupado[i]=true;
    		    player.cantusuarios++;
                encontre=true;
            }
            else{
                i++;
            }
        }
    }
    else{
        printf("Esta todo lleno.\n");
    }
}

bool logIn(listaJugadores player, int &lugaruser){
    char arr[cantNombre];
    bool sonIguales=false,igresoCorrectamente=true;
    int iguales;
    lugaruser=0;
    printf("Ingrese su nickname: ");
    scanf("%s",arr);
    while (!sonIguales and lugaruser<cantJugadores){
        iguales=strcmp(arr,player.lista[lugaruser].nickname);
        if(iguales==0 && player.ocupado[lugaruser]==true){
            sonIguales=true;
        }
        lugaruser++;
    }
    lugaruser--;
    if (sonIguales){
        printf("\n\tBienvenido %s\n",player.lista[lugaruser].nombre);
        printf("Su monto actual es de: %d\n\n",player.lista[lugaruser].saldo);
    }
    else{
        printf("Este nickname no está registrado.\n");
        igresoCorrectamente=false;
    }
    return igresoCorrectamente;
}

void modificarDatos(listaJugadores &player, int lugaruser){
    printf("Nickname nuevo: ");
    leoNombres(player.lista[lugaruser].nickname,cantNombre);
    printf("Edad: ");
    scanf("%d",&player.lista[lugaruser].edad);
    printf("CI: ");
    scanf("%d",&player.lista[lugaruser].CI);
    printf("Nombre: ");
    leoNombres(player.lista[lugaruser].nombre,cantNombre);
}

void funcionDelTop5(top5 deLoMejor, top5 masGanadores[], int &y){
    top5 copiaTemporal;
    while(deLoMejor.saldoGanado<masGanadores[y].saldoGanado && y<5){
        y++;
    }
    if(y<5){
        copiaTemporal=masGanadores[y];
        masGanadores[y]=deLoMejor;
        y++;
        funcionDelTop5(copiaTemporal,masGanadores,y);
    }
}

void jugarPartida (listaJugadores &player, int lugaruser, top5 masGanadores[]){
    top5 deLoMejor;
    int alazar,copa=0,victorias=0,cantCopa=0,apuesta=0,largo=20,multiplicador,perdidaTotal=0,perdidaParcial=0,saldo,y=0;
    char arreglo[20];
    bool comando,seguir=true;
    saldo=player.lista[lugaruser].saldo;
    if(player.lista[lugaruser].cont==3){
        player.lista[lugaruser].cont=0;
    }
    player.lista[lugaruser].arInicial[player.lista[lugaruser].cont]=saldo;
    deLoMejor.saldoInicial=saldo;
    strcpy(deLoMejor.nickName,player.lista[lugaruser].nickname);
    intrucciones();
    if(saldo>=50){
        printf("\nElige cuantas copas (de 3 a 9). Más copas, más ganas.Cuántas serán?\n\n");
        cantCopa=verficarCantCopas(arreglo,largo);
        printf("\n");
        while(seguir){
            comando=true;
            muestroCopas(cantCopa);
            printf("Copa?:\n");
            while(comando){
                comando=verificarCopa(arreglo,largo,victorias,perdidaTotal,saldo,perdidaParcial,copa,cantCopa,apuesta);
            }
            if(copa!=-1 && saldo>=50){
                alazar=ubicacionPelotita(cantCopa,victorias,copa);
                ubicacionGrafica(cantCopa,alazar);
                if(alazar==copa){
                    multiplicador=multiplicarApuesta(cantCopa);
                    vicroriaAcertada(saldo,apuesta,victorias,multiplicador,perdidaParcial);
                }
                else{
                    derrotaContundente(saldo,apuesta,victorias,perdidaParcial,perdidaTotal);
                }
                if(saldo<50){
                    printf("Para jugar hay que pagar.\n");
                    seguir=false;
                }
            }else{
                seguir=false;
            }
            printf("\n");
        }
    }else{
        printf("No tiene Saldo Suficiente. \n");
    }
    player.lista[lugaruser].saldo=saldo;
    player.lista[lugaruser].arFinal[player.lista[lugaruser].cont]=saldo;
    player.lista[lugaruser].cont++;
    deLoMejor.saldoFinal=saldo;
    if(deLoMejor.saldoFinal-deLoMejor.saldoInicial>0){
        deLoMejor.saldoGanado=deLoMejor.saldoFinal-deLoMejor.saldoInicial;
        funcionDelTop5(deLoMejor,masGanadores,y);
    }
}

bool menuUsuario(char opcMC, top5 masGanadores[], listaJugadores &player, int lugaruser){
    bool repetirMC;
    int i;
    switch (opcMC){
        case 'J':case 'j':
            jugarPartida(player,lugaruser,masGanadores);
            repetirMC=true;
        break;
        case 'U':case 'u':
            for(i=0;i<3;i++){
                printf("Saldo Inicial: %d \t Saldo Fina: %d \t\n",player.lista[lugaruser].arInicial[i],player.lista[lugaruser].arFinal[i]);
            }
            repetirMC=true;
        break;
        case 'T':case 't':
            for(i=0;i<5;i++){
                if(masGanadores[i].saldoGanado>0){
                    printf("Usuario: %s \t Saldo Inicial: %d \t Saldo Fina: %d \t\n",masGanadores[i].nickName,masGanadores[i].saldoInicial,masGanadores[i].saldoFinal);
                }
            }
            repetirMC=true;
        break;
        case 'C':case 'c':
            printf("Nos vemos la próxima.\n\n");
            repetirMC=false;
        break;
        case 'M':case 'm':
            modificarDatos(player,lugaruser);
            repetirMC=true;
        break;
        case 'D':case 'd':
            player.ocupado[lugaruser]=false;
            printf("Te diste de baja.\n");
            repetirMC=false;
        break;
        default:
            printf("ERROR: Opcion Incorrecta:\n\n");
            repetirMC=true;
        break;
    }
    return repetirMC;
}

void secondMain(listaJugadores &player,top5 mejoresPlayer[]){
    int i,lugaruser;
    char opcMI,opcMC;
    bool igresoCorrectamente=false,opcionCorrecta=false,repetirMI;
    player.cantusuarios=0;
    for(i=0;i<cantJugadores;i++){
        player.ocupado[i]=false;
    }
    for(i=0;i<5;i++){
        mejoresPlayer[i].saldoGanado=0;
    }
    do{
        opcMI=instruccionesMI();
        switch (opcMI){
            case 'I':case 'i':
                do{
                    igresoCorrectamente=logIn(player,lugaruser);
                    getchar();
                    do{
                        if(igresoCorrectamente){
                            opcMC=instruccionesMC();
                            opcionCorrecta=menuUsuario(opcMC,mejoresPlayer,player,lugaruser);
                        }
                    }while(opcionCorrecta);
                igresoCorrectamente=opcionCorrecta;
                }while(igresoCorrectamente);
                repetirMI=true;
            break;
            case 'R':case 'r':
                registrarse(player);
                repetirMI=true;
            break;
            case 'L':case 'l':
                for(i=0;i<cantJugadores;i++){
                    if(player.ocupado[i]==true){
                        printf("Nickname: %s\t Nombre: %s\t Edad: %d\t Saldo: %d\n",player.lista[i].nickname,player.lista[i].nombre,player.lista[i].edad,player.lista[i].saldo);
                    }
                }
                repetirMI=true;
            break;
            case 'S':case 's':
                printf("Nos vemos la próxima.\n");
                repetirMI=false;
            break;
            default:
                printf("ERROR: Opcion Incorrecta:\n\n");
                repetirMI=true;
            break;
        }
    }while(repetirMI);
}
