package com.minhduc;

public interface ITelephone {
    void powerOn();
    void dial(long number);
    void answer();
    boolean callPhone(long number);
    boolean isRinging();
}
