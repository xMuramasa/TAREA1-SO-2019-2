package tarea;
<<<<<<< HEAD

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.List;



public class Parte1 extends Thread{

    public int result;
    public HashMap<String,String> map;
    public List<String> Lines;
    String buffer1;
    String buffer2;
    Scanner scanner;
    
=======
/*
xd
*/
>>>>>>> 030fc5e761673ba1e48aef31107b9d850c8b4ba0

    public Parte1(){
        
        map = new HashMap<>();
        Lines = readFile("Inputs/funciones.txt");
        result = 0;

        for (String string : Lines) {
            scanner = new Scanner(string);

            if(string.indexOf('=') != -1 ){
                scanner.useDelimiter("=");
                buffer1 = scanner.next();
                buffer2 = scanner.next();
                map.put(buffer1, buffer2);
            }
            scanner.close();
        }
        System.out.println(map.get("f(x)").toString());
        
    }


    public void Parte_1(){
















        System.out.println("funciono 1");
    }


    public int operation(String operator, int a, int b){
        int result = 0;

        switch(operator){
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
    /**
     * Open and read a file, and return the lines in the file as a list
     * of Strings.
     * (Demonstrates Java FileReader, BufferedReader, and Java5.)
     */
    private List<String> readFile(String filename)
    {
        String line;
        BufferedReader reader = null;
        List<String> records = new ArrayList<String>();
        try
        {
            reader = new BufferedReader(new FileReader(filename));
            while ((line = reader.readLine()) != null)
            {
            records.add(line);
            }
            reader.close();
            return records;
        }
        catch (Exception e)
        {
            System.err.format("Exception occurred trying to read '%s'.", filename);
            e.printStackTrace();
            return null;
        }
    }
}