package tarea;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class MyThread extends Thread {

    int low, high;
    List<Long> arr;

    public MyThread(List<Long> S, int A, int D) {
        this.arr = S;
        this.low = A;
        this.high = D;
    }

    public int particion(List<Long> array, int low, int high) {

        Long pivote = array.get(high);
        //System.out.println("Pivot: " + pivote);

        int i = (low - 1);
        Long temp1, temp2;

        // System.out.println("Array en PART ANTES: " + arr.toString());

        for (int j = low; j < high; j++) {
            if (array.get(j) > pivote) {
                i++;
                temp1 = array.get(i);
                temp2 = array.get(j);
                array.set(i, temp2);
                array.set(j, temp1);
            }
        }

        temp1 = array.get(i + 1);
        temp2 = array.get(high);
        array.set(i + 1, temp2);
        array.set(high, temp1);

        // System.out.println("Array en PART DESP: " + arr.toString());

        return i + 1;
    }

    public void run() {
        recursion(this.arr, this.low, this.high);
    }

    public void recursion(List<Long> array, int low, int high) {

        if (low < high) {

            int part = particion(this.arr, this.low, this.high);

            MyThread hijoI = new MyThread(this.arr, this.low, part - 1);
            hijoI.start();

            try {
                hijoI.join();
            } catch (Exception e) {
            }

            MyThread hijoD = new MyThread(this.arr, part + 1, this.high);
            hijoD.start();

            try {
                hijoD.join();
            } catch (Exception e) {
            }
        }

    }
}

public class Parte2 extends Thread {

    public void Parte_2() {

        Scanner scan = new Scanner(System.in);

        System.out.print("Ingrese cantidad de elementos del arreglo: ");

        int n = scan.nextInt();

        List<Long> arr = new ArrayList<Long>();

        for (int i = 0; i < n; i++) {

            arr.add(scan.nextLong());
        }

        System.out.println("Array Antes de ser ordenado: " + arr.toString());

        MyThread sort = new MyThread(arr, 0, n - 1);

        sort.start();

        try {
            sort.join();
        } catch (Exception e) {
        }

        System.out.println("Sorting... Beep Boop");

        System.out.println("Array Después de ser ordenado: " + arr.toString());
        System.out.println("funciono 2");

        scan.close();

    }

}
