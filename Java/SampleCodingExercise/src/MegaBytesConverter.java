public class MegaBytesConverter {
    public static void printMegaBytesAndKiloBytes(int kiloBytes) {
        String msg;

        if (kiloBytes < 0) {
            msg = "Invalid Value";
        } else {
            msg = kiloBytes + " KB"
                    + " = "
                    + kiloBytes / 1024 + " MB"
                    + " and "
                    + kiloBytes % 1024 + " KB";
        }
        System.out.println(msg);
    }
}
