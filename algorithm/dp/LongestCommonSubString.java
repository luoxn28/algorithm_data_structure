package dp;

/**
 * 动态规划 - 最长公共子串
 * 两个字符串，求出它们之间最长的相同子字符串的长度。
 *
 * @author xiangnan
 */
public class LongestCommonSubString {

    public static void main(String[] args) {
        System.out.println(new LongestCommonSubString().lcs("1AB2345CD".toCharArray(), "12345EF".toCharArray()));
    }

    private int lcs(char[] a, char[] b) {
        int al = a.length;
        int bl = b.length;

        int max = 0;
        int[][] array = new int[al+1][bl+1];
        for (int i = 1; i <= al; i++) {
            for (int j = 1; j <= bl; j++) {
                if (a[i-1] == b[j-1]) {
                    array[i][j] = array[i-1][j-1] + 1;
                } else {
                    array[i][j] = 0;
                }

                max = Math.max(max, array[i][j]);
            }
        }

        return max;
    }
}
