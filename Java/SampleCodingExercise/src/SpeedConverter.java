public class SpeedConverter {
    public static long toMilesPerHour(double kilometersPerHour) {
        // 1.609
        long result;
        if (kilometersPerHour < 0) {
            result = -1;
        } else {
            result = (long) (Math.round(kilometersPerHour / 1.609));
        }
        return result;
    }

    public static void printConversion(double kilometersPerHour) {
        int result = (int) (toMilesPerHour(kilometersPerHour));
        if (result == -1) {
            System.out.println("Invalid Value");
        } else {
            String msg;
            msg = kilometersPerHour + " km/h"
                    + " = "
                    + result + " mi/h";
            System.out.println(msg);
        }
    }
}
