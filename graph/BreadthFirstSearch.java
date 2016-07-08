package graph;


import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

public class BreadthFirstSearch {

    // ---------------------------------- Instance Variables

    // 无向图
    Digraph graph;

    // 广度优先搜索后的顶点顺序
    List<Integer> sorted = new ArrayList<Integer>();

    // ---------------------------------- Constructors

    public BreadthFirstSearch(Digraph graph, int node) {
        if (node >= graph.getVertaxs()) {
            return;
        }

        this.graph = graph;
        // boolean数组默认都置为false，所以不用专门初始化
        boolean []marked = new boolean[graph.getVertaxs()];
        bfs(node, marked);
    }

    // ---------------------------------- Public Methods

    public List<Integer> getSorted() {
        return new ArrayList<Integer>(sorted);
    }

    // ---------------------------------- Private Methods

    private void bfs(int node, boolean []marked) {
        Deque<Integer> deque = new ArrayDeque<Integer>();

        marked[node] = true;
        sorted.add(node);
        deque.addLast(node);
        while (deque.size() > 0) {
            int vertax = deque.pollFirst();
            List<Integer> list = this.graph.adj(vertax);
            for (Integer ele : list) {
                if (!marked[ele]) {
                    marked[ele] = true;
                    sorted.add(ele);
                    deque.addLast(ele);
                }
            }
        }
    }

}
