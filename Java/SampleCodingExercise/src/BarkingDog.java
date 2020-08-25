public class BarkingDog {
    public static boolean shouldWakeUp(boolean barking, int hourOfDay) {
        return ((barking == true) && (((hourOfDay < 8) && (hourOfDay >= 0)) || ((hourOfDay <= 24) && (hourOfDay > 22))));
    }
}
