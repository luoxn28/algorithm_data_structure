package dp;

/**
 * 动态规划 - 最长公共子序列
 * 最长公共子序列（Longest Common SubSequence,LongestCommonSubSequence），顾名思义，是指在所有的子序列中最长的那一个。
 * 注意，子序列可以不连续，比如cnblogs和belong，序列bo都是二者的子序列。
 *
 * @author xiangnan
 */
public class LongestCommonSubSequence {

    public static void main(String[] args) {
        System.out.println(new LongestCommonSubSequence().lcs("1A2C3D4B56".toCharArray(), "B1D23CA45B6A".toCharArray()));
    }

    private int lcs(char[] a, char[] b) {
        int al = a.length;
        int bl = b.length;

        int[][] array = new int[al+1][bl+1];
        for (int i = 1; i <= al; i++) {
            for (int j = 1; j <= bl; j++) {
                if (a[i-1] == b[j-1]) {
                    array[i][j] = array[i-1][j-1] + 1;
                } else {
                    array[i][j] = Math.max(array[i-1][j-1], Math.max(array[i][j-1], array[i-1][j]));
                }
            }
        }

        return array[al][bl];
    }

}
