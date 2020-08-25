package com.company;

public class Main {

    public static void main(String[] args) {
	// write your code here
        byte myByteNum = 25;

        short myShortNum = 900;

        int myIntNum = 213564;

        long myLongNum = (50000L + 10L
                *(myByteNum + myIntNum + myShortNum));

        System.out.println("myLongNum = " + myLongNum);

        char myChar = '\u01C4';

        System.out.println("myChar = " + myChar);

    }
}
