package divideconquer;

import java.util.Random;

/**
 * 分治法 - 大数相乘
 *
 * @author xiangnan
 */
public class BigNumMultiply {

    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            int x = new Random().nextInt(9000) + 1000;
            int y = new Random().nextInt(9000) + 1000;

            assert x * y == new BigNumMultiply().multiply(x, y);
        }
    }

    private long multiply(long x, long y) {
        int n = Math.min(String.valueOf(x).length(), String.valueOf(y).length());

        if (x == 0 || y == 0 || n == 0) {
            return 0;
        } else if (n == 1) {
            return x * y;
        } else {
            int power = n / 2;
            long a = x / (long) Math.pow(10, power);
            long b = x - a * (long) Math.pow(10, power);
            long c = y / (long) Math.pow(10, power);
            long d = y - c * (long) Math.pow(10, power);

            long ac = multiply(a, c);
            long bd = multiply(b, d);
            long abcd = multiply(b, c) + multiply(a, d);
            return ac * (long) Math.pow(10, n) + abcd * (long) Math.pow(10, power) + bd;
        }
    }
}
