package com.minhduc;

public class Main {

    public static void main(String[] args) {
        // write your code here   add
        Car toyota = new Car();
        toyota.setModel("1997");
        System.out.println("Your toyota model is " + toyota.getModel());

        Person Gift = new Person();
        Gift.setFirstName("Gift");
        System.out.println("Your name is " + Gift.getFirstName());
    }
}
