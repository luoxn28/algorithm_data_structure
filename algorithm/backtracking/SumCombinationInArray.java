package backtracking;

import java.util.Arrays;
import java.util.LinkedList;

/**
 * 求数组中和为固定值的所有组合
 */
public class SumCombinationInArray {

    public static void main(String[] args) {
        LinkedList<Integer> list = new LinkedList<>(Arrays.asList(1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7));

        /*
         * 1. 数组为从小到大排序
         * 2. 求list中和为10的所有组合
         */
        new SumCombinationInArray().recall(list, 0, 0, 10, new LinkedList<>());
    }

    /**
     * 回溯法 求数组中和为固定值的组合
     */
    private void recall(LinkedList<Integer> list, int start, int current, int target, LinkedList<Integer> tmpList) {
        if (start >= list.size()) {
            return;
        }
        if (current + list.get(start) > target) {
            return;
        }

        current += list.get(start);
        tmpList.addLast(list.get(start));
        if (current == target) {
            System.out.println(tmpList);
        }

        recall(list, start + 1, current, target, tmpList);

        tmpList.removeLast();
        current -= list.get(start);

        int i = start + 1;
        while (i < list.size() && (int)list.get(i) == list.get(start)) {
            i++;
        }

        recall(list, i, current, target, tmpList);
    }

}
