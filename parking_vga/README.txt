parking_vga

Objetivos:
    -Gestión de ocupación de plazas en un parking
    -Visualizar el layout del parking con un circulo de color en cada plaza, que indica el estado.
    -Estados:
        - Verde: Libre
        - Rojo: Ocupado
        - Amarillo: Ocupando (Transición de verde a rojo, pasa a rojo en 5 segundos)
        - Morado: Librando (Transición de rojo a verde, pasa a verde en 5 segundos)
        - Gris: Indeterminado
    -Forzar estados, administrador fuerza que una plaza se muestre de un estado permanentemente.
    -Implementación:
        - Estados y ordenes de forzado con botones y switches
        - Layout se muestra por VGA a tiempo real
        - Datos de layout e imagen de fondo cargados de ficheros en tarjeta SD (json & BMP)

Implementado actualmente:
    -VGA (imagenes BMP, circulos, rectangulos y texto), timer, gpio, stdio, ficheros y otros
	-Parsear configuracion JSON
	-Logica de estados de las plazas de parking
	-Visualizacion del parking con estados de las plazas
	-Libreria de maquinas de estado
		-Modificada para poder pasar parametros a las funciones
	-La configuracion de prueba parking.json

Librerías externas:
	-hal/vga/*
	-lib/font8x8.h
	-lib/json.h, lib/json.c
	
Estructura de carpetas:
	-config: obtencion de implementaciones para interfaces genéricas
    -domain: solucion del problema especifico (parking)
    -hal: implementaciones para la ZYBO 7000 de interfaces en io
    -io: interfaces abstractas portables
    -lib: implementaciones portables de interfaces en io y otros componentes (parsear fichero BMP...)

Templates:
    -Se ha seguido el template definido y se han añadido comentarios para generar la documentación doxygen
