package com.minhduc;

public class MobilePhone implements ITelephone {
    private long number;
    private boolean isRinging;
    private boolean isOn = false;

    public MobilePhone(long number) {
        this.number = number;
    }

    @Override
    public void powerOn() {
        isOn = true;
        System.out.println("Mobile phone number " + number + " is powered up");
    }

    @Override
    public void dial(long number) {
        if (isOn) {
            System.out.println("Calling mobile phone number " + number);
        } else {
            System.out.println("Mobile phone is switched OFF");
        }
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
        if (number == this.number && isOn) {
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
