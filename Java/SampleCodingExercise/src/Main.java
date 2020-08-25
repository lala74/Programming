import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // Speed Converter Test
        double value = SpeedConverter.toMilesPerHour(10.25);
        System.out.println(value);
        SpeedConverter.printConversion(-5);

        System.out.println("\n");

        // MegaBytes Converter Test
        MegaBytesConverter.printMegaBytesAndKiloBytes(2500);

        System.out.println("\n");

        // Barking Dog Test
        System.out.println(BarkingDog.shouldWakeUp(false, 2));

        System.out.println("\n");

        // Leap Year Calculator Test
        System.out.println(LeapYear.isLeapYear(2500));

        System.out.println("\n");

        // Get input from user
        Scanner scanner = new Scanner(System.in);	// create an instance of Scanner Class
        System.out.print("Enter your year of birth : ");
        int year = scanner.nextInt();
        scanner.nextLine();

        int age = 2019 - year;

        System.out.print("Enter Your Name : ");
        String name = scanner.nextLine();		    // get your input

        System.out.println("Your name is " + name + ". And your are " + age + " years old.");
        scanner.close();				            // close scanner



    }
}
