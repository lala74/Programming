package com.minhduc;

import java.util.ArrayList;

public class GroceryList {
    private ArrayList<String> groceryList = new ArrayList<>();

    public void addGroceryItem(String item) {
        groceryList.add(item);
    }

    public void printGroceryList() {
        System.out.println("You have " + groceryList.size() + " items in Grocery List");
        for(int i=0; i<groceryList.size(); i ++) {
            System.out.println((i+1) + ". " + groceryList.get(i));
        }
    }

    public void modifyGroceryItem(int position, String newItem) {
        groceryList.set(position, newItem);
        System.out.println("Grocery item " + position + " has been changed to " + newItem);
    }

    public void removeGroceryItem(int position) {
        groceryList.remove(position);
    }

    public String findGroceryItem(String item) {
        // boolean exist = groceryList.contains(item);
        int position = groceryList.indexOf(item);
        if (position >= 0) {
            return  groceryList.get(position);
        } else {
            return null;
        }
    }
}
