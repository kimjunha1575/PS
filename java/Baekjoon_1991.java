import java.io.*;

// https://www.acmicpc.net/problem/1991

public class Baekjoon_1991 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        // 총 노드 수
        int tree_size = Integer.parseInt(br.readLine());
        
        // DAT 방식으로 접근하기 위해 노드 수와 상관없이 총 알파벳 수인 26개로 배열 초기화
        Vertex[] tree = new Vertex[26];

        // 트리 정보 저장
        for (int i = 0; i < tree_size; i++) {
            String[] input = br.readLine().split(" ");
            char data = input[0].charAt(0);
            char left = input[1].charAt(0);
            char right = input[2].charAt(0);
            tree[data - 'A'] = new Vertex(data - 'A', left == '.' ? -1 : left - 'A', right == '.' ? -1 : right - 'A');
        }

        // 조건에 맞춰 순회, 출력
        preorder(tree, tree[0].data);
        System.out.println();
        inorder(tree, tree[0]);
        System.out.println();
        postorder(tree, tree[0]);
        br.close();
    }

    // Preorder traversal
    public static void preorder(Vertex[] tree, int root) {
        if (root == -1) {
            return;
        }
        System.out.printf("%c", tree[root].data + 'A');
        if (tree[root].left != -1) {
            preorder(tree, tree[root].left);
        }
        if (tree[root].right != -1) {
            preorder(tree, tree[root].right);
        }
    }

    // Inorder traversal
    public static void inorder(Vertex[] tree, Vertex root) {
        if (root.left != -1) {
            inorder(tree, tree[root.left]);
        }
        System.out.printf("%c", root.data + 'A');
        if (root.right != -1) {
            inorder(tree, tree[root.right]);
        }
    }

    // Postorder traversal
    public static void postorder(Vertex[] tree, Vertex root) {
        if (root.left != -1) {
            postorder(tree, tree[root.left]);
        }
        if (root.right != -1) {
            postorder(tree, tree[root.right]);
        }
        System.out.printf("%c", root.data + 'A');
    }

    // Vertex class (Node)
    static class Vertex {
        public int data;
        public int left;
        public int right;

        public Vertex(int data, int left, int right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
    }
}
