package backtracking;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * 矩阵中寻找某条路径
 *   比如矩阵：[a b t g
 *             c f c s
 *             j d e h]
 *   路径：b f c e
 */
public class MatrixPath {

    public static void main(String[] args) {
        List<List<String>> matrix = new ArrayList<>();
        matrix.add(new ArrayList<>(Arrays.asList("a b t g".split(" "))));
        matrix.add(new ArrayList<>(Arrays.asList("c f c s".split(" "))));
        matrix.add(new ArrayList<>(Arrays.asList("j d e h".split(" "))));

        boolean hasPath = new MatrixPath().hasPath(matrix, "bfce");
        System.out.println(hasPath);
    }

    /**
     * 回溯法：首先任意一个点都有可能成为起点，所以要获得任意一点的坐标(位于第几行，第几列)
     *   其次要有一个数组记录这个点是否被访问过，同时要有一个指针来记录字符串中字符的位置。
     *   当某个点成为合法的起点时，即这个点与字符串中第一个字符相等，则可以继续朝上下左右搜索下一个点；
     *   如果这个点不能成为合法的起点，则恢复现场(这个点没有被访问过且字符串指针后退)
     */
    private boolean hasPath(List<List<String>> matrix, String str) {
        boolean[][] visited = new boolean[matrix.size()][matrix.get(0).size()];

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.get(i).size(); j++) {
                if (isPath(matrix, i, j, visited, str)) {
                    return true;
                }
            }
        }

        return false;
    }

    private int index = 0;
    private boolean isPath(List<List<String>> matrix, int i, int j, boolean[][] visited, String str) {
        if (index == str.length()) {
            return true;
        }

        boolean flag = false;
        if (i >= 0 && j >= 0 && i < matrix.size() && j < matrix.get(i).size() &&
                !visited[i][j] && matrix.get(i).get(j).equals(String.valueOf(str.charAt(index)))) {
            index++;
            visited[i][j] = true;

            flag = isPath(matrix, i + 1, j, visited, str) ||
                    isPath(matrix, i - 1, j, visited, str) ||
                    isPath(matrix, i, j + 1, visited, str) ||
                    isPath(matrix, i, j - 1, visited, str);
            if (!flag) {
                index--;
                visited[i][j] = false;
            }
        }

        return flag;
    }

}
