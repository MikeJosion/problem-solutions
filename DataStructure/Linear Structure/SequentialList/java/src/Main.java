public class Main {
    public static void main(String[] args) {
        System.out.println("======== 1. 初始化测试 ========");
        SequentialList list = new SequentialList();
        list.printList(); // 应该是空的

        System.out.println("\n======== 2. 插入测试 ========");
        list.insertList(10, 0); // [10]
        list.insertList(20, 1); // [10, 20]
        list.insertList(30, 2); // [10, 20, 30]
        list.insertList(99, 0); // 插队 -> [99, 10, 20, 30]
        list.printList();

        System.out.println("\n======== 3. 扩容测试 (填满它!) ========");
        // 当前有4个，再插7个，总共11个，会超过容量10
        for (int i = 0; i < 7; i++) {
            list.insertList(i + 100, list.sizeList());
        }
        list.printList(); // 检查是否有数据丢失

        System.out.println("\n======== 4. 获取与查找测试 ========");
        int val = list.getList(2);
        System.out.println("下标 2 的值是: " + val); // 应该是 20

        int index = list.findList(30);
        System.out.println("数字 30 的下标是: " + index); // 应该是 3

        System.out.println("\n======== 5. 删除测试 ========");
        System.out.println("删除下标 0 (原来的99):");
        list.removeList(0);
        list.printList();

        System.out.println("删除无效下标 100:");
        list.removeList(100); // 应该报错

        System.out.println("\n======== 🎉 测试结束 ========");
    }
}