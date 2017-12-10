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
	-Logica de estados de las plazas de parking
	-Visualizacion del parking con estados de las plazas

Falta implementar:
    -Parsear configuracion (imagen de fondo, posiciones plazas... en fichero json)
		-Ahora mismo estos datos estan metidos a mano en la funcion parking_init
	-Integrar la libreria de maquinas de estado para las plazas
	-Implementar hal/axi_gpio para acceder a los switches y botones de la FPGA
	-Simular estados forzados con switches
	
Estructura de carpetas:
    -domain: solucion del problema especifico (parking)
    -hal: implementaciones para la ZYBO 7000 de interfaces en io
    -io: interfaces abstractas portables
    -lib: implementaciones portables de interfaces en io y otros componentes (parsear fichero BMP...)

Templates:
    -Se ha seguido el template definido para el proyecto en io/gpio.h e io/gpio.c como prueba
