package graph;

import java.util.ArrayList;
import java.util.List;

public class Digraph {

    // ---------------------------------- Instance Variables

    // 邻接表List
    private List<List<Integer>> array;

    // ---------------------------------- Constructors

    public Digraph() {
        this(8);
    }

    public Digraph(int nodes) {
        if (nodes < 8) {
            nodes = 8;
        }
        array = new ArrayList<List<Integer>>(8);
        System.out.println();
        for (int i = 0; i < nodes; i++) {
            array.add(new ArrayList<Integer>());
        }
    }

    // ---------------------------------- Public Methods

    /**
     * 往Digraph中添加一条边
     * @param a 节点a
     * @param b 节点b
     */
    public void add(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return;
        }

        array.get(a).add(b);
        array.get(b).add(a);
    }

    /**
     * 从Digraph中移除一条边
     * @param a
     * @param b
     */
    public void remove(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return;
        }

        array.get(a).remove(Integer.valueOf(b));
        array.get(b).remove(Integer.valueOf(a));
    }

    /**
     * Digraph中是否包含边(a, b)
     * @param a
     * @param b
     */
    public boolean contains(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return false;
        }

        return array.get(a).contains(b);
    }

    /**
     * 返回Digraph中顶点个数
     */
    public int getVertaxs() {
        return array.size();
    }

    /**
     * 返回Digraph中边的个数
     */
    public int getEdges() {
        int edges = 0;

        for (List<Integer> ele : array) {
            edges += ele.size();
        }
        return edges >> 1;
    }

    @Override
    public String toString() {
        StringBuffer buffer = new StringBuffer();
        for (int i = 0; i < array.size(); i++) {
            List<Integer> ele = array.get(i);
            buffer.append(i + ": ");
            for (Integer node : ele) {
                buffer.append(node + " ");
            }
            buffer.append("\n");
        }

        return buffer.toString();
    }

}
