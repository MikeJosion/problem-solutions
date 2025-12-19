public class LinkedList {
    //“存储（变量）” 和 “动作（函数）”
    private static class Node{
        //简单理解:java class = c struct + functions + security
        int data;
        Node next;
        public Node(int data){
            this.data = data;
            this.next = null;
        }
    }
    private Node head;//头指针
    private int size; //不是必需,但是可以带来性能的提升,和代码便利

    public boolean insertList(int value, int index){
        if(index < 0 || index > size){
            System.out.println("下标输入不合理");
            return false;
        }
        
    }
}
