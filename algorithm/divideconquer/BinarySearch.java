package divideconquer;

import java.util.Arrays;
import java.util.List;

/**
 * 二分查找
 *
 * @author xiangnan
 */
public class BinarySearch {

    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        System.out.println(new BinarySearch().search(list, 6));
    }

    /**
     * while (low <= high)不能改为<，否则的话条件判断不完整，比如：
     *		a[3] = {1, 3, 5};待查找的键为5，此时在(low < high)条件下就会找不到
     *		因为low和high相等时，指向元素5，但是此时条件不成立，没有进入while()中
     *
     * @param list 数组
     * @param num 待查找的值
     * @return 找到为该键在数组中的下标，否则为-1
     */
    private int search(List<Integer> list, int num) {
        int left = 0;
        int right = list.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (num == list.get(mid)) {
                return mid;
            } else if (num < list.get(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return -1;
    }

}
