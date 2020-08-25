package com.minhduc;

import java.util.ArrayList;

public class Branch {
    private String name;
    private ArrayList<Customer> customers;

    public Branch(String name) {
        this.name = name;
        this.customers = new ArrayList<Customer>();
    }

    public String getName() {
        return name;
    }

    public ArrayList<Customer> getCustomers() {
        return customers;
    }

    public boolean addCustomer(String customerName, double initAmout) {
        Customer existCustomer = findCustomer(customerName);
        if (existCustomer == null) {
            this.customers.add(new Customer(customerName, initAmout));
            return true;
        }
        return false;

    }

    public boolean addCustomerTransaction(String customerName, double transaction) {
        Customer existCustomer = findCustomer(customerName);
        if (existCustomer != null) {
            existCustomer.addTransaction(transaction);
            return true;
        }
        return false;
    }

    private Customer findCustomer(String customerName) {
        for (int i=0; i<customers.size(); i++) {
            if (this.customers.get(i).getName().equals(customerName)) {
                return customers.get(i);
            }
        }
        return null;
    }

    public boolean showTransaction(String stringName) {
        Customer existCustomer = findCustomer(stringName);
        if (existCustomer != null) {
            for (int i=0; i<existCustomer.getTransactions().size(); i++) {
                System.out.println("Transaction " + (i+1) + ": " + existCustomer.getTransactions().get(i));
            }
            return true;
        }
        return false;
    }
}
