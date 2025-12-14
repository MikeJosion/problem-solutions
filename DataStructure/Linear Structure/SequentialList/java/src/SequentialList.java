public class SequentialList {
    //C 语言（面向过程） 和 Java（面向对象） 最本质的区别。
    //简单来说：C 语言里，数据和操作是“分家”的；Java 里，数据和操作是“一家人”。
    //先将c里的结构体定义
    private int[] data;  //存放数据的数组
    private int size;  //当前的元素个数
    private int capacity; //数组的最大容量

    //初始化
    public SequentialList() {
        this.size = 0;
        this.capacity = 10;
        this.data = new int[capacity];
    }

    //插入
    public boolean insertList(int value, int index) {
        if (index < 0 || index > size) {
            System.out.println("下标的位置不合法");
            return false;
        }
        //扩容的逻辑:先找新房,搬家具,交钥匙
        if (size == capacity) {
            System.out.println("顺序表满了,需要扩容");
            //找新房
            int newCapacity = capacity * 2;
            int[] newData = new int[newCapacity];
            //搬家具
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            //交钥匙
            this.data = newData;
            this.capacity = newCapacity;
        }
        //腾出位置
        for (int i = size - 1; i >= index; i--) {
            data[i + 1] = data[i];
        }
        data[index] = value;
        size++;
        return true;
    }

    public boolean removeList(int index) {
        if (index < 0 || index >= size) {
            System.out.println("你输入的下标存在问题");
            return false;
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
        return true;
    }

    public int getList(int index) {
        if (index < 0 || index >= size) {
            System.out.println("你输入的下标存在问题");
            return -1;
        }
        return data[index];
    }

    public int findList(int value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    public void printList() {
        for (int i = 0; i < size; i++) {
            System.out.println(data[i] + " ");
        }
    }

    public int sizeList() {
        return size;
    }

    public int capacity() {
        return capacity;
    }
}

