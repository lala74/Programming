package com.minhduc;

import java.util.ArrayList;

public class Bank {
    private String name;
    private ArrayList<Branch> branches;

    public Bank(String name) {
        this.name = name;
        this.branches = new ArrayList<Branch>();
    }

    public boolean addBranch(String branchName) {
        Branch existBranch = findBranch(branchName);
        if (existBranch == null) {
            return branches.add(new Branch(branchName));
        }
        return false;
    }

    public Branch findBranch(String branchName) {
        for (int i=0; i<this.branches.size(); i++) {
            if (this.branches.get(i).getName().equals(branchName)) {
                return this.branches.get(i);
            }
        }
        return null;
    }

    public boolean addCustomertoBranch(String branchName, String customerName, double initTransaction) {
        Branch existBranch = findBranch(branchName);
        if (existBranch != null) {
            existBranch.addCustomer(customerName, initTransaction);
            return true;
        }
        return false;
    }

    public boolean addCustomerTransaction(String branchName, String customerName, double amount) {
        Branch existBranch = findBranch(branchName);
        if (existBranch != null) {
            return existBranch.addCustomerTransaction(customerName, amount);
        }
        return false;
    }

    public boolean showCustomerofBranch(String branchName, boolean showTransaction) {
        Branch existBranch = findBranch(branchName);
        if (existBranch != null) {
            System.out.println("Branch " + branchName);
            for (int i=0; i<existBranch.getCustomers().size(); i++) {
                System.out.println("Customer " + (i+1) + ": " + existBranch.getCustomers().get(i).getName());
                if (showTransaction == true) {
                    existBranch.showTransaction(existBranch.getCustomers().get(i).getName());
                }
            }
            return true;
        }
        return false;
    }
}
