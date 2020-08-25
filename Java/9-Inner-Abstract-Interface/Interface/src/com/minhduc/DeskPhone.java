package com.minhduc;

public class DeskPhone implements ITelephone {
    private long number;
    private boolean isRinging;

    public DeskPhone(long number) {
        this.number = number;
    }

    @Override
    public void powerOn() {
        System.out.println("Phone " + number + " is ON");
    }

    @Override
    public void dial(long number) {
        System.out.println("Calling " + number);
    }

    @Override
    public void answer() {
        if (isRinging) {
            System.out.println("Answering...");
            isRinging = false;
        }
    }

    @Override
    public boolean callPhone(long number) {
        if (number == this.number) {
            System.out.println("Ring Ring");
            isRinging = true;
        } else {
            isRinging = false;
        }
        return isRinging;
    }

    @Override
    public boolean isRinging() {
        return isRinging;
    }
}
