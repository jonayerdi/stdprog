Cambios realizados a Doxyfile:
	- Poner PROJECT_NAME y PROJECT_BRIEF
	- Poner PROJECT_LOGO
	- Poner OPTIMIZE_OUTPUT_FOR_C a YES
	- Añadir la carpeta src a INPUT
	- Añadir parking_state_machine.png a IMAGE_PATH
	- Poner carpeta docs como OUTPUT_DIRECTORY
	- Poner RECURSIVE a YES, ya que se usan subcarpetas en src
	- Añadir a EXCLUDE los ficheros importados (no estan comentados para doxygen):
		- src/hal/vga/*
		- src/lib/font8x8.h
		- src/lib/json.*
		- src/lib/state_machine.*
	- Poner SOURCE_BROWSER a YES 
	- Poner GENERATE_LATEX a NO 
	- Configurar el uso de la herramienta dot de GraphViz:
		- Poner HAVE_DOT a YES
		- Configurar el DOT_PATH
		- Poner CALL_GRAPH a YES
		- Poner CALLER_GRAPH a YES

Motivacion de la documentacion:
	- Se han documentado todas las funciones con una breve descripcion de lo que hacen, 
	la descripcion de cada parametro, y los posibles valores de retorno, con el fin de 
	facilitar la tarea de comprender el funcionamiento de cada modulo y de saber como
	utilizarlo, puesto que gran parte del codigo es la API de desarrollo que presumiblemente
	se usaria para otros proyectos.
	- Se ha creado una imagen con la maquina de estados de las plazas de parking con
	el fin de ayudar a comprender el comportamiento que tiene que tener esta aplicacion
	en concreto. Esta imagen se muestra en la documentacion de domain/parking_spot_state_machine.h
	y domain/parking_spot_state_machine.c, que son los ficheros donde se implementa
	esta maquina de estados.
	