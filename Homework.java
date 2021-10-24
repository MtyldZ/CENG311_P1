import java.io.File;
import java.io.FileNotFoundException;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Date;

public class Homework {

    public static int[] values = new int[(int) Math.pow(2, 28)];
    public static int length = 0;
    
     private static void queue(int[] a) {
        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(length);
        for (int i = 0; i < length; i++)
            priorityQueue.add(a[i]);
        //       System.out.println(priorityQueue);
    }

    public static void main(String[] args) {
    	String filePath = "input-2^26.txt";
        try {
            File file = new File(filePath);
            Scanner reader = new Scanner(file);
            System.out.println("Starting The file reading process... name: " + filePath);
            while (reader.hasNext()) {
                String data = reader.next();
                
            	values[length] = Integer.parseInt(data);
                length++;
            }
            System.out.println("Finishing The file reading process...");
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.printf("An error occurred. Name: " + filePath);
            e.printStackTrace();
        }
        System.out.println("Starting The Queue process...");
        double startTime = (new Date()).getTime();
        queue(values);
        double stopTime = (new Date()).getTime();
        System.out.println("Finishing The Queue process...");
        System.out.printf("Queue process is done. Time spent " + String.format("%.9f", (stopTime - startTime) / 1000.0) + " seconds.");

    }
}
