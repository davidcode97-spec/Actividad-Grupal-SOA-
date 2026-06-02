#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void intervaloFicheros() {
    /*Almacenamos rutas en variables*/
    char ruta[500];
    char rutaCompleta[1000];

    double tamanoMinimoMB;
    double tamanoMaximoMB;
    /*Se almacenan tamaños de los intervalos indicados comop input */
    long long tamanoMinimoBytes;
    long long tamanoMaximoBytes;

    int encontrados = 0;

    DIR *directorio;
    struct dirent *entrada;
    struct stat infoArchivo;

    printf("\nEjercicio 5 - Buscar ficheros por intervalo de tamaño\n");

   
    getchar();

    printf("Introduzca la ruta del directorio: ");
    fgets(ruta, sizeof(ruta), stdin);

    /*
     * Elimina el salto de línea final que añade fgets.
     */
    ruta[strcspn(ruta, "\n")] = '\0';
    /*Solicita tamañi mínimo y máximo*/
    printf("Introduzca el tamaño minimo en Megabytes: ");
    scanf("%lf", &tamanoMinimoMB);

    printf("Introduzca el tamaño maximo en Megabytes: ");
    scanf("%lf", &tamanoMaximoMB);
    /*Veririca tamaños indicados*/
    if (tamanoMinimoMB < 0 || tamanoMaximoMB < 0) {
        printf("\nError: los tamaños no pueden ser negativos.\n");
        return;
    }

    if (tamanoMinimoMB > tamanoMaximoMB) {
        printf("\nError: el tamaño minimo no puede ser mayor que el tamaño maximo.\n");
        return;
    }

    /*
     * Convierte de MB a bytes porque stat().st_size trabaja en bytes.
     */
    tamanoMinimoBytes = (long long)(tamanoMinimoMB * 1024 * 1024);
    tamanoMaximoBytes = (long long)(tamanoMaximoMB * 1024 * 1024);

    directorio = opendir(ruta);

    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return;
    }
    /*Muestra info de intervalo que se usará para la búsqueda*/
    printf("\nFicheros encontrados entre %.2f MB y %.2f MB:\n", tamanoMinimoMB, tamanoMaximoMB);
    printf("Ruta revisada: %s\n", ruta);
    printf("Equivalente en bytes: %lld - %lld\n", tamanoMinimoBytes, tamanoMaximoBytes);
    printf("--------------------------------------------------------------------------\n");
    /*Recorre las entradas del directorio*/
    while ((entrada = readdir(directorio)) != NULL) {

        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        /*Aquí se construye la ruta completa del directorio*/
        snprintf(rutaCompleta, sizeof(rutaCompleta), "%s/%s", ruta, entrada->d_name);
        /*Se obtiene info del tamaño, permisos, propietario, fechas, etc*/
        if (stat(rutaCompleta, &infoArchivo) == -1) {
            perror("Error al obtener informacion del fichero");
            continue;
        }

        if (S_ISREG(infoArchivo.st_mode)) {
            /*Comprueba si el tamaño del ficher está dentro del intervalo*/
            if (infoArchivo.st_size >= tamanoMinimoBytes &&
                infoArchivo.st_size <= tamanoMaximoBytes) {

                double tamanoArchivoMB = (double) infoArchivo.st_size / (1024 * 1024);

                printf("Nombre: %-35s Tamaño: %lld bytes / %.4f MB\n",
                       entrada->d_name,
                       (long long) infoArchivo.st_size,
                       tamanoArchivoMB);

                encontrados++;
            }
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron ficheros dentro del intervalo indicado.\n");
    }

    closedir(directorio);
}