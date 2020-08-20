public class MySingleLinkedList<T>{
  
  public node<T> head; // 첫번째 노드 주소
  public int size; // 현재 노드의 갯수
  
  public MySingleLinkedList(){
    head = null;
    size = 0;
  }
  
  public void addFirst(T item){
  // newNode에는 새로운 노드의 주소가 들어있음.
  // newNode는 새로운 노드를 가리키는 참조변수라는 것 잊지말기!!
    Node<T> newNode = new Node<T>(item);
    newNode.next = head;
    head = newNode;
    size++;
  }
  public void addAfter(Node<T> before,T item){
    Node<T> newNode = new Node<T>(item);
    newNode.next = before.next;
    before.next = newNode;
    size++;
  }
  
  public T removeFirst(){
    if(head==null)
      return null;
    T temp = head.data;
    head = head.next;
    size--;
    return temp;
  }
}
