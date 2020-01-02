package tarea;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


class MyThread extends Thread{

    int low, high;
    List<Integer> arr;

    public MyThread(List<Integer> S, int A, int D){
        this.arr =  S;
        this.low =  A;
        this.high = D;
    }

    public int particion(List<Integer> array, int low, int high) {

        int pivote = array.get(low);
        System.out.println("Pivot: " + pivote);

        int i = (low - 1);
        int temp1,temp2;
        
		
        for (int j = low; j < high; j++) {
            if (array.get(j) < pivote) {
                i++;
                temp1 = array.get(i);
                temp2 = array.get(j);
                array.set(i,temp2);
                array.set(j,temp1);
            }
        }
		
        temp1 = array.get(i+1);
        temp2 = array.get(high);
        array.set(i+1, temp2);
        array.set(high, temp1);
		
        return i + 1;
    }
    
    public void run() {
		recursion(this.arr, this.low, this.high);
	}

	public void recursion(List<Integer> array, int low, int high) {

		if (low < high) {
	
			int part = particion(this.arr, this.low, this.high);
	
			MyThread hijoI = new MyThread(this.arr, this.low, part-1);
			hijoI.start();

            try{
                hijoI.join();
            }catch(Exception e){
                System.out.println("Me Cai hijo 1");
            }
            
            MyThread hijoD = new MyThread(this.arr, part+1, this.high);
            hijoD.start();
            

            try{
                hijoD.join();
            }catch(Exception e){
                System.out.println("Me Cai hijo 2");
            }
		}

	}
}

public class Parte2 extends Thread{
    

    public void Parte_2(){
        
        Scanner scan = new Scanner(System.in);
        
        System.out.print("Ingrese cantidad de elementos del arreglo: ");
        
        int n = scan.nextInt();

        List<Integer> arr = new ArrayList<Integer>();
        
        for(int i = 0; i < n; i++){
			
            arr.add(scan.nextInt());
		}
		
        System.out.println("Array Antes de ser ordenado: " + arr.toString());

        MyThread sort = new MyThread(arr, 0, n-1);
        
        sort.start();

        try {
			sort.join();
		} catch (Exception e) {}
             
        System.out.println("Sorting... Beep Boop");

        System.out.println("Array Después de ser ordenado: " + arr.toString());
        System.out.println("funciono 2");

        scan.close();
            
	}
	
}

// 15, 0, 28, 1, 78, 79, 365, 456, 752, 1024
 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 