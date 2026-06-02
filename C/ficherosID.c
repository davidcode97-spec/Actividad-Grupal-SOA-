#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void ficherosID() {

    char ruta[500];
    char rutaCompleta[1000];

    int uidBuscado;
    int encontrados = 0;

    DIR *directorio;
    struct dirent *entrada;
    struct stat infoArchivo;

    printf("\nEjercicio 6 - Buscar ficheros por UID\n");

    getchar();

    printf("Introduzca la ruta del directorio: ");
    fgets(ruta, sizeof(ruta), stdin);

    ruta[strcspn(ruta, "\n")] = '\0';

    printf("Introduzca el UID del usuario: ");
    scanf("%d", &uidBuscado);

    directorio = opendir(ruta);

    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return;
    }

    printf("\nFicheros propiedad del UID %d:\n", uidBuscado);
    printf("Ruta revisada: %s\n", ruta);
    printf("------------------------------------------------------------\n");
    /*Recorre las entradas del directorio*/
    while ((entrada = readdir(directorio)) != NULL) {

        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        /*Construye ruta completa del fichero*/
        snprintf(rutaCompleta, sizeof(rutaCompleta), "%s/%s", ruta, entrada->d_name);

        if (stat(rutaCompleta, &infoArchivo) == -1) {
            perror("Error al obtener informacion del fichero");
            continue;
        }

        if (S_ISREG(infoArchivo.st_mode)) {
            /*Compara UIDs del propietario y del usuario*/
            if (infoArchivo.st_uid == uidBuscado) {
                printf("Nombre: %-35s UID propietario: %d\n",
                       entrada->d_name,
                       infoArchivo.st_uid);

                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron ficheros para el UID indicado.\n");
    }

    closedir(directorio);
}