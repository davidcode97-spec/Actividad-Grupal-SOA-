#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void revisionFicheros() {
    /*Variables que almacenan las rutas*/
    char ruta[500];
    char rutaCompleta[1000];

    DIR *directorio;
    struct dirent *entrada;
    struct stat infoArchivo;

    FILE *salida;

    printf("\n Revision de ficheros\n");

    getchar();
    /*Se introduce ruta que se revisará contenido 
    La ruta puede contener espacios, ya que se reemplazó scanf por fgets */
    printf("Introduzca la ruta del directorio: ");
    fgets(ruta, sizeof(ruta), stdin);
    /*Elimina el /n que agrega fgets al extraer ruta */
    ruta[strcspn(ruta, "\n")] = '\0';
    /*Intenta abrir directorio de la ruta indicada*/
    directorio = opendir(ruta);
    /*Aplica condición si el directorio no existe o no puede abrirse mostrará mensaje de error*/
    if (directorio == NULL) {
        perror("Error al abrir el directorio");
        return;
    }
    /*Si logra abrir se escribirá en archivo txt */
    salida = fopen("listado_ficheros.txt", "w");
    /*Si no se puede crear archivo, se finaliza función*/
    if (salida == NULL) {
        perror("Error al crear listado_ficheros.txt");
        closedir(directorio);
        return;
    }

    fprintf(salida, "Listado de ficheros del directorio: %s\n\n", ruta);
    fprintf(salida, "%-35s %-15s %-30s\n", "Nombre", "Tamaño(bytes)", "Ultima modificacion");
    fprintf(salida, "--------------------------------------------------------------------------------\n");
    /*Recorre el contenido del directorio*/
    while ((entrada = readdir(directorio)) != NULL) {
        /*No considera . y .. como parte de las rutas a construir*/
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        /*Muestra la ruta completa de los ficheros encontrados en el directorio ruta + fichero*/
        snprintf(rutaCompleta, sizeof(rutaCompleta), "%s/%s", ruta, entrada->d_name);
        /*Obtiene info del fichero */
        if (stat(rutaCompleta, &infoArchivo) == -1) {
            perror("Error al obtener informacion del fichero");
            continue;
        }

        /*
         * Solo se listan ficheros no otros elementos
         */
        if (S_ISREG(infoArchivo.st_mode)) {

            char fecha[100];
            /*Formatea la fecha almacenada*/
            struct tm *tiempo = localtime(&infoArchivo.st_mtime);
            /*Imprimir nombre del fichero, tamaño y fecha*/
            strftime(fecha, sizeof(fecha), "%d/%m/%Y %H:%M:%S", tiempo);

            fprintf(
                salida,
                "%-35s %-15lld %-30s\n",
                entrada->d_name,
                (long long) infoArchivo.st_size,
                fecha
            );
        }
    }

    fclose(salida);
    closedir(directorio);

    printf("\nArchivo listado_ficheros.txt creado correctamente.\n");
}