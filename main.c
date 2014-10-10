#ifdef __linux__
#define LIMPIAR "CLEAR"
#endif // __linux__

#ifdef __MINGW32__
#define LIMPIAR "CLS"
#endif // __MINGW32__

#ifdef __MINGW64__
#define LIMPIAR "CLS"
#endif // __MINGW64__


#include <stdio.h>
#include <stdlib.h>

#define MAX_CAMPO 15
#define DELIM_CAMPO ':'
#define DELIM_REG '#'
#define tam_cadena 15

int readFile(char *nomFile, char delimCampo, char delimRegistro);
void addRegistro(char *nomFile, char delimCampo, char delimRegistro);
void readLine(char cadena[], int tam);
void createFile(char* nameFile);
int readInt();

int main(int argc, char *argv[])
{
    int op = 0;
    char nom_file[tam_cadena];
    do{
        system(CLEANER);
        printf("\n\t\t##                                                      ##");
        printf("\n\t\t# | >>_ _ _ _++=[-> SIST. ARCHIVOS RLV <-]=++_ _ _ _<< | #");
        printf("\n\t\t# | >_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ < | #");
        printf("\n\t\t# | >                                                < | #");
        printf("\n\t\t# | >              [x1] Crear Fichero                < | #");
        printf("\n\t\t# | >              [x2] Agregar Usuario              < | #");
        printf("\n\t\t# | >              [x3] Mostrar Fichero              < | #");
        printf("\n\t\t# | >              [x4] Salir                        < | #");
        printf("\n\t\t# | >_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ < | #");
        printf("\n\t\t##                                                      ##");
        printf("\n\t\t\t        Ingrese opcion opcion: ");
        op = readInt();
        switch(op){
            case 1: printf("\n\t\t\t    Ingrese nombre de archivo: ");
                    readLine(nom_file,tam_cadena);
                    createFile(nom_file);
                    break;
            case 2: printf("\n\t\t\t    Ingrese nombre de archivo: ");
                    readLine(nom_file,tam_cadena);
                    addRegistro(nom_file,DELIM_CAMPO,DELIM_REG);
                    break;
            case 3: printf("\n\t\t\t    Ingrese nombre de archivo: ");
                    readLine(nom_file,tam_cadena);
                    system(CLEANER);
                    printf("\n\t      Nombre   ApellidoP   ApellidoM      DNI            Sexo\n");
                    printf("\t=============================================================\n\t");
                    readFile(nom_file,DELIM_CAMPO,DELIM_REG);
                    fgetchar();
                    break;
            case 4: printf("\n\t\t\t    Good bye :)");
                    break;
            default:printf("\n\t\t\t    [msgError]: Opcion no valida.");
        }
    }while(op!=4);
    return 0;
}

int readInt()
{
  char buf[BUFSIZ];
  char *p;
  long int i;

  if (fgets(buf, sizeof(buf), stdin) != NULL)
  {
    i = strtol(buf, &p, 10);
    if (buf[0] != '\n' && (*p == '\n' || *p == '\0'))
      return i;
  }
}

void readLine(char cadena[], int tam)
{
    char c;
    fgets(cadena,tam,stdin);
    if (cadena[strlen(cadena)-1] == '\n')
        cadena[strlen(cadena)-1] = '\0';
    else
    {
        cadena[tam-1] = '\0';
        while((c = getchar()) != '\n'){};
    }
}

void createFile(char* nameFile)
{
    FILE* fd;
    fd = fopen(nameFile,"wt");
    fclose(fd);
}


int readFile(char *nomFile, char delimCampo, char delimRegistro)
{

    FILE* fd;

    if( ( fd=fopen(nomFile,"rt")) == NULL )
    {
        printf("\n\t\t\t    [msgError]: No se pudo abrir el archivo.");
        return -1;
    }
    else
    {
        fseek(fd,0,0);
        int i=0;
        char buffer[MAX_CAMPO];
        while( !feof(fd) ){

            buffer[i++] = fgetc(fd);

            if( buffer[i-1] == delimCampo)
            {
                buffer[i-1] = '\0';
                printf("% 12s",buffer);
                i = 0;
            }

            if( buffer[i-1] == delimRegistro)
            {
                buffer[i-1] = '\0';
                i = 0;
                printf("% 12s\n\t",buffer);
            }
        } // Fin de while
        fclose(fd);
    }
    return 0;
}

void addRegistro(char *nomFile, char delimCampo, char delimRegistro)
{

    FILE* fd;

    if( ( fd=fopen(nomFile,"a+t")) == NULL )
    {
        printf("\n\t\t\t    MSG => No se pudo abrir el archivo.");
        return -1;
    }
    else
    {

        char buffer[tam_cadena];
        char sexo;
        fseek(fd,0,2);

        printf("\n\t\t\t    Nombre: ");
        readLine(buffer,tam_cadena);
        fputs(buffer,fd);
        fputc(DELIM_CAMPO,fd);

        printf("\n\t\t\t    Apellido Paterno: ");
        readLine(buffer,tam_cadena);
        fputs(buffer,fd);
        fputc(DELIM_CAMPO,fd);

        printf("\n\t\t\t    Apellido Materno: ");
        readLine(buffer,tam_cadena);
        fputs(buffer,fd);
        fputc(DELIM_CAMPO,fd);

        printf("\n\t\t\t    DNI: ");
        readLine(buffer,tam_cadena);
        fputs(buffer,fd);
        fputc(DELIM_CAMPO,fd);

        printf("\n\t\t\t    Sexo (M/F): ");
        sexo = fgetchar();
        fputc(sexo,fd);
        fputc(DELIM_REG,fd);
        while((getchar()) != '\n'){};
    }
    fclose(fd);
}
