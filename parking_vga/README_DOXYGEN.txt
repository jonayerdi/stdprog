Cambios realizados a Doxyfile:
	- Poner PROJECT_NAME y PROJECT_BRIEF
	- Poner OPTIMIZE_OUTPUT_FOR_C a YES
	- Añadir la carpeta src a INPUT
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
	