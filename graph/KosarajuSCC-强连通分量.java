package graph;

import java.util.ArrayList;
import java.util.List;

/**
 * KosarajuSCC - 有向图强连通分量算法
 */
public class KosarajuSCC {

    // ---------------------------------- Instance Variables

    // 强连通分量个数
    private int strongConnection;

    // ---------------------------------- Construction

    public KosarajuSCC(Graph graph) {
        DepthFirstSearch depthFirstSearch = new DepthFirstSearch(graph);
        List<Integer> list = depthFirstSearch.getSorted();
        List<Integer> sorted = new ArrayList<>();
        for (int i = list.size() - 1; i >= 0; i--) {
            sorted.add(list.get(i));
        }

        // 得到新的转置图graph2
        int nodes = graph.getVertaxs();
        Graph graph2 = new Graph(nodes);
        for (int i = 0; i < nodes; i++) {
            List<Integer> list2 = graph.adj(i);
            for (Integer ele : list2) {
                graph2.add(ele, i);
            }
        }

        System.out.println(list);
        System.out.println(sorted);
        boolean []marked = new boolean[graph2.getVertaxs()];
        for (int i = 0; i < sorted.size(); i++) {
            int node = sorted.get(i);
            if (!marked[node]) {
                dfs(graph2, node, marked);
                strongConnection++;
            }
        }
    }

    // ---------------------------------- Public Methods

    public int getStrongConnection() {
        return strongConnection;
    }

    // ---------------------------------- Private Methods

    private void dfs(Graph graph, int node, boolean []marked) {
        marked[node] = true;
        List<Integer> nodes = graph.adj(node);
        for (int i = 0; i < nodes.size(); i++) {
            if (!marked[nodes.get(i)]) {
                dfs(graph, nodes.get(i), marked);
            }
        }
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
