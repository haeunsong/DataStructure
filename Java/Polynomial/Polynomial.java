import MySingleLinkedList;
import Node; 

public class Polynomial {
	
	public char name;
	public MySingleLinkedList<Term> terms;
	
	public Polynomial(char name) {
		this.name = name;
		terms = new MySingleLinkedList<Term>();
	}
	
	// addTerm 중요!!!
	// 기존의 다항식에 새로운 항을 추가하는 메서드
	// coef * x ^ expo
	// i) 추가하려는 항과 동일 차수의 항이 이미 있는 경우 -> 기존 항의 계수만 변경
	// (계수가 0이 되는 경우 항 삭제)
	// ii) 그렇지 않은 경우 -> 새로운 항을 삽입(항들은 차수의 내림차순으로 항상 정렬됨)
	public void addTerm(int coef,int expo) {
		if(coef==0)
			return;
		Node<Term> p = terms.head,q=null;
		while(p!=null && p.data.expo>expo) {
			q=p;
			p = p.next;
		}
		if(p!=null && p.data.expo == expo) {
			p.data.coef += coef; // 계수 더해주기
			if(p.data.coef==0) {
				// 항 삭제(노드 삭제)
				if(q==null)
					terms.removeFirst();
				else
					terms.removeAfter(q);
			}
		}else { // add after q
			Term t = new Term(coef,expo);
			if(q==null)
				terms.addFirst(t);
			else
				terms.addAfter(q,t);
		}
	}
	
	public int calc(int x) {
		int result = 0;
		
		Node<Term> p = terms.head;
		while(p!=null) {
			result += p.data.calc(x);
			p = p.next;
		}
		return result;
	}
	
	public String toString() {
		// 다른 방법: StringBuilder 사용
		String result = "";
		Node<Term> p = terms.head;
		while(p!=null) {
			result += (p.data.toString());
			p = p.next;
		}
			return result;
	}
	
}
