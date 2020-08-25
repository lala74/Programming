package com.minhduc;

import java.util.ArrayList;

public class Customer {
    private String name;
    private ArrayList<Double> transactions;

    public Customer(String name, double amount) {
        this.name = name;
        this.transactions = new ArrayList<Double>();
        addTransaction(amount);
    }

    public void addTransaction(Double transaction) {
        this.transactions.add(transaction);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<Double> getTransactions() {
        return transactions;
    }
}
