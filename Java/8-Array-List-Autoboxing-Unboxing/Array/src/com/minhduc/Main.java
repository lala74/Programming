package com.minhduc;

import java.util.Scanner;

public class Main {

    private static Scanner scanner = new Scanner(System.in);
    private static GroceryList groceryList = new GroceryList();

    public static void main(String[] args) {
        boolean quit = false;
        int choice = 0;
        printInstruction();

        while(!quit) {
            System.out.printf("Enter your choice: ");
            choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 0:
                    printInstruction();
                    break;
                case 1:
                    groceryList.printGroceryList();
                    break;
                case 2:
                    addItem();
                    break;
                case 3:
                    modifyItem();
                    break;
                case 4:
                    removeItem();
                    break;
                case 5:
                    searchItem();
                    break;
                case 6:
                    System.out.println("Goodbye, see you later");
                    quit = true;
                    break;
            }
        }
    }

    public static void printInstruction() {
        System.out.println("Press :");
        System.out.println("0 - to display Instruction");
        System.out.println("1 - to display Grocery list");
        System.out.println("2 - to add item to Grocery list");
        System.out.println("3 - to modify item in Grocery list");
        System.out.println("4 - to remove an item");
        System.out.println("5 - to search for an item");
        System.out.println("6 - to quit app");
    }

    public static void addItem() {
        System.out.printf("Enter a grocery item: ");
        groceryList.addGroceryItem(scanner.nextLine());
    }

    public static void modifyItem() {
        System.out.printf("Enter position to modify item: ");
        int position = scanner.nextInt();
        scanner.nextLine();
        System.out.printf("Enter new grocery item: ");
        groceryList.modifyGroceryItem(position, scanner.nextLine());
    }

    public static void removeItem() {
        System.out.printf("Enter position of removing item: ");
        groceryList.removeGroceryItem(scanner.nextInt());
    }

    public static void searchItem() {
        System.out.printf("Enter item to search: ");
        String result = groceryList.findGroceryItem(scanner.nextLine());
        if (result != null) {
            System.out.println("We have found " + result);
        } else {
            System.out.println("Item is not on the Grocery List");
        }
    }

/***************************/
/**       Sort Array      **/
/***************************/
/**
    public static void main(String[] args) {
	// write your code here
        int len;
        System.out.println("Type length : \r");
        len = scanner.nextInt();
        scanner.nextLine();
        int[] myIntArray = new int[len];

        myIntArray = getIntegers(len);
        myIntArray = sortIntegers(myIntArray);
        printArray(myIntArray);
        scanner.close();
    }

    private static int[] getIntegers(int len) {
        int[] array = new int[len];
        for (int i=0; i<len; i++) {
            array[i] = scanner.nextInt();
        }
        return array;
    }

    private static void printArray(int[] array) {
        for (int i=0; i<array.length; i++) {
            System.out.println("Value of element " + i + " is : " + array[i]);
        }
    }

    private static int[] sortIntegers(int[] array) {
        int temp;
        for (int i=0; i<array.length-1; i++) {
            for (int j=0; j<array.length-1; j++) {
                if (array[j] < array[j+1]) {
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
        }
        return array;
    }
 **/
}
