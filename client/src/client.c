#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip = "127.0.0.1";
	char* puerto = "37373";
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	// Loggeamos el valor de config

	config = iniciar_config();

	char* clave = config_get_string_value (config, "CLAVE");
	log_info(logger, clave);


	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	//enviar_mensaje(clave, socket_cliente);
	
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "first log", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create ("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	// La primera te la dejo de yapa
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	// ¡No te olvides de liberar las lineas antes de regresar!
	char* leido;
	
	leido = readline("> ");

	while(strcmp(leido, "")){
		//log_info(logger, leido);
		free(leido);

		leido = readline("> ");
	}
	
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = readline("> ");
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	while(strcmp(leido, "")){
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
        free(leido);
        leido = readline("> ");
	}

	enviar_paquete(paquete, conexion);

	free(leido);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
