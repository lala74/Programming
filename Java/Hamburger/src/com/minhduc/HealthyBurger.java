package com.minhduc;

public class HealthyBurger extends Hamburger {
    private String healthyAddition1Name;
    private double healthyAddition1Price;
    private String healthyAddition2Name;
    private double healthyAddition2Price;

    public HealthyBurger(String meat, double price) {
        super("Healthy Burger", meat, "Brown", price);
    }

    public void addHealthyAddition1(String name, double price) {
        this.healthyAddition1Name = name;
        this.healthyAddition1Price = price;
    }

    public void addHealthyAddition2(String name, double price) {
        this.healthyAddition2Name = name;
        this.healthyAddition2Price = price;
    }

    @Override
    public double totalPrice() {
        double totalPrice = super.totalPrice();

        if (this.healthyAddition1Name != null) {
            totalPrice += this.healthyAddition1Price;
            System.out.println("Added healthy " + this.healthyAddition1Name + " for an extra : " + this.healthyAddition1Price + "\n");
        }

        if (this.healthyAddition2Name != null) {
            totalPrice += this.healthyAddition2Price;
            System.out.println("Added healthy " + this.healthyAddition2Name + " for an extra : " + this.healthyAddition2Price + "\n");
        }

        return totalPrice;
    }
}
