package com.minhduc;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Bank bank = new Bank("Gift and Lala 's Bank");

        bank.addBranch("Quy den");
        bank.addCustomertoBranch("Quy den", "Lala", 100);

        bank.addBranch("Saving for house");
        bank.addCustomertoBranch( "Saving for house", "Gift", 550.75);
        bank.addCustomertoBranch( "Saving for house", "Lala", 150);

        bank.addCustomerTransaction("Quy den", "Lala", 120);
        bank.addCustomerTransaction("Quy den", "Lala", 150);

        bank.addCustomerTransaction("Saving for house", "Gift", 1020);
        bank.addCustomerTransaction("Saving for house", "Lala", 50);

        bank.showCustomerofBranch("Saving for house", true);
        System.out.println("--------------");
        bank.showCustomerofBranch("Quy den", true);
    }
}
