package graph;


import java.util.ArrayList;
import java.util.List;

/**
 * 深度优先搜索
 */
public class DepthFirstSearch {

    // ---------------------------------- Instance Variables

    // 无向图
    Digraph graph;

    // 深度优先搜索后的顶点顺序
    List<Integer> sorted = new ArrayList<Integer>();

    // ---------------------------------- Constructors

    DepthFirstSearch(Digraph graph, int node) {
        if (node >= graph.getVertaxs()) {
            return;
        }

        this.graph = graph;
        // boolean数组默认都置为false，所以不用专门初始化
        boolean []marked = new boolean[graph.getVertaxs()];
        dfs(node, marked);
    }

    // ---------------------------------- Public Methods

    public List<Integer> getSorted() {
        return new ArrayList<Integer>(sorted);
    }

    // ---------------------------------- Private Methods

    private void dfs(int node, boolean []marked) {
        if (marked[node]) {
            return;
        }

        marked[node] = true;
        sorted.add(node);
        List<Integer> nodes = this.graph.adj(node);
        for (int i = 0; i < nodes.size(); i++) {
            dfs(nodes.get(i), marked);
        }
    }

}
