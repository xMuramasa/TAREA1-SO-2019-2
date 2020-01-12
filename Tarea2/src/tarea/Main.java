package tarea;

import java.util.Scanner;

public class Main {

	public static void main(String[] args)  {

		Parte1 p1 = new Parte1();
		Parte2 p2 = new Parte2();

		Scanner input = new Scanner(System.in);

		System.out.println("Seleccione parte de la tarea a correr:");
		System.out.println("[1] Parte 1\n[2] Parte 2");

		boolean flag = true;

		while (flag) {

			int usrInput = input.nextInt();

			System.out.println("Ha seleccionado " + usrInput);

			if (usrInput == 1) {
				try{
					p1.Parte_1();
					// p2.Parte_2();
					flag = false;
				}catch(Exception e){
					
				}
				p1.Parte_1();
				// p2.Parte_2();
				flag = false;
				
			} else if (usrInput == 2) {
				p2.Parte_2();
				// p1.Parte_1();
				flag = false;
			} else {
				System.out.println("Seleccione nuevamente");
			}
		}
		input.close();
	}

}