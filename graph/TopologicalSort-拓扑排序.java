package graph;

import java.util.ArrayList;
import java.util.List;

/**
 * 有向图的拓扑排序
 */
public class TopologicalSort {

    // ---------------------------------- Instance Variable

    // 顶点的拓扑排序
    List<Integer> order = new ArrayList<>();

    // ---------------------------------- Constructors

    public TopologicalSort(Graph graph) {

        DepthFirstSearch depthFirstSearch = new DepthFirstSearch(graph);
        List<Integer> dfsNodes = depthFirstSearch.getSorted();
        System.out.println(dfsNodes);
        for (int i = dfsNodes.size() - 1; i >= 0; i--) {
            order.add(dfsNodes.get(i));
        }
    }

    // ---------------------------------- Public Methods

    public List<Integer> getOrder() {
        return order;
    }

}

/**
 * 深度优先搜索
 */
class DepthFirstSearch {

    // ---------------------------------- Instance Variables

    // 有向图
    Graph graph;

    // 深度优先搜索后的顶点顺序
    List<Integer> sorted = new ArrayList<Integer>();

    // ---------------------------------- Constructors

    public DepthFirstSearch(Graph graph) {
        this.graph = graph;
        // boolean数组默认都置为false，所以不用专门初始化
        boolean []marked = new boolean[graph.getVertaxs()];

        for (int i = 0; i < marked.length; i++) {
            if (!marked[i]) {
                dfs(i, marked);
            }
        }
    }

    // ---------------------------------- Public Methods

    public List<Integer> getSorted() {
        return new ArrayList<Integer> (sorted);
    }

    // ---------------------------------- Private Methods

    private void dfs(int node, boolean []marked) {
        if (marked[node]) {
            return;
        }

        marked[node] = true;
        List<Integer> nodes = this.graph.adj(node);
        for (int i = 0; i < nodes.size(); i++) {
            if (!marked[nodes.get(i)]) {
                dfs(nodes.get(i), marked);
            }
        }
        sorted.add(node);
    }

}
