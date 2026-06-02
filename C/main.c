
void revisionFicheros();
void intervaloFicheros();
void ficherosID();

int main() {

    int opcion;

    do {
        printf("\n");
        printf("================================================\n");
        printf(" SISTEMAS OPERATIVOS AVANZADOS\n");
        printf("================================================\n");
        printf("1. Revisar ficheros de un directorio\n");
        printf("2. Buscar ficheros por intervalo de tamaño\n");
        printf("3. Buscar ficheros por ID de usuario\n");
        printf("0. Salir\n");
        printf("=============================================\n");
        printf("Seleccione una opcion: ");

        /*
         * Aquí tomamos la opción seleccionada desde el menú
         */
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                /*
                 * Llamamos a la función revisionFicheros.c
                 */
                revisionFicheros();
                printf("Fin de consulta\n");
                printf("_________");
                break;

            case 2:
                /*
                 * Llamamos a la función intervaloFicheros.c
                 */
                intervaloFicheros();
                printf("Fin de consulta\n");
                printf("__________");
                break;

            case 3:
                /*
                 * Llamamos a la función  ficherosID.c
                 */
                ficherosID();
                printf("Fin de consulta\n");
                printf("__________");
                break;

            case 0:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
                printf("Fin de consulta\n");
                printf("_____________");
                break;
        }

    } while (opcion != 0);

    return 0;
}