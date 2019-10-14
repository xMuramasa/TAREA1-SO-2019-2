### TAREA1-SO-2019-2
# Repositorio de la Tarea 1 de Sistemas Operativos
# ENTREGA FINAL

			(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ) (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)


# LEER LAS INSTRUCCIONES DE ENTREGA 3
# Integrantes:
	
	- Nombre: ROL
	- Zhuo Chang 201773617-8 
	- Martín Salinas Scussolin 201773557-0

			
			(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)
					(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)


# Instrucciones de uso:
	
	** para correr el programa en una linea (make clean && make && make run)
   #### Entrega 1:
		** Funcionan todas las funciones que se encuentran comentadas **. 
		* Para probar funciones, editar el archivo main.c
		* Se compila usando make, dentro de la carpeta src (escribir en la consola: make)
		luego, ejecutar usando el comando: make run
					
					(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)
					
   #### Entrega 2:
		** Funciona todo lo que se encuentra comentado **
		* main.c contiene todo el trabajo de esta entrega, se hicieron las funciones: 
			play, printHand y se updatearon otras. 
		* los forks y sus respectivos pipes deberian funcionar correctamente
		* # El programa una vez corriendo, seguira infinitamente hasta que se haga un #ctrl+c 
		  en al consola, dado que no se han implementado la modalidad de juego.
	
						(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)
					
   #### Entrega 3:
		** Funciona todo lo que se encuentra comentado **
		* main.c contiene todo el trabajo de esta entrega, se hicieron las funciones: 
			drawDrop, createGame, entre otras. 
		* los forks y sus respectivos pipes deberian funcionar correctamente
		* # El programa cuenta con condicones de término y avisos de +2, +4, 
			cambio de color, etc.
		* EL PRIMER JUGADOR QUE JUEGUE UN REVERSA JUGARÁ 2 VECES, POR FAVOR CONSIDERAR ESTE CASO


						(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)
	

			(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧ ✧ﾟ･: *ヽ(◕ヮ◕ヽ)


# Responsabilidades de lo que se hizo (entrega 1):
	
	- Zhuo Chang: funcion createDeck, moveFileToFolder, myRemoveFile, Draw, checkCreate, checkMove.
	- Martín Salinas Scussolin: funcion myRmdir, myMkdir, createDeck, Draw, DrawHand, moveFileToFolder.

# Responsabilidades de lo que se hizo (entrega 2):
		
	- Zhuo Chang: Creacion y revision de forks y pipes. Funcion play.
	- Martín Salinas Scussolin: Revision de forks y pipes. Funcion play. Funcion printHand

# Responsabilidades de lo que se hizo (entrega 3):
		
	- Zhuo Chang: revision de pipes, comunicaion para caso REVERSE
	- Martín Salinas Scussolin: Funcion createGame. Funcion drawDrop, comentado del código
