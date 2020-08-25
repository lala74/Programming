package com.minhduc;

import java.util.Iterator;

public class Main {

    public static void main(String[] args) {
	// write your code here
        ITelephone DucPhone;
        DucPhone = new DeskPhone(767447415);
        DucPhone.powerOn();
        DucPhone.callPhone(767447415);
        DucPhone.answer();

        ITelephone GiftPhone;
        GiftPhone = new MobilePhone(796760237);
        GiftPhone.powerOn();
        GiftPhone.callPhone(796760237);
        GiftPhone.answer();
    }
}
