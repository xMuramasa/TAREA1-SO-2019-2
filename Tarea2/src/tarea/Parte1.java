package tarea;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.List;
import java.util.regex.Pattern;
import java.util.Scanner;
import java.util.regex.Matcher;
// ∗
public class Parte1 extends Thread{

    public int result;
    public HashMap<String,String> map;
    public List<String> Lines;
    String buffer1;
    String buffer2;
    Scanner scanner;
    int i = 1;

    public Parte1(){
        
        map = new HashMap<>();
        Lines = readFile("Inputs/funciones.txt");
        result = 0;

        for (String string : Lines) {
            scanner = new Scanner(string);

            if(string.indexOf('=') != -1 ){

                scanner.useDelimiter("=");

                buffer1 = scanner.next();
                buffer1 = buffer1.replace("(x)","");

                buffer2 = scanner.next();
                buffer2 = buffer2.replace("(x)","");


                // yasu regex piola
                Pattern pattern1 = Pattern.compile("\\(\\w([*|/|+|-]\\w)+\\)");
                String temp;
                Matcher matcher1;

                matcher1 = pattern1.matcher(buffer2);

                while (matcher1.find()) {
                    temp = matcher1.group().replace("(", "").replace(")", "");
                    map.put("&" + String.valueOf(i), temp);
                    buffer2 = buffer2.replace(matcher1.group(), "&" + String.valueOf(i) + "");
                    i++;

                }

                map.put(buffer1, buffer2);
            }
            scanner.close();
        }      
    }

    public void printMap() {
        System.out.println(map.toString());
    }

    public void Parte_1() {

        // codigoooooooooooooooooo
        System.out.println("Introduzca sentencia a evaluar: ");

        Scanner scannerInput = new Scanner(System.in);
        String[] parts = scannerInput.next().split("\\(");
        

        System.out.println("funciono 1");//

        String function = parts[0];
        String value = parts[1].replace(")","");


        MyThread2 nomasfunciones = new MyThread2(map, function, Integer.parseInt(value));
        nomasfunciones.start();
        
        try {
            nomasfunciones.join();
        } catch (Exception e) {
        }

        System.out.println("Resultado = "+ nomasfunciones.getRes());

        
        

        //llamar recursion(function,value)

        scannerInput.close();

    }

    int count(String ec) {
        int result = 0;
        for (int k = 0; k < ec.length(); k++) {
            if ((ec.charAt(k) == '+') || (ec.charAt(k) == '*') || (ec.charAt(k) == '/') || (ec.charAt(k) == '-') ) {
                    result++;
                }
        }
        return result;
    }


    // DONT TOUCH!
    /**
     * Open and read a file, and return the lines in the file as a list of Strings.
     * (Demonstrates Java FileReader, BufferedReader, and Java5.)
     */
    private List<String> readFile(String filename) {
        String line;
        BufferedReader reader = null;
        List<String> records = new ArrayList<String>();
        try {
            reader = new BufferedReader(new FileReader(filename));
            while ((line = reader.readLine()) != null) {
                records.add(line);
            }
            reader.close();
            return records;
        } catch (Exception e) {
            System.err.format("Exception occurred trying to read '%s'.", filename);
            e.printStackTrace();
            return null;
        }
    }
}

class MyThread2 extends Thread {
  
  private int res; 
  private HashMap<String, String> map; 
  private String ecuacion; 
  private int value;
  
  // constructor de la clase ok 
  public MyThread2(HashMap<String, String> M,String E, int val) { 
      this.map = M; 
      this.ecuacion = E; 
      this.value = val; 
    }
    
    public int getRes(){
        return this.res;
    }

    public void run() {
        this.res = parse(this.ecuacion, this.value);
    }
    // ok public 
    int operation(String operator, int a, int b) { 
        int result = 0;
        switch (operator) {
            case "+": 
                result = a + b;
                break; 
            case "-": 
                result = a - b; 
                break; 
            case "/": 
                result = a / b;
                break; 
            case "*": 
                result = a * b;
                break;
            default: 
                return 0; 
        }
        return result; 
    }

    
    public int parse(String ecuation, int value){
    
        int res = 0;
        String num1 = "";
        String num2 = "";
        String op = "";
        int flag = 0;

        
        String fun = map.get(ecuation);
        System.out.println(fun);


        
        for(int k = 0; k < fun.length(); k++){
            //System.out.println(fun.charAt(k));
            if(flag == 0 && (fun.charAt(k) == '*') || (fun.charAt(k) == '/') || (fun.charAt(k) == '+') || (fun.charAt(k) == '-')){
                flag = 1;
                op = op.concat(String.valueOf(fun.charAt(k)));
            }
            else if (flag == 0){
                num1 = num1.concat(String.valueOf(fun.charAt(k)));
            }
            else{
                num2 = num2.concat(String.valueOf(fun.charAt(k)));
            }
        }
        System.out.println("---------------");
        System.out.println(num1);
        System.out.println(op);
        System.out.println(num2);
        System.out.println("---------------");


        if (num1.equals("x")){
            res = res + value;
        }
        else if ( ! (num1.equals("1") || num1.equals("2") || num1.equals("3") || num1.equals("4") || num1.equals("5")|| num1.equals("6")|| num1.equals("7")|| num1.equals("8") || num1.equals("9"))){
            System.out.println("in if");
            res = parse(num1,value);
            //aqui va thread
        }
        else{
            res = res + Integer.parseInt(num1); 
        }
        
        if (num2.equals("x")){
            res = res + value;
        }
        else if (!(num2.equals("1") || num2.equals("2") || num2.equals("3") || num2.equals("4") || num2.equals("5") || num2.equals("6") || num2.equals("7") || num2.equals("8") || num2.equals("9"))) {
            res = parse(num2, value);
            // thread goes here
        }
        else{
            res = res + Integer.parseInt(num2);
        }

        return res; 
    }
  }
 