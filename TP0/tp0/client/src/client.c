#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	log_info(logger, "Iniciare la creacion del config");
	
	config = iniciar_config();

	log_info(logger, "Se creó el Config");

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP");
	log_info(logger, "Se cargó la configuración con los valores: \n IP: %s", ip);

	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, "Se cargó la configuración con los valores: \n PUERTO: %s", puerto);

	valor = config_get_string_value(config, "CLAVE");

	log_info(logger, "Se cargó la configuración con los valores: \n CLAVE: %s", valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	if (conexion == 0){
		log_info(logger, "Error al establecer una conexion con el servidor");
		exit(1);
	}

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);
	log_info(logger, "Se envio al servidor el mensaje CLAVE: %s", valor);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "INICIAR LOG", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	//t_config* nuevo_config = config_create("cliente.config");

	t_config* nuevo_config;

	if ((nuevo_config = config_create("../cliente.config")) == NULL) { 
					  ^^^^^^^^^^^^^^^^^^^^^
	// Como el cwd de linux es la propia carpeta de donde está el proceso, es necesario el ".."
	// Si querés que te ande en el VS, poné solo "cliente.config" y va a andar. De última, podes cambiar
	// el cwd en el settings.json (Hay una guía en el docs de Rutas relativas que te puede ayudar.)
		
		printf("No pude crear el config");
		exit(2);
	}

	return nuevo_config;
}


void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	while (*leido != '\0'){
		log_info(logger, leido);
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las lineas antes de regresar!

	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	leido = readline("> ");
	while (*leido != '\0'){
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		leido = readline("> ");
	}

	enviar_paquete(paquete, conexion);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
	eliminar_paquete(paquete);
	free(leido);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	if (logger != NULL){
		log_destroy(logger);
	}
	if (config != NULL){
		config_destroy(config);
	}
	if(conexion != 0){
		close(conexion);
	}
}
