import java.io.BufferedInputStream;   
import java.util.LinkedList;   
import java.util.Scanner;   
  
/*  
 * To change this template, choose Tools | Templates  
 * and open the template in the editor.  
 */  
/**  
 * poj1915最初做这道题时，我是就c去做的，但到了具体编程时，我发现有些地方要用到  
 * 自定义类型的队列，自己去重写那些队列显行太麻烦了，本来C++就有现成的queue可以  
 * 用，但我没学过c++，所以就想到用java。代码也很快就写了出来，但提交时却说内存溢出  
 * 想了很久后，就大概猜到是什么原因，最初我是在得到size后就把整张棋盘都建了出来。  
 * 这样就产生了很多的对象，自然多了许多没有用的对象霸占了许多内存。之后我就改为  
 * 当需要时才去建棋格子的对象，果然少了很多内存。最后终于通过了。不过跟那些以前通过  
 * 的人相比，我占用的内存还是太多了。  
 * @author NC  
 */  
public class Main {   
  
    private static int[][] directions = new int[][]{   
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};   
  
    static void BreadthFirstSearch(int startX, int startY,   
            chessNode[][] chessPanel, int size) {   
        chessNode currentNode = null, nextNode = null;   
        LinkedList<chessNode> queue = new LinkedList();   
        currentNode = chessPanel[startY][startY] =   
                new chessNode(startX, startY, true, 0, false);   
        queue.addLast(currentNode);//初始棋格入队   
        while (!queue.isEmpty()) {   
            currentNode = queue.removeFirst();//出队   
            if (currentNode.isTarget()) {//如果走到了目的位置   
                break;   
            }   
            for (int i = 0; i < 8; i++) {   
                //遍历八个方向   
                int x = currentNode.getX() + directions[i][0];   
                int y = currentNode.getY() + directions[i][1];   
                int step = currentNode.getStep();   
                if (x >= 0 && x < size && y >= 0 && y < size) {   
                    //如果棋格没有越界，并且没有访问过   
                    if (chessPanel[x][y] == null) {   
                        chessPanel[x][y] = new chessNode(x, y, false, 0, false);   
                    }   
                    nextNode = chessPanel[x][y];   
                    if (!nextNode.isVisited()) {   
                        nextNode.setVisited(true);//标记访问过   
                        nextNode.setStep(step + 1);//记录步数   
                        queue.addLast(nextNode);//入队   
                    }   
                }   
            }   
        }   
    }   
  
    public static void main(String[] args) {   
        int n = 0;   
        int size = 0;   
        int startX = 0, startY = 0, endX = 0, endY = 0;   
        Scanner scanner = new Scanner(new BufferedInputStream(System.in));   
        n = scanner.nextInt();   
        for (int i = 0; i < n; i++) {   
            size = scanner.nextInt();//棋盘大小为size*size   
            startX = scanner.nextInt();//初始位置x坐标   
            startY = scanner.nextInt();//初始位置y坐标   
            endX = scanner.nextInt();//目的位置x坐标   
            endY = scanner.nextInt();//目的位置y坐标   
            chessNode[][] chessPanel = new chessNode[size][size];   
            //设置目的位置true   
            chessPanel[endX][endY] = new chessNode(endX, endY, false, 0, true);   
            //广度优先遍历   
            BreadthFirstSearch(startX, startY, chessPanel, size);   
            //输出最少步数   
            System.out.println(chessPanel[endX][endY].getStep());   
        }   
    }   
}   
  
class chessNode {   
  
    private int x;   
    private int y;   
    private boolean visited;//标记是否访问过   
    private int step;//记录从初始位置到当前棋格的最少步数   
  
    public int getX() {   
        return x;   
    }   
  
    public chessNode(int x, int y, boolean visited, int step, boolean target) {   
        this.x = x;   
        this.y = y;   
        this.visited = visited;   
        this.step = step;   
        this.target = target;   
    }   
  
    public void setX(int x) {   
        this.x = x;   
    }   
  
    public int getY() {   
        return y;   
    }   
  
    public void setY(int y) {   
        this.y = y;   
    }   
    private boolean target;   
  
    public boolean isVisited() {   
        return visited;   
    }   
  
    public void setVisited(boolean visited) {   
        this.visited = visited;   
    }   
  
    public int getStep() {   
        return step;   
    }   
  
    public void setStep(int step) {   
        this.step = step;   
    }   
  
    public boolean isTarget() {   
        return target;   
    }   
  
    public void setTarget(boolean target) {   
        this.target = target;   
    }   
}  
