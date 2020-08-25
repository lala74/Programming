package com.minhduc;

public class Main {

    public static void main(String[] args) {
	// write your code here
        double priceOfHamburgerGift;
        Hamburger hamburgerOfGift = new Hamburger("Gift", "Boeuf", "Long baguette", 3.5);
        hamburgerOfGift.addAddition1("Tomate", 1.2);
        hamburgerOfGift.addAddition2("Onion", 0.7);
        priceOfHamburgerGift = hamburgerOfGift.totalPrice();

        System.out.println("Total price is " + priceOfHamburgerGift);

        double priceOfHamburgerDuc;
        HealthyBurger hamburgerOfDuc = new HealthyBurger("Pork", 4.7);
        hamburgerOfDuc.addHealthyAddition1("Egg", 1.4);
        hamburgerOfDuc.addAddition1("Chicken", 2.5);
        priceOfHamburgerDuc = hamburgerOfDuc.totalPrice();

        System.out.println("Total price is " + priceOfHamburgerDuc);
    }
}
