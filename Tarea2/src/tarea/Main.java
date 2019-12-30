package tarea;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        System.out.println("Seleccione parte de la tarea a correr:");
        System.out.println("[0] Parte 1\n[1] Parte 2");
        
        boolean flag = true;
        
        while(flag){
            
        int usrInput = input.nextInt();

        System.out.println("Ha seleccionado " + usrInput);

        if(usrInput == 0){
            Parte2();
            Parte1();
            flag = false;
        }
        else if(usrInput == 1){
            Parte2();
            Parte1();
            flag = false;
        }
        else{
            System.out.println("Seleccione nuevamente");
        }
        }
    }

}