package backtracking;

import javafx.util.Pair;

import java.util.LinkedList;

/**
 * N皇后问题
 */
public class NQueen {

    public static void main(String[] args) {
        // 8皇后问题，8皇后的解共有92个
        new NQueen().recall(0, 8, new LinkedList<>());
    }

    private int num = 0;

    /**
     * 回溯法求N皇后问题
     */
    private void recall(int i, int end, LinkedList<Pair<Integer /*x*/, Integer/*y*/>> list) {
        if (list.size() == end) {
            System.out.println(++num + " " + list);
            return;
        } else if (i >= end) {
            return;
        }

        for (int j = 0; j < end; j++) {
            if (!listIsValid(list, i, j)) {
                continue;
            }

            list.addLast(new Pair<>(i, j));
            recall(i + 1, end, list);
            list.removeLast();
        }
    }

    /**
     * 约束条件（皇后不能处于同一行、不能处于同一列、不能同一个斜线上）
     */
    private boolean listIsValid(LinkedList<Pair<Integer, Integer>> list, int x, int y) {
        boolean flag = true;

        for (Pair<Integer, Integer> pair : list) {
            if (pair.getKey() == x || pair.getValue() == y || Math.abs(x - pair.getKey()) == Math.abs(y - pair.getValue())) {
                flag = false;
                break;
            }
        }

        return flag;
    }

}
