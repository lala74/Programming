package com.minhduc;

public class Hamburger {
    private String name;
    private String meat;
    private String breadRollType;
    private double price;

    private String addition1Name;
    private double addition1Price;

    private String addition2Name;
    private double addition2Price;

    private String addition3Name;
    private double addition3Price;

    private String addition4Name;
    private double addition4Price;

    public Hamburger() {
        this("none", "none", "none", 0);
    }

    public Hamburger(String name, String meat, String breadRollType, double price) {
        this.name = name;
        this.meat = meat;
        this.breadRollType = breadRollType;
        this.price = price;
    }

    public void addAddition1(String name, double price) {
        this.addition1Name = name;
        this.addition1Price = price;
    }

    public void addAddition2(String name, double price) {
        this.addition2Name = name;
        this.addition2Price = price;
    }

    public void addAddition3(String name, double price) {
        this.addition3Name = name;
        this.addition3Price = price;
    }

    public void addAddition4(String name, double price) {
        this.addition4Name = name;
        this.addition4Price = price;
    }

    public double totalPrice() {
        double totalPrice = this.price;
        System.out.println("Hamburger name : " + this.name + "\n"
                            + "Meat : " + this.meat + "\n"
                            + "Bread Roll Type : " + this.breadRollType + "\n"
                            + "Base price : " + this.price + "\n");
        if (this.addition1Name != null) {
            totalPrice += this.addition1Price;
            System.out.println("Added " + this.addition1Name + " for an extra : " + this.addition1Price + "\n");
        }

        if (this.addition2Name != null) {
            totalPrice += this.addition2Price;
            System.out.println("Added " + this.addition2Name + " for an extra : " + this.addition2Price + "\n");
        }

        if (this.addition3Name != null) {
            totalPrice += this.addition3Price;
            System.out.println("Added " + this.addition3Name + " for an extra : " + this.addition3Price + "\n");
        }

        if (this.addition4Name != null) {
            totalPrice += this.addition4Price;
            System.out.println("Added " + this.addition4Name + " for an extra : " + this.addition4Price + "\n");
        }

        return totalPrice;
    }
}
