package graph;

import java.util.ArrayList;
import java.util.List;

/**
 * 有向图
 */
public class Graph {

    // ---------------------------------- Instance Variable

    // 邻接表
    private List<List<Integer>> array;

    // ---------------------------------- Constructors

    public Graph() {
        this(8);
    }

    public Graph(int size) {
        if (size <= 0) {
            size = 8;
        }

        array = new ArrayList<>(size);
        for (int i = 0; i < size; i++) {
            array.add(new ArrayList<>());
        }
    }

    // ---------------------------------- Public Methods

    // 返回顶点个数
    public int getVertaxs() {
        return array.size();
    }

    // 往有向图中添加边(a, b)，方向 a -> b
    public void add(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return;
        }

        array.get(a).add(b);
    }

    // 从图中移除边(a, b)，方向 a -> b
    public void remove(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return;
        }

        array.get(a).remove(Integer.valueOf(b));
    }

    /**
     * 返回某个顶点关联的所有顶点
     *
     * 注意：返回的是邻接表的引用，进行通过该引用进行修改操作
     */
    public List<Integer> adj(int a) {
        if (a >= array.size()) {
            return new ArrayList<>();
        }

        return array.get(a);
    }

    // 有向图中是否包含边(a, b)，方向 a -> b
    public boolean contains(int a, int b) {
        if (a >= array.size() || b >= array.size()) {
            return false;
        }

        return array.get(a).contains(b);
    }

    @Override
    public String toString() {
        StringBuffer buffer = new StringBuffer();

        for (int i = 0; i  < array.size(); i++) {
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
