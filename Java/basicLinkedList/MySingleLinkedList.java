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
  
  // 제거하는 노드의 데이터 반환
  public T removeFirst(){
    if(head==null)
      return null;
    T temp = head.data;
    head = head.next;
    size--;
    return temp;
  }
  public T removeAfter(Node<T> before){
    if(before.next==null)
      return null;
    T temp = before.next.data;
    before.next = before.next.next;
    return temp;
  }
  
  // index번째 노드의 주소 반환
  public Node<T> getNode(int index){
    if(index<0 || index>=size)
      return null;
    Node<T> p = head; // p가 첫번째 노드를 가리킴.
    for(int i=0;i<index;i++)
      p = p.next; 
    return p;
  }
  
  // index번째 노드의 값 반환
  public T get(int index){
    if(index < 0 || index >= size) return null;
    return getNode(index).data;
  }
  
  // search
  public int indexOf(T item){
    // head를 마음대로 바꾸면 안되니까 복사해서 사용함.
    Node<T> p = head;
    while(p!=null){
      if(p.data.equals(item))
        return index;
      p = p.next;
      index++;
    }
    return -1;
  }
  
  public void add(int index,T item){
    if(index<0 || index>size)
      return;
    if(index==0)
      addFirst(item);
    else{
      Node<T> q = getNode(index-1);
      addAfter(q,item);
    }
  }
  
  // index번째 노드 삭제하고 그 안의 데이터 반환
  public T remove(int index){
    if(index<0 || index >= size)
			return null;
		if(index==0)
			return removeFirst();
    Node<T> q = getNode(index-1);
    return removeAfter(q);
  }
  // 해당 데이터를 받아서 그 노드를 삭제
  // p 바로 뒤를 q가 쫓아감
  public T remove(T item){
    Node<T> p = head;
    Node<T> q = null;
    while(p!=null && !p.data.equals(item)){
      q=p;
      p=p.next;
    }
    if(p==null)
      return null;
    if(q==null)
      return removeFirst();
    else
      return removeAfter(q);
    
  }
}
